// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (twenty-second batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include "GameLogicObjectLookupView.h"

// Declaration-only views of the STLport list and the Apt reference whose
// rowed members these bodies call; no container code is instantiated here.
namespace _STL {
template <class T> class allocator;
template <class T, class A = allocator<T> > class list
{
public:
	void push_back(const T &value);
private:
	void *_M_node;
};
}

template <class T> class AptRef
{
public:
	AptRef<T> &operator=(const AptRef<T> &that);
private:
	T *m_object;
};

class Object;
class ObjectCreationList;
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);	// 0x0002DE78
};

// --- 0x0043DA87 (14B): the indexed +0x8C word.
class Rva0043DA87
{
public:
	int rva0043DA87(int index) const;
private:
	char m_pad[0x8C];
	int m_8C[1];
};

int Rva0043DA87::rva0043DA87(int index) const
{
	return m_8C[index];
}

// --- 0x0043DDE6 (18B): assignment of a holder of an Apt command-map
// reference (the rowed AptRef operator= 0x002174A4).
class AptCommandMap;

class Rva0043DDE6
{
public:
	Rva0043DDE6 &operator=(const Rva0043DDE6 &that);
private:
	AptRef<AptCommandMap> m_ref;
};

Rva0043DDE6 &Rva0043DDE6::operator=(const Rva0043DDE6 &that)
{
	m_ref = that.m_ref;
	return *this;
}

// --- 0x004476E7 (40B): whether a kind-6 entry's +0x38 address equals the
// peer's +0x14 address (rowed BfmeNetAddress 0x00248CBF).
struct BfmeNetAddress
{
	bool Rva00248CBF(const BfmeNetAddress *that) const;	// 0x00248CBF
	int m_words[4];
};

struct Rva004476E7Peer
{
	char m_pad[0x14];
	BfmeNetAddress m_address;								// +0x14
};

class Rva004476E7
{
public:
	int matchesPeerAddress(const Rva004476E7Peer *peer) const;
private:
	int m_00;
	int m_kind;												// +0x04
	char m_pad08[0x38 - 0x08];
	BfmeNetAddress m_address;								// +0x38
};

int Rva004476E7::matchesPeerAddress(const Rva004476E7Peer *peer) const
{
	if (peer && m_kind == 6 && peer->m_address.Rva00248CBF(&m_address))
		return 1;
	return 0;
}

// --- 0x00448F92 (20B): wrap the rowed 0x00448DCB lookup's node in a cursor.
struct Rva00448DCBNode;
struct BfmeStringRecord00448113;

struct Rva00448F92Cursor
{
	Rva00448F92Cursor(Rva00448DCBNode *node) : m_node(node) {}
	Rva00448DCBNode *m_node;
};

class Rva00448DCB
{
public:
	Rva00448DCBNode *rva00448DCB(const BfmeStringRecord00448113 &key);	// 0x00448DCB
	Rva00448F92Cursor findCursor(const BfmeStringRecord00448113 &key);
};

Rva00448F92Cursor Rva00448DCB::findCursor(const BfmeStringRecord00448113 &key)
{
	return Rva00448F92Cursor(rva00448DCB(key));
}

// --- 0x004494AC (14B): whether both the word and the following short are
// zero.
class Rva004494AC
{
public:
	int isZero() const;
private:
	int m_00;
	short m_04;
};

int Rva004494AC::isZero() const
{
	return m_00 == 0 && m_04 == 0;
}

// --- 0x0044BD21 (19B): construct the rowed 0x0044BC76 base from the
// argument's address.
class Rva0044BC76
{
public:
	Rva0044BC76(const int *value);							// 0x0044BC76
private:
	int m_words[3];
};

class Rva0044BD21 : public Rva0044BC76
{
public:
	Rva0044BD21(int value);
};

Rva0044BD21::Rva0044BD21(int value) : Rva0044BC76(&value)
{
}

// --- 0x0044E5AA (14B) / 0x00462457 (14B) / 0x0047B985 (14B): Object
// wrappers fixing the trailing flag of rowed 0x0028CDEB (false) and
// 0x00298979 (false, true).
class Rva00346BC0;
enum DamageType { DAMAGE_08 = 8 };
enum DeathType { DEATH_00 = 0 };

class Object
{
public:
	void rva0028CDEB(const Rva00346BC0 &mask, bool flag);	// 0x0028CDEB
	void defect(Object *other, bool flag);				// 0x00298979
	void clearMask(const Rva00346BC0 &mask);
	void rva00462457(Object *other);
	void rva0047B985(Object *other);
	void kill(DamageType damage, DeathType death);	// 0x002984D4
	ObjectCreationList *m_pad[14];
	ObjectCreationList *m_38;								// +0x38
};

void Object::clearMask(const Rva00346BC0 &mask)
{
	rva0028CDEB(mask, false);
}

void Object::rva00462457(Object *other)
{
	defect(other, false);
}

void Object::rva0047B985(Object *other)
{
	defect(other, true);
}

