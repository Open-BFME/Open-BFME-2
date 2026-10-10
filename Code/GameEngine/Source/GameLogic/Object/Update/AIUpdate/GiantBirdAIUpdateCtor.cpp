// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0GiantBirdAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0036B717,
// 388 bytes. BFME 2 only (no ZH counterpart; BFME 1 has only a byte
// lift). Target evidence: the body runs the pinned AIUpdateInterface ctor
// 0x0026E9BD, stores the five vtables (0x00817A80 primary) and builds three
// members: the 0xC4-byte member DeployStyleAIUpdate also keeps (ctor
// 0x0026AFDA, rowed dtor 0x0026B03D) at +0x3F0, a list at +0x4B4 (the
// ICF-folded STLport _List_base ctor 0x004EC36C; element type not
// established) and the 0x60-byte member at +0x4C8 (ctor 0x00312C95, vtable
// 0x007C7514), zeroing +0x4C4 between them. The body zeroes the scalars and
// four points (+0x3E4, +0x544, +0x560, +0x56C, each through its address),
// sets +0x55C to 2 and ORs bits into five 4-byte file-scope masks at VA
// 0x00E01EC0..0x00E01ED0 (memset by the rowed dynamic initializers
// 0x007AEDE7.., read by GiantBird code at 0x0036877F and 0x00368CD2; kept
// under the ledger's address names). Retail holds the first mask in a
// register and stores it last.
#include <list>
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

extern unsigned char g_00E01EC0[4];
extern unsigned char g_00E01EC4[4];
extern unsigned char g_00E01EC8[4];
extern unsigned char g_00E01ECC[4];
extern unsigned char g_00E01ED0[4];

inline UnsignedInt &maskWord(unsigned char (&mask)[4])
{
	return *(UnsignedInt *)mask;
}

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	virtual void aiDoCommand();
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterface24
{
public:
	virtual void slot0();
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x3E4 - 0x28];
};

// The 0xC4-byte member DeployStyleAIUpdate keeps at +0x3E4 (ctor 0x0026AFDA,
// rowed dtor 0x0026B03D).
class Rva0026AFDAMember
{
public:
	Rva0026AFDAMember();
	~Rva0026AFDAMember();
private:
	unsigned char m_pad[0xC4];
};

// The 0x60-byte member at +0x4C8 (ctor 0x00312C95, vtable 0x007C7514).
// Its destructor is the rowed virtual Rva008B77D one (0x0008B77D); the
// qualified call binds it directly.
class Rva008B77D
{
public:
	virtual ~Rva008B77D();
};

class Rva00312C95
{
public:
	Rva00312C95();
	~Rva00312C95() { ((Rva008B77D *)this)->Rva008B77D::~Rva008B77D(); }
private:
	unsigned char m_pad[0x60];
};

class GiantBirdAIUpdate : public AIUpdateInterface
{
public:
	GiantBirdAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual void rva0036B6B9();
protected:
	virtual ~GiantBirdAIUpdate();
private:
	Coord3D m_3E4; // +0x3E4
	Rva0026AFDAMember m_3F0; // +0x3F0
	_STL::list<Int> m_4B4; // +0x4B4
	Int m_4B8; // +0x4B8
	Real m_4BC; // +0x4BC
	Int m_4C0; // +0x4C0
	Int m_4C4; // +0x4C4
	Rva00312C95 m_4C8; // +0x4C8
	Int m_528; // +0x528
	Real m_52C; // +0x52C
	Real m_530; // +0x530
	Bool m_534; // +0x534
	Real m_538; // +0x538
	Real m_53C; // +0x53C
	Real m_540; // +0x540
	Coord3D m_544; // +0x544
	Bool m_550; // +0x550
	Int m_554; // +0x554
	Bool m_558; // +0x558
	Int m_55C; // +0x55C
	Coord3D m_560; // +0x560
	Coord3D m_56C; // +0x56C
	Bool m_578; // +0x578
};

GiantBirdAIUpdate::GiantBirdAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData),
	  m_4C4(0)
{
	m_4B8 = 0;
	m_528 = 0;
	m_534 = false;
	m_52C = 0.0f;
	m_530 = 0.0f;
	m_4BC = 0.0f;
	m_538 = 0.0f;
	m_53C = 0.0f;
	m_540 = 0.0f;
	zeroCoord(m_544);
	m_550 = false;

	UnsignedInt mask = maskWord(g_00E01EC0) | 0x28;
	maskWord(g_00E01ECC) |= mask;
	maskWord(g_00E01EC4) |= mask;
	maskWord(g_00E01EC8) |= mask;
	maskWord(g_00E01ECC) |= 4;
	maskWord(g_00E01EC8) |= 2;
	maskWord(g_00E01ECC) |= 2;
	maskWord(g_00E01EC4) |= 4;
	maskWord(g_00E01ED0) |= 0x88;
	maskWord(g_00E01EC0) = mask;

	m_554 = 0;
	m_558 = false;
	m_55C = 2;
	zeroCoord(m_3E4);
	m_4C0 = 0;
	zeroCoord(m_560);
	zeroCoord(m_56C);
	m_578 = false;
}

// ??1GiantBirdAIUpdate@@MAE@XZ, retail 0x0036B8E6, 123 bytes: the destructor
// body (EH): the five vtables are restored, then the +0x4C8 member, the +0x4B4
// list and the +0x3F0 member are destroyed in reverse construction order and
// the AIUpdateInterface base destructor (pinned 0x0026E836) runs last.
GiantBirdAIUpdate::~GiantBirdAIUpdate()
{
}

// ?rva0036B6B9@GiantBirdAIUpdate@@UAEXXZ, retail 0x0036B6B9, 94 bytes: primary
// vtable slot 89 (0x00817BE4; AIUpdateInterface's own slot is empty),
// directly before the constructor. When the bird's controlling player is the
// one this machine drives (the local player in the game logic's 0x00200084
// mode, else an AI player 0x002AA245 without the +0x5C flag) and the AI
// orders manager has no orders for it (0x003552C2), the bird is told to idle
// as an AI command.
class Player
{
public:
	Bool isLocalPlayer() const;
	Bool rva002AA245() const;
	unsigned char m_pad000[0x5C];
	Int m_5C;
};
struct GiantBirdObjectView { unsigned char m_pad000[0x74]; Int m_id; };
class Object { public: Player *getControllingPlayer() const; };
class Rva0023C6A4 { public: Bool rva00200084(); };
class GameLogic;
extern GameLogic *TheGameLogic;
enum NameKeyType { NAMEKEY_INVALID = 0 };
class Rva00355B61 { public: Bool rva003552C2(NameKeyType key); };
class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;

void GiantBirdAIUpdate::rva0036B6B9()
{
	Object *obj = getObject();
	Player *player = obj->getControllingPlayer();
	if (!player)
		return;
	Bool controlled;
	if (((Rva0023C6A4 *)TheGameLogic)->rva00200084())
		controlled = player->isLocalPlayer();
	else
	{
		if (player->m_5C != 0)
			return;
		controlled = player->rva002AA245();
	}
	if (!controlled)
		return;
	if (((Rva00355B61 *)TheAiOrdersManager)->rva003552C2((NameKeyType)((GiantBirdObjectView *)obj)->m_id))
		return;
	aiIdle(CMD_FROM_AI);
}
