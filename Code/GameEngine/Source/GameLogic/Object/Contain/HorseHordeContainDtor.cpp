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
#include "../../../../Include/Common/B5.h"
class DamageInfo;
enum BodyDamageType;
// The +0x2C interface (GarrisonContain overrides slot 2 as onBodyDamageStateChange):
// retail's table 0x00C58790 holds its three empty defaults (ret 4, ret 4, ret 0Ch).
#include "../../../../Include/Common/B6.h"
#include "../../../../Include/Common/B7.h"
#include "../../../../Include/Common/B8.h"

#include "../../../../Include/GameLogic/Module/TransportContain.h"

class ThingTemplate;
class PayloadContainView;
struct Coord3D;
// The +0xFC interface: retail's one-slot table 0x00C47834 holds the rowed
// TransportContain::createPayloadMember (0x00466FE0, TransportContain.cpp).
class HFC { public: virtual Object *createPayloadMember(const ThingTemplate *, PayloadContainView *, Object *, const char *, int) = 0; private: unsigned char m_pad[0x20 - 4]; };
// The +0x11C interface: slot 0 of retail's table 0x00C45838 is the rowed
// HordeContain::rva00472329 (0x00472329, HordeContainIface11CSlots.cpp).
class HLC { public: virtual void rva00472329(const Coord3D *, int) = 0; };


class HordeContain : public TransportContain, public HLC
{
public:
	virtual ~HordeContain();
	virtual void rva00472329(const Coord3D *, int);	// 0x00472329
};

class HorseHordeContain : public HordeContain
{
public:
	virtual ~HorseHordeContain();
};

HorseHordeContain::~HorseHordeContain()
{
}
