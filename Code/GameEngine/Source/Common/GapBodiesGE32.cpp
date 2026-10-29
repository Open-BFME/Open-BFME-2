// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// stlport46
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (thirty-second batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"

// Declaration-only views of the STLport vector, deque cursor and tree members
// these bodies call; no container code is instantiated here.
class Rva0059D7B1;
class Rva0059E882;

namespace _STL {
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	void resize(unsigned count, T value);
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};

template <class T> struct _Deque_iterator_base
{
	void _M_advance(int n);
	T *_M_cur;
	T *_M_first;
	T *_M_last;
	T **_M_node;
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
	friend class ::Rva0059D7B1;
	friend class ::Rva0059E882;
	template <class KT> _Rb_tree_node<V> *_M_find(const KT &key) const;
	_Rb_tree_node<V> *_M_header;
	unsigned _M_node_count;
	C _M_key_compare;
};
}

// --- 0x00574251 (20B) / 0x0057426C (16B) / 0x0057427C (16B): forward to the
// receiver's own virtual slots 4, 1 and 5. 0x0057426C re-pushes both argument
// dwords and calls (ret 8) where two scalar arguments tail-jump: cl copies an
// 8-byte aggregate by value, so slot 1 takes one (ICoord2D here; Coord2D would
// give the same bytes).
class Rva00574251
{
public:
	virtual void slot00();
	virtual void slot04(ICoord2D value);
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10(int a, float b);
	virtual void slot14(float value);
	void rva00574251(int a, float b);
	void rva0057426C(ICoord2D value);
	void rva0057427C(float value);
};

void Rva00574251::rva00574251(int a, float b)
{
	slot10(a, b);
}

void Rva00574251::rva0057426C(ICoord2D value)
{
	slot04(value);
}

void Rva00574251::rva0057427C(float value)
{
	slot14(value);
}

// --- 0x005774D0 (19B): construct the rowed 0x005773DB base from the
// argument's address.
class Rva005773DB
{
public:
	Rva005773DB(const int *value);							// 0x005773DB
private:
	int m_words[3];
};

class Rva005774D0 : public Rva005773DB
{
public:
	Rva005774D0(int value);
};

Rva005774D0::Rva005774D0(int value) : Rva005773DB(&value)
{
}

// --- 0x0057A304 (15B): twice the +0x58 count plus the +0x5C flag.
class Rva0057A304
{
public:
	int rva0057A304() const;
private:
	char m_pad[0x58];
	int m_58;
	bool m_5C;
};

int Rva0057A304::rva0057A304() const
{
	return (m_5C != 0) + m_58 * 2;
}

// --- 0x0057A433 (26B): share a counted record (rowed 0x005D1A79 increment).
class Rva005D1A79DwordCounter
{
public:
	void inc();												// 0x005D1A79
};

class Rva0057A433
{
public:
	Rva0057A433(Rva005D1A79DwordCounter *const *record, int unused);
private:
	Rva005D1A79DwordCounter *m_record;
};

Rva0057A433::Rva0057A433(Rva005D1A79DwordCounter *const *record, int unused) : m_record(*record)
{
	if (m_record)
		m_record->inc();
}

// --- 0x0057E779 (40B): store a rule value, notify slot 1 and refresh its
// gadget (rowed AptMpGameRules::UpdateRuleGadget).
class AptMpGameRules
{
public:
	virtual void slot00();
	virtual void slot04(int rule, int flag);
	void UpdateRuleGadget(int rule);						// 0x0057E5B5
	void rva0057E779(int rule, int value);
private:
	char m_pad[0x8C - 4];
	int m_rules[1];											// +0x8C
};

void AptMpGameRules::rva0057E779(int rule, int value)
{
	m_rules[rule] = value;
	slot04(rule, 0);
	UpdateRuleGadget(rule);
}

// --- 0x0057EF0A (14B) / 0x0058A193 (14B): resize a pointer / id vector
// (rowed resize 0x000E6D39, 0x005839A7) with null / invalid fill.
class Drawable;
enum ObjectID { INVALID_ID = 0 };

class Rva0057EF0A : public _STL::vector<Drawable *>
{
public:
	void rva0057EF0A(unsigned count);
};

void Rva0057EF0A::rva0057EF0A(unsigned count)
{
	resize(count, 0);
}

class Rva0058A193 : public _STL::vector<ObjectID>
{
public:
	void rva0058A193(unsigned count);
};

void Rva0058A193::rva0058A193(unsigned count)
{
	resize(count, INVALID_ID);
}

// --- 0x0057FD5F (15B): close the +0x64 in-game chat (rowed 0x005AFCB4 with
// true).
class ChatWindowsInGame
{
public:
	bool rva005AFCB4(bool flag);							// 0x005AFCB4
};

class Rva0057FD5F
{
public:
	void rva0057FD5F();
private:
	char m_pad[0x64];
	ChatWindowsInGame *m_chat;
};

void Rva0057FD5F::rva0057FD5F()
{
	if (m_chat)
		m_chat->rva005AFCB4(true);
}

