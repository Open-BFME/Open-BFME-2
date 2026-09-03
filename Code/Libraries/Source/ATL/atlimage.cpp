// cl: -O1 -G7
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
typedef long HRESULT;
typedef int BOOL;
typedef unsigned short WORD;
typedef unsigned short USHORT;
typedef unsigned char *LPBYTE;

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
extern "C" __declspec(dllimport) void __cdecl free(void *block);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);
extern "C" void *__cdecl memcpy(void *destination, const void *source, unsigned int size);
extern "C" void *__cdecl _alloca(unsigned int size);
extern "C" __declspec(dllimport) int __cdecl _resetstkoflw(void);
extern "C" unsigned long __cdecl _exception_code(void);
#define GetExceptionCode _exception_code

namespace Gdiplus
{

class GpImage;

typedef int INT;
typedef unsigned long ARGB;

typedef INT PixelFormat;

#define PixelFormatIndexed 0x00010000
#define PixelFormatGDI 0x00020000
#define PixelFormatAlpha 0x00040000
#define PixelFormatPAlpha 0x00080000
#define PixelFormatCanonical 0x00200000

#define PixelFormat32bppRGB (9 | (32 << 8) | PixelFormatGDI)
#define PixelFormat32bppARGB (10 | (32 << 8) | PixelFormatAlpha | PixelFormatGDI | PixelFormatCanonical)

inline UINT GetPixelFormatSize(PixelFormat pixfmt)
{
    return (pixfmt >> 8) & 0xff;
}

inline BOOL IsIndexedPixelFormat(PixelFormat pixfmt)
{
    return (pixfmt & PixelFormatIndexed) != 0;
}

inline BOOL IsAlphaPixelFormat(PixelFormat pixfmt)
{
    return (pixfmt & PixelFormatAlpha) != 0;
}

struct ColorPalette
{
public:
    UINT Flags;
    UINT Count;
    ARGB Entries[1];
};

class BitmapData
{
public:
    UINT Width;
    UINT Height;
    INT Stride;
    PixelFormat PixelFormat;
    void *Scan0;
    unsigned int Reserved;
};

class Rect
{
public:
    Rect(INT x, INT y, INT width, INT height)
    {
        X = x;
        Y = y;
        Width = width;
        Height = height;
    }

    INT X;
    INT Y;
    INT Width;
    INT Height;
};

enum ImageLockMode
{
    ImageLockModeRead = 0x0001
};

class GpGraphics;

enum Status
{
    Ok = 0
};

typedef void(__stdcall *DebugEventProc)(int level, char *message);

struct GdiplusStartupInput
{
    unsigned int GdiplusVersion;
    DebugEventProc DebugEventCallback;
    int SuppressBackgroundThread;
    int SuppressExternalCodecs;

    GdiplusStartupInput(
        DebugEventProc debugEventCallback = 0,
        int suppressBackgroundThread = 0,
        int suppressExternalCodecs = 0)
    {
        GdiplusVersion = 1;
        DebugEventCallback = debugEventCallback;
        SuppressBackgroundThread = suppressBackgroundThread;
        SuppressExternalCodecs = suppressExternalCodecs;
    }
};

extern "C" Status __stdcall GdipDeleteGraphics(GpGraphics *graphics);

typedef Status(__stdcall *NotificationHookProc)(unsigned long *token);
typedef void(__stdcall *NotificationUnhookProc)(unsigned long token);

struct GdiplusStartupOutput
{
    NotificationHookProc NotificationHook;
    NotificationUnhookProc NotificationUnhook;
};

Status __stdcall GdiplusStartup(
    unsigned long *token, const GdiplusStartupInput *input, GdiplusStartupOutput *output);
void __stdcall GdiplusShutdown(unsigned long token);

// Only the pieces CImage::Load touches: the constructor and destructor it
// calls out of line at 0x00001368 and 0x000012A3, and the inline
// GetLastStatus it reads the result through.
class Image
{
public:
    virtual ~Image();
    virtual Image *Clone();

    Status GetLastStatus() const
    {
        Status lastStatus = lastResult;
        lastResult = Ok;
        return lastStatus;
    }

    UINT GetWidth();
    UINT GetHeight();
    PixelFormat GetPixelFormat();
    INT GetPaletteSize();
    Status GetPalette(ColorPalette *palette, INT size);

protected:
    GpImage *nativeImage;
    mutable Status lastResult;
    mutable Status loadStatus;
};

class Bitmap : public Image
{
public:
    Bitmap(const unsigned short *filename, int useEmbeddedColorManagement = 0);
    Bitmap(INT width, INT height, INT stride, PixelFormat format, unsigned char *scan0);

    Status LockBits(const Rect *rect, UINT flags, PixelFormat format, BitmapData *lockedBitmapData);
    Status UnlockBits(BitmapData *lockedBitmapData);
};

class Graphics
{
public:
    Graphics(Image *image);

    ~Graphics()
    {
        GdipDeleteGraphics(nativeGraphics);
    }

