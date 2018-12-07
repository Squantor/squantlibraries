/*
 * Mock for the standard input/output streams, enables 
 * testing of anything that uses serial input/output
 * 
 */
#ifndef MOCK_STDIO_H
#define MOCK_STDIO_H
#include <stdint.h>
#include <results.h>

result mockStdioSetup();

void mockStdinReset();
result mockStdinIsEmpty();
result mockStdinStatus();
result mockStdinWrite(char c);
result mockStdinPuts(char * s);
result mockStdinRead(char *c);

void mockStdoutReset();
result mockStdoutStatus();
result mockStdoutIsEmpty();
result mockStdoutWrite(char c);
result mockStdoutRead(char *c);
char * mockStdoutGets(char * restrict s, int size);
int mockStdoutClear(void);

#endif