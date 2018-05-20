/*
The MIT License (MIT)

Copyright (c) 2018 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <sqstring.h>
#include <sqstdlib.h>
#include <sqstdio.h>

#include <results.h>
#include <cmdline.h>
#include <parse_ansi.h>

#define	ASCII_BS    (8)     // backspace
#define ASCII_SPACE (32)    // space
#define	ASCII_CR    (13)    // Carriage Return
#define ASCII_ESC   (27)    // escape

#define INC_WRAP(value, mask) (((value) + 1) & ((mask) - 1))
#define DEC_WRAP(value, mask) (((value) - 1) & ((mask) - 1))

typedef enum
{
    promptNormal,
    promptEscape,
} promptState_t;

static char historyBuffer[CMDLINE_BUFSIZE];
static int historyIndexEnd;
static int historyIndexBegin;
// where are we pointing when going through history
static int historyIndexIndex;


// how many characters are there on the prompt?
static uint16_t promptFill = 0;



result cmdlineParse(const cmdLineEntry * cmdLineEntries, char * line);

void cmdlineInit()
{
    historyIndexBegin = historyIndexEnd = 0;
    sqmemset(historyBuffer, 0, sizeof(historyBuffer));
}

void cmdlineBufferAdd(char c)
{
    historyBuffer[historyIndexEnd] = c;
    historyIndexEnd = INC_WRAP(historyIndexEnd, CMDLINE_BUFSIZE);
}

void cmdlineBufferRemove()
{
    // zero out the character
    historyBuffer[historyIndexEnd] = 0;
    historyIndexEnd = DEC_WRAP(historyIndexEnd, CMDLINE_BUFSIZE);
}

void promptEraseCharacters(uint16_t count)
{
    for(uint16_t i = 0; i < count; i++)
    {
        sqputchar(ASCII_BS);
        sqputchar(ASCII_SPACE);
        sqputchar(ASCII_BS);        
        promptFill--;
    }
}

void promptAddCharacter(char c)
{
    sqputchar(c);
    promptFill++;
}

result cmdlineParse(const cmdLineEntry * cmdLineEntries, char * line)
{
    char *strtok_state;
    char commandline[CMDLINE_MAX_LENGTH];
    sqstrncpy(commandline, line, sizeof(commandline));
    char *trigger = sqstrtok_r(commandline,STRTOK_DELIM, &strtok_state);
    // trigger can be NULL when you just push enter
    if(trigger != NULL)
    {
        // match to the command table
        while(cmdLineEntries->argHandler != NULL)
        {
            if(sqstrcmp(trigger, cmdLineEntries->strTrigger) == 0)
            {
                int arguments[CMDLINE_MAX_ARGS];
                // matched, parse arguments of commandline
                for(int j = 0; j < cmdLineEntries->argCnt; j++)
                {
                    char *arg = sqstrtok_r(NULL,STRTOK_DELIM, &strtok_state);
                    if(arg == NULL)
                        return cmdlineInvalidArg;
                    arguments[j] = sqstrstol(arg);
                }
                // call the matched command with the argument count
                cmdLineEntries->argHandler(arguments);
                return noError;
            }
            cmdLineEntries++;
        }   
    }
    return cmdlineNotFound;
}

// call periodically to fetch received characters
void cmdlineProcess(const cmdLineEntry * cmdLineEntries)
{
    char newcommand[CMDLINE_MAX_LENGTH];
    static promptState_t promptState = promptNormal;
    
    int c = sqgetchar();
    
    // handling functions for escape sequences
    switch(promptState)
    {
        case promptNormal:
            switch(c)
            {
                case ASCII_BS:
                    if(historyBuffer[DEC_WRAP(historyIndexEnd, CMDLINE_BUFSIZE)] != 0)
                    {
                        cmdlineBufferRemove();
                        promptEraseCharacters(1);
                    }
                    break;
                case ASCII_CR:
                    sqputchar(ASCII_CR);
                    promptFill = 0;
                    // note, we are filling the buffer end to start,
                    char * p = &newcommand[CMDLINE_MAX_LENGTH-1];
                    // terminate string
                    *p = 0;
                    // scan backward through history and copy backwards to the buffer
                    int i = DEC_WRAP(historyIndexEnd, CMDLINE_BUFSIZE);
                    while ((historyBuffer[i] != 0) && (p >= newcommand))
                    {
                        p--;
                        *p = historyBuffer[i];
                        i = DEC_WRAP(i, CMDLINE_BUFSIZE);
                    }
                    // call handler
                    cmdlineParse(cmdLineEntries, p);
                    // terminate the history buffer
                    cmdlineBufferAdd(0);
                    break;
                case ASCII_ESC:
                    ansiParse(c);
                    promptState = promptEscape;
                    break;
                case EOF:
                    break;
                default:
                    cmdlineBufferAdd(c);
                    promptAddCharacter(c);
                    break;
            }
        break;
        case promptEscape:
            {
                ansiSequence ansiState = ansiParse(c);
                // we have successfully parsed the sequence
                if(ansiState > ansiKnown)
                {
                    switch(ansiState)
                    {
                        case ansiError:
                            // unknown ansi escape, return to normal operation
                            promptState = promptNormal;
                        break;
                        case ansiCursorUp:
                            // clear out current commandline
                            promptEraseCharacters(promptFill);
                            promptFill = 0;
                            int indexClearHist = DEC_WRAP(historyIndexEnd, CMDLINE_BUFSIZE);
                            while(historyBuffer[indexClearHist] != 0)
                            {
                                historyBuffer[indexClearHist] = 0;
                                indexClearHist = DEC_WRAP(indexClearHist, CMDLINE_BUFSIZE);
                            }
                            historyIndexEnd = INC_WRAP(indexClearHist, CMDLINE_BUFSIZE);
                            // cleared buffer, lets continue from here
                            int indexSearchPrev = DEC_WRAP(indexClearHist, CMDLINE_BUFSIZE);
                            if(indexSearchPrev != historyIndexBegin)
                            {
                                while((historyBuffer[indexSearchPrev] != 0))
                                {
                                    // find previous in history
                                    indexSearchPrev = DEC_WRAP(indexSearchPrev, CMDLINE_BUFSIZE);
                                }
                                // end found, put on prompt and history
                                indexSearchPrev = INC_WRAP(indexSearchPrev, CMDLINE_BUFSIZE);
                                while(historyBuffer[indexSearchPrev] != 0)
                                {
                                    cmdlineBufferAdd(historyBuffer[indexSearchPrev]);
                                    promptAddCharacter(historyBuffer[indexSearchPrev]);
                                    indexSearchPrev = INC_WRAP(indexSearchPrev, CMDLINE_BUFSIZE);
                                }
                            }
                            else
                            {
                                // we are at the end of history, do nothing
                            }
                            // put in newcommand and on the prompt
                            promptState = promptNormal;
                        break;
                        case ansiCursorDown:
                            // TODO go to next command if available
                            promptState = promptNormal;
                        break;
                        default:
                        break;
                    }
                }
            }
        break;
        default:
            // TODO assert
        break;
    }
}

