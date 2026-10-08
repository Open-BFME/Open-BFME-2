// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?updateState@Team@@QAEXXZ @0x0039F0E3 1163B.
// Identity (target): the one REL32 caller is TeamPrototype::updateState
// (0x003A34AC) on each +0x334 list team; the body runs the template info's
// create / enemy-sighted / all-clear / destroyed / idle scripts like Zero
// Hour Team::updateState (donor for flow and field names).
// BFME 2 deltas (target): nothing runs without a prototype; the created block
// also waits for the +0x113 byte to be clear and the rowed 0x0039E0D0 gate,
// sets +0x5F, hands every live member's AI (+0x258, rowed dword setter
// 0x002628B6) the LuaScriptEngine record named by the template info's +0xC4
// string (0x00337DEF), counts a horde member through its contain's horde
// interface (slot 31, then slot 96 with 0), and finishes with the rowed
// Object member 0x002947A8 on each member; the +0x128 byte latches the
// rowed 0x0039E8EB; enemy checks run every eighth frame by team id and go
// through BFME 2's linked partition filter chain (relationship 1, alive,
// same map status, attack range -1.0f, KindOf mask 0 / {89, 134}); scripts
// run through the rowed ScriptEngine 0x0020C140 with the prototype name as
// scope. Shape: the DLINK iterator and Team::iterate_TeamMemberList are
// defined in-TU over the virtual-inheritance Object skeleton
// (ScriptActions_doTeamHuntWithCommandButton.cpp), and the filter chain is
// built innermost first (the KindOf filter links the attack-range filter).
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../GameLogicObjectLookupView.h"
#include "../PartitionRangeQueryCallView.h"

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C0719C, allow 0x00261513.
class Rva00261513Filter : public Rva000421C8
{
public:
	Rva00261513Filter(const Object *obj, bool flag, float value)
		: m_obj(obj), m_flag(flag), m_value(value) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	bool m_flag;
	float m_value;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// The 224-bit KindOf mask; the (unused, bit, bit) constructor is 0x0006EE7A.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit1, int bit2) throw();	// 0x0006EE7A
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

extern PartitionManager *ThePartitionManager;

class HordeContainInterface
{
public:
#define HORDE_SLOT(n) virtual void hordeSlot##n();
	HORDE_SLOT(0) HORDE_SLOT(1) HORDE_SLOT(2) HORDE_SLOT(3) HORDE_SLOT(4)
	HORDE_SLOT(5) HORDE_SLOT(6) HORDE_SLOT(7) HORDE_SLOT(8) HORDE_SLOT(9)
	HORDE_SLOT(10) HORDE_SLOT(11) HORDE_SLOT(12) HORDE_SLOT(13) HORDE_SLOT(14)
	HORDE_SLOT(15) HORDE_SLOT(16) HORDE_SLOT(17) HORDE_SLOT(18) HORDE_SLOT(19)
	HORDE_SLOT(20) HORDE_SLOT(21) HORDE_SLOT(22) HORDE_SLOT(23) HORDE_SLOT(24)
	HORDE_SLOT(25) HORDE_SLOT(26) HORDE_SLOT(27) HORDE_SLOT(28) HORDE_SLOT(29)
	HORDE_SLOT(30) HORDE_SLOT(31) HORDE_SLOT(32) HORDE_SLOT(33) HORDE_SLOT(34)
	HORDE_SLOT(35) HORDE_SLOT(36) HORDE_SLOT(37) HORDE_SLOT(38) HORDE_SLOT(39)
	HORDE_SLOT(40) HORDE_SLOT(41) HORDE_SLOT(42) HORDE_SLOT(43) HORDE_SLOT(44)
	HORDE_SLOT(45) HORDE_SLOT(46) HORDE_SLOT(47) HORDE_SLOT(48) HORDE_SLOT(49)
	HORDE_SLOT(50) HORDE_SLOT(51) HORDE_SLOT(52) HORDE_SLOT(53) HORDE_SLOT(54)
	HORDE_SLOT(55) HORDE_SLOT(56) HORDE_SLOT(57) HORDE_SLOT(58) HORDE_SLOT(59)
	HORDE_SLOT(60) HORDE_SLOT(61) HORDE_SLOT(62) HORDE_SLOT(63) HORDE_SLOT(64)
	HORDE_SLOT(65) HORDE_SLOT(66) HORDE_SLOT(67) HORDE_SLOT(68) HORDE_SLOT(69)
	HORDE_SLOT(70) HORDE_SLOT(71) HORDE_SLOT(72) HORDE_SLOT(73) HORDE_SLOT(74)
	HORDE_SLOT(75) HORDE_SLOT(76) HORDE_SLOT(77) HORDE_SLOT(78) HORDE_SLOT(79)
	HORDE_SLOT(80) HORDE_SLOT(81) HORDE_SLOT(82) HORDE_SLOT(83) HORDE_SLOT(84)
	HORDE_SLOT(85) HORDE_SLOT(86) HORDE_SLOT(87) HORDE_SLOT(88) HORDE_SLOT(89)
	HORDE_SLOT(90) HORDE_SLOT(91) HORDE_SLOT(92) HORDE_SLOT(93) HORDE_SLOT(94)
	HORDE_SLOT(95)
#undef HORDE_SLOT
	virtual int getMemberCount(void *filter);	// slot 96 (+0x180)
};

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void containSlot##n();
	CONTAIN_SLOT(0) CONTAIN_SLOT(1) CONTAIN_SLOT(2) CONTAIN_SLOT(3) CONTAIN_SLOT(4)
	CONTAIN_SLOT(5) CONTAIN_SLOT(6) CONTAIN_SLOT(7) CONTAIN_SLOT(8) CONTAIN_SLOT(9)
	CONTAIN_SLOT(10) CONTAIN_SLOT(11) CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14)
	CONTAIN_SLOT(15) CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23) CONTAIN_SLOT(24)
	CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27) CONTAIN_SLOT(28) CONTAIN_SLOT(29)
	CONTAIN_SLOT(30)