    Status DrawImage(Image *image, INT x, INT y);

protected:
    GpGraphics *nativeGraphics;
    mutable Status lastResult;

private:
    Graphics(const Graphics &);
    Graphics &operator=(const Graphics &);
};

}

namespace ATL
{

// atlconv.h's CA2WEX, declared far enough for CImage::Load: retail calls the
// constructor out of line at 0x00002206 and inlines the destructor.
template <int t_nBufferLength = 128>
class CA2WEX
{
public:
    CA2WEX(const char *psz);

    ~CA2WEX()
    {
        if (m_psz != m_szBuffer)
        {
            free(m_psz);
        }
    }

    operator unsigned short *() const { return m_psz; }

public:
    unsigned short *m_psz;
    unsigned short m_szBuffer[t_nBufferLength];

private:
    CA2WEX(const CA2WEX &);
    CA2WEX &operator=(const CA2WEX &);
};

typedef CA2WEX<> CT2W;

template <typename N>
inline N __stdcall AtlAlignUp(N n, unsigned long nAlign) throw()
{
    return (N((n + (nAlign - 1)) & ~(N(nAlign) - 1)));
}

class CCRTAllocator;

namespace _ATL_SAFE_ALLOCA_IMPL
{
// ATL 7.1 verbatim. The margin is _ATL_SAFE_ALLOCA_STACK_MARGIN, 0x2000, and
// it shows in the body as `add eax, 0x2003 / and al, 0xFC` - the probe rounds
// the request up to a dword before handing it to __chkstk. The filter tests
// for STATUS_STACK_OVERFLOW, 0xC00000FD, and the handler calls _resetstkoflw
// so the guard page is usable again. Named by the reloc sweep from the
// _ATL_SAFE_ALLOCA call sites in this same unit.
bool __cdecl _AtlVerifyStackAvailable(unsigned int Size)
{
    bool bStackAvailable = true;
    __try
    {
        void *p = _alloca(Size + 0x2000);
        p;
    }
    __except (GetExceptionCode() == 0xC00000FDL)
    {
        bStackAvailable = false;
        _resetstkoflw();
    }
    return bStackAvailable;
}

template <class Allocator>
class CAtlSafeAllocBufferManager
{
private:
    struct CAtlSafeAllocBufferNode
    {
        CAtlSafeAllocBufferNode *m_pNext;
        unsigned char _pad[4];
    };

    CAtlSafeAllocBufferNode *m_pHead;

public:
    CAtlSafeAllocBufferManager() : m_pHead(0) {}

    void *Allocate(unsigned int nRequestedSize);
    ~CAtlSafeAllocBufferManager();
};
}

}

#define _ATL_SAFE_ALLOCA(nRequestedSize, nThreshold)                                      ((nRequestedSize <= nThreshold &&                                                       ATL::_ATL_SAFE_ALLOCA_IMPL::_AtlVerifyStackAvailable(nRequestedSize))                    ? _alloca(nRequestedSize)                                                             : _AtlSafeAllocaManager.Allocate(nRequestedSize))

#define _ATL_SAFE_ALLOCA_DEF_THRESHOLD 1024

#define FALSE 0
#define TRUE 1
#define BI_BITFIELDS 3
#define DIB_RGB_COLORS 0

namespace ATL
{

class CImage
{
private:
    class CInitGDIPlus
    {
    public:
        bool Init() throw();
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
    static const DWORD createAlphaChannel = 0x01;

    enum DIBOrientation
    {
        DIBOR_DEFAULT,
        DIBOR_TOPDOWN,
        DIBOR_BOTTOMUP
    };

    virtual ~CImage() throw();

    CImage() throw();
    void Attach(HBITMAP bitmap, DIBOrientation orientation) throw();
    void Destroy() throw();
    HBITMAP Detach() throw();
    HDC GetDC() const throw();
    void ReleaseDC() const throw();
    void SetColorTable(UINT firstColor, UINT colors, const RGBQUAD *colorTable) throw();
    BOOL Create(int nWidth, int nHeight, int nBPP, DWORD dwFlags) throw();
    BOOL CreateEx(int nWidth, int nHeight, int nBPP, DWORD eCompression,
        const DWORD *pdwBitfields, DWORD dwFlags) throw();
    HRESULT Load(const char *pszFileName) throw();

    void *GetBits() throw() { return (m_pBits); }
    int GetHeight() const throw() { return (m_nHeight); }
    int GetPitch() const throw() { return (m_nPitch); }
    int GetWidth() const throw() { return (m_nWidth); }
    HRESULT CreateFromGdiplusBitmap(Gdiplus::Bitmap &bmSrc) throw();

