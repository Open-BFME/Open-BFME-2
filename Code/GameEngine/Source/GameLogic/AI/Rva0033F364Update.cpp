// cl: /O1 /G7 /DNDEBUG /MD
// ?update@Rva0033F364@@UAE?AW4StateReturnType@@XZ @0x003492BD 225B
// Evidence: vslot slot 6 of vtable 0x00810F40 owned by Rva0033F364 ctor; TurretStateMachine goal checks and frame gate via g_Va00DBA4E4 and TheGameLogic.

typedef bool Bool;
typedef float Real;

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Player;
class Object;
class Thing
{
public:
	void setOrientation(Real angle);
};

class ProviderInner
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76();
	virtual Bool slot77(Object *o);
	virtual void s78(); virtual void s79(); virtual void s80(); virtual void s81();
	virtual void s82(); virtual void s83(); virtual void s84();
	virtual Bool slot85(Object *o);
};

class Provider250
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
	virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
	virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
	virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
	virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
	virtual void p28(); virtual void p29(); virtual void p30();
	virtual ProviderInner *slot31();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool rva002943B2(const Player *p);
	Real rva000B4542(const Coord3D *pos) const;
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	Real m_44; // +0x44
	unsigned char m_pad48[0x250 - 0x48];
	Provider250 *m_provider250; // +0x250
};

class TurretStateMachine
{
public:
	Bool rva004D7ADD();
	Object *getGoalObject();
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	int m_frame; // +0x40
};

extern int g_Va00DBA4E4;
extern GameLogic *TheGameLogic;
Bool rva00344EB2Gate(Object *a, Thing *b);

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(int status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	TurretStateMachine *m_machine; // +0x18
	unsigned m_hash; // +0x1C
};

class Rva0033F364 : public State
{
public:
	virtual StateReturnType update();
private:
	int m_20; // +0x20
};

StateReturnType Rva0033F364::update()
{
	Object *owner = m_machine->m_owner;
	if (m_machine->rva004D7ADD())
		return STATE_SUCCESS;
	Object *goal = m_machine->getGoalObject();
	if (goal == 0)
		return STATE_SUCCESS;
	if (goal->rva002943B2(owner->getControllingPlayer()))
		return STATE_FAILURE;
	Provider250 *provider = owner->m_provider250;
	if (provider)
	{
		ProviderInner *inner = provider->slot31();
		if (inner == 0)
			return STATE_SUCCESS;
		if (rva00344EB2Gate(owner, (Thing *)goal))
			return STATE_FAILURE;
		if (inner->slot85(goal))
		{
			inner->slot77(goal);
			m_20 = g_Va00DBA4E4 * 3 + TheGameLogic->m_frame;
			return STATE_CONTINUE;
		}
		if ((unsigned)TheGameLogic->m_frame >= (unsigned)m_20)
		{
			_WriteBarrier();
			return STATE_FAILURE;
		}
		return STATE_CONTINUE;
	}
	else
	{
		Real add = owner->m_44;
		Real rel = owner->rva000B4542(&goal->m_position);
		((Thing *)owner)->setOrientation(rel + add);
		return STATE_CONTINUE;
	}
}