#undef CONTAIN_SLOT
	virtual HordeContainInterface *getHordeContainInterface();	// slot 31 (+0x7C)
};

class AIUpdateInterface
{
public:
#define AI_SLOT(n) virtual void aiSlot##n();
	AI_SLOT(0) AI_SLOT(1) AI_SLOT(2) AI_SLOT(3) AI_SLOT(4)
	AI_SLOT(5) AI_SLOT(6) AI_SLOT(7) AI_SLOT(8) AI_SLOT(9)
	AI_SLOT(10) AI_SLOT(11) AI_SLOT(12) AI_SLOT(13) AI_SLOT(14)
	AI_SLOT(15) AI_SLOT(16) AI_SLOT(17) AI_SLOT(18) AI_SLOT(19)
	AI_SLOT(20) AI_SLOT(21) AI_SLOT(22) AI_SLOT(23) AI_SLOT(24)
	AI_SLOT(25) AI_SLOT(26) AI_SLOT(27) AI_SLOT(28) AI_SLOT(29)
	AI_SLOT(30) AI_SLOT(31) AI_SLOT(32) AI_SLOT(33) AI_SLOT(34)
	AI_SLOT(35) AI_SLOT(36) AI_SLOT(37) AI_SLOT(38) AI_SLOT(39)
	AI_SLOT(40) AI_SLOT(41) AI_SLOT(42) AI_SLOT(43) AI_SLOT(44)
	AI_SLOT(45) AI_SLOT(46) AI_SLOT(47) AI_SLOT(48) AI_SLOT(49)
	AI_SLOT(50) AI_SLOT(51) AI_SLOT(52) AI_SLOT(53) AI_SLOT(54)
	AI_SLOT(55) AI_SLOT(56) AI_SLOT(57) AI_SLOT(58) AI_SLOT(59)
	AI_SLOT(60) AI_SLOT(61) AI_SLOT(62) AI_SLOT(63) AI_SLOT(64)
	AI_SLOT(65) AI_SLOT(66) AI_SLOT(67) AI_SLOT(68) AI_SLOT(69)
	AI_SLOT(70) AI_SLOT(71) AI_SLOT(72) AI_SLOT(73) AI_SLOT(74)
	AI_SLOT(75) AI_SLOT(76) AI_SLOT(77) AI_SLOT(78) AI_SLOT(79)
	AI_SLOT(80) AI_SLOT(81) AI_SLOT(82) AI_SLOT(83) AI_SLOT(84)
	AI_SLOT(85) AI_SLOT(86) AI_SLOT(87) AI_SLOT(88) AI_SLOT(89)
	AI_SLOT(90) AI_SLOT(91) AI_SLOT(92) AI_SLOT(93) AI_SLOT(94)
	AI_SLOT(95) AI_SLOT(96) AI_SLOT(97) AI_SLOT(98) AI_SLOT(99)
	AI_SLOT(100) AI_SLOT(101) AI_SLOT(102) AI_SLOT(103) AI_SLOT(104)
	AI_SLOT(105) AI_SLOT(106) AI_SLOT(107) AI_SLOT(108) AI_SLOT(109)
#undef AI_SLOT
	virtual bool isIdle();	// slot 110 (+0x1B8)
};

