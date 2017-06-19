#include "atabash.h"
#include <ctype.h>

/* this crypt an alpha with Atbash rotation method */
static inline wchar_t atbash(wchar_t c)
{
    size_t index;
    wchar_t ch, uplow;
    /*if it's not an alphanum, we keep, initial value */
    ch = c;

    if(isalpha(c))
    {
        if(isupper(c))
            uplow = 'A';
        else
            uplow = 'a';
        index = NBALPHA - (c - uplow);
        ch = uplow + index;
    }
    else if(isdigit(c))
        ch = '9' - (c - '0');

    return ch;
}



/*main function */
extern void encryptAtbash(wchar_t *data)
{
    if (!data) return;

    for(; *data; data++)
        *data = atbash(*data);
}

/*next step : write in binary file the data.
wchar_t chToBin(wchar_t c)
{
    int i;
    //i = 15 ? bits
    for (i = 7; i >= 0; --i)
    {
        putchar( (c & (1 << i)) ? '1' : '0' );
}
    putchar('\n');
}
*/

/*
write char to binary
void printbinchar(char character)
{
    char output[9];
    itoa(character, output, 2);
    printf("%s\n", output);
}
*/
