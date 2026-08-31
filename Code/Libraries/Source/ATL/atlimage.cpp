// cl: /O1
// Microsoft Visual C++ .NET 2003 ATL 7.1 atlimage.h members.

struct HBITMAP__;
typedef HBITMAP__ *HBITMAP;

struct HDC__;
typedef HDC__ *HDC;

typedef void *HGDIOBJ;
typedef void *HANDLE;
typedef long LONG;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char *LPBYTE;
typedef unsigned short USHORT;
typedef unsigned long SIZE_T;
typedef int BOOL;

struct BITMAP
{
    LONG bmType;
    LONG bmWidth;
    LONG bmHeight;
    LONG bmWidthBytes;
    WORD bmPlanes;
    WORD bmBitsPixel;
    void *bmBits;
};

struct BITMAPINFOHEADER
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
};

struct DIBSECTION
{
    BITMAP dsBm;
    BITMAPINFOHEADER dsBmih;
    DWORD dsBitfields[3];
    HANDLE dshSection;
    DWORD dsOffset;
};

struct tagRGBQUAD
{
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
};
typedef tagRGBQUAD RGBQUAD;

struct BITMAPINFO
{
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
};

typedef BITMAPINFO *LPBITMAPINFO;

struct CRITICAL_SECTION
{
    unsigned char data[24];
};

extern "C" __declspec(dllimport) LONG __stdcall InterlockedExchange(volatile LONG *target, LONG value);
extern "C" __declspec(dllimport) HDC __stdcall CreateCompatibleDC(HDC dc);
extern "C" __declspec(dllimport) int __stdcall DeleteDC(HDC dc);
extern "C" __declspec(dllimport) HGDIOBJ __stdcall SelectObject(HDC dc, HGDIOBJ object);
extern "C" __declspec(dllimport) int __stdcall DeleteObject(HGDIOBJ object);
extern "C" __declspec(dllimport) UINT __stdcall SetDIBColorTable(
    HDC dc, UINT firstColor, UINT colors, const RGBQUAD *colorTable);
extern "C" __declspec(dllimport) int __stdcall GetObjectA(HGDIOBJ object, int bytes, void *data);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) HBITMAP __stdcall CreateDIBSection(
    HDC dc, const BITMAPINFO *info, UINT usage, void **bits, HANDLE section, DWORD offset);
extern "C" int __cdecl abs(int value);
extern "C" void *__cdecl memset(void *dest, int value, unsigned int count);
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
extern "C" void *__cdecl _alloca(unsigned int size);

#define USES_ATL_SAFE_ALLOCA_EX(x) \
    ATL::_ATL_SAFE_ALLOCA_IMPL::CAtlSafeAllocBufferManager<x> _AtlSafeAllocaManager
#define USES_ATL_SAFE_ALLOCA USES_ATL_SAFE_ALLOCA_EX(ATL::CCRTAllocator)

#define _ATL_SAFE_ALLOCA(nRequestedSize, nThreshold) \
    ((nRequestedSize <= nThreshold && \
        ATL::_ATL_SAFE_ALLOCA_IMPL::_AtlVerifyStackAvailable(nRequestedSize)) ? \
        _alloca(nRequestedSize) : \
        _AtlSafeAllocaManager.Allocate(nRequestedSize))

#define _ATL_SAFE_ALLOCA_DEF_THRESHOLD 1024

#define FALSE 0
#define TRUE 1
#define BI_RGB 0
#define BI_BITFIELDS 3
#define DIB_RGB_COLORS 0

namespace Gdiplus
{
void __stdcall GdiplusShutdown(unsigned long token);
}

namespace ATL
{

class CCRTAllocator;

namespace _ATL_SAFE_ALLOCA_IMPL
{

// Declared, never defined: the stack-probe arm of _ATL_SAFE_ALLOCA below is
// dead whenever the request is over the threshold, so no call is emitted.
bool _AtlVerifyStackAvailable(SIZE_T size);

// atlalloc.h's heap fallback for _ATL_SAFE_ALLOCA. Declared, never defined:
// Allocate and the destructor are out-of-line bodies of their own, and a
// definition here would let MSVC inline them into every caller.
template <class Allocator>
class CAtlSafeAllocBufferManager
{
private:
    struct CAtlSafeAllocBufferNode;

    CAtlSafeAllocBufferNode *m_pHead;

public:
    CAtlSafeAllocBufferManager() : m_pHead(0) {}
    void *Allocate(SIZE_T requestedSize);
    ~CAtlSafeAllocBufferManager();
};

}

class CImage
{
private:
    class CInitGDIPlus
    {
    public:
        void ReleaseGDIPlus() throw();
        void IncreaseCImageCount() throw();
        void DecreaseCImageCount() throw();

    private:
        unsigned long m_dwToken;
        CRITICAL_SECTION m_sect;
        LONG m_nCImageObjects;
    };

    class CDCCache
    {
    public:
        HDC GetDC() throw();
        void ReleaseDC(HDC dc) throw();

    private:
        HDC m_ahDCs[4];
    };

public:
    enum DIBOrientation
    {
        DIBOR_DEFAULT,
        DIBOR_TOPDOWN,
        DIBOR_BOTTOMUP
    };

    enum
    {
        createAlphaChannel = 1
    };

    virtual ~CImage() throw();

