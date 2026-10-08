// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "AIRingHeroTactic" skirmish-AI tactic (vtable 0x008723E8; ctor
// 0x005AC7EC in Rva004ECECDTacticCtors.cpp, dtor 0x005AC7E1 and ??_G, slot 9
// 0x005AC8F2 in Rva004ECECDTacticCreate.cpp). Base chain, all
// address-derived: Rva005DCC24 over AITacticOffensive over the AITactic.cpp object
// AITactic. Layout: +0x58 the ring hero's id, +0x5C, +0x60 "escorting",
// +0x64 the escort. The owner's TheSkirmishAIManager record keeps
// AIRingHeroTactic_IsRunning and AIRingHeroTactic_NextLogicFrameRun.
//
//   0x005ACA97  slot 1: schedule the first run 5 * g_Va00DBA4E4 frames out;
//               once due and not running, apply when the ring hero is found
//               (0x005ACA2D) and 0x005AC98A agrees, else push the next run
//               out again
//   0x005AC866  slot 2: forget the hero and clear both keys
//   0x005AC924  slot 3: set the running key, then the AITactic's slot 3
//   0x005ACBE3  slot 6: start: find the hero, then 0x005AC98A
//   0x005ACBFF  slot 7 (not here yet): escort the hero
//   0x005ACA2D  find the owner's ring hero (template +0x121 bit 5) into +0x58
#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

struct Rva005AC7E1Template
{
	char m_pad000[0x120];
	unsigned char m_120;
	unsigned char m_121;
};

class Object;

class Rva00352ECA
{
public:
	void rva00352ECA(void *target, CommandSourceType source);
};

class AICommandInterface
{
public:
	void rva0026C347(Object *target, CommandSourceType source);
};

class Rva005AC7E1AI
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual void v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual void v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual bool isIdle();		// slot 110 (+0x1B8)
	char m_pad04[0x20 - 4];
	AICommandInterface m_commands;	// +0x20
};

class Object
{
public:
	char m_pad000[4];
	Rva005AC7E1Template *m_04;	// +0x04
	char m_pad008[0x74 - 8];
	ObjectID m_id;			// +0x74
	char m_pad078[0x94 - 0x78];
	unsigned char m_94;		// +0x94
	char m_pad095[0x258 - 0x95];
	Rva005AC7E1AI *m_ai;		// +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_438;		// +0x438
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned int getFrame() const { return m_40; }
	char m_pad000[0x40];
	unsigned int m_40;		// +0x40
};
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
};

struct Rva005AC7E1IDs
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

class Player;

struct Rva005AC7E1Holder
{
	char m_pad00[8];
	Rva005C4AD1LeaField *m_08;	// +0x08
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, int count);
	virtual void v4();
	virtual void v5();
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
	void end(bool a, bool b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x24 - 0x11];
	Player *m_owner;		// +0x24
	char m_pad28[0x58 - 0x28];
};

class AIRingHeroTactic : public AITacticOffensive
{
public:
	virtual ~AIRingHeroTactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, int count);
	virtual void run();
	bool weHaveGollum();
	bool enemyHasRingHeroUpgrade();
private:
	ObjectID m_hero;	// +0x58
	int m_5C;		// +0x5C
	bool m_escorting;	// +0x60
	unsigned char m_pad61[3];
	Object *m_escort;	// +0x64
};

void AIRingHeroTactic::cleanUp()
{
	m_hero = INVALID_ID;
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	record->rva002C717E(AsciiString("AIRingHeroTactic_IsRunning"), 0);
	record->rva002C717E(AsciiString("AIRingHeroTactic_NextLogicFrameRun"), 0);
	m_5C = 0;
}

bool AIRingHeroTactic::initializeTeamTemplate(void *unit, int count)
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	record->rva002C717E(AsciiString("AIRingHeroTactic_IsRunning"), 1);
	return AITactic::initializeTeamTemplate(unit, count);
}

bool AIRingHeroTactic::weHaveGollum()
{
	IntMap *objects = *(IntMap **)g_00DFEEF8->rva002A8F24(m_owner);
	for (unsigned int i = 0; i < objects->bucket_count(); ++i) {
		Rva005AC7E1IDs *ids = (Rva005AC7E1IDs *)((Rva005C4AD1LeaField *)objects)->get();
		Object *obj = TheGameLogic->findObjectByID(ids->m_begin[i]);
		if (obj && (obj->m_04->m_121 & 0x20)) {
			m_hero = obj->m_id;
			return true;
		}
	}
	return false;
}

bool AIRingHeroTactic::canRun(void *)
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	int running = record->rva002C7196(AsciiString("AIRingHeroTactic_IsRunning"));
	unsigned int next = record->rva002C7196(AsciiString("AIRingHeroTactic_NextLogicFrameRun"));
	if (!next) {
		record->rva002C717E(AsciiString("AIRingHeroTactic_NextLogicFrameRun"), g_Va00DBA4E4 * 5);
	} else if (!running && TheGameLogic->getFrame() >= next) {
		if (weHaveGollum() && enemyHasRingHeroUpgrade())
			return true;
		int later = record->rva002C7196(AsciiString("AIRingHeroTactic_NextLogicFrameRun"));
		record->rva002C717E(AsciiString("AIRingHeroTactic_NextLogicFrameRun"), g_Va00DBA4E4 * 5 + later);
	}
	return false;
}

void AIRingHeroTactic::run()
{
	m_escort = 0;
	m_running = true;
	m_escorting = false;
	weHaveGollum();
	enemyHasRingHeroUpgrade();
}
