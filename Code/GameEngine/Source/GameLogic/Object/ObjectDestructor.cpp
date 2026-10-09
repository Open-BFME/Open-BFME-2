// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// ??1Object@@MAE@XZ retail 0x00299CE4 (962 bytes; pinned placeholder
// ??1Rva00299CE4@@UAE@XZ).
//
// Identity: WorldBuilder twin 0x00CBE740 is Object::~Object (Object.cpp,
// asserts lines 811..933) and its callees map one to one; the scalar deleting
// destructor 0x0029A10F (vtable 0x00BFC300 slot 7) calls this body. It
// installs Object's five vftables (0x00BFC300 +0x00, 0x00BFC2F0 +0x60,
// 0x00BFC2D8 +0x64, 0x00BFC2B8 +0x6C, 0x00BFC290 +0x70), the virtual base's
// 0x00BFC27C through the vbptr at +0x68 and the vtordisp at vbase-4, then runs
// the Zero Hour Object::~Object statements with BFME's additions, destroys
// fourteen members (EH states 14..1), resets the Snapshot vftable 0x00BBB554
// at +0x60 and calls the Thing destructor 0x0030A120.
// Donor: Open-BFME-1 game/GameEngine/Source/GameLogic/Object/
// ObjectDestructor.cpp (BFME1 0x001D4010, same base shape and statement
// order). Target facts: offsets (+0x54 from BFME1 past +0x1E8 and more past
// +0x2B8), the KindOf bits 190/144/90/25/89 of the template's set at +0x108
// with no override chain, the CreateAHero save on a local player's hero, the
// non-virtual ScriptEngine notifications, the partition removal through the
// +0x64 base, the +0xA4 owned list and the trailing +0x494..+0x4B4 members.
// Field names follow the donor and Zero Hour where the statement matches.
// Codegen notes: the owned modules go through ::delete (virtual destructor
// with flag 0 then the global operator delete); the +0x64 base pointer for
// the partition call comes from an inline member of that base, and the
// radar override source is read once into a local, which keeps EDI as the
// zero register and pushes EBX late as retail does. GameLogic is the
// canonical view (GameLogicObjectLookupView.h), which needs a
// sendObjectDestroyed declaration (0x0023CD67).

#include "ascii_string.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "Common/Snapshot.h"
#include "../../Common/GameLogicObjectLookupView.h"

void free(void *);
void operator delete[](void *);

class Team;
class Player
{
public:
	bool isLocalPlayer() const;
};

enum ObjectStatusTypes { OBJECT_STATUS_0x33 = 0x33 };

// KindOf bits the body tests, by position only.
enum Rva00299CE4Kind { KIND_25 = 25, KIND_89 = 89, KIND_90 = 90, KIND_144 = 144, KIND_190 = 190 };

struct Rva00299CE4Template
{
	unsigned char m_unmodelled000[0x108];
	unsigned int m_kindOf[14];						// +0x108
	__forceinline bool isKindOf(Rva00299CE4Kind kind) const
	{
		return (m_kindOf[(unsigned int)kind >> 5] & (1 << (kind & 31))) != 0;
	}
};

// Thing (destructor 0x0030A120, 0x60 bytes): primary vftable, template at +4.
class Rva0030A120
{
public:
	virtual ~Rva0030A120();
	const Rva00299CE4Template *m_template;			// +0x04
	unsigned char m_unmodelled008[0x58];
};

// Base subobjects Object installs vftables for.
struct Rva00BFC27CVirtualBase
{
	virtual void vbaseSlot0();
};
class Rva00739770 { public: void rva00739770(void *obj); };
class PartitionManager;
extern PartitionManager *TheShroudManager;
struct Rva00BFC2D8Base : virtual Rva00BFC27CVirtualBase
{
	virtual void base064Slot0();
	void unregisterFromPartition() { ((Rva00739770 *)TheShroudManager)->rva00739770(this); }
};
struct Rva00BFC2B8Base { virtual void base06CSlot0(); };
struct Rva00BFC290Base { virtual void base070Slot0(); };

