// cl: /O1 /G7 /DNDEBUG /MD
//
// ??0CastleMemberBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00395B66, 73 bytes.
// CastleMemberBehavior behavior ctor over the rowed BehaviorModule base
// (0x253330, thing plus data): forwards both args to the base, stores the
// first +0x10 slot value, zeroes +0x14/+0x18/+0x1C and the bytes at
// +0x24/+0x25, then re-stores the primary vtable slot and the +0x0C/+0x10
// secondary slots (address-of TU-local dummies, DIR32-masked) and stores 1
// at +0x20. The double +0x10 store uses the ToggleMounted union-plus-barrier
// shape so retail keeps both. The rowed instance factory 0x24AAEE
// (news 0x28) is the sole raw caller. Row supersedes the ctor pin.

class Xfer;
class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" const void *const __identifier("??_7Rva002B0F3CIface@@6B@")[];
// Retail stores 0x00C1A22C (+0) and 0x00C1A170 (+0x0C); the data ledger binds
// CastleMemberBehavior.cpp's compiled tables there.
extern "C" const void *const __identifier("??_7CastleMemberBehavior@@6BRva0049B47C@@@")[];
extern "C" const void *const __identifier("??_7CastleMemberBehavior@@6BMiBase1@@@")[];
// Retail table 0x00C1A160 (+0x10, 3 slots). The ledger binds
// ??_7CastleMemberBehavior@@6B@ there, but this unit's own two-slot view of the
// class owns that name (naming it emits a conflicting copy), so the unit owns
// the complete initialized table (Rva004DF324Dtor.cpp s_10 precedent): each
// slot names a matched row at retail's slot target, taken by address and never
// called through these erased signatures.
extern "C" {
void __identifier("?rva0039922D@CastleBehavior@@QAEXPAURva00398E4AArg@@@Z")();
void __identifier("?slot0@Rva0086EE20@@UAEXH@Z")();
void __identifier("?onStateChanged@Rva00397BD9@@UAEXHHH@Z")();
}
static const void *const s_secondary10[3] = {
	(const void *)&__identifier("?rva0039922D@CastleBehavior@@QAEXPAURva00398E4AArg@@@Z"), //  0 0x0039922D
	(const void *)&__identifier("?slot0@Rva0086EE20@@UAEXH@Z"), //  1 0x0047A69C
	(const void *)&__identifier("?onStateChanged@Rva00397BD9@@UAEXHHH@Z")  //  2 0x00397BD9
};

// Opaque BehaviorModule base; ctor resolves to its row. Its virtual
// destructor gives the classes their real vptr at +0. CastleMemberBehavior is
// novtable: its ctor stores the three tables by hand, after the field
// stores, so body order is source order (retail's order).
class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	virtual ~BehaviorModule();
	protected: virtual void xfer(Xfer*);

protected:
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
};

class __declspec(novtable) CastleMemberBehavior : public BehaviorModule
{
public:
	CastleMemberBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer*);

private:
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	unsigned char m_25;
	unsigned char m_pad26[0x28 - 0x26];
};

// ??0CastleMemberBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x395B66
CastleMemberBehavior::CastleMemberBehavior(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData)
{
	*(const void **)((char *)this + 0x10) = __identifier("??_7Rva002B0F3CIface@@6B@");
	_ReadWriteBarrier();
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_24 = 0;
	m_25 = 0;
	*(const void **)this = __identifier("??_7CastleMemberBehavior@@6BRva0049B47C@@@");
	m_p0C = __identifier("??_7CastleMemberBehavior@@6BMiBase1@@@");
	m_p10 = s_secondary10;
	m_20 = 1;
}

// Native3957C6..39585A is the complete148B snapshot transfer. The named
// factory/constructor/pool-key and literal getter independently establish
// CastleMemberBehavior; field14/18 IDs,1C unsigned,24/25 flags and20 audio
// handle are native access facts. Pre/base/post order is target-specific.
// Existing XferObjectID3060B2 and BehaviorModule4C9C7D supply owned calls.
// The following vtable slot views describe only the invoked ABI; original
// transfer method name and the unaccessed virtual slots remain unknown.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
 unsigned char loaded,current;
};
#include "../../../../Include/Common/GameAudio.h"
extern AudioManager* TheAudio;
enum ObjectID { INVALID_ID=0 };
void XferObjectID(Xfer*, ObjectID*);
void CastleMemberBehavior::xfer(Xfer* xfer) {
 Xfer::Version v; v.loaded = 1; v.current = 1; *xfer == v;
 XferObjectID(xfer,reinterpret_cast<ObjectID*>(&m_14));
 *xfer == reinterpret_cast<bool &>(m_24);
 *xfer == reinterpret_cast<unsigned &>(m_1C);
 XferObjectID(xfer,reinterpret_cast<ObjectID*>(&m_18));
 BehaviorModule::xfer(xfer);
 XferObjectID(xfer,reinterpret_cast<ObjectID*>(&m_18));
 *xfer == reinterpret_cast<unsigned &>(m_1C);
 *xfer == reinterpret_cast<bool &>(m_25);
 TheAudio->xferAudioHandle(xfer,reinterpret_cast<unsigned*>(&m_20));
}