// --- 0x0044E5D6 (17B): store the flag at +0x7C, clearing +0x74 with it when
// false.
class Rva0044E5D6
{
public:
	void rva0044E5D6(bool flag);
private:
	char m_pad[0x74];
	bool m_74;
	char m_pad75[0x7C - 0x75];
	bool m_7C;
};

void Rva0044E5D6::rva0044E5D6(bool flag)
{
	if (!flag)
		m_74 = flag;
	m_7C = flag;
}

// --- 0x0045A1EB (12B) / 0x0045A1F7 (12B): +0x1C flag tests (any of the low
// three bits; bit 3 clear).
class Rva0045A1EB
{
public:
	bool hasLowFlags() const;
	bool isBit3Clear() const;
private:
	char m_pad[0x1C];
	unsigned m_flags;
};

bool Rva0045A1EB::hasLowFlags() const
{
	return (m_flags & 7) != 0;
}

bool Rva0045A1EB::isBit3Clear() const
{
	return (m_flags & 8) == 0;
}

// --- 0x0045D388 (15B): whether bit 1 or 2 of the +0x18C byte is set.
class Rva0045D388
{
public:
	bool rva0045D388() const;
private:
	char m_pad[0x18C];
	unsigned char m_flags;
};

bool Rva0045D388::rva0045D388() const
{
	return (m_flags & 6) != 0;
}

// --- 0x0045ED7E (14B): call the stored member function on the target with
// the stored argument.
class __single_inheritance Rva0045ED7ETarget;

class Rva0045ED7E
{
public:
	void invokeCallback(Rva0045ED7ETarget *target);
private:
	void (Rva0045ED7ETarget::*m_method)(int value);
	int m_value;
};

void Rva0045ED7E::invokeCallback(Rva0045ED7ETarget *target)
{
	(target->*m_method)(m_value);
}

// --- 0x0045F363 (26B): three zero words and the 0x00C4254C default.
extern float g_00C4254C;

class Rva0045F363
{
public:
	Rva0045F363();
private:
	int m_00;
	int m_04;
	int m_08;
	float m_0C;
};

Rva0045F363::Rva0045F363()
{
	float scale = g_00C4254C;
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = scale;
}

// --- 0x004608CA (22B): mark +0xB8 and store the value at +0xBC.
class Rva004608CA
{
public:
	void rva004608CA(const int &value);
private:
	char m_pad[0xB8];
	bool m_set;
	int m_value;											// +0xBC
};

void Rva004608CA::rva004608CA(const int &value)
{
	m_set = true;
	m_value = value;
}

// --- 0x00462465 (18B) / 0x004624EB (25B): a pointer paired with the
// 0x00E0362C tag; the override (on the +0x20 interface) answers its own
// interface, null when the object is null.
extern unsigned g_Va00E0362C;

struct Rva00462465
{
	Rva00462465(void *object);
	void *m_object;
	unsigned *m_tag;
};

Rva00462465::Rva00462465(void *object) : m_object(object), m_tag(&g_Va00E0362C)
{
}

class Rva004624EBHead
{
public:
	virtual void slot00();
private:
	int m_words[7];
};

class Rva004624EBFace
{
public:
	virtual Rva00462465 rva004624EB();
};

class Rva004624EB : public Rva004624EBHead, public Rva004624EBFace
{
public:
	virtual Rva00462465 rva004624EB();
};

Rva00462465 Rva004624EB::rva004624EB()
{
	return Rva00462465(static_cast<Rva004624EBFace *>(this));
}

// --- 0x00462697 (15B): whether the +0x04 list is empty.
struct Rva00462697Node
{
	Rva00462697Node *m_next;
};

struct Rva00462697List
{
	Rva00462697Node *m_head;
};

class Rva00462697
{
public:
	bool rva00462697() const;
private:
	int m_00;
	Rva00462697List *m_list;
};

bool Rva00462697::rva00462697() const
{
	Rva00462697Node *head = m_list->m_head;
	return head->m_next == head;
}

// --- 0x00466E12 (17B): two zero words and the 99999 sentinel.
class Rva00466E12
{
public:
	Rva00466E12();
private:
	int m_00;
	int m_04;
	int m_08;
};

Rva00466E12::Rva00466E12() : m_00(0), m_04(0), m_08(99999)
{
}

// --- 0x00468A04 (24B): copy a 12-byte block and a word.
struct Rva00468A04Block
{
	int m_words[3];
};

struct Rva00468A04Record
{
	Rva00468A04Block m_block;
	int m_0C;
};

class Rva00468A04
{
public:
	void rva00468A04(const Rva00468A04Record &record);
private:
	Rva00468A04Block m_block;
	int m_0C;
};

void Rva00468A04::rva00468A04(const Rva00468A04Record &record)
{
	m_block = record.m_block;
	m_0C = record.m_0C;
}

// --- 0x0047A881 (20B): the address of the indexed 28-byte record after the
// +0x188 table's leading word.
struct Rva0047A881Record
{
	int m_words[7];
};

