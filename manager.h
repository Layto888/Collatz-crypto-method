#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

/* We use to encrypt the characters between '' and '~' which let us 222 possibilities of rotation for each
 * wchar_t.*/
#define LAST_RASCII 254
#define FIRST_RASCII ' '
/* default collatz startkey */
#define KEY 12345
/*the break point for collatz  sequence : in other words reloop seq when it reach this value */
#define DEFAULT_MIN_SEQ 16
/* use jump line character '\n' if defined */
#define ENTER


/* Enable assert in release mode */
#undef NDEBUG
#include <assert.h>
#include <wchar.h>



typedef struct
{
    size_t len;        /*the length of the message */
    size_t cp_print;   /*The number of characters that can't be printable after encryption.                       */
    unsigned key;      /*secret encryption key (defined by user as a alphanum password then => hashtable to get key)*/
    unsigned startval; /*the value used to start the sequence of collatz (choosed by user or by default)*/
    unsigned minseq;   /*the minimum value the sequence could reach.*/
    wchar_t *codedMsg; /*contain encrypted data or NULL if error*/
    wchar_t *clearMsg; /*contain decrypted or NULL */

} Collatz;

extern void coll_Init(Collatz *, const char * const, unsigned);
extern wchar_t *coll_Encrypt(Collatz *, const wchar_t * const);
extern wchar_t *coll_Decrypt(Collatz *);
extern void coll_dispose(Collatz *);

#endif
