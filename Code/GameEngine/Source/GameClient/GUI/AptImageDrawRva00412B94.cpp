// cl: /O1 /arch:SSE /G7 /MD /Oy-
// Ghidra FUN_00812b94, 107B, cdecl RET. GameEngine registers the
// 0x009FE4CC singleton as TheAptPlayer at 0x0022F1D1. Its helper
// 0x00223AC4 (306B RET8) resolves an Image from path/parameter strings;
// 0x00412AF3 (161B cdecl RET) parses the image draw mode from parameters.
// The actual draw uses the rowed W3DDisplay float-coordinate wrapper.
#include "../../../../Libraries/Include/Lib/Coord2D.h"

class Image;
class AptPlayer;
extern AptPlayer *TheAptPlayer;
class Rva00223AC4
{
public:
    Image *rva00223AC4(const char *path, const char *parameters);
};
int Rva00412AF3(const char *parameters);

class Display;
extern Display *TheDisplay;
class W3DDisplay
{
public:
    void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

// ?Rva00412B94@@YAXPBVCoord2D@@0PBD1@Z
void Rva00412B94(const Coord2D *origin, const Coord2D *size,
                 const char *path, const char *parameters)
{
    Image *image = reinterpret_cast<Rva00223AC4 *>(TheAptPlayer)
        ->rva00223AC4(path, parameters);
    if (image)
    {
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3(
            image, origin->x, origin->y, size->x + origin->x,
            size->y + origin->y, -1, Rva00412AF3(parameters));
    }
}
