// ?update@FireWeaponUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.92 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// FireWeaponUpdate (BFME 2): the update and its sleep-time helper.
//
// BANKED (partial) FireWeaponUpdate::update 0x0048BEE8 432 B. Same size and
// the whole rotate+add tail now matches; what is left is slot assignment
// (iterator/s/c at -0x14/-0x10/-0x0C vs retail -0x0C/-0x14/-0x10) and the
// multiply operand roles (retail keeps s/c in registers and multiplies by the
// offset in memory). Levers: offset.set(x, y, 0.0f) through the inline
// set(Real,Real,Real) gives retail's y add (addss xmm1,[pos.y] before the
// x store); assigning the fields directly (offset.x = ...; z = 0) instead
// gives retail's multiply operands and slots exactly but loads pos.y first
// (436 B). rotate(s, c) is Coord2D::Rotate-shaped in place, then
// pos.Add(offset, pos) (x = l.x + r.x ...; z = l.z + r.z late-folds to the
// pos.z reload/store). Tried and worse: Coord2D offset + Add(Coord2D,
// Coord3D) (no z store, 422 B), both-temp rotates, set(&m_offset) then z = 0,
// block-copy init, rotate(angle) computing sin/cos inside, sin/cos before set.
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

// class-gate: allow Coord3D the canonical data-only header cannot declare the out-of-line lengthSqr (rowed 0x00065A1A) update calls; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real lengthSqr() const;
	void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
	void set(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	Coord3D &Add(const Coord3D &left, const Coord3D &right) { x = left.x + right.x; y = left.y + right.y; z = left.z + right.z; return *this; }
	void rotate(Real sine, Real cosine) { Real new_x = cosine * x - sine * y; y = cosine * y + sine * x; x = new_x; }
};

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_orientation; }
	// Condition words at +0x11C and +0x124 tested for the hero-mode and
	// charging triggers; bit names unknown.
	Bool testFlag11C4() const { return (m_flags11C >> 4) & 1; }
	Bool testFlag124_28() const { return (m_flags124 >> 28) & 1; }
	Bool isEffectivelyDead() const { return (m_flags438 & 1) != 0; }

private:
	char m_unknown00[0x38];
	Coord3D m_pos; // +0x38
	Real m_orientation; // +0x44
	char m_unknown48[0x11C - 0x48];
	UnsignedInt m_flags11C; // +0x11C
	char m_unknown120[0x124 - 0x120];
	UnsignedInt m_flags124; // +0x124
	char m_unknown128[0x438 - 0x128];
	unsigned char m_flags438; // +0x438
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	Object *forceFireWeapon(const Object *source, const Coord3D *pos);
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

class FireWeaponUpdateModuleData
{
public:
	char m_unknown00[0x0C];
	Bool m_heroModeTrigger; // +0x0C
	Bool m_chargingModeTrigger; // +0x0D
	Bool m_aliveOnly; // +0x0E
};

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
// (Ghidra boundary; sole call at the end of update below). Sleeps until the
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

// ?update@FireWeaponUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048BEE8 432B
// (Ghidra boundary; vtable slot of the +0x10 interface; OilSpillUpdate's
// update calls it first). Skips firing when a set trigger flag is not met
// (hero mode, charging) or the object is dead with AliveOnly; then fires
// the single weapon when ready, else every due nugget entry whose weapon is
// ready, at the object position plus its offset rotated by the object's
// orientation; one-shot entries never fire again.
UpdateSleepTime FireWeaponUpdate::update()
{
	const FireWeaponUpdateModuleData *data = getFireWeaponUpdateModuleData();
	if (data->m_heroModeTrigger && !getObject()->testFlag124_28())
		return rva0048BA3E();
	if (data->m_chargingModeTrigger && !getObject()->testFlag11C4())
		return rva0048BA3E();
	if (data->m_aliveOnly && getObject()->isEffectivelyDead())
		return rva0048BA3E();

	if (m_weapon)
	{
		if (m_weapon->getStatus() == READY_TO_FIRE)
			m_weapon->forceFireWeapon(getObject(), getObject()->getPosition());
	}
	else
	{
		UnsignedInt now = TheGameLogic->getFrame();
		for (_STL::list<FireWeaponEntry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
		{
			FireWeaponEntry *entry = *it;
			if (now > entry->m_nextFireFrame && entry->m_weapon->getStatus() == READY_TO_FIRE)
			{
				Object *me = getObject();
				Coord3D pos;
				pos.set(me->getPosition());
				if (entry->m_offset.lengthSqr() > 0.0f)
				{
					Real angle = me->getOrientation();
					Coord3D offset;
					offset.set(entry->m_offset.x, entry->m_offset.y, 0.0f);
					Real s = (Real)sin(angle);
					Real c = (Real)cos(angle);
					offset.rotate(s, c);
					pos.Add(offset, pos);
				}
				entry->m_weapon->forceFireWeapon(getObject(), &pos);
				if (entry->m_oneShot)
					entry->m_nextFireFrame = 0xFFFFFFFF;
			}
		}
	}
	return rva0048BA3E();
}
