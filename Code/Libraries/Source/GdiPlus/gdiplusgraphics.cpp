// cl: /O1 /GX-
// Microsoft Platform SDK GDI+ 1.0 GdiPlusGraphics.h inlines. Graphics carries
// no vtable, so its two members sit at +0 and +4 and the constructor writes
// lastResult before nativeGraphics - the order the retail body has.

typedef unsigned int size_t;
typedef int INT;

namespace Gdiplus
{

enum Status
{
    Ok = 0
};

class GpGraphics;
class GpImage;

namespace DllExports
{
extern "C" void *__stdcall GdipAlloc(size_t size);
extern "C" void __stdcall GdipFree(void *ptr);
extern "C" Status __stdcall GdipGetImageGraphicsContext(GpImage *image, GpGraphics **graphics);
extern "C" Status __stdcall GdipDrawImageI(GpGraphics *graphics, GpImage *image, INT x, INT y);
}

class GdiplusBase
{
public:
    void(operator delete)(void *in_pVoid) { DllExports::GdipFree(in_pVoid); }
    void *(operator new)(size_t in_size) { return DllExports::GdipAlloc(in_size); }
    void(operator delete[])(void *in_pVoid) { DllExports::GdipFree(in_pVoid); }
    void *(operator new[])(size_t in_size) { return DllExports::GdipAlloc(in_size); }
};

class Image : public GdiplusBase
{
public:
    friend class Graphics;

    virtual ~Image();
    virtual Image *Clone();

protected:
    GpImage *nativeImage;
    mutable Status lastResult;
    mutable Status loadStatus;
};

class Graphics : public GdiplusBase
{
public:
    Graphics(Image *image);

    Status DrawImage(Image *image, INT x, INT y);

protected:
    void SetNativeGraphics(GpGraphics *graphics) { this->nativeGraphics = graphics; }

    Status SetStatus(Status status) const
    {
        if (status != Ok)
            return (lastResult = status);
        else
            return status;
    }

    GpGraphics *nativeGraphics;
    mutable Status lastResult;
};

Graphics::Graphics(Image *image)
{
    GpGraphics *graphics = 0;

    if (image != 0)
    {
        lastResult = DllExports::GdipGetImageGraphicsContext(image->nativeImage, &graphics);
    }
    SetNativeGraphics(graphics);
}

Status Graphics::DrawImage(Image *image, INT x, INT y)
{
    return SetStatus(DllExports::GdipDrawImageI(nativeGraphics,
                                                image ? image->nativeImage : 0,
                                                x,
                                                y));
}

}
