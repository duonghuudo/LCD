#ifndef STRINGCONVENT_H
#define STRINGCONVENT_H
#include <stdint.h>

//-----------------------Dec2String-----------------------
// Convert a 32-bit number in unsigned decimal format
// Input: n is input number
//        string is an empty string
// Output: none
// n=0,    then create "0"
// n=3,    then create "3"
// n=89,   then create "89"
// n=123,  then create "123"
// n=9999, then create "9999"
void Dec2String(uint32_t n, char string[16]);

//-----------------------Fix2String-----------------------
// Output a 32-bit number in unsigned fixed-point format, 0.001 format
// Input: n is input number
//        string is an empty string// Input: none
// Output: none
// n=0,    then create "0.000"
// n=3,    then create "0.003"
// n=89,   then create "0.089"
// n=123,  then create "0.123"
// n=9999, then create "9.999"
// n>9999, then create "*.***"
void Fix2String(uint32_t n, char string[16]);

#endif