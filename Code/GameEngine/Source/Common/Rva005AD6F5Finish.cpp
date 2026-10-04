// ?rva005AD6F5@Rva005AD6C3@@QAEXXZ
// Finish pass 2026-10-04 seat6 from reverse/attempts/0x005ad6f5.cpp
// cl: /O1 /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva005AD6C3@@QAE@PBURva005DCC4BSource@@@Z @ 0x005AD6C3 39B
// Derived of rowed Rva005DCC4B: base converts source+0x74, then +0x08=0 and
// +0x0C=TheGameLogic frame+0x40. Evidence: call at 0x005AD6CA to rowed
// ??0Rva005DCC4B@@QAE@PBURva005DCC4BSource@@@Z, vtable 0x0087258C at [this],
// TheGameLogic 0x00DFE78C deref +0x40, caller 0x00506AC4 new 0x10 pushes Object
// into vector<ModuleData*>.
//
// The assert path its bodies pass GetGameLogicRandomValue names the retail
// file GameLogic/SkirmishAI/AITacticalAI/AITacticalNavy/AINavyUnitBattleShip.cpp.
// Layout: +0x04 the ship's id (base), +0x08 the current target's id, +0x0C
// the frame the next attack order is due.
//
//   0x005AD806  slot 0 (the vtable's only entry): keep attacking the target
//               every 25 frames, forget it once gone, or pick a random one of
//               the owner's tracked targets; with none, 0x005AD6F5
//   0x005AD6F5  when the ship's AI is idle, attack the first tracked target
//               whose template has +0x11F bit 4, else a random such object
#include <vector>

typedef int Int;

enum ObjectID
{
	INVALID_ID = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

struct Rva005DCC4BSource
{
	char m_bytes00[0x74];
	Int m_field74;
};

class Rva005DCC4B
{
public:
	Rva005DCC4B(const Rva005DCC4BSource *source);
	virtual void update() = 0;

	Int m_field04;
};

class Object;

class AICommandInterface
{
public:
	void rva003C7653(Object *target, CommandSourceType source);
};

class Rva005AD6C3AI
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
	virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
	virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
	virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
	virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
	virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
	virtual void v048(); virtual void v049(); virtual void v050(); virtual void v051();
	virtual void v052(); virtual void v053(); virtual void v054(); virtual void v055();
	virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063();
	virtual void v064(); virtual void v065(); virtual void v066(); virtual void v067();
	virtual void v068(); virtual void v069(); virtual void v070(); virtual void v071();
	virtual void v072(); virtual void v073(); virtual void v074(); virtual void v075();
	virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083();
	virtual void v084(); virtual void v085(); virtual void v086(); virtual void v087();
	virtual void v088(); virtual void v089(); virtual void v090(); virtual void v091();
	virtual void v092(); virtual void v093(); virtual void v094(); virtual void v095();
	virtual void v096(); virtual void v097(); virtual void v098(); virtual void v099();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103();
	virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107();
	virtual void v108(); virtual void v109();
	virtual bool isIdle();		// slot 110 (+0x1B8)
	char m_pad04[0x20 - 4];
	AICommandInterface m_commands;	// +0x20
};

struct Rva005AD6C3Template
{
	char m_pad000[0x11F];
	unsigned char m_11F;
};

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad000[4];
	Rva005AD6C3Template *m_04;	// +0x04
	char m_pad008[0x8C - 8];
	Object *m_8C;			// +0x8C, next in TheGameLogic's list
	char m_pad090[0x258 - 0x90];
	Rva005AD6C3AI *m_ai;		// +0x258
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	Object *getFirstObject();
	char m_pad00[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

struct Rva002A8AB1Record
{
	void *rva002C6ACB();
};

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

namespace _STL
{
template <class T> struct hash;
template <class T> struct equal_to;
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

struct Rva005AD6C3Holder
{
	char m_pad00[4];
	Rva005C4AD1LeaField *m_04;	// +0x04
	Rva005C4AD1LeaField *m_08;	// +0x08
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Rva005AD6C3 : public Rva005DCC4B
{
public:
	Rva005AD6C3(const Rva005DCC4BSource *source);
	virtual void update();
	void rva005AD6F5();

	Int m_field08;
	Int m_field0C;
};

Rva005AD6C3::Rva005AD6C3(const Rva005DCC4BSource *source)
	: Rva005DCC4B(source)
{
	m_field08 = 0;
	m_field0C = (Int)TheGameLogic->m_frame;
}

void Rva005AD6C3::rva005AD6F5()
{
	Object *ship = TheGameLogic->findObjectByID((ObjectID)m_field04);
	if (!ship->m_ai->isIdle())
		return;
	Player *player = (Player *)g_00DFEEF8->rva002A8AB1(ship->getControllingPlayer())->rva002C6ACB();
	Rva005AD6C3Holder *holder = (Rva005AD6C3Holder *)g_00DFEEF8->rva002A8F24(player);
	Rva005C4AD1LeaField *units = holder->m_08;
	bool attacked = false;
	unsigned int count = ((IntMap *)units)->bucket_count();
	if (count > 0) {
		for (unsigned int i = 0; i < count; ++i) {
			if (attacked)
				return;
			Object *obj = TheGameLogic->findObjectByID((*(ObjectID **)units->get())[i]);
			if (obj->m_04->m_11F & 0x10) {
				ship->m_ai->m_commands.rva003C7653(obj, CMD_FROM_PLAYER);
				attacked = true;
			}
		}
		if (attacked)
			return;
	}
	for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->m_8C) {
		if ((obj->m_04->m_11F & 0x10) && GetGameLogicRandomValue(0, 9,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticalNavy\\AINavyUnitBattleShip.cpp",
			120) == 0) {
			ship->m_ai->m_commands.rva003C7653(obj, CMD_FROM_PLAYER);
			return;
		}
	}
}
