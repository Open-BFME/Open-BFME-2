// _bfmeReload1221
// partial score=0.9857 date=2026-10-06
// cl: /O2 /MD
// Audit4ccdc5494ece2fad-AptRand.cpp semantic source, exact first two loops.
// Native full281B through RET70F828 followed by INT3; old Ghidra275 truncates
// the final return sequence. Existing next/seed provider and state storage
// establish this C ABI. Trial279B: raw last state uses EDX instead of native
// ESI plus a copy to EDX; no exact claim. Original provider spelling retained.

extern int g_bfmeIndexFA;
extern int g_bfmeStateFA[625];
extern unsigned int *g_bfmeNext1221;
void bfmeSeed(int);
#define state ((unsigned int *)g_bfmeStateFA)
#define SO_RAND_STATE_VECTOR_LENGTH     (624)
#define SO_RAND_PERIOD                  (397)
#define SO_RAND_MAGIC                   (0x9908B0DFU)

#define SO_RAND_HI_BIT(u)       ((u) & 0x80000000U)
#define SO_RAND_LO_BIT(u)       ((u) & 0x00000001U)
#define SO_RAND_LO_BITS(u)      ((u) & 0x7FFFFFFFU)
#define SO_RAND_MIX_BITS(u, v)  (SO_RAND_HI_BIT(u)|SO_RAND_LO_BITS(v))

extern "C" unsigned int bfmeReload1221( void )
{
    unsigned int *p0=state, *p2=state+2, *pM=state+SO_RAND_PERIOD, s0, s1;
    int j;

    if( g_bfmeIndexFA < -1 ) bfmeSeed( 4357 );

    g_bfmeIndexFA = SO_RAND_STATE_VECTOR_LENGTH - 1;
    g_bfmeNext1221 = state + 1;

    for( s0 = state[0], s1 = state[1], j = SO_RAND_STATE_VECTOR_LENGTH - SO_RAND_PERIOD + 1; --j; s0 = s1, s1 = *p2++ )
    {
        *p0++ = *pM++ ^ (SO_RAND_MIX_BITS(s0, s1) >> 1) ^ (SO_RAND_LO_BIT(s1) ? SO_RAND_MAGIC : 0U);
    }

    for( pM = state, j = SO_RAND_PERIOD; --j; s0 = s1, s1 = *p2++ )
    {
        *p0++ = *pM++ ^ (SO_RAND_MIX_BITS(s0, s1) >> 1) ^ (SO_RAND_LO_BIT(s1) ? SO_RAND_MAGIC : 0U);
    }

    s1=state[0], *p0 = *pM ^ (SO_RAND_MIX_BITS(s0, s1) >> 1) ^ (SO_RAND_LO_BIT(s1) ? SO_RAND_MAGIC : 0U);
    s1 ^= (s1 >> 11);
    s1 ^= (s1 <<  7) & 0x9D2C5680U;
    s1 ^= (s1 << 15) & 0xEFC60000U;

    return(s1 ^ (s1 >> 18));
}
