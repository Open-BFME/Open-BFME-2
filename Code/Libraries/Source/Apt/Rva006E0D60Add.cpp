// cl: /MD
// ?rva006E0D60@Rva006E0D60@@QAEXPAVAptValue@@@Z, retail 0x006E0D60, 63 bytes.
// AptSet word add storing arg then AddRef with m_nElements/m_nSize guard.
// Evidence: unlock lane unblocking 4 callers; AddRef virtual slot 0 via
// AptValuePtrStack neighbour; same /O2 shape as Apt neighbours.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptValue {
public:
    virtual void AddRef();
    virtual void Release();
};
class Rva006E0D60 {
    int m_nElements;
    int m_nSize;
    AptValue **m_ppElements;
public:
    void rva006E0D60(AptValue *p);
};
void Rva006E0D60::rva006E0D60(AptValue *p)
{
    if (m_nElements >= m_nSize) {
        g_bfmeAptAssertAtE17734("m_nElements < m_nSize", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x76);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    m_ppElements[m_nElements] = p;
    ++m_nElements;
    p->AddRef();
}
