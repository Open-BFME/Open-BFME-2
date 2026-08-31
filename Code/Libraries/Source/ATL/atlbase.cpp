// cl: /O1
// Microsoft Visual C++ .NET 2003 ATL 7.1 _ATL_WIN_MODULE70 constructor.
namespace ATL {
class CComCriticalSection
{
public:
    CComCriticalSection() throw();
    unsigned char m_sec[0x18];
};

struct _ATL_WIN_MODULE70
{
    unsigned int cbSize;
    CComCriticalSection m_csWindowCreate;
    void *m_pCreateWndList;
    unsigned int m_rgWindowClassAtoms[3];

    _ATL_WIN_MODULE70();
};

_ATL_WIN_MODULE70::_ATL_WIN_MODULE70()
{
    m_rgWindowClassAtoms[0] = 0;
    m_rgWindowClassAtoms[1] = 0;
    m_rgWindowClassAtoms[2] = 0;
}
}
