// cl: /MD /EHsc
// Address-derived recovery of 0x006FFCE0 (155B), an AptActionInterpreter string
// worker. Retail clears the EAStringC out parameter through the const char*
// ctor 0x006D4C80 (empty literal 0x00BBAC1C) and operator= 0x006D3030, calls
// the unrowed filler 0x006FF980 with (value, sBuf, 1), then asserts
// sBuf.Size() != 0 at AptActionInterpreter.cpp 0x6C1 using the accessor
// 0x006D3750. The SEH frame is the EAStringC temporary's destructor 0x006D3010.
// The handler and callee names are address-derived.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class EAStringC
{
    void *m_pData;
public:
    EAStringC(const char *value);
    ~EAStringC();
    EAStringC &operator=(const EAStringC &other);
    unsigned int rva006D3750() const;
};

class AptValue;

void rva006ff980(AptValue *value, EAStringC &sBuf, int arg);

void rva006ffce0(AptValue *value, EAStringC &sBuf)
{
    {
        EAStringC tmp("");
        sBuf = tmp;
    }
    rva006ff980(value, sBuf, 1);
    if (!(sBuf.rva006D3750() != 0)) {
        g_bfmeAptAssertAtE17734("sBuf.Size() != 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x6C1);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
}
