// cl: /O1
// Microsoft Visual C++ .NET 2003 ATL 7.1 atlimage.h members.

struct HBITMAP__;
typedef HBITMAP__ *HBITMAP;

struct HDC__;
typedef HDC__ *HDC;

typedef void *HGDIOBJ;
typedef long LONG;

extern "C" __declspec(dllimport) LONG __stdcall InterlockedExchange(volatile LONG *target, LONG value);
extern "C" __declspec(dllimport) HDC __stdcall CreateCompatibleDC(HDC dc);
extern "C" __declspec(dllimport) int __stdcall DeleteDC(HDC dc);
extern "C" __declspec(dllimport) HGDIOBJ __stdcall SelectObject(HDC dc, HGDIOBJ object);

namespace ATL
{

class CImage
{
private:
    class CDCCache
    {
    public:
        HDC GetDC() throw();
        void ReleaseDC(HDC dc) throw();

    private:
        HDC m_ahDCs[4];
    };

public:
    virtual ~CImage() throw();

    HBITMAP Detach() throw();
    HDC GetDC() const throw();

private:
    HBITMAP m_hBitmap;
    void *m_pBits;
    int m_nWidth;
    int m_nHeight;
    int m_nPitch;
    int m_nBPP;
    bool m_bIsDIBSection;
    bool m_bHasAlphaChannel;
    long m_iTransparentColor;
    mutable HDC m_hDC;
    mutable int m_nDCRefCount;
    mutable HBITMAP m_hOldBitmap;

    static CDCCache s_cache;
};

HDC CImage::CDCCache::GetDC() throw()
{
    HDC dc;

    for (int i = 0; i < 4; ++i)
    {
        dc = (HDC)InterlockedExchange((volatile LONG *)&m_ahDCs[i], 0);
        if (dc != 0)
        {
            return dc;
        }
    }

    dc = CreateCompatibleDC(0);
    return dc;
}

void CImage::CDCCache::ReleaseDC(HDC dc) throw()
{
    for (int i = 0; i < 4; ++i)
    {
        HDC oldDC = (HDC)InterlockedExchange((volatile LONG *)&m_ahDCs[i], (LONG)dc);
        if (oldDC == 0)
        {
            return;
        }
        dc = oldDC;
    }

    DeleteDC(dc);
}

HDC CImage::GetDC() const throw()
{
    ++m_nDCRefCount;
    if (m_hDC == 0)
    {
        m_hDC = s_cache.GetDC();
        m_hOldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
    }

    return m_hDC;
}

HBITMAP CImage::Detach() throw()
{
    HBITMAP hBitmap = m_hBitmap;
    m_hBitmap = 0;
    m_pBits = 0;
    m_nWidth = 0;
    m_nHeight = 0;
    m_nBPP = 0;
    m_nPitch = 0;
    m_iTransparentColor = -1;
    m_bHasAlphaChannel = false;
    m_bIsDIBSection = false;
    return hBitmap;
}

}
