#include <sqstdlib.h>
#include <sqstdio.h>

// std in/out/err defined as weak so they can be overridden
// OVERRIDE THESE STRUCTS IN YOUR PROJECT!
const rStream __attribute__((weak)) sqstdindef = {
    NULL,
};

const wStream __attribute__((weak)) sqstdoutdef = {
    NULL,
};

const rStream * sqstdin = &sqstdindef;
const wStream * sqstdout = &sqstdoutdef;



