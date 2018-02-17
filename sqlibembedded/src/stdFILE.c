#include <sqstdlib.h>
#include <sqstdio.h>

// std in/out/err defined as weak so they can be overridden
// OVERRIDE THESE STRUCTS IN YOUR PROJECT!
const sqFILE __attribute__((weak)) sqstdindef = {
    NULL,
    NULL,
};

const sqFILE __attribute__((weak)) sqstdoutdef = {
    NULL,
    NULL,
};

const sqFILE __attribute__((weak)) sqsterrdef = {
    NULL,
    NULL,
};

const sqFILE * sqstdin = &sqstdindef;
const sqFILE * sqstdout = &sqstdoutdef;
const sqFILE * sqstderr = &sqsterrdef;



