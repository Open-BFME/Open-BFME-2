// cl: /O1 /EHsc /MD /arch:SSE /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// SkirmishAI.cpp -- SkirmishAI members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function and its
// callee SkirmishAI::transferUnitsToPlayer (0x002C6AFA); retail supplies the
// bytes. When a slave AI dies its units go to the player whose index is at
// +0x178.

#pragma pointers_to_members(full_generality, multiple_inheritance)

#include <map>
#include <new>
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

typedef int Int;

extern "C" void *memset(void *s, int c, unsigned n);

struct Coord3DBase;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

// BFME 2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (AITacticsGenerator.cpp has the same
// view): Version +0x28, AsciiString +0x6C, Real +0x70, UnsignedInt +0x78,
// Int +0x7C, Bool +0x90.
class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

// The +0x17C AsciiString -> int variable map; its rowed STLport spelling
// (clear 0x001F8927, operator[] 0x002C6F8C) keeps the established payload
// name from Rva002C717EMethod.cpp.
struct TreeHintPayload001F8ACB
{
	int m_val;
	TreeHintPayload001F8ACB() : m_val(0) {}
	TreeHintPayload001F8ACB(const TreeHintPayload001F8ACB &o) : m_val(o.m_val) {}
};

typedef _STL::pair<const AsciiString, TreeHintPayload001F8ACB> TreeHintPair001F8ACB;
typedef _STL::map<AsciiString, TreeHintPayload001F8ACB, _STL::less<AsciiString>, _STL::allocator<TreeHintPair001F8ACB> > Map001F8ACB;

// Rowed byte getter at 0x002AA22A reads Player+0x734; rowed dword getter at
// 0x005C4AF5 reads Team+0x40 (next team in the prototype's instance list).
class Rva002AA22AByteField
{
public:
	unsigned char get() const;			// 0x002AA22A
};

class Rva005C4AF5DwordField
{
public:
	int get() const;				// 0x005C4AF5
};

typedef int (Rva005C4AF5DwordField::*TeamNext)() const;

template<int NUMBITS>
class BitFlags
{
public:
	// Retail sub esp,0x2c leaves 0x24 bytes for kinds+member-ptr(8): kinds is
	// 0x24 bytes here; only the low 0x1c is memset (retail push 0x1c) with the
	// three ors below. N=69 mangles to $0EF (A=0..P=15 hex digits).
	union
	{
		unsigned int m_words[9];
		unsigned char m_bytes[0x24];
	};
};

class Team;

// TeamPrototype view: instance-list head is TeamFactory's +0x334 pattern
// (TeamFactoryFindTeam/TeamPrototypeTeamIterators precedent).
class TeamPrototype
{
public:
	unsigned char m_pad[0x334];
	Team *m_firstTeam;				// +0x334
};

struct ListNode
{
	ListNode *m_next;				// +0x00
	ListNode *m_prev;				// +0x04
	TeamPrototype *m_value;			// +0x08
};

// Player view: rva002AE2ED (rowed) grants this player the other player's
// sciences; +0x24 is copied from the dying AI's player (retail-measured).
// +0x2EC is the destination team (TeamDidPartialEnter 0x0039E9FD precedent);
// +0x32C is the prototype list head (list object with sentinel); the byte
// getter above proves +0x734.
class Player : public Rva002AA22AByteField
{
	friend class SkirmishAI;
public:
	void rva002AE2ED(Player *other);			// 0x002AE2ED
	Int getField24() const { return m_field24; }
	void setField24(Int value) { m_field24 = value; }

private:
	unsigned char m_pad00[0x24];
	Int m_field24;						// +0x24
	unsigned char m_pad28[0x2EC - 0x28];
	Team *m_team2EC;					// +0x2EC
	unsigned char m_pad2F0[0x32C - 0x2F0];
	ListNode *m_listHead32C;				// +0x32C list sentinel
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);				// 0x002A7A29
};

extern PlayerList *ThePlayerList;

class Object;

// Team view: transferKindOfUnitsTo is the rowed kind-filtered twin at
// 0x0039E6D1 (TeamDidPartialEnter.cpp); the +0x40 next link is the rowed
// Rva005C4AF5DwordField getter above, reached here through a member pointer
// so the call stays indirect like retail's.
class Team : public Rva005C4AF5DwordField
{
public:
	void transferKindOfUnitsTo(Team *newTeam, const BitFlags<69> &kinds);	// 0x0039E6D1
};

// SkirmishAI's AIBuilder base sits at offset 0; its onUnitCreated (WB name,
// unrowed 0x004EC3AC) takes the new unit, an object and a horde flag.
class AIBuilder
{
public:
	AIBuilder(Player *);
	~AIBuilder();
	void onUnitCreated(Object *object, Object *other, bool isHorde);	// 0x004EC3AC
	void update(); // WB 0x0136EAF0; native 0x004ECB19
	void DoXfer(Xfer *xfer);					// 0x004EC1D9
private:
	unsigned char m_prefix[0x15C];
};