// Owned objects deleted through their virtual destructor (slot 0).
struct Rva00299CE4Owned { virtual ~Rva00299CE4Owned(); };

class GeometryInfo { public: virtual ~GeometryInfo(); unsigned char m_data[0x58]; };
class Rva002913EB { public: ~Rva002913EB(); unsigned char m_data[0xa0]; };
class WeaponSet { public: virtual ~WeaponSet(); unsigned char m_data[0x68]; };
class Rva001EB05E { public: ~Rva001EB05E(); unsigned char m_data[0x2c]; };
class Rva001DB3E0List { public: ~Rva001DB3E0List(); };
class Rva004DDF3A { public: ~Rva004DDF3A(); };
struct CameraMarker;

namespace _STL {
template <class T> class allocator {};
template <class T, class A> class _List_base
{
public:
	~_List_base();
	void *m_node;
};
template <class T, class A = allocator<T> > class vector
{
public:
	~vector()
	{
		if (_M_start)
			free(_M_start);
	}
	T *begin() { return _M_start; }
	T *end() { return _M_finish; }
	T *erase(T *first, T *last);
	void clear() { erase(begin(), end()); }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

class AIGroup { public: bool remove(class Object *obj); };

class CreateAHeroData { public: bool WriteNamedHeroAtRva004074CF(); };
class CreateAHeroManager { public: CreateAHeroData *rva002197A6(int id); };
extern CreateAHeroManager *TheCreateAHeroManager;

struct SearchArg0042638E;
class Rva0042638E { public: bool rva0042638E(const SearchArg0042638E *arg); };
class EmotionSystem;
extern EmotionSystem *TheEmotionSystem;

// TheGameLogic's frame copy (Zero Hour updateObjectsChangedTriggerAreas).
struct Rva00299CE4LogicFrames
{
	unsigned char m_unmodelled000[0x40];
	unsigned int m_frame;							// +0x40
	unsigned char m_unmodelled044[0x180 - 0x44];
	unsigned int m_triggerAreaFrame;				// +0x180
};
extern GameLogic *TheGameLogic;

class Rva002039B6Host { public: void rva002039B6(); };
class ScriptEngine { public: void rva00356FAF(int obj); };
extern ScriptEngine *TheScriptEngine;

class Rva002D37Owner { public: void rva002D373E(int obj); };
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

struct Rva002D76C6Owner;
class Radar { public: void removeObject(Rva002D76C6Owner *obj); };
extern Radar *TheRadar;

class Object : public Rva0030A120, public Snapshot, public Rva00BFC2D8Base, public Rva00BFC2B8Base, public Rva00BFC290Base
{
public:
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *xfer);
	virtual void base064Slot0();
	virtual void base06CSlot0();
	virtual void base070Slot0();
	virtual void vbaseSlot0();

	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes bit) const;
	void setTeam(Team *team);
	void rva0028BAC0();
	const Rva00299CE4Template *getTemplate() const { return m_template; }
	__forceinline bool isKindOf(Rva00299CE4Kind kind) const { return getTemplate()->isKindOf(kind); }

protected:
	virtual ~Object();

public:
	int m_id;										// +0x74
	unsigned char m_unmodelled078[0x10];
	AsciiString m_name;								// +0x88
	unsigned char m_unmodelled08C[0x18];
	Rva004DDF3A *m_a4;								// +0xA4
	GeometryInfo m_geometryInfo;					// +0xA8
	GeometryInfo *m_geometryClone;					// +0x104
	unsigned char m_unmodelled108[0xa0];
	AIGroup *m_group;								// +0x1A8
	unsigned char m_unmodelled1AC[0x7c];
	void *m_228, *m_22c, *m_230, *m_234, *m_238, *m_23c;	// +0x228
	void *m_firingTracker;							// +0x240
	Rva00299CE4Owned **m_behaviors;					// +0x244
	unsigned char m_unmodelled248[8];
	void *m_contain, *m_body, *m_ai, *m_physics;	// +0x250
	void *m_radarData;								// +0x260
	Rva00299CE4Owned *m_experienceTracker;			// +0x264
	Rva002913EB m_268;								// +0x268
	AsciiString m_308;								// +0x308
	unsigned char m_unmodelled30C[0x24];
	WeaponSet m_weaponSet;							// +0x330
	Rva00299CE4Owned *m_39c;						// +0x39C
	Rva00299CE4Owned *m_3a0;						// +0x3A0
	unsigned char m_unmodelled3A4[0x64];
	_STL::_List_base<CameraMarker, _STL::allocator<CameraMarker> > m_408;	// +0x408
	unsigned char m_unmodelled40C[0x10];
	AsciiString m_41c;								// +0x41C
	AsciiString m_420;								// +0x420
	AsciiString m_424;								// +0x424
	unsigned char m_unmodelled428[0x18];
	_STL::_List_base<int, _STL::allocator<int> > m_440;	// +0x440
	unsigned char m_unmodelled444[0xc];
	Rva001DB3E0List *m_450;							// +0x450
	unsigned char m_unmodelled454;
	bool m_455;										// +0x455
	unsigned char m_unmodelled456[0x12];
	Rva001EB05E m_468;								// +0x468
	AsciiString m_494;								// +0x494
	unsigned char m_unmodelled498[0xc];
	_STL::vector<int> m_4a4;						// +0x4A4
	unsigned char m_unmodelled4B0[4];
	_STL::vector<void *> m_4b4;						// +0x4B4
	unsigned char m_unmodelled4C0[4];
	void *m_partitionData;							// +0x4C4
	unsigned char m_unmodelled4C8[8];
};

