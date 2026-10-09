// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD /Oy- /EHsc
// Native 0x00412BFF..0x00412DD8 (473B), cdecl RET; sibling of Rva00412B94 and
// 0x00223BF6 on the TheAptPlayer singleton (0x009FE4CC).
// Evidence: strings "RadialClockOverlay1/2" looked up once each through
// TheMappedImageCollection 0x002D92F6 into function statics (guard bits 1/2);
// 0x00223BF6 fills {Real fraction, Image *image}; the overlays are drawn only
// while 0 <= fraction < 1, through the TheDisplay forwarder 0x000A48C4 with
// fraction * 100 as its fifth Real. The second draw's trailing Int is a color
// from TheGlobalData +0x1160, or +0x1164 when the local player's +0x34 record
// has the byte flag at +0x1BC set.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"

class Image;
class AptPlayer;
extern AptPlayer *TheAptPlayer;

struct RadialClockResult
{
    float fraction;
    Image *image;
};

class Rva00223BF6
{
public:
    void rva00223BF6(RadialClockResult *out, const char *path, const char *parameters);
};

class ImageCollection
{
public:
    const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

class Rva000A4826
{
public:
    void rva000A48C4(int a, float b, float c, float d, float e, float f, int g);
};
class Display;
extern Display *TheDisplay;

class PlayerTemplateFlags
{
public:
    char m_pad[0x1BC];
    bool m_flag;
};
class PlayerClockView
{
public:
    char m_pad[0x34];
    PlayerTemplateFlags *m_record;
};
class PlayerListClockView
{
public:
    char m_pad[0x10];
    PlayerClockView *m_local;
};
extern PlayerListClockView *ThePlayerList;

class GlobalDataClockView
{
public:
    char m_pad[0x1160];
    int m_colorA;
    int m_colorB;
};
extern GlobalDataClockView *TheGlobalData;

// ?Rva00412BFF@@YAXPBVCoord2D@@0PBD1@Z
void Rva00412BFF(const Coord2D *origin, const Coord2D *size,
                 const char *path, const char *parameters)
{
    RadialClockResult result;
    reinterpret_cast<Rva00223BF6 *>(TheAptPlayer)
        ->rva00223BF6(&result, path, parameters);
    if (result.fraction >= 0.0f && result.fraction < 1.0f)
    {
        static const Image *overlay1 =
            TheMappedImageCollection->findImageByName(AsciiString("RadialClockOverlay1"));
        static const Image *overlay2 =
            TheMappedImageCollection->findImageByName(AsciiString("RadialClockOverlay2"));

        int color = TheGlobalData->m_colorA;
        if (ThePlayerList && ThePlayerList->m_local && ThePlayerList->m_local->m_record
            && ThePlayerList->m_local->m_record->m_flag)
            color = TheGlobalData->m_colorB;

        if (overlay1 && result.image)
            reinterpret_cast<Rva000A4826 *>(TheDisplay)->rva000A48C4(
                (int)overlay1, origin->x, origin->y, size->x + origin->x,
                size->y + origin->y, result.fraction * 100.0f, (int)result.image);
        if (overlay2)
            reinterpret_cast<Rva000A4826 *>(TheDisplay)->rva000A48C4(
                (int)overlay2, origin->x, origin->y, size->x + origin->x,
                size->y + origin->y, result.fraction * 100.0f, color);
    }
}
