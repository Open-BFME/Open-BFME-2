// Target facts: SurfaceClass's constructor (RVA 0x001165D0) calls _Create_DX8_Surface (0x0011DC60) and stores its result at +0; it has no base calls or vtable stores. Get_Description (0x00116620) dereferences that pointer before calling COM slot 12. SurfaceClass has no retail virtual functions; its one-pointer layout is four bytes, with no RefCountClass base.
// Get_Description copies Format, Width and Height to description offsets +0, +4 and +8 at RVAs 0x0011666C, 0x00116675 and 0x00116672. The other rowed methods are GetSurfaceMemoryUsage (0x00116910), TintSurface (0x00116990), DrawPixel (0x00116C30) and rva00116D10 (0x00116D10); all remain out of line.
// Zero Hour WW3D2/surfaceclass.h names the wrapped pointer D3DSurface and supplies SurfaceDescription's field names; field00 denotes the target's +0 resource pointer. The retail constructor's four arguments include WW3DFormat and _D3DPOOL; the factory (0x0011DC60) obtains an IDirect3DSurface9 through device slot 36. Its COM table belongs to the resource pointed to by +0, not to SurfaceClass.

#ifndef BFME2_WW3D2_SURFACECLASS_H
#define BFME2_WW3D2_SURFACECLASS_H

enum WW3DFormat;
enum _D3DPOOL;
class IDirect3DSurface9;

class SurfaceClass
{
public:
    struct SurfaceDescription
    {
        unsigned int Format;
        unsigned int Width;
        unsigned int Height;
    };

    SurfaceClass(unsigned int width, unsigned int height, WW3DFormat format, _D3DPOOL pool);
    __declspec(noinline) void Get_Description(SurfaceDescription &description);
    unsigned int GetSurfaceMemoryUsage() const;
    void TintSurface(float red, float green, float blue);
    void DrawPixel(unsigned int x, unsigned int y, unsigned int color);
    void rva00116D10(unsigned int x, unsigned int y, unsigned char alpha);

private:
    IDirect3DSurface9 *field00;
};

#endif
