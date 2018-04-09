/*
 * Standard stream definitions with their helper functions
 */
#include <sqstdlib.h>
#include <sqstdio.h>
#include <results.h>
#include <mock_stdio.h>

result stdinRead(uint8_t *c)
{
	if(mockStdinStatus() == queueNotEmpty)
	{
        mockStdinRead(c);
		return noError;
	}
	else
		return streamEOF;
}

const rStream sqstdindef = {
	stdinRead,
};

result stdoutWrite(uint8_t c)
{
	if(mockStdoutStatus() == queueFull)
		return streamEOF;
	else
		return noError;
}

const wStream sqstdoutdef = {
	stdoutWrite,
};
