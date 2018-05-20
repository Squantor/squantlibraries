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
result mockStdinWrite(uint8_t c);
result mockStdinPuts(char * s);
result mockStdinRead(uint8_t *c);

void mockStdoutReset();
result mockStdoutStatus();
result mockStdoutIsEmpty();
result mockStdoutWrite(uint8_t c);
result mockStdoutRead(uint8_t *c);
char * mockStdoutGets(char * restrict s, int size);

#endif