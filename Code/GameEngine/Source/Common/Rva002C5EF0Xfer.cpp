// cl: /O1 /MD /GX /arch:SSE
// ?rva002C5EF0@Rva002C5EF0@@QAEXPAVXfer@@@Z @0x002C5EF0 117B. Xfer-style persist with Version(1 3) then uint at +0 m_0, Coord at +4, uint at +0x10, float at +0x14, global BfmeTacticalInterestZoneSerial, float at +0x18, version-gated uint at +0x1c. Evidence: unlock lane, slots 0x28 Version 0x78 uint 0x60 Coord 0x70 float match reversed-overload layout, callers 0x002C6429 0x002C64A4 in 0x002C63A1, neighbours DispDwordLeaFieldGetters/Disp8NullAdjustGetters.
class Player;
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
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
class ModuleData;
class Object;
class DamageInfo;

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	unsigned char m_current;
	unsigned char m_minimum;
};

#include "../../../Libraries/Include/Lib/Coord3DBase.h"

extern unsigned int BfmeTacticalInterestZoneSerial;
// BfmeTacticalInterestZoneSerial: matched references place it at VA 0xdfefc8 (loader-zero scalar in .data).
unsigned int BfmeTacticalInterestZoneSerial;

class Rva002C5EF0
{
public:
	Rva002C5EF0(const Coord3DBase &position,float radius,Player *player);
	void rva002C5EF0(Xfer *xfer);
private:
	unsigned int m_0;
	Coord3DBase m_4;
	unsigned int m_10;
	float m_14;
	float m_18;
	unsigned int m_1c;
};

void Rva002C5EF0::rva002C5EF0(Xfer *xfer)
{
	Xfer::Version version;
	version.m_current = 1;
	version.m_minimum = 3;
	*xfer == version;
	*xfer == m_0;
	*xfer == m_4;
	*xfer == m_10;
	*xfer == m_14;
	*xfer == BfmeTacticalInterestZoneSerial;
	*xfer == m_18;
	if (version.m_minimum >= 3)
		*xfer == m_1c;
}

// Complete native2A8808..2A8810 follows RET2A8807 and clears the same
// existing unsigned global used by the verified serializer above. The
// original function spelling and higher-level reset role remain unknown.
void Rva002A8808Clear()
{
    BfmeTacticalInterestZoneSerial=0;
}

// Native2C6234..2C6354 constructs the 32-byte tactical interest-zone record.
// Two ordered writes fix the initial id/position store order; a named template
// pointer retains the native last-use register inside the hit loop.
#include <string.h>
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "PartitionRangeQueryCallView.h"
#include "GameLogicObjectLookupView.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

template<class T> __forceinline volatile T &orderedMemberWrite(T &value)
{
    return *(volatile T *)&value;
}

#include "../../Include/GameLogic/PartitionFilter.h"

// Native BFAD10 slot1 tests effective-death status; donor purpose: alive filter.
#include "../../Include/GameLogic/Rva0026119DFilter.h"

// Native C004D8 slot1 tests player relationship against flags at +0x10.
class Rva00261409Filter : public Rva000421C8
{
public:
    Rva00261409Filter(Player *player, bool match, int flags)
        : m_player(player), m_match(match), m_flags(flags) {}
    virtual bool allow(Object *obj);
    virtual int getPlayerMask();
    Player *m_player;
    bool m_match;
    int m_flags;
};

// Seven native words; N retains the rowed Thing query's existing ABI spelling.
template<int N> class BitFlags
{
public:
    BitFlags() { memset(this, 0, sizeof(*this)); }
    void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
    unsigned int m_bits[7];
};

#include "../../Include/Common/ThingTemplate.h"

#include "Thing/thing.h"

extern PartitionManager *ThePartitionManager;
extern GameLogic *TheGameLogic;

Rva002C5EF0::Rva002C5EF0(const Coord3DBase &position, float radius, Player *player)
{
    const Coord3D *pos = reinterpret_cast<const Coord3D *>(&position);
    orderedMemberWrite(m_0) = ++BfmeTacticalInterestZoneSerial;
    orderedMemberWrite(m_4.x) = pos->x;
    m_4.y = pos->y;
    m_4.z = pos->z;
    m_14 = radius;
    _ReadWriteBarrier();
    m_10 = 0;
    m_18 = 0.0f;
    m_1c = TheGameLogic->getFrame();
    BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos, radius, 0,
        Rva0026119DFilter().link(&Rva00261409Filter(player, true, 4)), 0);
    BitFlags<69> mask;
    mask.set(3);
    mask.set(90);
    Object *obj;
    while ((obj = hits.next()) != 0) {
        if (reinterpret_cast<Thing *>(obj)->isAnyKindOf(mask)) {
            const ThingTemplate *thingTemplate = reinterpret_cast<Thing *>(obj)->m_template;
            m_18 += thingTemplate->m_threatLevel;
        }
    }
}
