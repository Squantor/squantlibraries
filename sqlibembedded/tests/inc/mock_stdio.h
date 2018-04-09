/*
 * Mock for the standard input/output streams, enables 
 * testing of anything that uses serial input/output
 * 
 */
#ifndef MOCK_STDIO_H
#define MOCK_STDIO_H
#include "results.h"

result mockStdioSetup();
result mockStdinWrite();
result mockStdinRead();
result mockStdoutWrite();
result mockStdoutRead();

#endif