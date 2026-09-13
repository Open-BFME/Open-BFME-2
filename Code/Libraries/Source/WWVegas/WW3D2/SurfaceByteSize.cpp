// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// BFME SurfaceClass is the one-pointer COM owner established by the matched
// surface-level accessor and its caller TextureHandleApply.cpp. The query
// and pixel-size helper retain address-qualified BFME identities.
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
