// ?link@BfmeLinkedObj@@QAEXPAV1@H@Z
// partial score=0.79 date=2026-10-09
// cl: /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?transferAssetsFromThat@Player@@QAEXPAV1@_N@Z @0x002AEA9F 1032B.
//
// Target evidence: thiscall on Player with ret 8; the second argument is
// read as a byte (cmp byte ptr [ebp+0xC]) so it is a bool; the +0x2EC
// default team guards the body; that player's +0x32C team-prototype list
// is walked with the team-instance member pointer 0x009C4AF5 (as in
// PlayerRva002AD93A.cpp) calling the rowed Team 0x003A1C3A with true on
// every team; every member that is none of kind-of 0x59/0x86/0x2F goes to
// one of two four-byte STLport lists (0x004EC36C/0x005925E2/0x004EC395)
// by status 0x3E; the first list is moved to the default team (rowed
// 0x00290DBB unless status 0x26; status 0x50 when the flag is set; a
// kind-of 0x6D container takes the team instead; otherwise contain slots
// 0x10/0x08/0x54 then setTeam and TheRadar remove/add) between a save and
// restore of the +0x3BC member's +0x110 flag (setter 0x0039B780) with the
// pinned 0x0039CBCE per object; the second list runs the rowed 0x0029A12B
// unless status 0x26; that player's completed upgrade mask (+0x13C) is
// copied (0x0004548B) and every set bit but the thirteen faction and hero
// choice upgrades is granted through the rowed addUpgrade 0x002AE329 with
// status 2; then that player's money (+0x90) is withdrawn (0x003B0CB3) and
// deposited here (0x003B0D7C); then the +0x60 score block's +0x18/+0x1C
// counts are added here with one bumped by that player's +0x34 +0x1BC flag.
// Donor (Zero Hour Player::transferAssetsFromThat): the team walk, the
// collect-then-setTeam split and the money transfer. The caller 0x003BB667
// (pinned ?bfmeLinkObjectsA70) is ScriptActions' transfer-assets action.

#include "ascii_string.h"
#include "PlayerUpgradeStatus.h"
#include <list>

namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };

class Object;
class Team;
class Player;

template <class OBJCLASS>
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

// The member iterator BFME2 returns by value from Team::iterate_TeamMemberList
// (24 bytes, out-of-line advance; see TeamRva0039DDC2.cpp).
template <>
class DLINK_ITERATOR<Object>
{
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

#include "Common/Snapshot.h"

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva003A1C3A(bool flag);
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
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad[0x108];
	unsigned char m_kindOf[0x20];
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool slot02();
	virtual void slot03();
	virtual Bool slot04();
#define CONTAIN_SLOT(n) virtual void slot##n();
	CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07) CONTAIN_SLOT(08) CONTAIN_SLOT(09)
	CONTAIN_SLOT(10) CONTAIN_SLOT(11) CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14)
	CONTAIN_SLOT(15) CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20)
#undef CONTAIN_SLOT
	virtual void slot21(Team *team); // slot 0x54
};

// Object::rva00290DBB's two player views.
struct Rva002A9B58;

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline bool isKindOf(int t) const { return getTemplate()->isKindOf(t); }
	ContainModuleInterface *getContain() const { return m_contain; }
	Object *getContainedBy() const { return m_containedBy; }
	Bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
	void setTeam(Team *team);
	void rva00290DBB(Rva002A9B58 *oldOwner, Rva002A9B58 *newOwner);
	void rva0029A12B();

private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x250 - 0x08];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_containedBy; // +0x274
};

struct Rva002D76C6Owner;

class Radar
{
public:
	void removeObject(Rva002D76C6Owner *obj);
	void addObject(Object *obj);
};
extern Radar *TheRadar;

class W3DBridge
{
public:
	void setEnabled(bool enable);
};