// --- 0x005851BF (14B, cdecl): advance a deque cursor (rowed _M_advance
// 0x00584CB2).
struct BfmeE12
{
	float x, y, z;
};

void Rva005851BF(_STL::_Deque_iterator_base<BfmeE12> &cursor, int count)
{
	cursor._M_advance(count);
}

// --- 0x00599F65 (15B): the record of the +0x14 key in the 0x00DFEEF8 table
// (rowed 0x002A8AB1).
struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *key);				// 0x002A8AB1
};

extern Rva002A8F24 *TheSkirmishAIManager;

class Rva00599F65
{
public:
	Rva002A8AB1Record *rva00599F65();
private:
	char m_pad[0x14];
	void *m_key;
};

Rva002A8AB1Record *Rva00599F65::rva00599F65()
{
	return TheSkirmishAIManager->rva002A8AB1(m_key);
}

// --- 0x0059AE72 (34B): with a positive +0x0C amount, the rowed 0x0041950A
// check of the +0x2C template's auto-resolve weapon for the +0x08 object.
class ThingTemplate
{
public:
	void *getCurrentLivingWorldAutoResolveWeapon(const void *key) const;	// 0x0033A9E2
};

class Rva004194D6
{
public:
	bool rva0041950A();										// 0x0041950A
};

struct Rva0059AE72Object
{
	char m_pad[0x10];
	int m_10;
};

class Rva0059AE72
{
public:
	bool rva0059AE72();
private:
	int m_00;
	int m_04;
	Rva0059AE72Object *m_object;							// +0x08
	float m_amount;											// +0x0C
	char m_pad10[0x2C - 0x10];
	ThingTemplate *m_template;								// +0x2C
};

bool Rva0059AE72::rva0059AE72()
{
	if (m_amount <= 0.0f)
		return false;
	return ((Rva004194D6 *)m_template->getCurrentLivingWorldAutoResolveWeapon(&m_object->m_10))->rva0041950A();
}

// --- 0x0059D7B1 (19B): the value slot of the key in the +0x04
// map<int,int> (rowed _M_find 0x00388F63).
typedef _STL::pair<const int, int> Rva0059D7B1Pair;
typedef _STL::_Rb_tree<int, Rva0059D7B1Pair, _STL::_Select1st<Rva0059D7B1Pair>, _STL::less<int>, _STL::allocator<Rva0059D7B1Pair> > Rva0059D7B1Tree;

class Rva0059D7B1
{
public:
	int *rva0059D7B1(int key);
private:
	int m_00;
	Rva0059D7B1Tree m_map;
};

int *Rva0059D7B1::rva0059D7B1(int key)
{
	return &m_map._M_find(key)->_M_value_field.second;
}

// --- 0x0059E882 (31B): whether the name is a key of the +0x04 record's
// +0x08 string map (rowed _M_find 0x001F8437).
typedef _STL::pair<const AsciiString, AsciiString> Rva0059E882Pair;
typedef _STL::_Rb_tree<AsciiString, Rva0059E882Pair, _STL::_Select1st<Rva0059E882Pair>, _STL::less<AsciiString>, _STL::allocator<Rva0059E882Pair> > Rva0059E882Tree;

struct Rva0059E882Record
{
	int m_00;
	int m_04;
	Rva0059E882Tree m_map;									// +0x08
};

class Rva0059E882
{
public:
	bool rva0059E882(const AsciiString &name) const;
private:
	int m_00;
	Rva0059E882Record *m_record;
};

bool Rva0059E882::rva0059E882(const AsciiString &name) const
{
	Rva0059E882Tree &map = m_record->m_map;
	_STL::_Rb_tree_node<Rva0059E882Pair> *end = map._M_header;
	return map._M_find(name) != end;
}

// --- 0x0059E9AD (16B): the rowed 0x0059E861 check of the record's +0x04
// name.
class Rva0059E861
{
public:
	bool rva0059E861(const AsciiString &name);				// 0x0059E861
	bool rva0059E9AD(const void *record);
};

struct Rva0059E9ADRecord
{
	int m_00;
	AsciiString m_name;
};

bool Rva0059E861::rva0059E9AD(const void *record)
{
	return rva0059E861(((const Rva0059E9ADRecord *)record)->m_name);
}

// --- 0x0059EAD9 (15B) / 0x0059EAF0 (20B) / 0x0059EB04 (15B): the +0x1008
// 16-bit value; set and clear the +0xFF4 flagged +0xFF8 word.
class Rva0059EAD9
{
public:
	void rva0059EAD9(short value);
	void rva0059EAF0(int value);
	void rva0059EB04();
private:
	char m_pad[0xFF4];
	bool m_set;												// +0xFF4
	int m_value;											// +0xFF8
	char m_padFFC[0x1008 - 0xFFC];
	short m_1008;
};

void Rva0059EAD9::rva0059EAD9(short value)
{
	m_1008 = value;
}

void Rva0059EAD9::rva0059EAF0(int value)
{
	m_set = true;
	m_value = value;
}

void Rva0059EAD9::rva0059EB04()
{
	m_value = 0;
	m_set = false;
}
