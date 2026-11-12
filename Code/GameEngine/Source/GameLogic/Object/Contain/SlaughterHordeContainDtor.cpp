// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1SlaughterHordeContain@@UAE@XZ, retail 0x004803FB, 118 bytes.
// Virtual dtor over vtable 0x00C48AA0 (slot 0 deleting dtor at 0x00480645
// calls this body). Restores nine vtable slots at +0x00 +0x0C +0x10 +0x20
// +0x24 +0x28 +0x2C +0x30 +0x34 (DIR32), destroys the AsciiString at +0x9E8
// through the pinned 0x00036410 dtor (single tracked member state 0), then
// calls the rowed GarrisonContain base dtor at 0x00478067. Layout from the
// rowed ctor 0x0048034E (HordeGarrisonContain base, m_9E4 int cleared, m_9E8
// cleared string null, factory 0x0024C036 news 0x9EC) over the GarrisonContain
// 0x9E0 shape (Coord3D array at +0x424). Shape follows GarrisonContainDtor
// (TU-local nine-base OpenContain chain with inline Coord3D, empty derived
// body, entry derived stores kept so no novtable).

class B0 { public: virtual void b0(); private: unsigned char m_pad[8]; };
#include "../../../../Include/Common/B1.h"
#include "../../../../Include/GameLogic/Module/B2.h"
class B3 { public: virtual void b3(); };
#include "../../../../Include/Common/B4.h"
class B5 { public: virtual void b5(); };
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

#include "ascii_string.h"

class SlaughterHordeContain : public GarrisonContain
{
public:
	virtual ~SlaughterHordeContain();

private:
	int m_pad9E0; // +0x9E0 (Horde intermediate pad)
	int m_9E4; // +0x9E4
	AsciiString m_str9E8; // +0x9E8
};

SlaughterHordeContain::~SlaughterHordeContain()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?b0@B0@@UAEXXZ=??_GSlaughterHordeContain@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?b2@B2@@UAEXXZ=?update@SlaughterHordeContain@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?b5@B5@@UAEXXZ=?onDie@CitadelSlaughterHordeContain@@UAEXPBVDamageInfo@@@Z")
#pragma comment(linker, "/alternatename:?b7@B7@@UAEXXZ=?isExitBusy@HordeGarrisonContain@@UBE_NXZ")
