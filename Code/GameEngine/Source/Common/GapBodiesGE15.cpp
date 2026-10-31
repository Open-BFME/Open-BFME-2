// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (fifteenth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees use the ledger's
// existing spellings.

struct GapPair
{
	int a;
	int b;
};

// --- 0x002E7334 (26B): a word and a pair; 0x002E734E (58B): cell callback.
struct Rva002E734ECell { int m_pad00[3]; unsigned int m_flags; };

struct Rva002E7334
{
	Rva002E7334(int value, const GapPair &pair);
	int rva002E734E(Rva002E734ECell *from, Rva002E734ECell *to, int cellColumn, int cellRow);
	int m_00;
	int m_04;
	int m_08;
};

Rva002E7334::Rva002E7334(int value, const GapPair &pair) : m_00(value), m_04(pair.a), m_08(pair.b)
{
}

// ?rva002E734E@Rva002E7334@@QAEHPAURva002E734ECell@@0HH@Z @0x002E734E (58B)
// The trailing "&& 1" keeps retail's movzx between shr 16 and and 1.
int Rva002E7334::rva002E734E(Rva002E734ECell *from, Rva002E734ECell *to, int cellColumn, int cellRow)
{
	if (cellColumn == m_04 && cellRow == m_08)
		return 0;
	unsigned int flags = to->m_flags;
	if ((flags & 0xF) == 0 || (flags & 0xF) == 1)
		return ((unsigned char)(flags >> 16) & 1) && 1;
	return 1;
}

// --- 0x004E4E05 (37B): copy five settings from another record;
// 0x004E4E2A (48B): the +0x08 value clamped to [0, 1].
class Rva004E4E05
{
public:
	void rva004E4E05(const Rva004E4E05 *that);
	void rva004E4E2A(float value);
private:
	char m_pad[8];
	float m_08;
	char m_pad0C[0x18 - 0x0C];
	int m_18;
	char m_pad1C[0x24 - 0x1C];
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
};

void Rva004E4E05::rva004E4E05(const Rva004E4E05 *that)
{
	m_24 = that->m_24;
	m_30 = that->m_30;
	m_18 = that->m_18;
	m_28 = that->m_28;
	m_2C = that->m_2C;
}

void Rva004E4E05::rva004E4E2A(float value)
{
	m_08 = (!(0.0f > value) && value > 1.0f) ? 1.0f : (0.0f > value ? 0.0f : value);
}

// --- 0x0030F642 (55B): unlink a node (+0x04 previous, +0x08 next) from the
// list with tail +0x0C and head +0x10, clearing its +0x0C; 0x0030F679 (30B):
// whether a node from the tail back carries the id (+0x10).
struct Rva0030F642Node
{
	int m_00;
	Rva0030F642Node *m_prev;								// +0x04
	Rva0030F642Node *m_next;								// +0x08
	int m_0C;
	int m_id;												// +0x10
};

class Rva0030F642
{
public:
	void rva0030F642(Rva0030F642Node *node);
	bool rva0030F679(int id) const;
private:
	char m_pad[0x0C];
	Rva0030F642Node *m_tail;								// +0x0C
	Rva0030F642Node *m_head;								// +0x10
};

// --- 0x0052A603 / 0x0052A634 (30B each): vtables 0x00C684AC / 0x00C684B4
// over a cleared word and a pair; 0x0052A621 (19B) / 0x0052A652 (8B): the
// +0x08 member's rowed 0x0052A36A / 0x0052A387.
#define GAP_VTABLE_PAIR_CTOR(NAME) \
	class NAME \
	{ \
	public: \
		NAME(const GapPair &pair); \
		virtual ~NAME() {} \
	private: \
		int m_04; \
		int m_08; \
		int m_0C; \
	}; \
	NAME::NAME(const GapPair &pair) : m_04(0), m_08(pair.a), m_0C(pair.b) \
	{ \
	}

GAP_VTABLE_PAIR_CTOR(Rva0052A603)
GAP_VTABLE_PAIR_CTOR(Rva0052A634)

struct Out0052A36A;

class Rva0052A36A
{
public:
	void rva0052A36A(Out0052A36A *out);						// 0x0052A36A
	void rva0052A387(int value);							// 0x0052A387
};

class Rva0052A621
{
public:
	Out0052A36A *rva0052A621(Out0052A36A *out);
	void rva0052A652(int value);
private:
	char m_pad[8];
	Rva0052A36A m_08;
};

Out0052A36A *Rva0052A621::rva0052A621(Out0052A36A *out)
{
	m_08.rva0052A36A(out);
	return out;
}

void Rva0052A621::rva0052A652(int value)
{
	m_08.rva0052A387(value);
}

// --- 0x005DBB4D (45B): the 8x8 short table at +0x838, 0 out of range.
class Rva005DBB4D
{
public:
	short rva005DBB4D(unsigned short row, unsigned short column) const;
private:
	char m_pad[0x838];
	short m_table[8][8];
};

short Rva005DBB4D::rva005DBB4D(unsigned short row, unsigned short column) const
{
	if (row < 8 && column < 8)
		return m_table[row][column];
	return 0;
}