// ??1Object@@MAE@XZ
Object::~Object()
{
	m_455 = true;

	if (isKindOf(KIND_190) && getControllingPlayer() && getControllingPlayer()->isLocalPlayer())
	{
		CreateAHeroData *hero = TheCreateAHeroManager->rva002197A6(m_id);
		if (hero)
			hero->WriteNamedHeroAtRva004074CF();
	}

	if (isKindOf(KIND_144) || isKindOf(KIND_90))
		((Rva0042638E *)TheEmotionSystem)->rva0042638E((const SearchArg0042638E *)this);

	if (!isKindOf(KIND_25) && !isKindOf(KIND_89))
	{
		Rva00299CE4LogicFrames *frames = (Rva00299CE4LogicFrames *)TheGameLogic;
		frames->m_triggerAreaFrame = frames->m_frame;
		if (TheScriptEngine)
			((Rva002039B6Host *)TheScriptEngine)->rva002039B6();
	}

	Rva002D37Owner *overrideSource = (Rva002D37Owner *)theRadarWindowOverrideSource;
	if (overrideSource && !testStatus(OBJECT_STATUS_0x33))
		overrideSource->rva002D373E((int)this);

	if (m_radarData)
		TheRadar->removeObject((Rva002D76C6Owner *)this);

	TheGameLogic->sendObjectDestroyed(this);

	rva0028BAC0();

	setTeam(0);

	if (m_partitionData)
		unregisterFromPartition();

	if (m_group)
		m_group->remove(this);

	m_ai = 0;
	m_physics = 0;
	m_contain = 0;
	m_body = 0;

	for (Rva00299CE4Owned **b = m_behaviors; *b; ++b)
	{
		::delete *b;
		*b = 0;
	}
	delete [] m_behaviors;
	m_behaviors = 0;

	m_4b4.clear();

	if (m_experienceTracker)
		::delete m_experienceTracker;
	m_experienceTracker = 0;

	m_firingTracker = 0;
	m_228 = 0;
	m_22c = 0;
	m_230 = 0;
	m_234 = 0;
	m_238 = 0;
	m_23c = 0;

	m_id = 0;

	if (TheScriptEngine)
		TheScriptEngine->rva00356FAF((int)this);

	if (m_geometryClone != &m_geometryInfo)
		::delete m_geometryClone;

	delete m_450;

	if (m_39c)
		::delete m_39c;
	m_39c = 0;
	if (m_3a0)
		::delete m_3a0;
	m_3a0 = 0;

	delete m_a4;
	m_a4 = 0;
}
