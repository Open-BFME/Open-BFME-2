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
class AptValue {
public:
    virtual void unused0();
};
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
class AptActionQueueC {
    Rva006E3230Action *m_aActionPool;
    Rva006E3230Action *m_pCurrent;
    Rva006E3230Action *m_pEnd;
    char _padC[4];
    int m_iActionPoolSize;
public:
    void rva006E3230(Rva006E3230Action *pCur);
    void rva006E3810(AptValue *pContext, AptValue *pA, AptValue *pB, int iD, int iE);
};
void AptActionQueueC::rva006E3810(AptValue *pContext, AptValue *pA, AptValue *pB, int iD, int iE)
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
        ((Rva006E3740Slot *)m_pCurrent)->pValue0->unused0();
        ((Rva006E3740Slot *)m_pCurrent)->pValue1 = pA;
        ((Rva006E3740Slot *)m_pCurrent)->pValue1->unused0();
        ((Rva006E3740Slot *)m_pCurrent)->pValue2 = pB;
        ((Rva006E3740Slot *)m_pCurrent)->field4 = iD;
        return;
    }
    Rva006CC110Log(4, "!!!!!!!!!!!!! AptAnimationPoolData:  Dequeue is full !!!!!!!!");
}
