/*
 * Standard stream definitions with their helper functions
 */
#include <sqstdlib.h>
#include <sqstdio.h>
#include <results.h>
#include <mock_stdio.h>

result stdinRead(uint8_t *c)
{
	if()
	{
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
	if(1 == 1)
		return streamEOF;
	else
		return noError;
}

const wStream sqstdoutdef = {
	stdoutWrite,
};