class Rva004E93A8 { public: int rva004E93A8(); };
class Rva004E9600;
class Rva002A8F24 {
public:
 Rva004E9600 *rva002A8B24(void *key);
};
extern Rva002A8F24 *g_00DFEEF8;
class Rva00506B1B { public: void rva00506B2F(); };

// Native TacticalAI +0x10 is the tactics generator. WB names the two
// forwarding members; their retail tails reach its established Team methods.
class Rva00506909
{
public:
    void rva005059A1(Team *team);
    void rva00505A56(Team *team);
};

class TacticalAI
{
public:
    __declspec(noinline) void Register(Team *team);
    __declspec(noinline) void UnRegister(Team *team);
    void DoXfer(Xfer *xfer);					// 0x002C63A1
private:
    unsigned char m_pad00[0x10];
    Rva00506909 *m_generator;
};

class Rva002C60E4 {
public:
 Rva002C60E4(void *, bool);
private:
 unsigned char m_storage[0x2C];
};

class SkirmishAI : public AIBuilder
{
public:
	SkirmishAI(Player *player, void *master, bool first);
	void Register(Team *team);
	void UnRegister(Team *team);
	void onUnitCreated(Object *object, Object *other);
	void onHordeCreated(Object *object, Object *other);
	__declspec(noinline) void doSpecialSlaveAIDying();
	__declspec(noinline) void doSpecialMasterAIDying();
	void transferUnitsToPlayer(Player *player);		// 0x002C6AFA
	Int resetMaster();					// 0x002C68CE
	void doSpecialSlaveAIUpdate();				// 0x002C6879
	void update();
	void updatePhase();
	void DoXfer(Xfer *xfer);

private:
	Player *m_player;					// +0x15C
	void *m_specialMaster160; // native constructor stores second argument
	TacticalAI *m_tacticalAI;			// +0x164
	bool m_disabled168;					// +0x168, set: creations are ignored
	unsigned char m_pad169[3];
	Int m_difficulty16C;
	float m_time170;
	unsigned int m_frame174;
	Int m_masterPlayerIndex;				// +0x178
	Map001F8ACB m_values17C;				// +0x17C (size at +0x180)
};

// WB E8A420 and native 2C6EE0 agree on base/player/master/first arguments.
// Native constructor fixes all field initializers and the 0x2C allocation;
// 2C717E and 2C7196 independently establish the string-to-int map at +17C.
SkirmishAI::SkirmishAI(Player *player, void *master, bool first)
 : AIBuilder(player), m_player(player), m_specialMaster160(master),
   m_tacticalAI(0), m_disabled168(false), m_difficulty16C(0), m_time170(0),
   m_frame174(TheGameLogic->getFrame()), m_masterPlayerIndex(-1)
{
 m_tacticalAI = reinterpret_cast<TacticalAI *>(new Rva002C60E4(player, first));
}

// WB E8A830 names update and its special slave/master paths. Native
// 002C6BFF..002C6C8E fixes the 143-byte extent and the release-build shape:
// disabled flag +168, master index +178, player +15C, tactical delegate +164.
// The registry lookup returns the same receiver immediately passed to the
// rowed count provider 4E93A8; its semantic class name remains unresolved.
// The tactical delegate is passed unchanged to the rowed +4-flag dispatcher
// 506B2F. These casts preserve the existing address-named provider contracts.
void SkirmishAI::update()
{
 if (!m_disabled168) {
  if (!m_player->get()) {
   if (m_masterPlayerIndex != -1)
    doSpecialSlaveAIUpdate();
   updatePhase();
   AIBuilder::update();
   reinterpret_cast<Rva00506B1B *>(m_tacticalAI)->rva00506B2F();
  } else {
   if (m_masterPlayerIndex == -1)
    doSpecialMasterAIDying();
   else
    doSpecialSlaveAIDying();
   m_disabled168 = true;
  }
 } else {
  unsigned int count = reinterpret_cast<Rva004E93A8 *>(
   g_00DFEEF8->rva002A8B24(m_player))->rva004E93A8();
  if (count > 1 || (count == 1 && m_specialMaster160 != 0))
   reinterpret_cast<Rva00506B1B *>(m_tacticalAI)->rva00506B2F();
 }
}

// SkirmishAI::doSpecialSlaveAIDying, retail 0x002C6BE1.
void SkirmishAI::doSpecialSlaveAIDying()
{
	transferUnitsToPlayer(ThePlayerList->getNthPlayer(m_masterPlayerIndex));
}

// SkirmishAI::doSpecialMasterAIDying, retail 0x002C6B92 (79 bytes).
// Identity (target): WB SkirmishAI.cpp names it and its callees resetMaster
// (0x002C68CE), doSpecialSlaveAIUpdate (0x002C6879) and transferUnitsToPlayer
// (wb-lead 3/callgraph). A new master index (not -1) is stored at +0x178;
// the new master inherits the dying AI player's sciences and +0x24 value and
// receives its units.
void SkirmishAI::doSpecialMasterAIDying()
{
	Int master = resetMaster();
	if (master != -1)
	{
		m_masterPlayerIndex = master;
		doSpecialSlaveAIUpdate();
		Player *masterPlayer = ThePlayerList->getNthPlayer(master);
		masterPlayer->rva002AE2ED(m_player);
		masterPlayer->setField24(m_player->getField24());
		transferUnitsToPlayer(masterPlayer);
	}
}

