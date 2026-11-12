// cl: /DNDEBUG /MD
//
// ??1TunnelContain@@UAE@XZ retail 0x0047DB00 67 bytes.
// TunnelContain public virtual destructor over GarrisonContain base 0x00478067.
// Restores nine vtable slots at +0x00 +0x0C +0x10 +0x20 +0x24 +0x28 +0x2C +0x30 +0x34
// then tail-jumps to base dtor.
// Donor ZH TunnelContain empty dtor.
// Identity via deleting wrapper 0x0047DC5C slot0 vtable 0x00C47740
// and pool key 0x0047DB43 with TunnelContain string.
// Layout from ctor 0x0047DBF7 base HordeGarrisonContain plus bytes at 0x9E4.
// Shape follows CaveContainDtor plus GarrisonContainDtor precedent.

class B0 { public: virtual void b0(); private: unsigned char m_pad[8]; };
#include "../../../../Include/Common/B1.h"
#include "../../../../Include/GameLogic/Module/B2.h"
class B3 { public: virtual void b3(); };
#include "../../../../Include/Common/B4.h"
#include "../../../../Include/Common/B5.h"
class DamageInfo;
enum BodyDamageType;
// The +0x2C interface: retail's GarrisonContain-family table 0x00C463D8 keeps its two
// empty one-argument defaults (ret 4) and GarrisonContain's slot-2 override.
#include "../../../../Include/Common/B6.h"
#include "../../../../Include/Common/B7.h"
#include "../../../../Include/Common/B8.h"

class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	virtual ~OpenContain();
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class GarrisonContain : public OpenContain
{
public:
	virtual ~GarrisonContain();
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState); // the rowed 0x0047876A

private:
	unsigned char m_padFC424[0x424 - 0xFC];
	Coord3D m_garrisonPoint[120];
	unsigned char m_tail[0x9E0 - 0x9C4];
};

class TunnelContain : public GarrisonContain
{
public:
	virtual ~TunnelContain();
};

TunnelContain::~TunnelContain()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?b1@B1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?b0@B0@@UAEXXZ=??_GTunnelContain@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?b2@B2@@UAEXXZ=?update@TunnelContain@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?b3@B3@@UAEXXZ=?rva0046261B@SlaughterHordeContain@@UAEX_N@Z")
#pragma comment(linker, "/alternatename:?b4@B4@@UAEXXZ=?rva004628D1@Rva004628D1@@UAEXPAVObject@@HH@Z")
#pragma comment(linker, "/alternatename:?b5@B5@@UAEXXZ=?onDie@TunnelContain@@UAEXPBVDamageInfo@@@Z")
#pragma comment(linker, "/alternatename:?b7@B7@@UAEXXZ=?isExitBusy@HordeGarrisonContain@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?b8@B8@@UAEXXZ=??1Region2D@@QAE@XZ")
