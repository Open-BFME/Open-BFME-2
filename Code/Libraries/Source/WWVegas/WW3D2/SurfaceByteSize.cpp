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
