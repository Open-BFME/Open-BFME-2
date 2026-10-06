// cl: /O2 /MD
// AptActionQueueC::RemoveActionFor (WorldBuilder name, its __FUNCTION__ string) @0x006E4D50 441B.
// Removes one matching type-1 action holding the given AptValue: scans the
// circular action pool from m_pCurrent to m_pEnd (stride 24), validates the
// start cursor, skips non-matching or protected (m_pExec) entries with
// wrap-around asserts at _Apt.h 0x4e0/0x4e1, and on a match deletes it via
// memmove (tail shift or head advance) after Release through vtable slot 1.
// Gap case asserts NOT_REACHED at AptAnimation.cpp 0x73d. Layout/stride and
// assert-triple spelling shared with Rva006E3230Validate.cpp; caller
// 0x006E2B40 passes the same pool this and an AptValue.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
};
struct Rva006E3230Action
{
    int eActionType;
    char _pad4[8];
    AptValue *m_pValues[3];
};
class AptActionQueueC
{
public:
    void rva006E3230(Rva006E3230Action *pCur);
    void RemoveActionFor(AptValue *pArg);
private:
    Rva006E3230Action *m_aActionPool;
    Rva006E3230Action *m_pCurrent;
    Rva006E3230Action *volatile m_pEnd;
    Rva006E3230Action *m_pExec;
    int m_iActionPoolSize;
};
void AptActionQueueC::RemoveActionFor(AptValue *pArg)
{
    rva006E3230(m_pCurrent);
    Rva006E3230Action *pCur = m_pCurrent;
    AptValue *arg = pArg;
    while (pCur != m_pEnd)
    {
        if (pCur->eActionType == 1 && pCur->m_pValues[2] == arg)
        {
            if (pCur == m_pExec)
            {
                Rva006E3230Action *pNext = pCur + 1;
                if (pNext == &m_aActionPool[m_iActionPoolSize])
                    pNext = m_aActionPool;
                rva006E3230(pNext);
                pCur = pNext;
                continue;
            }
            if (pCur < m_pEnd)
            {
                arg->Release();
                memmove(pCur, pCur + 1, (m_pEnd - pCur - 1) * sizeof(Rva006E3230Action));
                Rva006E3230Action *pNewEnd = m_pEnd - 1;
                if (pNewEnd < m_aActionPool)
                    pNewEnd = &m_aActionPool[m_iActionPoolSize] - 1;
                rva006E3230(pNewEnd);
                m_pEnd = pNewEnd;
                return;
            }
            if (pCur > m_pCurrent)
            {
                arg->Release();
                memmove(m_pCurrent + 1, m_pCurrent, (pCur - m_pCurrent) * sizeof(Rva006E3230Action));
                Rva006E3230Action *pNext = m_pCurrent + 1;
                if (pNext == &m_aActionPool[m_iActionPoolSize])
                    pNext = m_aActionPool;
                rva006E3230(pNext);
                m_pCurrent = pNext;
                return;
            }
            if (pCur == m_pCurrent)
            {
                Rva006E3230Action *pNext = m_pCurrent + 1;
                if (pNext == &m_aActionPool[m_iActionPoolSize])
                    pNext = m_aActionPool;
                rva006E3230(pNext);
                m_pCurrent = pNext;
                return;
            }
            g_bfmeAptAssertAtE17734("NOT_REACHED", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x73d);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        pCur = pCur + 1;
        if (pCur == &m_aActionPool[m_iActionPoolSize])
            pCur = m_aActionPool;
        if (!(pCur >= &m_aActionPool[0]))
        {
            g_bfmeAptAssertAtE17734("pCur >= &m_aActionPool[0]", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x4e0);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        if (!(pCur < &m_aActionPool[m_iActionPoolSize]))
        {
            g_bfmeAptAssertAtE17734("pCur < &m_aActionPool[ m_iActionPoolSize ]", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x4e1);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
    }
}
