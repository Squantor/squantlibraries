#include <sqctypetable.h>

const ctypeEntry asciiTableCtypes[128] =
{
    {ctypeIsNone}, // NUL
    {ctypeIsNone}, // SOH
    {ctypeIsNone}, // STX
    {ctypeIsNone}, // ETX
    {ctypeIsNone}, // EOT
    {ctypeIsNone}, // ENQ
    {ctypeIsNone}, // ACK
    {ctypeIsNone}, // BEL
    {ctypeIsNone}, // BS
    {ctypeIsSpace}, // TAB
    {ctypeIsSpace}, // LF
    {ctypeIsSpace}, // VT
    {ctypeIsSpace}, // FF
    {ctypeIsSpace}, // CR
    {ctypeIsNone}, // SO
    {ctypeIsNone}, // SI
    {ctypeIsNone}, // DLE
    {ctypeIsNone}, // DC1
    {ctypeIsNone}, // DC2
    {ctypeIsNone}, // DC3
    {ctypeIsNone}, // DC4
    {ctypeIsNone}, // NAK
    {ctypeIsNone}, // SYN
    {ctypeIsNone}, // ETB
    {ctypeIsNone}, // CAN
    {ctypeIsNone}, // EM
    {ctypeIsNone}, // SUB
    {ctypeIsNone}, // ESC
    {ctypeIsNone}, // FS
    {ctypeIsNone}, // GS
    {ctypeIsNone}, // RS
    {ctypeIsNone}, // US
    {ctypeIsSpace}, // Space
    {ctypeIsNone}, // !
    {ctypeIsNone}, // "
    {ctypeIsNone}, // #
    {ctypeIsNone}, // $
    {ctypeIsNone}, // %
    {ctypeIsNone}, // &
    {ctypeIsNone}, // '
    {ctypeIsNone}, // (
    {ctypeIsNone}, // )
    {ctypeIsNone}, // *
    {ctypeIsNone}, // +
    {ctypeIsNone}, // ,
    {ctypeIsNone}, // -
    {ctypeIsNone}, // .
    {ctypeIsNone}, // /
    {ctypeIsDigit | ctypeIsXdigit}, // 0
    {ctypeIsDigit | ctypeIsXdigit}, // 1
    {ctypeIsDigit | ctypeIsXdigit}, // 2
    {ctypeIsDigit | ctypeIsXdigit}, // 3
    {ctypeIsDigit | ctypeIsXdigit}, // 4
    {ctypeIsDigit | ctypeIsXdigit}, // 5
    {ctypeIsDigit | ctypeIsXdigit}, // 6
    {ctypeIsDigit | ctypeIsXdigit}, // 7
    {ctypeIsDigit | ctypeIsXdigit}, // 8
    {ctypeIsDigit | ctypeIsXdigit}, // 9
    {ctypeIsNone}, // :
    {ctypeIsNone}, // ;
    {ctypeIsNone}, // <
    {ctypeIsNone}, // =
    {ctypeIsNone}, // >
    {ctypeIsNone}, // ?
    {ctypeIsNone}, // @
    {ctypeIsUpper | ctypeIsXdigit}, // A
    {ctypeIsUpper | ctypeIsXdigit}, // B
    {ctypeIsUpper | ctypeIsXdigit}, // C
    {ctypeIsUpper | ctypeIsXdigit}, // D
    {ctypeIsUpper | ctypeIsXdigit}, // E
    {ctypeIsUpper | ctypeIsXdigit}, // F
    {ctypeIsUpper}, // G
    {ctypeIsUpper}, // H
    {ctypeIsUpper}, // I
    {ctypeIsUpper}, // J
    {ctypeIsUpper}, // K
    {ctypeIsUpper}, // L
    {ctypeIsUpper}, // M
    {ctypeIsUpper}, // N
    {ctypeIsUpper}, // O
    {ctypeIsUpper}, // P
    {ctypeIsUpper}, // Q
    {ctypeIsUpper}, // R
    {ctypeIsUpper}, // S
    {ctypeIsUpper}, // T
    {ctypeIsUpper}, // U
    {ctypeIsUpper}, // V
    {ctypeIsUpper}, // W
    {ctypeIsUpper}, // X
    {ctypeIsUpper}, // Y
    {ctypeIsUpper}, // Z
    {ctypeIsNone}, // [
    {ctypeIsNone}, /* \ */
    {ctypeIsNone}, // ]
    {ctypeIsNone}, // ^
    {ctypeIsNone}, // _
    {ctypeIsNone}, // `
    {ctypeIsLower | ctypeIsXdigit}, // a
    {ctypeIsLower | ctypeIsXdigit}, // b
    {ctypeIsLower | ctypeIsXdigit}, // c
    {ctypeIsLower | ctypeIsXdigit}, // d
    {ctypeIsLower | ctypeIsXdigit}, // e
    {ctypeIsLower | ctypeIsXdigit}, // f
    {ctypeIsLower}, // g
    {ctypeIsLower}, // h
    {ctypeIsLower}, // i
    {ctypeIsLower}, // j
    {ctypeIsLower}, // k
    {ctypeIsLower}, // l
    {ctypeIsLower}, // m
    {ctypeIsLower}, // n
    {ctypeIsLower}, // o
    {ctypeIsLower}, // p
    {ctypeIsLower}, // q
    {ctypeIsLower}, // r
    {ctypeIsLower}, // s
    {ctypeIsLower}, // t
    {ctypeIsLower}, // u
    {ctypeIsLower}, // v
    {ctypeIsLower}, // w
    {ctypeIsLower}, // x
    {ctypeIsLower}, // y
    {ctypeIsLower}, // z
    {ctypeIsNone}, // {
    {ctypeIsNone}, // |
    {ctypeIsNone}, // }
    {ctypeIsNone}, // ~
    {ctypeIsNone}, // DEL
} ;