// The +0x3BC member: its +0x110 flag (setter folded with W3DBridge's) and
// the pinned per-object call.
class Rva0039CBCE
{
public:
	Bool isEnabled() const { return m_enabled; }
	void setEnabled(Bool enable) { ((W3DBridge *)this)->setEnabled(enable); }
	void rva0039CBCE(Object *obj, Int x);

private:
	unsigned char m_pad[0x110];
	Bool m_enabled; // +0x110
};

class UpgradeTemplate
{
public:
	const AsciiString &getUpgradeName() const { return m_name; }
	UnsignedInt getUpgradeBit() const { return m_bit; }

private:
	unsigned char m_pad[0x8];
	AsciiString m_name; // +0x08
	unsigned char m_padC[0x38 - 0xC];
	UnsignedInt m_bit; // +0x38
};

// The 1024-bit upgrade mask (copy ctor rowed 0x0004548B, set-bit count
// rowed 0x00046827).
struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128 &other);
	void clear(UnsignedInt bit) { m_bits[bit >> 5] &= ~(1 << (bit & 0x1F)); }

	UnsignedInt m_bits[0x20];
};

class Rva00046827
{
public:
	Int rva00046827();
};

class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;

class Rva0026F0F0
{
public:
	void *rva0026F0F0(const void *mask);
};

class Rva0039B795;
class Rva0039B7AD;

class Rva003B0D7C
{
public:
	UnsignedInt rva003B0CB3(UnsignedInt amount, Rva0039B795 *source, bool flag);
	void rva003B0D7C(Int amount, Rva0039B7AD *source, bool flag);

	Int m_pad0;
	UnsignedInt m_money; // +0x04
};

class PlayerTemplateView
{
public:
	unsigned char m_pad[0x1BC];
	Bool m_1BC;
};

class ScoreKeeper
{
public:
	__forceinline void addCounts(const ScoreKeeper *other, Bool second)
	{
		Int a = other->m_18;
		Int b = other->m_1C;
		if (second)
			++b;
		else
			++a;
		m_18 += a;
		m_1C += b;
	}

	unsigned char m_pad[0x18];
	Int m_18; // +0x18
	Int m_1C; // +0x1C
};

class Player
{
public:
	void transferAssetsFromThat(Player *that, Bool flag);
	Upgrade *rva002AE329(const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status, Int x);
	Team *getDefaultTeam() const { return m_defaultTeam; }
	ScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }
	Rva003B0D7C *getMoney() { return &m_money; }

private:
	unsigned char m_pad00[0x34];
	PlayerTemplateView *m_playerTemplate; // +0x34
	unsigned char m_pad38[0x60 - 0x38];
	ScoreKeeper m_scoreKeeper; // +0x60
	unsigned char m_pad80[0x90 - 0x80];
	Rva003B0D7C m_money; // +0x90
	unsigned char m_pad98[0x13C - 0x98];
	BfmeFixedStorage128 m_upgradesCompleted; // +0x13C
	unsigned char m_pad1BC[0x2EC - 0x1BC];
	Team *m_defaultTeam; // +0x2EC
	unsigned char m_pad2F0[0x32C - 0x2F0];
	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C
	unsigned char m_pad330[0x3BC - 0x330];
	Rva0039CBCE m_3BC; // +0x3BC
};

