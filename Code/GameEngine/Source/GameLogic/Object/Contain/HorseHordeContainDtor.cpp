// cl: /DNDEBUG /MD
//
// ??1HorseHordeContain@@UAE@XZ, retail 0x00476653, 87 bytes.
// Slot evidence: ??_G at 0x00476730 (ContainModuleDeletingDtors) calls here.
// Restores 11 vptrs (+0x00 +0x0C +0x10 +0x20 +0x24 +0x28 +0x2C +0x30 +0x34
// +0xFC +0x11C) then tail-jumps to pinned ??1HordeContain@@UAE@XZ at
// 0x0046F901. Low nine match TransportContainDtor ten-vptr pattern (B0-B8)
// and HordeContain base 0x0046F901 (nine shared); derived overrides at +0
// +0x20 +0x11C. No member teardown, no EH. TransportContainDtor precedent.
class Thing;
class ModuleData;
class Object;

class B0 { public: virtual void b0(); private: unsigned char m_pad[8]; };
#include "../../../../Include/Common/B1.h"
#include "../../../../Include/GameLogic/Module/B2.h"
class B3 { public: virtual void b3(); };
#include "../../../../Include/Common/B4.h"
class B5 { public: virtual void b5(); };
class DamageInfo;
enum BodyDamageType;
// The +0x2C interface (GarrisonContain overrides slot 2 as onBodyDamageStateChange):
// retail's table 0x00C58790 holds its three empty defaults (ret 4, ret 4, ret 0Ch).
class B6
{
public:
	virtual void b6(DamageInfo *) { }
	virtual void d01(DamageInfo *) { }
	virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType) { }
};
#include "../../../../Include/Common/B7.h"
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	virtual ~OpenContain();
};

class HFC { public: virtual void hfc(); private: unsigned char m_pad[0x20 - 4]; };
class HLC { public: virtual void hlc(); };

class HordeContain : public OpenContain, public HFC, public HLC
{
public:
	virtual ~HordeContain();
};

class HorseHordeContain : public HordeContain
{
public:
	virtual ~HorseHordeContain();
};

HorseHordeContain::~HorseHordeContain()
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
#pragma comment(linker, "/alternatename:?hfc@HFC@@UAEXXZ=?createPayloadMember@TransportContain@@UAEPAVObject@@PBVThingTemplate@@PAVPayloadContainView@@PAV2@PBDH@Z")
#pragma comment(linker, "/alternatename:?hlc@HLC@@UAEXXZ=?rva00472329@HordeContain@@UAEXPBUCoord3D@@H@Z")
