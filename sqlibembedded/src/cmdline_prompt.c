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
#include <cmdline_cmd.h>
#include <parse_ansi.h>
#include <queue_string.h>

#define ASCII_NUL   (0)
#define	ASCII_BS    (8)     // backspace
#define ASCII_SPACE (32)    // space
#define	ASCII_CR    (13)    // Carriage Return
#define ASCII_ESC   (27)    // escape

typedef enum
{
    promptNormal,
    promptEscape,
} promptState_t;

// how many characters printed on the console prompt?
static uint16_t promptConsoleFill = 0;
// command history
t_queueString * commandHistory;

void promptInit(t_queueString * q)
{
    commandHistory = q;
}

/*
 * Delete characters prompt and history
 */
static void promptDel(uint16_t count)
{
    for(uint16_t i = 0; i < count; i++)
    {
        sqputchar(ASCII_BS);
        sqputchar(ASCII_SPACE);
        sqputchar(ASCII_BS);        
        promptConsoleFill--;
    }
}

/*
 * Add characters to prompt
 */
static void promptAdd(char c)
{
    sqputchar(c);
    promptConsoleFill++;
}


/*
 *  Prompt handler, call periodically from your mainloop
 */
void promptProcess(const cmdLineEntry * cmdLineEntries)
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
                    break;
                case ASCII_CR:
                    sqputchar(ASCII_CR);
                    promptConsoleFill = 0;
                    // note, we are filling the buffer end to start,
                    char * p = &newcommand[CMDLINE_MAX_LENGTH-1];
                    // terminate string
                    *p = ASCII_NUL;
                    // call handler
                    cmdlineParse(cmdLineEntries, p);
                    break;
                case ASCII_ESC:
                    ansiParse(c);
                    promptState = promptEscape;
                    break;
                case EOF:
                    break;
                default:
                    promptAdd(c);
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
                            // history available?
                            if(1)
                            {
                                // clear prompt/history
                                promptDel(promptConsoleFill);
                                promptConsoleFill = 0;
                            }
                            promptState = promptNormal;
                        break;
                        case ansiCursorDown:
                            // TODO go to next command if available
                            // clear prompt/history
                            promptDel(promptConsoleFill);
                            promptConsoleFill = 0;
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

