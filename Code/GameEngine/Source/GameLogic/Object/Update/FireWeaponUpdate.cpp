// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// FireWeaponUpdate (BFME 2): the sleep-time helper of update. update itself
// (0x0048BEE8, 432 B) is banked in reverse/attempts/0x0048bee8.cpp.
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

class Weapon
{
public:
	UnsignedInt getPossibleNextShotFrame() const { return m_whenWeCanFireAgain; }

private:
	char m_unknown00[0x18];
	UnsignedInt m_whenWeCanFireAgain; // +0x18
};

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
	Real m_offset[3]; // +0x0C, a Coord3D
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
