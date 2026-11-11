// cl: /O2 /MD
// AptActionQueueC::rva006E3810 @0x006E3810 191B.
// Front-insert twin of rva006E3740 (Rva006E3230Validate.cpp): asserts
// pContext->getIsDefined() at AptAnimation.cpp:1771 (0x6EB) through the
// shared Apt assert triple (E17734 + DDC01C + int3), steps the current cursor
// back one 24-byte element (wrapping to the last pool slot), validates it via
// rva006E3230, logs Dequeue-full when it meets m_pEnd, else stores the cursor
// and fills a type-2 action: field8 = arg5, three AptValue slots (first two
// AddRef'd through vtable slot 0) and field4 = arg4. Evidence: same queue
// object, stride, assert and log immediates as the rowed rva006E3740 and
// rva006E4C70 siblings; callers 0x006E2349 0x006E23F0 0x006FA2A6.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
struct Rva006E3230Action { char data[24]; };
#include "AptValue.h"
class Rva006DBB60ShrNAndField
{
public:
    bool get() const;
};
void __cdecl Rva006CC110Log(int level, const char *fmt, ...);
struct Rva006E3740Slot {
    int eActionType;
    int field4;
    int field8;
    AptValue *pValue0;
    AptValue *pValue1;
    AptValue *pValue2;
};
#include "AptActionQueueC.h"
void AptActionQueueC::enqueueFront(AptValue *pContext, AptValue *pA, AptValue *pB, int iD, int iE)
{
    if (!((const Rva006DBB60ShrNAndField *)pContext)->get()) {
        g_bfmeAptAssertAtE17734("pContext->getIsDefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x6eb);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    Rva006E3230Action *pPrev = m_pCurrent - 1;
    if (pPrev < m_aActionPool)
        pPrev = &m_aActionPool[m_iActionPoolSize] - 1;
    rva006E3230(pPrev);
    if (pPrev != m_pEnd) {
        m_pCurrent = pPrev;
        ((Rva006E3740Slot *)m_pCurrent)->eActionType = 2;
        ((Rva006E3740Slot *)m_pCurrent)->field8 = iE;
        ((Rva006E3740Slot *)m_pCurrent)->pValue0 = pContext;
        ((Rva006E3740Slot *)m_pCurrent)->pValue0->AddRef();
        ((Rva006E3740Slot *)m_pCurrent)->pValue1 = pA;
        ((Rva006E3740Slot *)m_pCurrent)->pValue1->AddRef();
        ((Rva006E3740Slot *)m_pCurrent)->pValue2 = pB;
        ((Rva006E3740Slot *)m_pCurrent)->field4 = iD;
        return;
    }
    Rva006CC110Log(4, "!!!!!!!!!!!!! AptAnimationPoolData:  Dequeue is full !!!!!!!!");
}

// AptActionQueueC::rva006E38D0 @0x006E38D0 73B. Ghidra-unlisted queue depth:
// the 24-byte element distance from the cursor to m_pEnd, wrapped by the pool
// size when negative and then asserted positive (asm breakpoint barrier keeps
// the return move after it) ("iDelta > 0",
// AptAnimation.cpp line 0x75F, retail texts). Address-derived name.
int AptActionQueueC::rva006E38D0()
{
    int iDelta = m_pEnd - m_pCurrent;
    if (iDelta < 0) {
        iDelta += m_iActionPoolSize;
        if (!(iDelta > 0)) {
            g_bfmeAptAssertAtE17734("iDelta > 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x75f);
            if (g_bfmeAptBreakOnAssertAtDDC01C) {
                __asm int 3
            }
        }
    }
    return iDelta;
}

// AptActionQueueC::rva006E32A0 @0x006E32A0 36B. Ghidra-unlisted step-back
// helper: the element before pCur, wrapping to the last pool slot, validated
// through the rowed rva006E3230 and returned. Same wrap as rva006E3810 above.
Rva006E3230Action *AptActionQueueC::rva006E32A0(Rva006E3230Action *pCur)
{
    Rva006E3230Action *pPrev = pCur - 1;
    if (pPrev < m_aActionPool)
        pPrev = &m_aActionPool[m_iActionPoolSize] - 1;
    rva006E3230(pPrev);
    return pPrev;
}
