#include <inttypes.h>
#include <results.h>

// shut off unused variables warning here
#pragma GCC diagnostic ignored "-Wunused-parameter"

result __attribute__((weak)) logfsRead(uint32_t address, void *s, uint32_t n)
{
	return error;
}

result __attribute__((weak)) logfsWrite(uint32_t address, void *s, uint32_t n)
{
	return error;
}

// restore commandline options
#pragma GCC diagnostic pop
