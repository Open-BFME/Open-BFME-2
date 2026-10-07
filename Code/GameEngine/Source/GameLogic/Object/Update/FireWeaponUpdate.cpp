// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// FireWeaponUpdate (BFME 2): the sleep-time helper of update, and xfer.
// update itself (0x0048BEE8, 432 B) is banked in
// reverse/attempts/0x0048bee8.cpp.
//
// Target facts. The module data (ctor row 0x0048BC03, parse table 0xC4C210)
// holds the FireWeaponNugget list at +0x08 and the HeroModeTrigger,
// ChargingModeTrigger and AliveOnly flags at +0x0C/+0x0D/+0x0E. The module
// (ctor row 0x0048C0C5) keeps a single Weapon at +0x20, a list of per-nugget
// entries at +0x24 (0x18-byte records built by the helper 0x0048BDF8: weapon,
// next fire frame, one-shot flag, offset) and a ready flag at +0x28.
// update is reached through the UpdateModuleInterface at +0x10.
// Zero Hour's FireWeaponUpdate::update fires one weapon when isOkayToFire;
// BFME 2 adds the trigger checks and the nugget list, so the bodies here are
// read from retail, with names from the INI field table.

#include <list>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// A reference maximum that compares with '>': retail keeps the entry's frame
// when it is strictly later, which STLport's max (a < b) spells the other way.
template <class T> inline const T &maxOf(const T &a, const T &b) { return a > b ? a : b; }

class Thing;
class ModuleData;
class Object;
class FireWeaponUpdateModuleData;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
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

// MSVC lists a virtual's overloads in reverse declaration order, so
// operator==(Version &) is slot 0x28 and operator==(bool &) slot 0x90.
class Xfer
{
public:
	class Version;

	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3D &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Weapon : public Snapshot
{
public:
	UnsignedInt getPossibleNextShotFrame() const { return m_whenWeCanFireAgain; }

private:
	char m_unknown04[0x18 - 0x04];
	UnsignedInt m_whenWeCanFireAgain; // +0x18
};

class WeaponTemplate;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
};

extern WeaponStore *TheWeaponStore;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_unknown00[0x40];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// One FireWeaponNugget instance (0x18 bytes, built by 0x0048BDF8).
struct FireWeaponEntry
{
	Weapon *m_weapon;
	UnsignedInt m_nextFireFrame; // +0x04
	Bool m_oneShot; // +0x08
	Coord3D m_offset; // +0x0C
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	void xfer(Xfer *xfer);

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class FireWeaponUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

protected:
	virtual void xfer(Xfer *xfer);
	UpdateSleepTime rva0048BA3E();
	const FireWeaponUpdateModuleData *getFireWeaponUpdateModuleData() const
	{
		return (const FireWeaponUpdateModuleData *)m_moduleData;
	}

private:
	Weapon *m_weapon; // +0x20
	_STL::list<FireWeaponEntry *> m_entries; // +0x24
	Bool m_entriesReady; // +0x28
};

// ?rva0048BA3E@FireWeaponUpdate@@IAE?AW4UpdateSleepTime@@XZ @0x0048BA3E 105B
// (Ghidra boundary; called at every exit of update 0x0048BEE8). Sleeps until the
// earliest frame any entry may fire again: the later of its weapon's next
// shot frame (Weapon +0x18) and its own next fire frame, minimised over the
// list; forever when the list is empty. Method name unknown.
UpdateSleepTime FireWeaponUpdate::rva0048BA3E()
{
	UnsignedInt next = 0xFFFFFFFF;
	for (_STL::list<FireWeaponEntry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
	{
		FireWeaponEntry *entry = *it;
		UnsignedInt frame = maxOf(entry->m_nextFireFrame, entry->m_weapon->getPossibleNextShotFrame());
		next = _STL::min(frame, next);
	}
	if (next == 0xFFFFFFFF)
		return UPDATE_SLEEP_FOREVER;
	UnsignedInt now = TheGameLogic->getFrame();
	if (next <= now)
		return UPDATE_SLEEP_NONE;
	return (UpdateSleepTime)(next - now);
}

// ?xfer@FireWeaponUpdate@@MAEXPAVXfer@@@Z @0x0048BAA7 332B (Ghidra boundary;
// slot 3 of the primary vftable 0x00C4C198, called as the base by
// OilSpillUpdate::xfer). Version 2 before the rowed UpdateModule::xfer; the
// single weapon (allocated through TheWeaponStore on load) is skipped by a
// light CRC; version 2 adds the ready flag and, per entry, its one-shot flag,
// next fire frame, offset and weapon snapshot, in two identical loops for
// load and save.
void FireWeaponUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	UpdateModule::xfer(xfer);
	if (!xfer->IsLightCRC())
	{
		Bool hasWeapon = m_weapon != NULL;
		*xfer == hasWeapon;
		if (hasWeapon)
		{
			if (xfer->IsLoading())
				m_weapon = TheWeaponStore->allocateNewWeapon(NULL, PRIMARY_WEAPON);
			*xfer == *m_weapon;
		}
	}
	if (version.m_minimum >= 2)
	{
		*xfer == m_entriesReady;
		if (xfer->IsLoading())
		{
			for (_STL::list<FireWeaponEntry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
			{
				FireWeaponEntry *entry = *it;
				*xfer == entry->m_oneShot;
				*xfer == entry->m_nextFireFrame;
				*xfer == entry->m_offset;
				*xfer == *entry->m_weapon;
			}
		}
		else if (xfer->IsStoring())
		{
			for (_STL::list<FireWeaponEntry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
			{
				FireWeaponEntry *entry = *it;
				*xfer == entry->m_oneShot;
				*xfer == entry->m_nextFireFrame;
				*xfer == entry->m_offset;
				*xfer == *entry->m_weapon;
			}
		}
	}
}
