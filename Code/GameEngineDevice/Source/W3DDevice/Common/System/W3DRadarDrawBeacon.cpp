// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
// BF1 f98983a7d W3DRadarEventRva006C1280.cpp supplies event projection and
// animation semantics. Target 4DDBF..4DE72 RET24 proves a six-argument member;
// target event records are 80B at +2C, animation table +14A8 and client-frame
// query is slot31. Original method name remains unknown. Keep duration as
// a float local: native retains it on the x87 stack across the size conversion.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "W3DDevice/Common/W3DRadar.h"

extern int BfmeClientFramesPerSecond;
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

void W3DRadar::rva0004DDBF(int x, int y, int w, int h, int i, int unused)
{
    RadarEvent *event = &m_event[i];
    int type = event->type;
    unsigned frame = reinterpret_cast<BeaconClientFrame *>(TheGameClient)->getFrame();
    const float duration = BfmeClientFramesPerSecond * 1.5;
    int size = (int)((1.0f - (float)(frame - event->createFrame) / duration) *
        (w * (2.0f / 3.0f)));
    if (size < 16)
        size = 16;

    ICoord2D pixel;
    radarToPixel(&event->radarLoc, &pixel, x, y, w, h);
    int px = pixel.x - size / 2;
    int py = pixel.y - size / 2;
    m_eventImages[type]->draw(px, py, size, size);
}
