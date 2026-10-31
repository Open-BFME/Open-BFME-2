// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (twenty-sixth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.

// Declaration-only views of the STLport vector and tree copy constructors
// these holders call; no container code is instantiated here.
namespace _STL {
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	vector(const vector<T, A> &that);
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};

template <class A, class B> struct pair
{
	A first;
	B second;
};
template <class P> struct _Select1st
{
};
template <class T> struct less
{
};
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
public:
	_Rb_tree(const _Rb_tree<K, V, KoV, C, A> &that);
private:
	void *_M_header;
	unsigned _M_node_count;
	C _M_key_compare;
};
}

class Player;
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };

// --- 0x004E569C (20B): clear the +0x14 / +0x10 ids and the +0x0C / +0x08
// 16-bit sentinels.
class Rva004E569C
{
public:
	void resetIds();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

void Rva004E569C::resetIds()
{
	m_14 = -1;
	m_10 = -1;
	m_0C = 0xFFFF;
	m_08 = 0xFFFF;
}

// --- 0x004E6928 (13B): zero the +0x00, +0x08 and +0x0C words.
class Rva004E6928
{
public:
	Rva004E6928();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

Rva004E6928::Rva004E6928() : m_00(0), m_08(0), m_0C(0)
{
}

// --- 0x004E7A51 (19B, cdecl): the +0x54 word of ThePlayerList's +0x10
// player, 0 without one.
class PlayerList;
extern PlayerList *ThePlayerList;

struct Rva004E7A51Player
{
	char m_pad[0x54];
	int m_54;
};

struct Rva004E7A51List
{
	char m_pad[0x10];
	Rva004E7A51Player *m_10;
};

int Rva004E7A51()
{
	Rva004E7A51Player *player = ((Rva004E7A51List *)ThePlayerList)->m_10;
	if (player)
		return player->m_54;
	return 0;
}

// --- 0x004E7A64 (18B): a zero word, a zero float and a zero word.
class Rva004E7A64
{
public:
	Rva004E7A64();
private:
	int m_00;
	float m_04;
	int m_08;
};

Rva004E7A64::Rva004E7A64() : m_00(0), m_04(0.0f), m_08(0)
{
}

// --- 0x004E8F76 (65B) / 0x004E8FB7 (63B): walks of a gate-behavior pointer
// vector: open (rowed 0x004992D5 with false, true) and close (rowed
// 0x0049924B with true) the allied gates failing the slot-6 test.
class GateOpenAndCloseBehavior
{
	friend class Rva004E8F37;
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual bool slot18();
	Player *getControllingPlayer() const;							// 0x004989D7
	Relationship getRelationship(const Player *player) const;	// 0x004989DF
private:
	void rva004992D5(bool a, bool b);						// 0x004992D5
	void rva0049924B(bool a);								// 0x0049924B
};

class Rva004E8F37
{
public:
	bool rva004E8F37(Player *player);
	void openAlliedGates(const Player *player);
	void closeAlliedGates(const Player *player);
private:
	GateOpenAndCloseBehavior **m_begin;
	GateOpenAndCloseBehavior **m_end;
};

// --- 0x004E8F37 (63B, RET 4): false as soon as a gate behaviour owned by the
// player answers slot 6 (vtable +0x18) with true; true otherwise, including
// for an empty vector. Codegen: the empty check reads the MEMBERS before the
// cached end/iterator locals (guarding on the locals lets cl rotate the loop
// and drop retail's jmp-to-test).
bool Rva004E8F37::rva004E8F37(Player *player)
{
	if (m_begin == m_end)
		return true;
	GateOpenAndCloseBehavior **end = m_end;
	for (GateOpenAndCloseBehavior **it = m_begin; it != end; ++it)
	{
		GateOpenAndCloseBehavior *gate = *it;
		if (gate->getControllingPlayer() == player && gate->slot18())
			return false;
	}
	return true;
}

void Rva004E8F37::openAlliedGates(const Player *player)
{
	GateOpenAndCloseBehavior **end = m_end;
	for (GateOpenAndCloseBehavior **it = m_begin; it != end; ++it)
	{
		GateOpenAndCloseBehavior *gate = *it;
		if (!gate->slot18() && gate->getRelationship(player) == ALLIES)
			gate->rva004992D5(false, true);
	}
}

void Rva004E8F37::closeAlliedGates(const Player *player)
{
	GateOpenAndCloseBehavior **end = m_end;
	for (GateOpenAndCloseBehavior **it = m_begin; it != end; ++it)
	{
		GateOpenAndCloseBehavior *gate = *it;
		if (!gate->slot18() && gate->getRelationship(player) == ALLIES)
			gate->rva0049924B(true);
	}
}

// --- 0x004EACB3 (66B): sum the counts of the +0x28 (index, count) entries
// whose player exists, is not the given one and is its enemy.
class Player
{
public:
	Relationship getRelationship(const Player *that) const;	// 0x002AC3E0
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);						// 0x002A7A29
};

struct Rva004EACB3Entry
{
	int m_index;
	int m_count;
};

class Rva004EACB3
{
public:
	int rva004EACB3(const Player *player) const;
private:
	char m_pad[0x28];
	Rva004EACB3Entry *m_begin;
	Rva004EACB3Entry *m_end;
};

int Rva004EACB3::rva004EACB3(const Player *player) const
{
	int total = 0;
	const Rva004EACB3Entry *end = m_end;
	for (const Rva004EACB3Entry *it = m_begin; it != end; ++it)
	{
		Player *other = ThePlayerList->getNthPlayer(it->m_index);
		if (other && other != player && player->getRelationship(other) == ENEMIES)
			total += it->m_count;
	}
	return total;
}

// --- 0x004F5F96 (13B) / 0x004F5FBC (19B): the +0x0C amount is spent; spend
// from it.
class Rva004F5F96
{
public:
	bool rva004F5F96() const;
	void rva004F5FBC(float amount);
private:
	int m_00;
	int m_04;
	int m_08;
	float m_0C;
};

bool Rva004F5F96::rva004F5F96() const
{
	return m_0C <= 0.0f;
}

void Rva004F5F96::rva004F5FBC(float amount)
{
	m_0C -= amount;
}

// --- 0x004F613B (16B) / 0x004F6155 (16B): look the +0x08 object's +0x10
// block up in the +0x2C template (rowed 0x0033A9A5, rowed
// ThingTemplate::getCurrentLivingWorldAutoResolveWeapon).
class Rva00427157;

class Rva0033A9A5
{
public:
	const Rva00427157 *getCurrentLivingWorldAutoResolveArmor(const void *key);		// 0x0033A9A5
};

class ThingTemplate
{
public:
	void *getCurrentLivingWorldAutoResolveWeapon(const void *key) const;	// 0x0033A9E2
};

struct Rva004F613BObject
{
	char m_pad[0x10];
	int m_10;
};

class Rva004F613B
{
public:
	const Rva00427157 *rva004F613B();
	void *rva004F6155();
private:
	int m_00;
	int m_04;
	Rva004F613BObject *m_object;							// +0x08
	char m_pad0C[0x2C - 0x0C];
	void *m_template;										// +0x2C
};

const Rva00427157 *Rva004F613B::rva004F613B()
{
	return ((Rva0033A9A5 *)m_template)->getCurrentLivingWorldAutoResolveArmor(&m_object->m_10);
}

void *Rva004F613B::rva004F6155()
{
	return ((ThingTemplate *)m_template)->getCurrentLivingWorldAutoResolveWeapon(&m_object->m_10);
}

// --- 0x004F621F (21B): the length of the indexed +0x0C pointer list.
struct Rva004F621FList
{
	void **m_begin;
	void **m_end;
	void **m_storage;
};

class Rva004F621F
{
public:
	int rva004F621F(int index) const;
private:
	Rva004F621FList m_lists[2];
};

int Rva004F621F::rva004F621F(int index) const
{
	const Rva004F621FList &list = m_lists[index + 1];
	return list.m_end - list.m_begin;
}

// --- 0x004F70C2 (15B) / 0x004F775B (12B): drop the last element of the
// +0x04-ended range (4-byte elements released through rowed 0x005F8FCC;
// 12-byte elements destroyed through rowed 0x005F8F96).
class Rva005F8FCC
{
public:
	void *rva005F8FCC(unsigned flags);						// 0x005F8FCC
private:
	int m_00;
};

class Rva005F8F96
{
public:
	~Rva005F8F96();											// 0x005F8F96
private:
	int m_words[3];
};

class Rva004F70C2
{
public:
	void rva004F70C2();
private:
	Rva005F8FCC *m_begin;
	Rva005F8FCC *m_end;
};

void Rva004F70C2::rva004F70C2()
{
	--m_end;
	m_end->rva005F8FCC(0);
}

class Rva004F775B
{
public:
	void rva004F775B();
private:
	Rva005F8F96 *m_begin;
	Rva005F8F96 *m_end;
};

void Rva004F775B::rva004F775B()
{
	--m_end;
	m_end->~Rva005F8F96();
}

// --- 0x004FA2D0 (18B) / 0x00504AA2 (18B): copies of holders of the rowed
// 0x004F9E76 and 0x005048B5 vectors.
struct BfmePod52;
struct Rva005048B5Record;

class Rva004FA2D0
{
public:
	Rva004FA2D0(const Rva004FA2D0 &that);
private:
	_STL::vector<BfmePod52> m_records;
};

Rva004FA2D0::Rva004FA2D0(const Rva004FA2D0 &that) : m_records(that.m_records)
{
}

class Rva00504AA2
{
public:
	Rva00504AA2(const Rva00504AA2 &that);
private:
	_STL::vector<Rva005048B5Record> m_records;
};

Rva00504AA2::Rva00504AA2(const Rva00504AA2 &that) : m_records(that.m_records)
{
}

// --- 0x004FA644 (21B): whether the +0x08 range of 88-byte records is not
// empty.
struct Rva004FA644Record
{
	int m_words[22];
};

class Rva004FA644
{
public:
	bool rva004FA644() const;
private:
	int m_00;
	int m_04;
	Rva004FA644Record *m_begin;
	Rva004FA644Record *m_end;
};

bool Rva004FA644::rva004FA644() const
{
	return (unsigned)(m_end - m_begin) > 0;
}

// --- 0x004FC163 (19B, cdecl): the +0x38 word of the rowed 0x0059E0F7
// lookup's record, 0 without one.
unsigned Rva0059E0F7(unsigned key);							// 0x0059E0F7

struct Rva004FC163Record
{
	char m_pad[0x38];
	int m_38;
};

int Rva004FC163(unsigned key)
{
	Rva004FC163Record *record = (Rva004FC163Record *)Rva0059E0F7(key);
	if (!record)
		return 0;
	return record->m_38;
}

// --- 0x004FF3A8 (14B): the referenced record's +0x08 word out through the
// pointer.
struct Rva004FF3A8Record
{
	int m_00;
	int m_04;
	int m_08;
};

struct Rva004FF3A8Handle
{
	Rva004FF3A8Handle(int value) : m_value(value) {}
	int m_value;
};

class Rva004FF3A8
{
public:
	Rva004FF3A8Handle rva004FF3A8() const;
private:
	Rva004FF3A8Record *m_record;
};

Rva004FF3A8Handle Rva004FF3A8::rva004FF3A8() const
{
	return Rva004FF3A8Handle(m_record->m_08);
}

// --- 0x005004CA (18B) / 0x005004DC (18B) / 0x005024A3 (18B): copies of
// holders of the rowed 0x004FFEAF, 0x004FFF54 and 0x00501E88 trees.
struct Rva004FFEAFLess
{
};

struct Rva004FFF54Less
{
};

struct Rva00501E3FElement
{
	Rva00501E3FElement(const Rva00501E3FElement &that);		// 0x005007AA
	int m_words[4];
};

typedef _STL::pair<const int, void *> Rva005004CAPair;
typedef _STL::pair<const int, Rva00501E3FElement> Rva005024A3Pair;

class Rva005004CA
{
public:
	Rva005004CA(const Rva005004CA &that);
private:
	_STL::_Rb_tree<int, Rva005004CAPair, _STL::_Select1st<Rva005004CAPair>, Rva004FFEAFLess, _STL::allocator<Rva005004CAPair> > m_tree;
};

Rva005004CA::Rva005004CA(const Rva005004CA &that) : m_tree(that.m_tree)
{
}

class Rva005004DC
{
public:
	Rva005004DC(const Rva005004DC &that);
private:
	_STL::_Rb_tree<int, Rva005004CAPair, _STL::_Select1st<Rva005004CAPair>, Rva004FFF54Less, _STL::allocator<Rva005004CAPair> > m_tree;
};

Rva005004DC::Rva005004DC(const Rva005004DC &that) : m_tree(that.m_tree)
{
}

class Rva005024A3
{
public:
	Rva005024A3(const Rva005024A3 &that);
private:
	_STL::_Rb_tree<int, Rva005024A3Pair, _STL::_Select1st<Rva005024A3Pair>, _STL::less<int>, _STL::allocator<Rva005024A3Pair> > m_tree;
};

Rva005024A3::Rva005024A3(const Rva005024A3 &that) : m_tree(that.m_tree)
{
}

// --- 0x00500A89 (29B): a key and a rowed-copy element (0x005007AA).
class Rva00500A89
{
public:
	Rva00500A89(const int &key, const Rva00501E3FElement &element);
private:
	int m_key;
	Rva00501E3FElement m_element;
};

Rva00500A89::Rva00500A89(const int &key, const Rva00501E3FElement &element) : m_key(key), m_element(element)
{
}

// --- 0x005041A2 (20B): wrap the rowed 0x00504112 lookup in a cursor.
struct Rva005041A2Cursor
{
	Rva005041A2Cursor(void *node) : m_node(node) {}
	void *m_node;
};

class Rva00504112
{
public:
	void *rva00504112(void *key);							// 0x00504112
	Rva005041A2Cursor rva005041A2(void *key);
};

Rva005041A2Cursor Rva00504112::rva005041A2(void *key)
{
	return Rva005041A2Cursor(rva00504112(key));
}

// --- 0x0050471F (27B, cdecl): build a float and a 12-byte block in place.
struct Rva0050471FBlock
{
	int m_words[3];
};

struct Rva0050471FPair
{
	float m_first;
	Rva0050471FBlock m_second;
};

void Rva0050471F(Rva0050471FPair *out, const float *first, const Rva0050471FBlock *second)
{
	out->m_first = *first;
	out->m_second = *second;
}
