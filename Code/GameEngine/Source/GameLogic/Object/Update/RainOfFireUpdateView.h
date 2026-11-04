// Private RainOfFire views: retail update, xfer and +0x20 interface agree on
// the 0x38-byte layout. Operand declarations stay with BfmeXfer's include.
#ifndef BFME_RAIN_OF_FIRE_UPDATE_VIEW_H
#define BFME_RAIN_OF_FIRE_UPDATE_VIEW_H
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

struct RainOfFireUpdateModuleData
{
    RainOfFireUpdateModuleData();
    void *vtable;
    char pad[4];
    unsigned startRainTime, darknessFadeTime;
    float height, darkness, jitter, dpsMin, dpsMax, rampup;
    Coord2D offset;
};

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
// The two-slot interface is installed at +0x20 by the retail constructors.
class Secondary20
{
public:
    virtual void rvaSlot0(float) = 0;
    virtual void rva004AC135(float) = 0;
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class RainOfFireUpdate : public UpdateModule, public Secondary20
{
public:
    virtual UpdateSleepTime update();
    void rva004AC18D(float);
    virtual void rva004AC135(float);
protected:
    virtual void xfer(Xfer *);
    virtual void loadPostProcess();
public:
    unsigned frame;
    float darkness, scale, pending, ramp;
public:
	virtual NameKeyType getModuleNameKey() const;
};
#endif