struct Rva0047A881Table
{
	int m_count;
	Rva0047A881Record m_records[1];
};

class Rva0047A881
{
public:
	Rva0047A881Record *rva0047A881(int index);
private:
	char m_pad[0x188];
	Rva0047A881Table *m_table;
};

Rva0047A881Record *Rva0047A881::rva0047A881(int index)
{
	return &m_table->m_records[index];
}

// --- 0x00481BFE (14B, cdecl): test the key against the flags (rowed
// BitFlags<11>::test 0x0023C59F).
template <int N> class BitFlags
{
public:
	bool test(const void *key) const;
};

bool Rva00481BFE(const void *key, const BitFlags<11> &flags)
{
	return flags.test(key);
}

// --- 0x0048595C (25B, cdecl): run the object's +0x38 creation list, when it
// has one, through the rowed 0x001F0410.
class ObjectCreationList
{
public:
	void rva001F0410(void *a, void *b);						// 0x001F0410
};

void Rva0048595C(Object *object, void *a, void *b)
{
	ObjectCreationList *list = object->m_38;
	if (list)
		list->rva001F0410(a, b);
}

// --- 0x00485B9C (28B): a cleared word, a cleared id, the owner and the
// value.
class Rva00485B9C
{
public:
	Rva00485B9C(int owner, const int &value);
private:
	int m_00;
	int m_04;
	int m_owner;
	int m_value;
};

Rva00485B9C::Rva00485B9C(int owner, const int &value) : m_00(0), m_04(-1), m_owner(owner), m_value(value)
{
}

// --- 0x004874F4 (23B): two zero words and two zero floats.
class Rva004874F4
{
public:
	Rva004874F4();
private:
	int m_00;
	int m_04;
	float m_08;
	float m_0C;
};

Rva004874F4::Rva004874F4() : m_00(0), m_04(0), m_08(0.0f), m_0C(0.0f)
{
}

// --- 0x0048BBF3 (16B): append the value to the +0x08 list (rowed
// list<int>::push_back 0x0005548F).
class Rva0048BBF3
{
public:
	void rva0048BBF3(int value);
private:
	int m_00;
	int m_04;
	_STL::list<int> m_list;
};

void Rva0048BBF3::rva0048BBF3(int value)
{
	m_list.push_back(value);
}

// --- 0x0048DBEE (19B): field-parse callback reading the block into the
// store through table 0x00C4C850.
extern const FieldParse g_00C4C850[];

void Rva0048DBEE(INI *ini, void *instance, void *store, const void *userData)
{
	ini->initFromINI(instance, g_00C4C850);
}

// --- 0x004639D5 (120B): an override on the +0x20 interface answering the
// percentage of the module data's +0x94 duration that has run since the
// keyed start frame in the +0xD0 map<int,int> (rowed _M_find 0x00388F63):
// 100 for an unknown key, an overrun or a zero duration, 0 on the start
// frame.
extern GameLogic *TheGameLogic;
class Rva004639D5;

namespace _STL {
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
template <class V> struct _Rb_tree_node
{
	int _M_color;
	void *_M_parent;
	void *_M_left;
	void *_M_right;
	V _M_value_field;
};
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
	friend class ::Rva004639D5;
	template <class KT> _Rb_tree_node<V> *_M_find(const KT &key) const;
	_Rb_tree_node<V> *_M_header;
	unsigned _M_node_count;
	C _M_key_compare;
};
}

typedef _STL::pair<const int, int> Rva004639D5Pair;
typedef _STL::_Rb_tree<int, Rva004639D5Pair, _STL::_Select1st<Rva004639D5Pair>, _STL::less<int>, _STL::allocator<Rva004639D5Pair> > Rva004639D5Tree;

struct Rva004639D5Data
{
	char m_pad[0x94];
	unsigned m_duration;									// +0x94
};

class Rva004639D5Head
{
public:
	virtual void slot00();
private:
	friend class Rva004639D5;
	Rva004639D5Data *m_data;								// +0x04
	int m_words[6];
};

class Rva004639D5Face
{
public:
	virtual int rva004639D5(int key);
};

class Rva004639D5 : public Rva004639D5Head, public Rva004639D5Face
{
public:
	virtual int rva004639D5(int key);
private:
	char m_pad24[0xF0 - 0x24];
	Rva004639D5Tree m_starts;								// +0xF0
};

int Rva004639D5::rva004639D5(int key)
{
	Rva004639D5Data *data = m_data;
	_STL::_Rb_tree_node<Rva004639D5Pair> *it = m_starts._M_find(key);
	if (it != m_starts._M_header)
	{
		unsigned elapsed = TheGameLogic->getFrame() - it->_M_value_field.second;
		unsigned duration = data->m_duration;
		if (elapsed <= duration)
		{
			if (elapsed == 0)
				return 0;
			if (duration != 0)
				return (int)((float)elapsed / (float)duration * 100.0f);
		}
	}
	return 100;
}
