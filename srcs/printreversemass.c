#include "../mTupperGraph.h"


void printreversemass(uint16_t *mass, uint32_t masslen)
{
    for(uint32_t i = masslen - 1; i > 0; i--)
    {
        printf("%u", (unsigned int)mass[i]);
    }
    printf("%u", (unsigned int)mass[0]);
    printf("\n\n\n");
}