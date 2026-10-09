// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// BF1 f98983a7d W3DRadarEventRva006C1280.cpp supplies event projection and
// animation semantics. Target 4DDBF..4DE72 RET24 proves a six-argument member;
// target event records are 80B at +2C, animation table +14A8 and client-frame
// query is slot31. Original method name remains unknown. Keep duration as
// a float local: native retains it on the x87 stack across the size conversion.
struct ICoord2D { int x,y; };
extern int g_009BA4E8;
class Anim2D
{
public:
    void draw(int, int, int, int);
};

class BeaconClientFrame
{
public:
#define SLOT(N) virtual void slot##N();
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6)
    SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12)
    SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18)
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
#undef SLOT
    virtual unsigned getFrame();
};

class GameClient;
extern GameClient *TheGameClient;

struct BeaconEventRecord
{
    int type;
    unsigned field04, frame;
    char pad0c[0x34];
    ICoord2D radarLoc;
    char pad48[8];
};

class W3DRadar
{
public:
    char pad00[0x2C];
    BeaconEventRecord events[64];
    char pad142c[0x7C];
    Anim2D *images[16];

    void rva0004DDBF(int, int, int, int, int, int);

protected:
    void radarToPixel(const ICoord2D *, ICoord2D *, int,int,int,int);
};

void W3DRadar::rva0004DDBF(int x, int y, int w, int h, int i, int unused)
{
    BeaconEventRecord *event = &events[i];
    int type = event->type;
    unsigned frame = reinterpret_cast<BeaconClientFrame *>(TheGameClient)->getFrame();
    const float duration = g_009BA4E8 * 1.5;
    int size = (int)((1.0f - (float)(frame - event->frame) / duration) *
        (w * (2.0f / 3.0f)));
    if (size < 16)
        size = 16;

    ICoord2D pixel;
    radarToPixel(&event->radarLoc, &pixel, x, y, w, h);
    int px = pixel.x - size / 2;
    int py = pixel.y - size / 2;
    images[type]->draw(px, py, size, size);
}
