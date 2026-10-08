// ?rva002AEEA7@Player@@QAEXH@Z
// partial score=0.96 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /O1 /arch:SSE /G7
// ?rva002AEEA7@Player@@QAEXH@Z @0x002AEEA7 400B Player orders all units to enter KindOf-7 structures via all-objects query plus team walks plus mask plus canEnter plus aiEnter. Evidence: LINK BONUS pin plus caller 0x003BBDB5 via ScriptActionsRva003BBD84 plus callee pins dlink_next 0x9C4AF5 plus iterate 0x263864 plus next 0x45623 plus getControllingPlayer 0x28AFA9 plus canEnter 0x41C2D0 plus rva0026C347 plus advance 0x263526 plus dtor 0x4AA28 plus BitSet 0x45411 plus filter 0x4584D plus forwarder 0x6256F0 plus globals KINDOFMASK_NONE ThePartitionManager TheActionManager plus donor Player garrisonAllUnits triple loop plus mask plus canEnter plus aiEnter plus sibling 0x002AF037 outer DLINK 0x32c plus team chain 0x334.
typedef int Int;
typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum CanEnterType
{
	CHECK_CAPACITY = 0,
	DONT_CHECK_CAPACITY = 1,
	COMBATDROP_INTO = 2
};

class Object;
class Team;
class Player;

template<class T> class DLINK_ITERATOR;

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

template<>
class DLINK_ITERATOR<Object>
{
private:
	Object* m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	Bool done() const throw() { return m_cur == 0; }
	Object* cur() const throw() { return m_cur; }
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team* dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	Player* getControllingPlayer() const;
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
private:
	unsigned char m_pad[0x334];
	Team* m_dlinkhead_TeamInstanceList;
};

struct PlayerTeamNode
{
	PlayerTeamNode* m_next;
	PlayerTeamNode* m_prev;
	TeamPrototype* m_value;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void* getContainedObjectSource();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37();
	virtual bool isValidContainerFor(const Object* obj, bool checkCapacity, bool flag);
	virtual void addToContain(Object* obj);
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80();
	virtual int getPlayerWhoEntered();
};

class AICommandInterface
{
public:
	void rva0026C347(Object* target, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_command;
};

class Thing
{
public:
	virtual ~Thing();
};

class Object : public Thing
{
public:
	virtual ~Object();
	ContainModuleInterface* getContain() const { return m_contain; }
	AIUpdateInterface* getAIUpdateInterface() const { return m_ai; }
	Player* getControllingPlayer() const;
private:
	const void* m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;
	unsigned char m_pad44[0x250 - 0x44];
	ContainModuleInterface* m_contain;
	unsigned char m_pad254[4];
	AIUpdateInterface* m_ai;
};

class Player
{
public:
	void rva002AEEA7(int val);
	int getPlayerMask() const { return 1 << m_playerIndex; }
private:
	unsigned char m_pad[0x54];
	int m_playerIndex;
	unsigned char m_pad58[0x32C - 0x58];
	PlayerTeamNode* m_playerTeamPrototypes;
};

class ActionManager
{
public:
	bool rvaDummy();
};

class BFMEActionManager
{
public:
	bool canEnterObject(const Object* obj, const Object* objectToEnter, CommandSourceType commandSource, CanEnterType mode, bool passThrough, bool* outFlag);
};
extern ActionManager* TheActionManager;

template<int N>
class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D& other) throw();
private:
	unsigned char m_bytes[28];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();
	unsigned m_bits[7];
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object* obj) = 0;
	virtual int getPlayerMask() { return -1; }
	Rva000421C8* m_next;
};

class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D& a, const BfmeFixedStorage0004543D& b) throw();
	virtual bool allow(Object* obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct BfmeWidePayloadCompat
{
	void* m_start;
	void* m_04;
	void* m_08;
	void* m_cursor;
};

struct BfmeWideResult
{
	void* m_value;
	~BfmeWideResult();
	Object* next() throw();
	Object* first() throw()
	{
		BfmeWidePayloadCompat* q = (BfmeWidePayloadCompat*)m_value;
		q->m_cursor = q->m_start;
		return next();
	}
};

struct BfmeResultPayloadA
{
	void* m_start;
	void* m_finish;
	void* m_end;
	void* m_cursor;
	int m_refCount;
};

struct BfmeResultA : public BfmeWideResult
{
};

class BfmeResultForwardB
{
public:
	BfmeResultA bfmeForwardResultB(int value);
};

class PartitionManager
{
public:
	void* m_pad10[4];
	void* m_impl;
};
extern PartitionManager* ThePartitionManager;

void Player::rva002AEEA7(int val)
{
	BfmeResultA hits = ((BfmeResultForwardB*)ThePartitionManager)->bfmeForwardResultB((int)&Rva0004584D(*(BfmeFixedStorage0004543D*)&Rva00045411BitSet(0, 7), *(BfmeFixedStorage0004543D*)&KINDOFMASK_NONE));
	for (PlayerTeamNode* it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		for (DLINK_ITERATOR<Team> iter = it->m_value->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team* team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> iterObj = team->iterate_TeamMemberList(); !iterObj.done(); iterObj.advance())
			{
				Object* obj = iterObj.cur();
				if (!obj)
					continue;
				AIUpdateInterface* ai = obj->getAIUpdateInterface();
				if (!ai)
					continue;
				Object* theBuilding = hits.first();
				while (theBuilding)
				{
					ContainModuleInterface* contain = theBuilding->getContain();
					if (contain)
					{
						int player = contain->getPlayerWhoEntered();
						if (!((player == 0) || (player == obj->getControllingPlayer()->getPlayerMask())))
						{
							theBuilding = hits.next();
							continue;
						}
					}
					Bool flag;
					if (!((BFMEActionManager*)TheActionManager)->canEnterObject(obj, theBuilding, (CommandSourceType)val, CHECK_CAPACITY, false, &flag))
					{
						theBuilding = hits.next();
						continue;
					}
					if (flag)
					{
						theBuilding = hits.next();
						continue;
					}
					(ai->m_command).rva0026C347(theBuilding, (CommandSourceType)val);
					theBuilding = hits.next();
				}
			}
		}
	}
}
