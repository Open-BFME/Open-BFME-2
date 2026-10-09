// cl: /O1 /EHsc /MD /arch:SSE /G7 /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// LivingWorldBattle constructor, retail 0x003F6F0D..0x003F7000 (243 bytes,
// ret 0x14). Its only caller is 0x0020FC56. Owner from the callees retail
// makes on the new object: WorldBuilder's LivingWorldBattle::AddArmy
// (pinned 0x003F6DF9), the battle-player find-or-create 0x003F6D35 on the
// +0x18 player-slot vector, and the rowed 0x003F43D3. The deleting
// destructor 0x003F6CDD (primary vtable 0x00C3709C slot 0) and the
// destructor 0x003F6A91 restore the same two vtables (0x00C3709C at +0 and
// 0x00C37088 at +4) and unwind in this order: the +0x18 vector, the +4
// listener base (vtable 0x00C3702C whose slot 0 the battle overrides with
// RemoveArmy through the thunk 0x003F59FE), the +8 list base (rowed ctor
// 0x00330757 and inline buffer free) and Snapshot (0x00BBB554) last. So the
// bases are declared Snapshot then the list then the listener; MSVC places
// the non-polymorphic list after both vtable pointers, which is why its
// constructor runs before the +4 vtable store. Fields: +0x24 second
// argument +0x28 the 8-byte fifth argument +0x30 zero +0x34 first argument
// +0x38 winning side -1 (LivingWorldBattle.cpp) +0x3C zero. For each player
// of the fourth argument the battle creates its slot and adds every army of
// the third argument whose +0x54 player id equals the player's +0x14 id.
// WorldBuilder twin 0x0104A380 (unnamed) has the same shape.
// class-gate: allow Snapshot proved codegen view: retail stores no Snapshot vtable before the +8 base call yet sets the Snapshot EH state first (and the dtor 0x003F6A91 restores 0x00BBB554 last); the canonical inline ctor stores 0x00BBB554 ahead of that call so a novtable view with a declared dtor stands in
#include <vector>

class Xfer;

class __declspec(novtable) Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();
protected:
	virtual void loadPostProcess(void) = 0;
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

typedef int Int;
typedef unsigned int UnsignedInt;

// The +8 list base: rowed out-of-line ctor at 0x00330757 (vector plus an
// int defaulted to -1).
class Rva00330757Member
{
public:
	Rva00330757Member() throw();
	~Rva00330757Member() throw();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
	int m_flags;
};

// The +4 listener interface (vtable 0x00C3702C: five empty slots).
class LivingWorldBattleListener
{
public:
	LivingWorldBattleListener() {}
	~LivingWorldBattleListener() {}
	virtual void onArmyRemoved(void *army);
	virtual void slot1(int a, int b);
	virtual void slot2(int a);
	virtual void slot3(int a);
	virtual void slot4(int a);
};

// 16-byte element stand-in whose vector base is the rowed 0x00211E58 body
// (the slots are 0x1C bytes; this constructor never touches them).
struct BfmeE16 { float x, y, z, w; };

struct LivingWorldBattlePlayerView
{
	char m_pad00[0x14];
	Int m_id; // +0x14
};

struct LivingWorldBattleArmyView
{
	char m_pad00[0x54];
	Int m_playerID; // +0x54
};

// The 8-byte fifth argument copied to +0x28; its member-wise inline copy
// ctor gives retail's store schedule (WorldBuilder copies it through a temp).
struct LivingWorldBattleCoord
{
	LivingWorldBattleCoord() { *(float *)&m_a = 0.0f; *(float *)&m_b = 0.0f; }
	LivingWorldBattleCoord(const LivingWorldBattleCoord &o) : m_a(o.m_a), m_b(o.m_b) {}
	Int m_a;
	Int m_b;
};

struct Rva003F6D35Inner;

class Rva003F6D35Owner
{
public:
	Rva003F6D35Inner *findOrCreateRva003F6D35(void *player);
};

class Rva003F43D3
{
public:
	void rva003F43D3();
};

class LivingWorldBattle : public Snapshot, public Rva00330757Member, public LivingWorldBattleListener
{
public:
	LivingWorldBattle();
	LivingWorldBattle(Int first, Int second,
		const _STL::vector<LivingWorldBattleArmyView *> &armies,
		const _STL::vector<LivingWorldBattlePlayerView *> &players,
		const LivingWorldBattleCoord &coord);
	virtual ~LivingWorldBattle();
	void AddArmy(Int player, void *army);
	virtual void onArmyRemoved(void *army);

protected:
	virtual void loadPostProcess(void);
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);

private:
	_STL::vector<BfmeE16> m_slots; // +0x18
	Int m_second; // +0x24
	LivingWorldBattleCoord m_coord; // +0x28
	Int m_30;
	Int m_first; // +0x34
	Int m_winningSide; // +0x38
	Int m_3C;
};

LivingWorldBattle::LivingWorldBattle(Int first, Int second,
	const _STL::vector<LivingWorldBattleArmyView *> &armies,
	const _STL::vector<LivingWorldBattlePlayerView *> &players,
	const LivingWorldBattleCoord &coord)
	: m_second(second), m_coord(coord), m_30(0), m_first(first), m_winningSide(-1), m_3C(0)
{
	for (UnsignedInt i = 0; i < players.size(); ++i)
	{
		LivingWorldBattlePlayerView *player = players[i];
		((Rva003F6D35Owner *)this)->findOrCreateRva003F6D35(player);
		for (UnsignedInt j = 0; j < armies.size(); ++j)
		{
			if (armies[j]->m_playerID == player->m_id)
				AddArmy((Int)player, armies[j]);
		}
	}
	((Rva003F43D3 *)this)->rva003F43D3();
}

// Native3F6A3A..3F6A8B81B default constructor, called by224B2100E6
// deserializer allocating0x40. Primary name() at3F6A8B returns
// LivingWorldBattle; vtables +0/+4 match the parameterized constructor.
// Both coordinate words are initialized through float views: native XORPS
// and two MOVSS independently prove this initialization type.
LivingWorldBattle::LivingWorldBattle()
 : m_second(0),m_coord(),m_30(0),m_first(0),m_winningSide(-1),m_3C(0)
{
}
