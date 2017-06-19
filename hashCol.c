#include "hashcol.h"

/* simple hash function to transform passeword encryption string to unsinged value. Used as encryption secret KEY.*/
extern unsigned hashcode(const char * const data)
{
    if(!data)
        return 0;

    size_t i;
    unsigned csum = 0, sumc = 0;
    unsigned temp = 0;

    for(i = 0; data[i]; ++i)
    {
        temp = data[i];
        sumc += temp * temp;
        csum += temp;

        if(~(i & 1))
        {
            csum <<= temp;
            sumc *= temp;
        }
        else
        {
            csum *= temp;
            sumc += temp;
        }
    }
    return (abs(csum - sumc)) + MIN_HASH;
}