// The AI's +0x220 dword setter (DispDwordFieldSetters.cpp).
class Rva002628B6DwordSlot
{
public:
	void set(int value);
};

// The rowed Object member 0x002947A8 (ObjectRva00294759.cpp).
class Rva00294759
{
public:
	void rva002947A8();
};

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

// Introduces the vbptr at its own +0; lands at +0x68 inside Object
// (TeamIterateTeamMemberList.cpp).
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad04[0x38 - 0x04];
	Coord3D m_pos;				// +0x38
	unsigned char m_pad44[0x68 - 0x44];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	float getVisionRange() const;	// 0x0028DDE0
	const Coord3D *getPosition() const { return &m_pos; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
private:
	unsigned char m_pad070[0x250 - 0x70];
	ContainModuleInterface *m_contain;	// +0x250
	void *m_body;				// +0x254
	AIUpdateInterface *m_ai;		// +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus;		// +0x438
};

// advance (0x00263526) and Team::iterate_TeamMemberList (0x00263864) are
// defined as in the header; neither is inlined here.
template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = ((*m_cur).*(m_getNextFunc))(); }
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

extern GameLogic *TheGameLogic;

class Team;

class ScriptEngine
{
public:
	void rva0020C140(const AsciiString &scope, const AsciiString &script, Team *team);
};
extern ScriptEngine *TheScriptEngine;

struct Rva00336283Element;

class LuaScriptEngine
{
public:
	Rva00336283Element *rva00337DEF(const AsciiString &name);
};
extern LuaScriptEngine *TheLuaScriptEngine;

static inline bool isEmpty(const AsciiString &s)
{
	return ((const StringBase<char> *)&s)->isEmpty();
}

class TeamTemplateInfo
{
public:
	char m_pad00[0xC0];
	AsciiString m_scriptOnCreate;		// +0xC0
	AsciiString m_luaOnCreate;		// +0xC4
	AsciiString m_scriptOnIdle;		// +0xC8
	int m_initialIdleFrames;		// +0xCC
	AsciiString m_scriptOnEnemySighted;	// +0xD0
	AsciiString m_scriptOnAllClear;		// +0xD4
	AsciiString m_scriptOnUnitDestroyed;	// +0xD8
	AsciiString m_scriptOnDestroyed;	// +0xDC
	float m_destroyedThreshold;		// +0xE0
};

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }
	const TeamTemplateInfo *getTemplateInfo() const { return &m_teamTemplate; }
private:
	char m_00[0x10];
	AsciiString m_name;			// +0x10
	char m_14[0x12C - 0x14];
	TeamTemplateInfo m_teamTemplate;	// +0x12C
};

class Team
{
public:
	void updateState();
	bool rva0039E0D0();
	Object *rva0039E8EB();
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const { return DLINK_ITERATOR<Object>(m_head, &Object::dlink_next_TeamMemberList); }
	const AsciiString &getName() const { return !m_proto ? AsciiString::TheEmptyString : m_proto->getName(); }

private:
	char m_pad00[0x30];
	TeamPrototype *m_proto;			// +0x30
	unsigned int m_id;			// +0x34
	Object *m_head;				// +0x38
	char m_pad3C[0x5C - 0x3C];
	bool m_enteredOrExited;			// +0x5C
	bool m_active;				// +0x5D
	bool m_created;				// +0x5E
	bool m_5F;				// +0x5F
	bool m_checkEnemySighted;		// +0x60
	bool m_seeEnemy;			// +0x61
	bool m_prevSeeEnemy;			// +0x62
	bool m_wasIdle;				// +0x63
	int m_destroyThreshold;			// +0x64
	int m_curUnits;				// +0x68
	char m_pad6C[0x113 - 0x6C];
	bool m_113;				// +0x113
	char m_pad114[0x128 - 0x114];
	bool m_128;				// +0x128
};