void Player::transferAssetsFromThat(Player *that, Bool flag)
{
	Team *defaultTeam = getDefaultTeam();
	if (!defaultTeam)
		return;

	_STL::list<const Object *> objsToTransfer;
	_STL::list<const Object *> objsToNotify;

	for (PlayerTeamNode *it = that->m_playerTeamPrototypes->m_next; it != that->m_playerTeamPrototypes; it = it->m_next)
	{
		for (DLINK_ITERATOR<Team> iter = it->m_value->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			team->rva003A1C3A(true);
			for (DLINK_ITERATOR<Object> iterObj = team->iterate_TeamMemberList(); !iterObj.done(); iterObj.advance())
			{
				const Object *obj = iterObj.cur();
				if (!obj)
					continue;
				if (obj->isKindOf(0x59) || obj->isKindOf(0x86) || obj->isKindOf(0x2F))
					continue;
				if (obj->testStatus((ObjectStatusTypes)0x3E))
					objsToNotify.push_back(obj);
				else
					objsToTransfer.push_back(obj);
			}
		}
	}

	Bool wasEnabled = m_3BC.isEnabled();
	m_3BC.setEnabled(false);
	for (_STL::list<const Object *>::iterator itObjs = objsToTransfer.begin(); itObjs != objsToTransfer.end(); ++itObjs)
	{
		Object *obj = const_cast<Object *>(*itObjs);
		if (!obj)
			continue;
		if (!obj->testStatus((ObjectStatusTypes)0x26))
			obj->rva00290DBB((Rva002A9B58 *)that, (Rva002A9B58 *)this);
		if (flag)
			obj->setStatus((ObjectStatusTypes)0x50, true);
		Object *container = obj->getContainedBy();
		if (container && container->isKindOf(0x6D))
		{
			container->setTeam(defaultTeam);
		}
		else
		{
			ContainModuleInterface *contain = obj->getContain();
			if (contain && (contain->slot04() || contain->slot02()))
				contain->slot21(defaultTeam);
			obj->setTeam(defaultTeam);
			TheRadar->removeObject((Rva002D76C6Owner *)obj);
			TheRadar->addObject(obj);
		}
		m_3BC.rva0039CBCE(obj, 1);
	}
	m_3BC.setEnabled(wasEnabled);

	for (_STL::list<const Object *>::iterator itNotify = objsToNotify.begin(); itNotify != objsToNotify.end(); ++itNotify)
	{
		if (*itNotify && !(*itNotify)->testStatus((ObjectStatusTypes)0x26))
			const_cast<Object *>(*itNotify)->rva0029A12B();
	}

	BfmeFixedStorage128 upgrades(that->m_upgradesCompleted);
	while (((Rva00046827 *)&upgrades)->rva00046827() > 0)
	{
		const UpgradeTemplate *upgradeTemplate = (const UpgradeTemplate *)((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0(&upgrades);
		if (!upgradeTemplate)
			break;
		const AsciiString &name = upgradeTemplate->getUpgradeName();
		if (name.compare("Upgrade_RohanDualEconomyChoice") != 0 &&
			name.compare("Upgrade_IsengardDualEconomyChoice") != 0 &&
			name.compare("Upgrade_MordorDualEconomyChoice") != 0 &&
			name.compare("Upgrade_EvilDualEconomyChoice") != 0 &&
			name.compare("Upgrade_MenFaction") != 0 &&
			name.compare("Upgrade_ElfFaction") != 0 &&
			name.compare("Upgrade_DwarvesFaction") != 0 &&
			name.compare("Upgrade_IsengardFaction") != 0 &&
			name.compare("Upgrade_MordorFaction") != 0 &&
			name.compare("Upgrade_WildFaction") != 0 &&
			name.compare("Upgrade_GandalfWhite") != 0 &&
			name.compare("Upgrade_Anduril") != 0 &&
			name.compare("Upgrade_ElvenGift") != 0)
		{
			rva002AE329(upgradeTemplate, UPGRADE_STATUS_COMPLETE, 0);
		}
		upgrades.clear(upgradeTemplate->getUpgradeBit());
	}

	UnsignedInt allMoney = that->getMoney()->m_money;
	that->getMoney()->rva003B0CB3(allMoney, 0, true);
	getMoney()->rva003B0D7C(allMoney, 0, true);

	if (that->getScoreKeeper())
	{
		ScoreKeeper *mine = getScoreKeeper();
		if (mine)
		{
			Int a = that->getScoreKeeper()->m_18;
			Int b = that->getScoreKeeper()->m_1C;
			if (that->m_playerTemplate->m_1BC)
				++b;
			else
				++a;
			mine->m_18 += a;
			mine->m_1C += b;
		}
	}
}
