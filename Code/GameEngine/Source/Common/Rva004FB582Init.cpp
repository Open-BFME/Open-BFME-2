// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FB582 (126B): channel-driven init. One-time init of the channel
// object at 0x00E04508 (its first byte is the done flag), three channel
// queries off the target's +0x14 field into +0x0C/+0x10/+0x14, then a
// by-value slot call on each of the +0x68/+0x74/+0x80 subobjects. The
// channel init is GatherWorldInformation; three callees are pinned.

// 0x0050366B is rowed as LWAIWorldInformation::GatherWorldInformation.
class LWAIWorldInformation
{
public:
	void GatherWorldInformation();
};

class Rva00501DF1
{
public:
	int rva00501DF1(int v);
};

class Rva00501813
{
public:
	int rva00501813(int v);
};

class Rva00501844
{
public:
	int rva00501844(int v);
};

// The three slot calls are range erases (begin, end) of the rowed vectors
// at 0x003FA4DB, 0x002BF70F and 0x005B129F.
struct BfmePod8;
struct BfmePod16;
struct Rva005B09D8Record;
namespace _STL
{
template <class _Tp> class allocator;
template <class _Tp, class _Alloc> class vector;
template <>
class vector<BfmePod8, allocator<BfmePod8> >
{
public:
	BfmePod8 *erase(BfmePod8 *first, BfmePod8 *last);
	void clear() { erase(_M_start, _M_finish); }
	BfmePod8 *_M_start;
	BfmePod8 *_M_finish;
};
template <>
class vector<BfmePod16, allocator<BfmePod16> >
{
public:
	BfmePod16 *erase(BfmePod16 *first, BfmePod16 *last);
	void clear() { erase(_M_start, _M_finish); }
	BfmePod16 *_M_start;
	BfmePod16 *_M_finish;
};
}
class Rva005B129FVector
{
public:
	Rva005B09D8Record *erase(Rva005B09D8Record *first, Rva005B09D8Record *last);
	void clear() { erase(_M_start, _M_finish); }
	Rva005B09D8Record *_M_start;
	Rva005B09D8Record *_M_finish;
};
typedef _STL::vector<BfmePod8, _STL::allocator<BfmePod8> > Rva003FA4DB;
typedef _STL::vector<BfmePod16, _STL::allocator<BfmePod16> > Rva002BF70F;
typedef Rva005B129FVector Rva005B129F;

struct Rva00E04508Channel
{
	unsigned char m_initialized;	// +0x00 done flag
};

// The data ledger owns this address in Rva007B6880Thunks.cpp.
extern unsigned int g_Va00E04508;

struct Rva004FB582Target
{
	char m_pad[0x14];
	int val14;	// +0x14 queried field
};

class Rva004FB582Owner
{
public:
	void rva004FB582();

private:
	Rva004FB582Target *m_00;	// +0x00 (queried target)
	char m_pad04[8];		// +0x04..0x0B
	int m_0C;			// +0x0C
	int m_10;			// +0x10
	int m_14;			// +0x14
	char m_pad18[0x50];		// +0x18..0x67
	Rva003FA4DB m_68;		// +0x68
	char m_pad70[4];		// +0x70..0x73
	Rva002BF70F m_74;		// +0x74
	char m_pad7C[4];		// +0x7C..0x7F
	Rva005B129F m_80;		// +0x80
};

void Rva004FB582Owner::rva004FB582()
{
	Rva00E04508Channel *channel = (Rva00E04508Channel *)&g_Va00E04508;
	if (!channel->m_initialized)
	{
		((LWAIWorldInformation *)channel)->GatherWorldInformation();
		channel->m_initialized = 1;
	}
	if (m_00)
	{
		m_0C = ((Rva00501DF1 *)channel)->rva00501DF1(m_00->val14);
		m_10 = ((Rva00501813 *)channel)->rva00501813(m_00->val14);
		m_14 = ((Rva00501844 *)channel)->rva00501844(m_00->val14);
	}
	m_68.clear();
	m_74.clear();
	m_80.clear();
}

// 0x004FB8A8 (124B): re-runs the channel init unconditionally, then for each
// LivingWorld player (TheLivingWorldLogic +0x8C vector, the rowed bounds-
// checked lookup 0x002B52A8) clears the +0x50 word of the player's +0x4C
// subobject (this owner's +0x04) and makes the same three slot calls, +0x80
// first. Identity unproven; address-derived name.
class Rva002E2903Player;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *GetPlayerAtIndex(int);
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva004FB8A8PlayerVector
{
	int size() const { return m_end - m_begin; }
	Rva002E2903Player **m_begin;
	Rva002E2903Player **m_end;
};

struct Rva004FB8A8Players
{
	char m_pad[0x8C];
	Rva004FB8A8PlayerVector m_players;	// +0x8C
};

class Rva004FB8A8Slots
{
public:
	char m_pad00[4];
	int m_04;					// player +0x50
	char m_pad08[0x60];
	Rva003FA4DB m_68;
	char m_pad70[4];
	Rva002BF70F m_74;
	char m_pad7C[4];
	Rva005B129F m_80;
};

void rva004FB8A8()
{
	((LWAIWorldInformation *)&g_Va00E04508)->GatherWorldInformation();
	for (int i = 0; i < ((Rva004FB8A8Players *)TheLivingWorldLogic)->m_players.size(); ++i)
	{
		Rva004FB8A8Slots *slots = (Rva004FB8A8Slots *)((char *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->GetPlayerAtIndex(i) + 0x4C);
		slots->m_04 = 0;
		slots->m_80.clear();
		slots->m_68.clear();
		slots->m_74.clear();
	}
}
