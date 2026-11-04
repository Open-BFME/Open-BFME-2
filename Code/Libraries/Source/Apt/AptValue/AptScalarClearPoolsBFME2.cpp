// cl: /MD /EHsc
// Source guide: public-material/777b24f0e1dc0929-AptInteger.cpp and
// dfdaf615e1a3b9ce-AptFloat.cpp, ClearPool. Retail independently proves all
// three pool heads, +8 next links, slot11 GC clearing and slot14 deletion.
// Boolean retail is pooled (also established by matched Create6D88C0),
// unlike the later Boolean donor singleton implementation.
// Each extent is 55 bytes through RET, followed by INT3 padding; Ghidra's
// 52-byte entries truncate the loop branch and omit POP/RET. Partial views.
#include "../AptValue.h"
#include "../../../../GameEngine/Include/Common/AptInteger.h"
extern AptInteger *g_aptIntegerFreeList;
void AptInteger::ClearPool()
{
    while (g_aptIntegerFreeList != 0) {
        AptInteger *next = g_aptIntegerFreeList->field08_next;
        g_aptIntegerFreeList->DestroyGCPointers();
        delete g_aptIntegerFreeList;
        g_aptIntegerFreeList = next;
    }
}
class AptFloat : public AptValue {
public:
    AptFloat *nextFree;
    static void ClearPool();
};
extern AptFloat *g_aptFloatFreeList;
void AptFloat::ClearPool()
{
    while (g_aptFloatFreeList != 0) {
        AptFloat *next = g_aptFloatFreeList->nextFree;
        g_aptFloatFreeList->DestroyGCPointers();
        delete g_aptFloatFreeList;
        g_aptFloatFreeList = next;
    }
}
#include "../AptBoolean.h"
extern AptBoolean *g_aptBooleanFreeList;
void AptBoolean::ClearPool()
{
    while (g_aptBooleanFreeList != 0) {
        AptBoolean *next = g_aptBooleanFreeList->field08_next;
        g_aptBooleanFreeList->DestroyGCPointers();
        delete g_aptBooleanFreeList;
        g_aptBooleanFreeList = next;
    }
}
