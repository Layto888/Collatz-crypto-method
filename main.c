/**<
* Collatz crypto wide format characters:
* Originally based on Caesar's encryption, but instead of having a key D with fixed offset.
* Encryption by this method use a variable C key offset witch is depending of the previous C value.
*
* The values ​​of C are determined by collatz's sequence. Aka: syracuse conjecture (Cf. see the wiki)
* The starting value given to the sequence, is the secret encryption and decryption Key.

     * NB: We take the table of the extended ascii.

 * Example:

            C = 15 -> Start value.
            The sequence C = 15 -> 46 -> 23 -> 70 -> 35 ... etc. Are the offset values for each char.

*
* @param std-c99.
* NDEBUG is undefined in relase mode for assertions.
* @author A.Amine
* @date  02/04/2017

*/

/*
 * TODO : correct the encode/decode of the '\n'.
 *
 * */

#include "manager.h"
#include "atabash.h"
#include "hashcol.h"
#include <stdio.h>
#include <assert.h>

#define _ATBASH 1

#ifndef READSTDIN
/* test message */
wchar_t test[] =
    L"This is a simple test for Collatz sequence crypto methode combined with atbash methode \n"
    "UPPER TESTE DONE and now numbers 0123456789 and some special chars : ?!;,<>²&éè'()-_- ç ~ ^ @[]{}+-*/.= % µ *@^\n"
    "and now rep : 1111111111111111111111111111111111111111111111111111 0000000000000000000000000000000000000000000";
#else

#define BUFF 4096
wchar_t test[BUFF];
#endif



int main(void)
{
    FILE *fp = NULL;
    assert(fp = fopen("data.txt", "w+"));

    Collatz col;
    coll_Init(&col, "111", DEFAULT_MIN_SEQ);

#ifdef READSTDIN
    /*Read from the stdin console, not recommended for special chars. Should use output file text.*/
    wmemset(test, 0, BUFF);
    fgetws(test, BUFF - 1, stdin);
#endif

#ifdef _ATBASH
    /*Encrypt data in first place with Atbash algo */
    encryptAtbash(test);
    fwprintf(fp, L"Clear -> Atbash:\n\n%ls\n\n", test);
#endif
    coll_Encrypt(&col, test);
    fwprintf(fp, L"Atbash -> Collatz with (%ld) non-printable characters:\n\n%ls\n\n", col.cp_print, col.codedMsg);
    coll_Decrypt(&col);

#ifdef _ATBASH
    encryptAtbash(col.clearMsg);
#endif
    fwprintf(fp, L"Collatz -> Clear:\n\n%ls\n", col.clearMsg);

    fclose(fp);
    coll_dispose(&col);
    return 0;
}

