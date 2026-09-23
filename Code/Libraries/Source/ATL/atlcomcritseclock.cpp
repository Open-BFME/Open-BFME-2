// cl: /O1
// Microsoft Visual C++ .NET 2003 ATL 7.1 CComCritSecLock<CComCriticalSection>.
//
// Identity: atls.lib's ??1CComCritSecLock COMDAT places uniquely at 0x00628CE7,
// and the constructor at 0x00628CBE, Lock at 0x00628C56 and Unlock at
// 0x00628CAD sit beside it in the same ATL run. The three members were first
// landed from a BFME 1 donor under opaque names (BfmeThingDWD); the bodies are
// atlbase.h's, and the EnterCriticalSection/LeaveCriticalSection imports take
// &m_cs.m_sec, which is the lock's first member.

typedef long HRESULT;

#define FAILED(hr) ((hr) < 0)
#define S_OK 0

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs);

namespace ATL
{

__declspec(noinline) __declspec(noreturn) void __stdcall AtlThrow(HRESULT hr);

class CComCriticalSection
{
public:
    HRESULT Lock() throw()
    {
        EnterCriticalSection(&m_sec);
        return 0;
    }
    HRESULT Unlock() throw()
    {
        LeaveCriticalSection(&m_sec);
        return 0;
    }

    unsigned char m_sec[0x18];
};

template< class TLock >
class CComCritSecLock
{
public:
    CComCritSecLock( TLock& cs, bool bInitialLock = true );
    ~CComCritSecLock() throw();

    HRESULT Lock() throw();
    void Unlock() throw();

private:
    TLock& m_cs;
    bool m_bLocked;

    CComCritSecLock( const CComCritSecLock& );
    CComCritSecLock& operator=( const CComCritSecLock& );
};

template< class TLock >
inline CComCritSecLock< TLock >::CComCritSecLock( TLock& cs, bool bInitialLock ) :
    m_cs( cs ),
    m_bLocked( false )
{
    if( bInitialLock )
    {
        HRESULT hr;

        hr = Lock();
        if( FAILED( hr ) )
        {
            AtlThrow( hr );
        }
    }
}

template< class TLock >
inline CComCritSecLock< TLock >::~CComCritSecLock() throw()
{
    if( m_bLocked )
    {
        Unlock();
    }
}

template< class TLock >
inline HRESULT CComCritSecLock< TLock >::Lock() throw()
{
    HRESULT hr;

    hr = m_cs.Lock();
    if( FAILED( hr ) )
    {
        return( hr );
    }
    m_bLocked = true;

    return( S_OK );
}

template< class TLock >
inline void CComCritSecLock< TLock >::Unlock() throw()
{
    m_cs.Unlock();
    m_bLocked = false;
}

template class CComCritSecLock< CComCriticalSection >;

}
