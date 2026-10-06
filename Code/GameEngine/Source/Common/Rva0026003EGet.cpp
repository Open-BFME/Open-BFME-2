// cl: /O1 /MD /arch:SSE /G7
// ?Rva0026003EGet@@YAHHPAXMM@Z @0x0026003E 158B
// Evidence: unlock lane, callers at 0x002601B7 0x0026026E in 0x002600DC, callee fabs 0x00629210 rowed.
// Clamp shape `if (m > 0) clamped = (a < 15) ? a : 15; else 0`
// reproduces the retail clamp branch orientation (jge to the 15 store). math.h's
// float fabs overload (rather than (float) of an extern double fabs) is what lets
// the x87 result stay in ST0 across the flag test and spill after the first pop.
#include <math.h>

struct Rva0026003EState {
    char m_pad[0x24];
    float m_vals[15];
    unsigned char m_flag60;
};

int __cdecl Rva0026003EGet(int a, void *objRaw, float f1, float f2)
{
    Rva0026003EState *obj = (Rva0026003EState *)objRaw;
    float diff = fabs(f2 - f1);
    if (obj->m_flag60) {
        int i2 = (int)f2;
        int i1 = (int)f1;
        int *p;
        if (i2 < i1)
            p = &i2;
        else
            p = &i1;
        return (int)(obj->m_vals[a] * diff) + *p;
    } else {
        int i2 = (int)f2;
        int i1 = (int)f1;
        int m = (a < 15) ? a : 15;
        int clamped;
        if (m > 0)
            clamped = (a < 15) ? a : 15;
        else
            clamped = 0;
        int *p = (i2 < i1) ? &i2 : &i1;
        return ((int)diff / 15) * clamped + *p;
    }
}
