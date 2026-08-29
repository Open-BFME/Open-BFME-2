// cl: /O1
// Microsoft Visual C++ .NET 2003 ATL 7.1 atlimage.h members.

struct HBITMAP__;
typedef HBITMAP__ *HBITMAP;

struct HDC__;
typedef HDC__ *HDC;

typedef long LONG;

extern "C" __declspec(dllimport) LONG __stdcall InterlockedExchange(volatile LONG *target, LONG value);
extern "C" __declspec(dllimport) HDC __stdcall CreateCompatibleDC(HDC dc);

namespace ATL
{

class CImage
{
private:
    class CDCCache
    {
    public:
        HDC GetDC() throw();

    private:
        HDC m_ahDCs[4];
    };

public:
    virtual ~CImage() throw();

    HBITMAP Detach() throw();

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