    CImage() throw();
    void Attach(HBITMAP bitmap, DIBOrientation orientation) throw();
    BOOL CreateEx(int nWidth, int nHeight, int nBPP, DWORD eCompression,
        const DWORD *pdwBitfields, DWORD dwFlags) throw();
    void Destroy() throw();
    HBITMAP Detach() throw();
    HDC GetDC() const throw();
    void ReleaseDC() const throw();
    void SetColorTable(UINT firstColor, UINT colors, const RGBQUAD *colorTable) throw();

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
    static CInitGDIPlus s_initGDIPlus;
    void UpdateBitmapInfo(DIBOrientation orientation);
};

void CImage::CInitGDIPlus::ReleaseGDIPlus() throw()
{
    EnterCriticalSection(&m_sect);
    if (m_dwToken != 0)
    {
        Gdiplus::GdiplusShutdown(m_dwToken);
    }
    m_dwToken = 0;
    LeaveCriticalSection(&m_sect);
}

void CImage::CInitGDIPlus::IncreaseCImageCount() throw()
{
    EnterCriticalSection(&m_sect);
    ++m_nCImageObjects;
    LeaveCriticalSection(&m_sect);
}

void CImage::CInitGDIPlus::DecreaseCImageCount() throw()
{
    EnterCriticalSection(&m_sect);
    if (--m_nCImageObjects == 0)
        ReleaseGDIPlus();
    LeaveCriticalSection(&m_sect);
}

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

void CImage::ReleaseDC() const throw()
{
    --m_nDCRefCount;
    if (m_nDCRefCount == 0)
    {
        HBITMAP bitmap = (HBITMAP)SelectObject(m_hDC, m_hOldBitmap);
        s_cache.ReleaseDC(m_hDC);
        m_hDC = 0;
    }
}

void CImage::SetColorTable(UINT firstColor, UINT colors, const RGBQUAD *colorTable) throw()
{
    GetDC();
    SetDIBColorTable(m_hDC, firstColor, colors, colorTable);
    ReleaseDC();
}

void CImage::UpdateBitmapInfo(DIBOrientation orientation)
{
    DIBSECTION dibsection;
    int bytes = GetObjectA(m_hBitmap, sizeof(DIBSECTION), &dibsection);

    if (bytes == sizeof(DIBSECTION))
    {
        m_bIsDIBSection = true;
        m_nWidth = dibsection.dsBmih.biWidth;
        m_nHeight = abs(dibsection.dsBmih.biHeight);
        m_nBPP = dibsection.dsBmih.biBitCount;
        m_nPitch = (((m_nWidth * m_nBPP) + 31) / 32) * 4;
        m_pBits = dibsection.dsBm.bmBits;
        if (orientation == DIBOR_DEFAULT)
        {
            orientation = (dibsection.dsBmih.biHeight > 0) ? DIBOR_BOTTOMUP : DIBOR_TOPDOWN;
        }
        if (orientation == DIBOR_BOTTOMUP)
        {
            m_pBits = LPBYTE(m_pBits) + ((m_nHeight - 1) * m_nPitch);
            m_nPitch = -m_nPitch;
        }
    }
    else
    {
        m_bIsDIBSection = false;
        m_nWidth = dibsection.dsBm.bmWidth;
        m_nHeight = dibsection.dsBm.bmHeight;
        m_nBPP = dibsection.dsBm.bmBitsPixel;
        m_nPitch = 0;
        m_pBits = 0;
    }
    m_iTransparentColor = -1;
    m_bHasAlphaChannel = false;
}

CImage::CImage() throw() :
    m_hBitmap(0),
    m_pBits(0),
    m_nWidth(0),
    m_nHeight(0),
    m_nPitch(0),
    m_nBPP(0),
    m_bIsDIBSection(false),
    m_bHasAlphaChannel(false),
    m_iTransparentColor(-1),
    m_hDC(0),
    m_nDCRefCount(0),
    m_hOldBitmap(0)
{
    s_initGDIPlus.IncreaseCImageCount();
}

CImage::~CImage() throw()
{
    Destroy();
    s_initGDIPlus.DecreaseCImageCount();
}

void CImage::Destroy() throw()
{
    if (m_hBitmap != 0)
    {
        DeleteObject(Detach());
    }
}

inline void CImage::Attach(HBITMAP bitmap, DIBOrientation orientation) throw()
{
    m_hBitmap = bitmap;
    UpdateBitmapInfo(orientation);
}

BOOL CImage::CreateEx(int nWidth, int nHeight, int nBPP, DWORD eCompression,
    const DWORD *pdwBitfields, DWORD dwFlags) throw()
{
    USES_ATL_SAFE_ALLOCA;
    LPBITMAPINFO pbmi;
    HBITMAP hBitmap;

    pbmi = (LPBITMAPINFO)_ATL_SAFE_ALLOCA(
        sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
    if (pbmi == 0)
        return FALSE;

    memset(&pbmi->bmiHeader, 0, sizeof(pbmi->bmiHeader));
    pbmi->bmiHeader.biSize = sizeof(pbmi->bmiHeader);
    pbmi->bmiHeader.biWidth = nWidth;
    pbmi->bmiHeader.biHeight = nHeight;
    pbmi->bmiHeader.biPlanes = 1;
    pbmi->bmiHeader.biBitCount = USHORT(nBPP);
    pbmi->bmiHeader.biCompression = eCompression;
    if (nBPP <= 8)
    {
        memset(pbmi->bmiColors, 0, 256 * sizeof(RGBQUAD));
    }
    else
    {
        if (eCompression == BI_BITFIELDS)
        {
            memcpy(pbmi->bmiColors, pdwBitfields, 3 * sizeof(DWORD));
        }
    }

    hBitmap = CreateDIBSection(0, pbmi, DIB_RGB_COLORS, &m_pBits, 0, 0);
    if (hBitmap == 0)
    {
        return FALSE;
    }

    Attach(hBitmap, (nHeight < 0) ? DIBOR_TOPDOWN : DIBOR_BOTTOMUP);

    if (dwFlags & createAlphaChannel)
    {
        m_bHasAlphaChannel = true;
    }

    return TRUE;
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
