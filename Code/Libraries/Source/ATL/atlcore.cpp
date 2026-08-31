// cl: /O1
// Microsoft Visual C++ .NET 2003 ATL 7.1 CComCriticalSection constructor.

extern "C" void *__cdecl memset(void *memory, int value, unsigned int size);

namespace ATL
{

class CComCriticalSection
{
public:
    CComCriticalSection() throw();

    unsigned char m_sec[0x18];
};

CComCriticalSection::CComCriticalSection() throw()
{
    memset(&m_sec, 0, sizeof(m_sec));
}

}
