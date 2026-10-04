// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /G7
// BFME SurfaceClass is the one-pointer COM owner established by the matched
// surface-level accessor and its caller TextureHandleApply.cpp. The query
// and pixel-size helper retain address-qualified BFME identities. /G7 is
// what selects the cmp-mem null check (83 39 00) over mov+test in the byte
// size query; without it the head diverges by three bytes.
class SurfaceClass
{
public:
    struct SurfaceDescription
    {
        unsigned int Format;
        unsigned int Width;
        unsigned int Height;
    };
    void Get_Description(SurfaceDescription &description);
    unsigned int Rva008FCA30_Surface_Byte_Size() const;
    void DrawPixel(unsigned int x, unsigned int y, unsigned int color);
    void rva00116D10(unsigned int x, unsigned int y, unsigned int alpha);
private:
    void *surface;
};

// Keep the actual caller with this local helper: MSVC 7.1 passes the
// description address in ECX and emits the retail selector-register choice.
// The helper stays out of line, as in retail. Its historical name is unknown.
static __declspec(noinline) unsigned int Rva008FC4F0_PixelSize(
    const SurfaceClass::SurfaceDescription &description)
{
    unsigned int size = 0;
    switch (description.Format)
    {
    case 21: case 22: // A8R8G8B8, X8R8G8B8
        size = 4;
        break;
    case 20: // R8G8B8
        size = 3;
        break;
    case 23: case 24: case 25: case 26: case 29: case 30: case 40: case 51:
        size = 2;
        break;
    case 27: case 28: case 41: case 50: case 52:
        size = 1;
        break;
    }
    return size;
}

unsigned int SurfaceClass::Rva008FCA30_Surface_Byte_Size() const
{
    if (!surface)
        return 0;
    SurfaceDescription description;
    const_cast<SurfaceClass *>(this)->Get_Description(description);
    unsigned int pixelSize = Rva008FC4F0_PixelSize(description);
    if (pixelSize)
        return description.Width * description.Height * pixelSize;
    if (description.Format != 0x31545844 && description.Format != 0x32545844 &&
        description.Format != 0x33545844 && description.Format != 0x34545844 &&
        description.Format != 0x35545844)
        return 0;
    unsigned int size = description.Width * description.Height;
    if (description.Format == 0x31545844)
        size /= 2;
    return size;
}

// ?Get_Description@SurfaceClass@@QAEXAAUSurfaceDescription@1@@Z, retail 0x00116620 (94B).
// The surface is a COM object: GetDesc is the __stdcall slot-12 virtual, so
// retail pushes (desc, this) with callee cleanup. D3DSURFACE_DESC is 32 bytes
// with Format/Width/Height at +0/+0x18/+0x1c; the null-surface path leaves
// the caller's description untouched. The memset intrinsic is what emits the
// retail xor-plus-eight-movs zeroing (brace init sinks the first store).
#include <string.h>
typedef long HRESULT;
struct D3DSurfaceDesc
{
    unsigned int Format;
    unsigned int Type;
    unsigned int Usage;
    unsigned int Pool;
    unsigned int Size;
    unsigned int MultiSampleType;
    unsigned int Width;
    unsigned int Height;
};
class D3DSurface
{
public:
#define V(n) virtual HRESULT __stdcall v##n() = 0;
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11)
#undef V
    virtual HRESULT __stdcall GetDesc(D3DSurfaceDesc *desc) = 0;
    virtual HRESULT __stdcall LockRect(void *locked, void *rect, unsigned flags) = 0;
    virtual HRESULT __stdcall UnlockRect() = 0;
};
void Log_DX8_ErrorCode(unsigned int code);
void SurfaceClass::Get_Description(SurfaceDescription &description)
{
    D3DSurfaceDesc d3dDesc;
    memset(&d3dDesc, 0, sizeof(d3dDesc));
    D3DSurface *d3dSurface = (D3DSurface *)surface;
    if (!d3dSurface)
        return;
    HRESULT hr = d3dSurface->GetDesc(&d3dDesc);
    if (hr != 0)
        Log_DX8_ErrorCode((unsigned int)hr);
    description.Format = d3dDesc.Format;
    description.Height = d3dDesc.Height;
    description.Width = d3dDesc.Width;
}

// ?rva00116680@Rva00116680@@QAEPAXPAH_N@Z, retail 0x00116680 (87B).
// Evidence: unlock lane (unblocks 5, incl 0x001321A7/1347 0x00158E90/2129);
// 9 jmp/call callers in unclaimed; Lock slot 0x34 with discard-derived flags
// 0x0800/0x2800 and pitch-out plus bits return; same TU/flags as neighbours.
struct D3DLockedRect
{
    int Pitch;
    void *pBits;
};
class Rva00116680
{
public:
    void *rva00116680(int *pitchOut, bool discard);
private:
    void *m_surface;
};

