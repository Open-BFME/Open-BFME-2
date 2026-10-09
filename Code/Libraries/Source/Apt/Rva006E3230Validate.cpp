// cl: /O2 /MD
// AptActionQueueC::rva006E3230 @0x006E3230 102B.
// AptActionQueueC::rva006E3DB0 @0x006E3DB0 17B.
// Validates an action pointer against the Apt action pool using _Apt.h asserts
// at lines 0x4e0 ("pCur >= &m_aActionPool[0]") and 0x4e1
// ("pCur < &m_aActionPool[ m_iActionPoolSize ]") via the shared Apt assert
// triple (E17734 + DDC01C + int3). Layout read from retail: base pointer at
// +0, current at +4, size at +0x10, stride 24 (lea size*3 then base+size*3*8).
// Callers at 0x006E3740 0x006E3810 0x006E4A90 0x006E4B80 0x006E4C70 0x006E4D50
// 0x006E6540 pass the same this, and AptAnimation.cpp Dequeue-full callers
// establish the queue owner. Chain 0x006E3DB0 validates and returns +4.
// Honest-address methods; no donor.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
struct Rva006E3230Action { char data[24]; };
class AptValue {
public:
    virtual void unused0(); virtual void unused1(); virtual void unused2();
    virtual void unused3(); virtual void unused4(); virtual void unused5();
    virtual void unused6(); virtual void unused7(); virtual void unused8();
    virtual void unused9(); virtual void unused10(); virtual void unused11();
    virtual void unused12();
public:
    // Slot 0x34: PDB name unknown (cf AptValueForceDelete.cpp); this body calls it.
    virtual void unused13();
    void setGCMark(bool value);
};
class Rva006DBB40ShrAndField
{
public:
    // Rowed body returns 0/1; all three retail call sites here test al, so
    // the true donor return type is bool (cf isUndefined). Twin pin below.
    bool get() const;
};
class Rva006DBB60ShrNAndField
{
public:
    bool get() const;
};
void __cdecl Rva006CC110Log(int level, const char *fmt, ...);
struct Rva006E3230ActionFull {
    int eActionType;
    char _pad4[8];
    AptValue *m_pValues[3];
};
struct Rva006E3740Slot {
    int eActionType;
    int field4;
    int field8;
    AptValue *pValue0;
    AptValue *pValue1;
    AptValue *pValue2;
};
struct Rva006E4B80Inner {
    char _pad[0x28];
    int m_val28;
};
class Rva006CFCD0 {
public:
    bool isSpriteInstBase() const;
};
class AptCIH {
public:
    virtual void AddRef();
    bool rva006CFCD0() const;
    char _pad4[0x48];
    Rva006E4B80Inner *m_pAt4C;
};
struct Rva006E4B80Slot {
    int eActionType;
    int field4;
    int field8;
    int fieldC;
    void *field10;
    AptCIH *field14;
};
class AptActionQueueC {
    Rva006E3230Action *m_aActionPool;
    Rva006E3230Action *m_pCurrent;
    Rva006E3230Action *m_pEnd;
    char _padC[4];
    int m_iActionPoolSize;
public:
    void rva006E3230(Rva006E3230Action *pCur);
    Rva006E3230Action *rva006E3DB0();
    Rva006E3230Action *rva006E3920(int arg);
    void rva006E39A0();
    void rva006E3740(AptValue *pContext, AptValue *pA, AptValue *pB, int iD, int iE);
    void rva006E4B80(void *pArg1, AptCIH *pCIH, int iArg3, int iArg4);
    void rva006E4C70(void *pArg1, AptCIH *pCIH, int iArg3, int iArg4);
};
void AptActionQueueC::rva006E3230(Rva006E3230Action *pCur)
{
    if (!(pCur >= &m_aActionPool[0])) {
        g_bfmeAptAssertAtE17734("pCur >= &m_aActionPool[0]", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x4e0);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (!(pCur < &m_aActionPool[m_iActionPoolSize])) {
        g_bfmeAptAssertAtE17734("pCur < &m_aActionPool[ m_iActionPoolSize ]", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x4e1);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
}
Rva006E3230Action *AptActionQueueC::rva006E3DB0()
{
    rva006E3230(m_pCurrent);
    return m_pCurrent;
}

// AptActionQueueC::rva006E3920 @0x006E3920 114B.
// Wraps an argument by the action-pool cursor: iOffset = m_pCurrent -
// m_aActionPool (element stride 24), asserted into [0, m_iActionPoolSize) at
// AptAnimation.cpp:1911, then returns &pool[wrapped (arg + iOffset)] with a
// signed modulo folded into range. Evidence: unlock lane, caller 0x006E39A0;
// layout/stride/names shared with the two bodies above.
Rva006E3230Action *AptActionQueueC::rva006E3920(int arg)
{
    int iOffset = m_pCurrent - m_aActionPool;
    if (iOffset < 0 || iOffset >= m_iActionPoolSize) {
        g_bfmeAptAssertAtE17734("(iOffset >= 0) && (iOffset < m_iActionPoolSize)", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x777);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    int idx = (arg + iOffset) % m_iActionPoolSize;
    if (idx >= 0)
        return &m_aActionPool[idx];
    return &m_aActionPool[idx + m_iActionPoolSize];
}

// AptActionQueueC::rva006E39A0 @0x006E39A0 246B chain lane.
// Drains newly queued actions: iDelta = m_pEnd - m_pCurrent (stride 24),
// wrapped by size and asserted positive at AptAnimation.cpp:1887, then for
// each k the wrapped action dispatches on eActionType: type 1 marks operand
// 2, type 2 marks operands 0 and 1 (setGCMark(true) plus virtual slot 0x34
// when the ShrAnd view reports the mark clear), anything else asserts
// NOT_REACHED at AptAnimation.cpp:1962. Evidence: caller 0x006E47C0;
// same queue object (rva006E3920 called with own this); vtable shape copied
// from AptValueForceDelete.cpp.
void AptActionQueueC::rva006E39A0()
{
    int iDelta = m_pEnd - m_pCurrent;
    if (iDelta < 0) {
        iDelta += m_iActionPoolSize;
        if (iDelta <= 0) {
            g_bfmeAptAssertAtE17734("iDelta > 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x75F);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
    }
    int k = 0;
    if (iDelta > 0) {
        do {
            Rva006E3230ActionFull *a = (Rva006E3230ActionFull *)rva006E3920(k);
            int t = a->eActionType;
            if (t == 1) {
                if (!((const Rva006DBB40ShrAndField *)a->m_pValues[2])->get()) {
                    a->m_pValues[2]->setGCMark(true);
                    a->m_pValues[2]->unused13();
                }
            } else if (t == 2) {
                if (!((const Rva006DBB40ShrAndField *)a->m_pValues[0])->get()) {
                    a->m_pValues[0]->setGCMark(true);
                    a->m_pValues[0]->unused13();
                }
                if (!((const Rva006DBB40ShrAndField *)a->m_pValues[1])->get()) {
                    a->m_pValues[1]->setGCMark(true);
                    a->m_pValues[1]->unused13();
                }
            } else {
                g_bfmeAptAssertAtE17734("NOT_REACHED && \"Encountered invalid pActionPool->eActionType\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x7AA);
                if (g_bfmeAptBreakOnAssertAtDDC01C)
                    __debugbreak();
            }
        } while (++k < iDelta);
    }
}

// AptActionQueueC::rva006E3740 @0x006E3740 195B.
// Enqueues a type-2 action: asserts pContext->getIsDefined() at
// AptAnimation.cpp:1718 via the shared Apt assert triple, wraps m_pEnd+1 by
// size back to base, validates it, logs and returns when it meets m_pCurrent
// (Dequeue full), else fills type 2 plus the five args and advances m_pEnd.
// Evidence: unlock lane packet; same queue object as rva006E3230/rva006E3920;
// stride 24 and assert/log immediates read from retail.
void AptActionQueueC::rva006E3740(AptValue *pContext, AptValue *pA, AptValue *pB, int iD, int iE)
{
    if (!((const Rva006DBB60ShrNAndField *)pContext)->get()) {
        g_bfmeAptAssertAtE17734("pContext->getIsDefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x6b6);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    Rva006E3230Action *pNext = m_pEnd + 1;
    if (pNext == &m_aActionPool[m_iActionPoolSize])
        pNext = m_aActionPool;
    rva006E3230(pNext);
    if (pNext != m_pCurrent) {
        ((Rva006E3740Slot *)m_pEnd)->eActionType = 2;
        ((Rva006E3740Slot *)m_pEnd)->field8 = iE;
        ((Rva006E3740Slot *)m_pEnd)->pValue0 = pContext;
        ((Rva006E3740Slot *)m_pEnd)->pValue0->unused0();
        ((Rva006E3740Slot *)m_pEnd)->pValue1 = pA;
        ((Rva006E3740Slot *)m_pEnd)->pValue1->unused0();
        ((Rva006E3740Slot *)m_pEnd)->pValue2 = pB;
        ((Rva006E3740Slot *)m_pEnd)->field4 = iD;
        m_pEnd = pNext;
        return;
    }
    Rva006CC110Log(4, "!!!!!!!!!!!!! AptAnimationPoolData:  Dequeue is full !!!!!!!!");
}

// AptActionQueueC::rva006E4B80 @0x006E4B80 225B.
// Type-1 enqueue sibling of rva006E3740: asserts pCIH->getIsDefined() at
// AptAnimation.cpp:1615, wraps m_pEnd+1, validates, logs Dequeue-full when it
// meets m_pCurrent, else stores type 1 plus chain int from [pCIH+0x4C]+0x28,
// arg1, pCIH (with AddRef slot0), arg4, arg3, advances m_pEnd. Evidence:
// unlock lane packet; same queue object; stride 24 and assert/log immediates.
void AptActionQueueC::rva006E4B80(void *pArg1, AptCIH *pCIH, int iArg3, int iArg4)
{
    if (!((const Rva006DBB60ShrNAndField *)pCIH)->get()) {
        g_bfmeAptAssertAtE17734("pCIH->getIsDefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x64f);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    Rva006E3230Action *pNext = m_pEnd + 1;
    if (pNext == &m_aActionPool[m_iActionPoolSize])
        pNext = m_aActionPool;
    rva006E3230(pNext);
    if (pNext != m_pCurrent) {
        ((Rva006E4B80Slot *)m_pEnd)->eActionType = 1;
        if (!((const Rva006CFCD0 *)pCIH)->isSpriteInstBase()) {
            g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        ((Rva006E4B80Slot *)m_pEnd)->fieldC = pCIH->m_pAt4C->m_val28;
        ((Rva006E4B80Slot *)m_pEnd)->field10 = pArg1;
        ((Rva006E4B80Slot *)m_pEnd)->field14 = pCIH;
        pCIH->AddRef();
        ((Rva006E4B80Slot *)m_pEnd)->field8 = iArg4;
        ((Rva006E4B80Slot *)m_pEnd)->field4 = iArg3;
        m_pEnd = pNext;
        return;
    }
    Rva006CC110Log(4, "!!!!!!!!!!!!! AptAnimationPoolData:  Dequeue is full !!!!!!!!");
}

// AptActionQueueC::rva006E4C70 @0x006E4C70 224B.
// Front-insert twin of rva006E4B80: same type-1 payload, but the current
// cursor steps back one element (wrapping to the last pool slot) and the
// Dequeue-full test compares it against m_pEnd; the cursor is stored before
// the isSpriteInstBase check. Assert line 0x682 in
// AptAnimation.cpp. Evidence: shared strings and stride with rva006E4B80.
void AptActionQueueC::rva006E4C70(void *pArg1, AptCIH *pCIH, int iArg3, int iArg4)
{
    if (!((const Rva006DBB60ShrNAndField *)pCIH)->get()) {
        g_bfmeAptAssertAtE17734("pCIH->getIsDefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x682);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    Rva006E3230Action *pPrev = m_pCurrent - 1;
    if (pPrev < m_aActionPool)
        pPrev = &m_aActionPool[m_iActionPoolSize] - 1;
    rva006E3230(pPrev);
    if (pPrev != m_pEnd) {
        m_pCurrent = pPrev;
        if (!((const Rva006CFCD0 *)pCIH)->isSpriteInstBase()) {
            g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        ((Rva006E4B80Slot *)m_pCurrent)->fieldC = pCIH->m_pAt4C->m_val28;
        ((Rva006E4B80Slot *)m_pCurrent)->eActionType = 1;
        ((Rva006E4B80Slot *)m_pCurrent)->field10 = pArg1;
        ((Rva006E4B80Slot *)m_pCurrent)->field14 = pCIH;
        pCIH->AddRef();
        ((Rva006E4B80Slot *)m_pCurrent)->field8 = iArg4;
        ((Rva006E4B80Slot *)m_pCurrent)->field4 = iArg3;
        return;
    }
    Rva006CC110Log(4, "!!!!!!!!!!!!! AptAnimationPoolData:  Dequeue is full !!!!!!!!");
}
