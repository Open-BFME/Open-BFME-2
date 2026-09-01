// cl: /O1
// Microsoft Platform SDK GDI+ 1.0 GdiPlusBitmap.h inlines, emitted out of line
// by the ATL 7.1 CImage translation unit that carries the Gdiplus::Image vtable.

typedef unsigned int size_t;
typedef int INT;

namespace Gdiplus
{

typedef INT Status;
const Status Ok = 0;

class GpImage;

namespace DllExports
{
extern "C" void *__stdcall GdipAlloc(size_t size);
extern "C" void __stdcall GdipFree(void *ptr);
extern "C" Status __stdcall GdipDisposeImage(GpImage *image);
extern "C" Status __stdcall GdipCloneImage(GpImage *image, GpImage **cloneImage);
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
    virtual ~Image();
    virtual Image *Clone();

protected:
    Image() {}
    Image(GpImage *nativeImage, Status status);

    void SetNativeImage(GpImage *nativeImage);

    Status SetStatus(Status status) const
    {
        if (status != Ok)
            return (lastResult = status);
        else
            return status;
    }

    GpImage *nativeImage;
    mutable Status lastResult;
    mutable Status loadStatus;

private:
    Image(const Image &C);
    Image &operator=(const Image &C);
};

Image::~Image()
{
    DllExports::GdipDisposeImage(nativeImage);
}

Image *Image::Clone()
{
    GpImage *cloneimage = 0;

    SetStatus(DllExports::GdipCloneImage(nativeImage, &cloneimage));

    return new Image(cloneimage, lastResult);
}

Image::Image(GpImage *nativeImage, Status status)
{
    SetNativeImage(nativeImage);
    lastResult = status;
}

void Image::SetNativeImage(GpImage *nativeImage)
{
    this->nativeImage = nativeImage;
}

}
