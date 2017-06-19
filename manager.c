#include "manager.h"
#include "hashcol.h"
#include <stdio.h>
#include <ctype.h>

/*Compute Collatz sequence : return 1 at the end of seq */
static inline unsigned collatz(unsigned value)
{
    if(value > 1)
        return (value & 1) ? ((value << 1) + (value | 1)) : (value >> 1);
    else
        return 1;
}

/* when the sequence key get value MIN_SEQ, we restart the sequence with initial key value.*/
static inline unsigned key_setter(Collatz *col)
{
    return (col->key <= col->minseq) ? col->startval : col->key;
}

#if 0
/*
 * New key setter methode : here we change completely the key under certain condition :
 * When the value of : col->minseq is reached we change the col->key to (col->key << 1); and restart the loop.
 * when the sequence key get value MIN_SEQ (see the deader file for MIN_SEQ), we restart the sequence with initial key value.*/
static inline unsigned collatzKey_set(Collatz *col, unsigned swap)
{
    /*DEBUG_("new key is : %d\n", col->key) ;*/
    return (col->key <= col->minseq) ? ((col->startval <<= swap)) : col->key;
}
#endif


/*This function shift the wchar_t c with an offset value, defined with the collatz sequence (the value is next "key").*/
static inline wchar_t _crypt(unsigned offset, wchar_t c)
{
    return ((FIRST_RASCII + (c + offset) % LAST_RASCII) - FIRST_RASCII);
}

/*Find the original value of the modulo operation, with the limit : val = LAST_RASCII*/
static inline wchar_t abswchar_t(int c, unsigned val)
{
    while(c < 0)
        c += val;
    return c;
}


static inline wchar_t _decrypt(unsigned offset, int c)
{
    /*The inverse operation of the encryption */
    c = c + FIRST_RASCII - (offset + FIRST_RASCII) % LAST_RASCII;
    /*We return from the negative result to the original result, if there's some negatives shit of course.*/
    c = abswchar_t(c, LAST_RASCII);
    return c;
}

/* tell if the character is between : LAST_RASCII 'wchar_t' and
 * FIRST_RASCII 'wchar_t ', or NOT. If not, nothing will be encrypted and the return is NULL.
 * For the ifdef commande : choose to crypt the carriage return '\n' of new line or not.
 *
 * */
static inline short isColAscii(wchar_t c)
{
#ifdef ENTER
    return (((c >= FIRST_RASCII) && (c <= LAST_RASCII)) || (c == '\n'));

#elif defined ALLCHARIOT
    return (((c >= FIRST_RASCII) && (c <= LAST_RASCII)) || (c == '\n')
            || (c == '\f') || (c == '\v') || (c == '\r') || (c == '\t'));
#endif
    return ((c >= FIRST_RASCII) && (c <= LAST_RASCII));
}


/*init data coll : Dont require a strong password in param's
 * because the hash function will generate anyway a big unsigned */
extern void coll_Init(Collatz *col, const char * const password , unsigned minseq)
{
    col->key = hashcode(password);
    col->minseq = minseq;
    col->startval = col->key;
    col->cp_print = 0;
    col->codedMsg = NULL;
    col->clearMsg = NULL;
}

/* ENC DATA with coll
   return NULL if the code message is an empty string or if isColAscii() return is false.
   If the password string is 'NULL' there will be no encryption.
*/
extern wchar_t * coll_Encrypt(Collatz *col, const wchar_t * const data)
{
    size_t i;

    if(!data) return NULL;

    col->len = wcslen(data);
    assert(col->codedMsg = (wchar_t*)malloc((col->len + 1) * sizeof(wchar_t)));
    wmemset(col->codedMsg, 0, (col->len + 1)) ;
    /*test here only for coll ascii limit from FIRST_RASCII to LAST_RASCII : see the file "manager.h"*/
    for(i = 0; i < col->len; i++)
    {
        if(isColAscii(data[i]))
        {
            col->key = collatz(col->key);
            col->key = key_setter(col);
            col->codedMsg[i] = _crypt(col->key, data[i]);
            /* count the non-printable characters */
            if (!isprint(col->codedMsg[i]))
                col->cp_print++;
        }
        else
        {
            free(col->codedMsg), col->codedMsg = NULL;
            return NULL;
        }
    }
    col->codedMsg[i] = L'\0';
    return col->codedMsg;
}




/*
DEC DATA with coll : return NULL if there's nothing to decrypt.*/
extern wchar_t * coll_Decrypt(Collatz *col)
{
    if(!col->codedMsg) return NULL;

    size_t i;

    assert(col->clearMsg = malloc((col->len + 1) * sizeof(wchar_t)));
    wmemset(col->clearMsg, 0, (col->len + 1));
    /* reset the key */
    col->key = col->startval;

    for(i = 0; i < col->len; i++)
    {
        col->key = collatz(col->key);
        col->key = key_setter(col);
        col->clearMsg[i] = _decrypt(col->key, col->codedMsg[i]);
    }
    col->clearMsg[i] = L'\0';
    return col->clearMsg;
}



/*free some ram space and shit you know */
extern void coll_dispose(Collatz *col)
{
    if(col->codedMsg)
        free(col->codedMsg), col->codedMsg = NULL;
    if(col->clearMsg)
        free(col->clearMsg), col->clearMsg = NULL;
}