    static bool InitGDIPlus() throw()
    {
        return s_initGDIPlus.Init();
    }

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

bool CImage::CInitGDIPlus::Init() throw()
{
    EnterCriticalSection(&m_sect);
    bool fRet = true;
    if (m_dwToken == 0)
    {
        Gdiplus::GdiplusStartupInput input;
        Gdiplus::GdiplusStartupOutput output;
        Gdiplus::Status status = Gdiplus::GdiplusStartup(&m_dwToken, &input, &output);
        if (status != Gdiplus::Ok)
            fRet = false;
    }
    LeaveCriticalSection(&m_sect);
    return fRet;
}

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

BOOL CImage::CreateEx(int nWidth, int nHeight, int nBPP, DWORD eCompression,
    const DWORD *pdwBitfields, DWORD dwFlags) throw()
{
    _ATL_SAFE_ALLOCA_IMPL::CAtlSafeAllocBufferManager<CCRTAllocator> _AtlSafeAllocaManager;
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

BOOL CImage::Create(int nWidth, int nHeight, int nBPP, DWORD dwFlags) throw()
{
    return (CreateEx(nWidth, nHeight, nBPP, 0, 0, dwFlags));
}

HRESULT CImage::Load(const char *pszFileName) throw()
{
    if (!InitGDIPlus())
    {
        return (0x80004005L);
    }

    Gdiplus::Bitmap bmSrc((CT2W)pszFileName);
    if (bmSrc.GetLastStatus() != Gdiplus::Ok)
    {
        return (0x80004005L);
    }

    return (CreateFromGdiplusBitmap(bmSrc));
}

HRESULT CImage::CreateFromGdiplusBitmap(Gdiplus::Bitmap &bmSrc) throw()
{
    Gdiplus::PixelFormat eSrcPixelFormat = bmSrc.GetPixelFormat();
    UINT nBPP = 32;
    DWORD dwFlags = 0;
    Gdiplus::PixelFormat eDestPixelFormat = PixelFormat32bppRGB;
    if (eSrcPixelFormat & PixelFormatGDI)
    {
        nBPP = Gdiplus::GetPixelFormatSize(eSrcPixelFormat);
        eDestPixelFormat = eSrcPixelFormat;
    }
    if (Gdiplus::IsAlphaPixelFormat(eSrcPixelFormat))
    {
        nBPP = 32;
        dwFlags |= createAlphaChannel;
        eDestPixelFormat = PixelFormat32bppARGB;
    }

    BOOL bSuccess = Create(bmSrc.GetWidth(), bmSrc.GetHeight(), nBPP, dwFlags);
    if (!bSuccess)
    {
        return (0x80004005L);
    }
    _ATL_SAFE_ALLOCA_IMPL::CAtlSafeAllocBufferManager<CCRTAllocator> _AtlSafeAllocaManager;
    Gdiplus::ColorPalette *pPalette = 0;
    if (Gdiplus::IsIndexedPixelFormat(eSrcPixelFormat))
    {
        UINT nPaletteSize = bmSrc.GetPaletteSize();

        pPalette = static_cast<Gdiplus::ColorPalette *>(
            _ATL_SAFE_ALLOCA(nPaletteSize, _ATL_SAFE_ALLOCA_DEF_THRESHOLD));
        if (pPalette == 0)
            return 0x8007000EL;

        bmSrc.GetPalette(pPalette, nPaletteSize);

        RGBQUAD argbPalette[256];
        for (UINT iColor = 0; iColor < pPalette->Count; iColor++)
        {
            Gdiplus::ARGB color = pPalette->Entries[iColor];
            argbPalette[iColor].rgbRed = (unsigned char)((color >> 16) & 0xff);
            argbPalette[iColor].rgbGreen = (unsigned char)((color >> 8) & 0xff);
            argbPalette[iColor].rgbBlue = (unsigned char)((color >> 0) & 0xff);
            argbPalette[iColor].rgbReserved = 0;
        }

        SetColorTable(0, pPalette->Count, argbPalette);
    }

    if (eDestPixelFormat == eSrcPixelFormat)
    {
        // The pixel formats are identical, so just memcpy the rows.
        Gdiplus::BitmapData data;
        Gdiplus::Rect rect(0, 0, GetWidth(), GetHeight());
        bmSrc.LockBits(&rect, Gdiplus::ImageLockModeRead, eSrcPixelFormat, &data);

        UINT nBytesPerRow = AtlAlignUp(nBPP * GetWidth(), 8) / 8;
        unsigned char *pbDestRow = static_cast<unsigned char *>(GetBits());
        unsigned char *pbSrcRow = static_cast<unsigned char *>(data.Scan0);
        for (int y = 0; y < GetHeight(); y++)
        {
            memcpy(pbDestRow, pbSrcRow, nBytesPerRow);
            pbDestRow += GetPitch();
            pbSrcRow += data.Stride;
        }

        bmSrc.UnlockBits(&data);
    }
    else
    {
        // Let GDI+ work its magic
        Gdiplus::Bitmap bmDest(GetWidth(), GetHeight(), GetPitch(), eDestPixelFormat,
            static_cast<unsigned char *>(GetBits()));
        Gdiplus::Graphics gDest(&bmDest);

        gDest.DrawImage(&bmSrc, 0, 0);
    }

    return (0);
}

}