void *Rva00116680::rva00116680(int *pitchOut, bool discard)
{
    void *surf = m_surface;
    if (!surf)
        return 0;
    D3DLockedRect locked;
    memset(&locked, 0, sizeof(locked));
    D3DSurface *s = (D3DSurface *)surf;
    unsigned flags = discard ? 0x2000 : 0;
    flags |= 0x0800;
    HRESULT hr = s->LockRect(&locked, 0, flags);
    if (hr != 0)
        Log_DX8_ErrorCode((unsigned int)hr);
    *pitchOut = locked.Pitch;
    return locked.pBits;
}

// ?rva001166E0@Rva001166E0@@QAEPAXPAHHHHH@Z, retail 0x001166E0 (120B).
// Evidence: unlock lane unblocks 5 incl 0x001321A7 and 0x00158E90;
// 6 callers in unclaimed with 5 pushes plus ecx; Lock slot 0x34 with rect
// and hardcoded 0x0800 plus pitch-out and bits return; same TU and flags.
struct BfmeRect
{
    int left;
    int top;
    int right;
    int bottom;
};
class Rva001166E0
{
public:
    void *rva001166E0(int *pitchOut, int left, int top, int right, int bottom);
private:
    void *m_surface;
};

void *Rva001166E0::rva001166E0(int *pitchOut, int left, int top, int right, int bottom)
{
    D3DLockedRect locked;
    BfmeRect rect;
    rect.top = top;
    rect.left = left;
    rect.right = right;
    rect.bottom = bottom;
    memset(&locked, 0, sizeof(locked));
    D3DSurface *s = (D3DSurface *)m_surface;
    HRESULT hr = s->LockRect(&locked, &rect, 0x800);
    if (hr != 0)
        Log_DX8_ErrorCode((unsigned int)hr);
    *pitchOut = locked.Pitch;
    return locked.pBits;
}

// ?DrawPixel@SurfaceClass@@QAEXIII@Z, retail 0x00116C30 (210B).
// Evidence: unlock lane unblocks 9 incl 0x00050125; 15 callers with 3 args;
// Lock slot 0x34 with rect plus Unlock slot 0x38; pixel-size 1/2/4 switch;
// BFME1 surfaceclass.cpp DrawPixel donor; same TU and flags.
void SurfaceClass::DrawPixel(unsigned int x, unsigned int y, unsigned int color)
{
    if (!surface)
        return;
    SurfaceDescription sd;
    Get_Description(sd);
    unsigned int size = Rva008FC4F0_PixelSize(sd);
    D3DLockedRect locked;
    memset(&locked, 0, sizeof(locked));
    BfmeRect rect;
    memset(&rect, 0, sizeof(rect));
    rect.bottom = (int)(y + 1);
    rect.top = (int)y;
    rect.left = (int)x;
    rect.right = (int)(x + 1);
    HRESULT hr = ((D3DSurface *)surface)->LockRect(&locked, &rect, 0);
    if (hr != 0)
        Log_DX8_ErrorCode((unsigned int)hr);
    unsigned char *cptr = (unsigned char *)locked.pBits;
    unsigned short *sptr = (unsigned short *)locked.pBits;
    unsigned int *lptr = (unsigned int *)locked.pBits;
    switch (size)
    {
    case 1:
        *cptr = (unsigned char)(color & 0xFF);
        break;
    case 2:
        *sptr = (unsigned short)(color & 0xFFFF);
        break;
    case 4:
        *lptr = color;
        break;
    }
    hr = ((D3DSurface *)surface)->UnlockRect();
    if (hr != 0)
        Log_DX8_ErrorCode((unsigned int)hr);
}

// ?SurfaceClass::rva00116D10 present-unmatched
// Native 0x00116D10..0x00116DB2: the DrawPixel sibling that changes only
// the high byte of an A8R8G8B8 pixel. Surface ownership, Get_Description,
// COM slots 13/14 and the rectangle layout agree with the matched sibling.
// The historical method name is unknown. The rectangle/lock sequence follows
// Open-BFME-1 6583b3c1ff SurfaceClass_DrawPixel.cpp; the format-21 test and
// single byte store are established directly from BFME2 retail.
void SurfaceClass::rva00116D10(unsigned int x, unsigned int y, unsigned int alpha)
{
    if (!surface)
        return;
    SurfaceDescription sd;
    Get_Description(sd);
    D3DLockedRect locked;
    memset(&locked, 0, sizeof(locked));
    BfmeRect rect;
    memset(&rect, 0, sizeof(rect));
    rect.bottom = (int)(y + 1);
    rect.top = (int)y;
    rect.left = (int)x;
    rect.right = (int)(x + 1);
    HRESULT hr = ((D3DSurface *)surface)->LockRect(&locked, &rect, 0);
    if (hr != 0)
        Log_DX8_ErrorCode((unsigned int)hr);
    if (sd.Format == 21)
        ((unsigned char *)locked.pBits)[3] = (unsigned char)alpha;
    hr = ((D3DSurface *)surface)->UnlockRect();
    if (hr != 0)
        Log_DX8_ErrorCode((unsigned int)hr);
}