// SkirmishAI::onUnitCreated, retail 0x002C6A8D (27 bytes): WB names it in
// SkirmishAI.cpp (asserts the object at line 357) and its callee
// AIBuilder::onUnitCreated, forwarded with the horde flag clear.
void SkirmishAI::onUnitCreated(Object *object, Object *other)
{
	if (!m_disabled168)
		AIBuilder::onUnitCreated(object, other, false);
}

// SkirmishAI::onHordeCreated, retail 0x002C6AA8 (27 bytes): WB's twin of
// onUnitCreated, forwarding with the horde flag set.
void SkirmishAI::onHordeCreated(Object *object, Object *other)
{
	if (!m_disabled168)
		AIBuilder::onUnitCreated(object, other, true);
}

// ?transferUnitsToPlayer@SkirmishAI@@QAEXPAVPlayer@@@Z @0x002C6AFA (152B).
// Identity (target): pinned name (lane=named); callers 0x002C6BD8
// (doSpecialSlaveAIDying) and 0x002C6BF8 (doSpecialMasterAIDying) both hand
// the master player's entry; prev 0x002C6AA8/next 0x002C6B92 live in this TU.
// Retail skips human/defeated players (byte field +0x734), hands the dying
// AI player's teams (list at m_player+0x32C, instances at +0x334, next at
// Team+0x40) to the new owner's +0x2EC team, filtered to KINDOF bits 3/90/14
// (memset 0x1c plus three ors). No donor.
void SkirmishAI::transferUnitsToPlayer(Player *player)
{
	if (player->get() != 0)
		return;
	Team *newTeam = player->m_team2EC;
	Player *src = m_player;
	ListNode **listAddr = &src->m_listHead32C;
	BitFlags<69> kinds;
	memset(&kinds, 0, 0x1c);
	kinds.m_words[0] |= 8;
	kinds.m_bytes[11] |= 4;
	kinds.m_bytes[1] |= 0x40;
	ListNode *head = *listAddr;
	ListNode *cur = head->m_next;
	if (cur == head)
		return;
	TeamNext next = &Rva005C4AF5DwordField::get;
	do
	{
		TeamPrototype *proto = cur->m_value;
		Team *team = proto->m_firstTeam;
		while (team != 0)
		{
			team->transferKindOfUnitsTo(newTeam, kinds);
			if (team != 0)
				team = (Team *)(team->*next)();
		}
		cur = cur->m_next;
	} while (cur != head);
}

// WB SkirmishAI.cpp lines 339/348 name these Team overloads and show the
// +0x168 creation guard and +0x164 TacticalAI delegate. Native complete
// extents: 002C6A5F..002C6A76 and 002C6A76..002C6A8D (RET4 each).
void SkirmishAI::Register(Team *team)
{
    if (!m_disabled168)
        m_tacticalAI->Register(team);
}

void SkirmishAI::UnRegister(Team *team)
{
    if (!m_disabled168)
        m_tacticalAI->UnRegister(team);
}

// SkirmishAI::DoXfer, retail 0x002C7008 (374 bytes). WB names it in
// SkirmishAI.cpp (callgraph lead; assert "numberOfVariables ==
// m_variables.size()"), with callees AIBuilder::DoXfer and TacticalAI::DoXfer
// on the +0x164 member. Version 1/1, the +0x168 flag, the +0x16C value
// through a copy, +0x170, +0x174 and the +0x178 master index; then the
// AsciiString -> int variables at +0x17C, cleared and rebuilt on load.
void SkirmishAI::DoXfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_disabled168;
	unsigned int difficulty = m_difficulty16C;
	*xfer == difficulty;
	m_difficulty16C = difficulty;
	*xfer == m_time170;
	*xfer == m_frame174;
	*xfer == m_masterPlayerIndex;
	AIBuilder::DoXfer(xfer);
	m_tacticalAI->DoXfer(xfer);
	unsigned int numberOfVariables = m_values17C.size();
	*xfer == numberOfVariables;
	if (xfer->IsStoring())
	{
		Map001F8ACB::iterator it = m_values17C.begin();
		Map001F8ACB::iterator end = m_values17C.end();
		while (it != end)
		{
			AsciiString name(it->first);
			Int value = it->second.m_val;
			*xfer == name;
			*xfer == value;
			++it;
		}
	}
	else if (xfer->IsLoading())
	{
		m_values17C.clear();
		for (unsigned int i = 0; i < numberOfVariables; ++i)
		{
			AsciiString name;
			Int value;
			*xfer == name;
			*xfer == value;
			m_values17C[name].m_val = value;
		}
	}
}