void Team::updateState()
{
	if (!m_proto)
		return;
	m_enteredOrExited = false;
	if (!m_active)
		return;

	const TeamTemplateInfo *pInfo = m_proto->getTemplateInfo();
	if (m_created && !m_113 && rva0039E0D0())
	{
		m_created = false;
		m_5F = true;

		if (!isEmpty(pInfo->m_scriptOnCreate))
			TheScriptEngine->rva0020C140(getName(), pInfo->m_scriptOnCreate, this);

		if (!isEmpty(pInfo->m_luaOnCreate))
		{
			Rva00336283Element *record = TheLuaScriptEngine->rva00337DEF(pInfo->m_luaOnCreate);
			for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
			{
				Object *obj = iter.cur();
				AIUpdateInterface *ai = obj->getAI();
				if (!obj->isEffectivelyDead() && ai)
					((Rva002628B6DwordSlot *)ai)->set((int)record);
			}
		}

		if (!isEmpty(pInfo->m_scriptOnDestroyed))
		{
			for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
			{
				ContainModuleInterface *contain = iter.cur()->getContain();
				HordeContainInterface *horde = contain ? contain->getHordeContainInterface() : 0;
				if (horde)
					m_curUnits += horde->getMemberCount(0);
				else
					m_curUnits++;
			}
			m_destroyThreshold = m_curUnits - (m_curUnits * pInfo->m_destroyedThreshold);
			if (m_destroyThreshold > m_curUnits - 1)
				m_destroyThreshold = m_curUnits - 1;
			if (m_destroyThreshold < 0)
				m_destroyThreshold = 0;
		}

		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			Object *obj = iter.cur();
			if (!obj)
				continue;
			((Rva00294759 *)obj)->rva002947A8();
		}
	}

	if (!m_5F)
		return;

	if (!m_128 && rva0039E8EB())
		m_128 = true;

	if (m_checkEnemySighted && ((m_id ^ TheGameLogic->getFrame()) & 7) == 0)
	{
		m_prevSeeEnemy = m_seeEnemy;
		m_seeEnemy = false;
		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			Object *obj = iter.cur();
			if (obj->isEffectivelyDead())
				continue;

			Object *pObj = ThePartitionManager->getClosestObject(obj->getPosition(), obj->getVisionRange(), 0,
				Rva00260EB1Filter(obj, 1, false).link(Rva0026119DFilter().link(Rva002611BFFilter(obj).link(
				Rva0004584D(*(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
				BfmeFixedStorage0004543D(0, 0x59, 0x86)).link(&Rva00261513Filter(obj, true, -1.0f))))));
			if (pObj)
			{
				m_seeEnemy = true;
				break;
			}
		}
		if (m_prevSeeEnemy != m_seeEnemy)
		{
			if (m_seeEnemy)
				TheScriptEngine->rva0020C140(getName(), pInfo->m_scriptOnEnemySighted, this);
			else
				TheScriptEngine->rva0020C140(getName(), pInfo->m_scriptOnAllClear, this);
		}
	}

	if (!isEmpty(pInfo->m_scriptOnDestroyed))
	{
		int prevUnits = m_curUnits;
		m_curUnits = 0;
		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			if (iter.cur()->isEffectivelyDead())
				continue;
			ContainModuleInterface *contain = iter.cur()->getContain();
			HordeContainInterface *horde = contain ? contain->getHordeContainInterface() : 0;
			if (horde)
				m_curUnits += horde->getMemberCount(0);
			else
				m_curUnits++;
		}
		if (m_curUnits != prevUnits && m_curUnits <= m_destroyThreshold)
		{
			TheScriptEngine->rva0020C140(getName(), pInfo->m_scriptOnDestroyed, this);
			m_destroyThreshold = -1;
		}
	}

	if (!isEmpty(pInfo->m_scriptOnIdle))
	{
		bool isIdle = true;
		bool anyAliveInTeam = false;
		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			if (iter.cur()->isEffectivelyDead())
				continue;
			AIUpdateInterface *ai = iter.cur()->getAI();
			if (!ai)
				continue;
			anyAliveInTeam = true;
			if (!ai->isIdle())
				isIdle = false;
		}
		if (anyAliveInTeam && isIdle && m_wasIdle)
			TheScriptEngine->rva0020C140(getName(), pInfo->m_scriptOnIdle, this);
		m_wasIdle = isIdle;
	}
}
