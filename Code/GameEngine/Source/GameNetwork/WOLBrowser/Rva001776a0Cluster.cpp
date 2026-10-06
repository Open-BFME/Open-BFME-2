// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived recovery of 0x001776A0 (109B), a void DX8WebBrowser helper
// that forwards a browser name through the COM pointer. Retail:
//   if (g_bfmeObjECF != 0)
//       g_bfmeObjECF->invoke(BfmeBstrVGP(name));
// The pointer's operator-> null-checks and raises E_POINTER via
// _com_issue_error 0x00654B20, the temporary is built by the const char*
// BSTR ctor 0x00176CD0 (ICF-folded with _bstr_t's rowed ctor), and invoke is
// the rowed BfmeBstrVGP overload 0x001770C0. Shape mirrors the sibling
// DX8WebBrowser::Is_Browser_Open at 0x00177710.
// Class/method identity is not proven; the function name is address-derived.

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

extern void __stdcall _com_issue_error(long error);

class BfmeThingVGP
{
public:
    void *m_bfme00;
    void *m_bfme04;
    int m_bfme08;
    int bfmeGoVGP() throw();
};

class BfmeBstrVGP
{
public:
    BfmeThingVGP *m_data;
    BfmeBstrVGP(const char *text) throw();
    BfmeBstrVGP(const BfmeBstrVGP &other) throw() : m_data(other.m_data) {}
    ~BfmeBstrVGP() throw()
    {
        if (m_data)
            m_data->bfmeGoVGP();
    }
};

class Rva00958D30
{
public:
    long invoke(BfmeBstrVGP arg);
};

class BfmeObjECFPtr
{
public:
    Rva00958D30 *m_ptr;

    operator Rva00958D30 *() const throw()
    {
        return m_ptr;
    }

    Rva00958D30 *operator->() const
    {
        if (!m_ptr)
            _com_issue_error(0x80004003);
        return m_ptr;
    }
};

extern BfmeObjECFPtr g_bfmeObjECF;

void rva001776a0(const char *browsername)
{
    if (g_bfmeObjECF == 0)
        return;
    g_bfmeObjECF->invoke(BfmeBstrVGP(browsername));
}
// ?g_bfmeObjECF@@3VBfmeObjECFPtr@@A: the global at VA 0xdf7040 is ?g_bfmeObjECF@@3PAUBfmeObjECF@@A.
#pragma comment(linker, "/alternatename:?g_bfmeObjECF@@3VBfmeObjECFPtr@@A=?g_bfmeObjECF@@3PAUBfmeObjECF@@A")
