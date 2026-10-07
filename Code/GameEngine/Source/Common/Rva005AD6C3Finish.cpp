// ?update@AINavyUnitBattleShip@@UAEXXZ
// Finish pass 2026-10-04 seat8 from reverse/attempts/0x005ad806.cpp
//
// Closing the last 21 bytes: naming the receiver `ship->m_ai` in a local
// `Rva005AD6C3AI *ai` immediately before the final attack command makes MSVC
// load it into a callee-saved register before it evaluates the two arguments,
// which is retail's `mov esi,[ebx+0x258]` / `push 0` / `push eax` / `call` /
// `lea ecx,[esi+0x20]`. Inlined, the same expression schedules the
// findObjectByID call first and reloads ecx from [ebx+0x258] afterwards.
// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0AINavyUnitBattleShip@@QAE@PBURva005DCC4BSource@@@Z @ 0x005AD6C3 39B
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

class AINavyUnitBattleShip : public Rva005DCC4B
{
public:
	AINavyUnitBattleShip(const Rva005DCC4BSource *source);
	virtual void update();
	void patrol();

	Int m_field08;
	Int m_field0C;
};

AINavyUnitBattleShip::AINavyUnitBattleShip(const Rva005DCC4BSource *source)
	: Rva005DCC4B(source)
{
	m_field08 = 0;
	m_field0C = (Int)TheGameLogic->m_frame;
}

// AINavyUnitBattleShip::patrol is defined with its retail-matched body in Code/GameEngine/Source/Common/Rva005AD6F5Finish.cpp (0x005AD6F5).

void AINavyUnitBattleShip::update()
{
	GameLogic *logic = TheGameLogic;
	Object *ship = logic->findObjectByID((ObjectID)m_field04);
	if (!ship)
		return;
	if (m_field08) {
		Object *target = logic->findObjectByID((ObjectID)m_field08);
		if (target) {
			if (logic->m_frame == (unsigned int)m_field0C) {
				ship->m_ai->m_commands.rva003C7653(target, CMD_FROM_PLAYER);
				m_field0C = TheGameLogic->m_frame + 25;
			}
		} else {
			m_field08 = 0;
		}
		return;
	}
	Player *player = (Player *)g_00DFEEF8->rva002A8AB1(ship->getControllingPlayer())->rva002C6ACB();
	if (!player)
		return;
	_STL::vector<ObjectID> targets(*(const _STL::vector<ObjectID> *)((Rva005AD6C3Holder *)g_00DFEEF8->rva002A8F24(player))->m_04->get());
	if (!targets.empty()) {
		ObjectID chosen = targets[GetGameLogicRandomValue(0, targets.size() - 1,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticalNavy\\AINavyUnitBattleShip.cpp",
			65)];
		m_field08 = chosen;
		Rva005AD6C3AI *ai = ship->m_ai;
		ai->m_commands.rva003C7653(TheGameLogic->findObjectByID(chosen), CMD_FROM_PLAYER);
	} else {
		patrol();
	}
}
