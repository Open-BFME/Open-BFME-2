// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (twenty-fourth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include <math.h>
#include <string.h>
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// Declaration-only views of the STLport vector and tree whose rowed members
// these bodies call; no container code is instantiated here.
class Rva004D1AAA;

namespace _STL {
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
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
	friend class ::Rva004D1AAA;
private:
	template <class KT> _Rb_tree_node<V> *_M_find(const KT &key) const;
	_Rb_tree_node<V> *_M_header;
	unsigned _M_node_count;
	C _M_key_compare;
};
}

class Object;
class ModuleData;

// --- 0x0049881D (20B): clear the +0x34 float and stamp the logic frame at
// +0x3C.
class Rva0049881D
{
public:
	void rva0049881D();
private:
	char m_pad[0x34];
	float m_34;
	int m_38;
	unsigned m_3C;
};

void Rva0049881D::rva0049881D()
{
	m_34 = 0.0f;
	m_3C = TheGameLogic->getFrame();
}

// --- 0x004AC8D9 (22B): store the float at +0x20 of the indexed +0x58 entry.
struct Rva004AC8D9Entry
{
	char m_pad[0x20];
	float m_20;
};

class Rva004AC8D9
{
public:
	void setEntryValue(int index, float value);
private:
	char m_pad[0x58];
	Rva004AC8D9Entry *m_entries[1];
};

void Rva004AC8D9::setEntryValue(int index, float value)
{
	m_entries[index]->m_20 = value;
}

// --- 0x004B2B01 (19B): append to the +0xC8 module-data vector (rowed
// push_back 0x004DFCB0).
class Rva004B2B01
{
public:
	void addModuleData(const ModuleData *data);
private:
	char m_pad[0xC8];
	_STL::vector<const ModuleData *> m_data;
};

void Rva004B2B01::addModuleData(const ModuleData *data)
{
	m_data.push_back(data);
}

// --- 0x004B3FDC (17B): the negation of the rowed 0x00406F9C check.
class Rva00406F9C
{
public:
	bool rva00406F9C(const void *key);						// 0x00406F9C
	int rva004B3FDC(const void *key);
};

int Rva00406F9C::rva004B3FDC(const void *key)
{
	return !rva00406F9C(key);
}

// --- 0x004BB937 (18B): whether the +0x4C0 word equals the argument.
class Rva004BB937
{
public:
	bool rva004BB937(int value) const;
private:
	char m_pad[0x4C0];
	int m_4C0;
};

bool Rva004BB937::rva004BB937(int value) const
{
	return m_4C0 == value;
}

// --- 0x004C09A1 (20B): remember the object's +0x74 word at +0x100.
struct Rva004C09A1Object
{
	char m_pad[0x74];
	int m_74;
};

class Rva004C09A1
{
public:
	void rva004C09A1(const Rva004C09A1Object *object);
private:
	char m_pad[0x100];
	int m_100;
};

void Rva004C09A1::rva004C09A1(const Rva004C09A1Object *object)
{
	if (object)
		m_100 = object->m_74;
}

// --- 0x004C2B45 (18B): a zero float and two zero words.
class Rva004C2B45
{
public:
	Rva004C2B45();
private:
	float m_00;
	int m_04;
	int m_08;
};

Rva004C2B45::Rva004C2B45() : m_00(0.0f), m_04(0), m_08(0)
{
}

// --- 0x004C81B7 (17B): store the +0x1918 float.
class Rva004C81B7
{
public:
	void rva004C81B7(float value);
private:
	char m_pad[0x1918];
	float m_1918;
};

void Rva004C81B7::rva004C81B7(float value)
{
	m_1918 = value;
}

// --- 0x004CA256 (20B): wrap the rowed 0x004C9FE0 lookup's node in a cursor.
struct AnimationSoundTreeNode;

struct Rva004CA256Cursor
{
	Rva004CA256Cursor(AnimationSoundTreeNode *node) : m_node(node) {}
	AnimationSoundTreeNode *m_node;
};

class AnimationSoundTree
{
public:
	AnimationSoundTreeNode *rva004C9FE0(const void *key);	// 0x004C9FE0
	Rva004CA256Cursor findCursor(const void *key);
};

Rva004CA256Cursor AnimationSoundTree::findCursor(const void *key)
{
	return Rva004CA256Cursor(rva004C9FE0(key));
}

// --- 0x004CB125 (21B) / 0x004CBBF4 (21B): a word out through the pointer
// and its paired flag (+0x37C/+0x380, +0x1D8/+0x1DC).
class Rva004CB125
{
public:
	bool rva004CB125(int *out) const;
private:
	char m_pad[0x37C];
	int m_37C;
	bool m_380;
};

bool Rva004CB125::rva004CB125(int *out) const
{
	*out = m_37C;
	return m_380;
}

class Rva004CBBF4
{
public:
	bool rva004CBBF4(int *out) const;
private:
	char m_pad[0x1D8];
	int m_1D8;
	bool m_1DC;
};

bool Rva004CBBF4::rva004CBBF4(int *out) const
{
	*out = m_1D8;
	return m_1DC;
}

// --- 0x004CEF4B (13B): the GameSpy stats challenge of the +0x101C game.
extern "C" char *GetChallenge(void *game);

class Rva004CEF4B
{
public:
	char *rva004CEF4B();
private:
	char m_pad[0x101C];
	void *m_game;
};

char *Rva004CEF4B::rva004CEF4B()
{
	return GetChallenge(m_game);
}

// --- 0x004CFAEB (17B): zero the 8 KB block.
class Rva004CFAEB
{
public:
	void rva004CFAEB();
private:
	char m_bytes[0x2000];
};

void Rva004CFAEB::rva004CFAEB()
{
	memset(this, 0, 0x2000);
}

// --- 0x004D0F27 (18B): run the rowed 0x004D04E0 and answer the receiver.
class Rva004D04C9
{
public:
	void *rva004D04E0(int value);							// 0x004D04E0
};

class Rva004D0F27 : public Rva004D04C9
{
public:
	Rva004D0F27 &rva004D0F27(int value);
};

Rva004D0F27 &Rva004D0F27::rva004D0F27(int value)
{
	rva004D04E0(value);
	return *this;
}

// --- 0x004D1AAA (20B): find in a map<unsigned short, int> (rowed _M_find
// 0x004DC8AB), wrapped in a cursor.
typedef _STL::pair<const unsigned short, int> Rva004D1AAAPair;
typedef _STL::_Rb_tree<unsigned short, Rva004D1AAAPair, _STL::_Select1st<Rva004D1AAAPair>, _STL::less<unsigned short>, _STL::allocator<Rva004D1AAAPair> > Rva004D1AAATree;

struct Rva004D1AAACursor
{
	Rva004D1AAACursor(_STL::_Rb_tree_node<Rva004D1AAAPair> *node) : m_node(node) {}
	_STL::_Rb_tree_node<Rva004D1AAAPair> *m_node;
};

class Rva004D1AAA : public Rva004D1AAATree
{
public:
	Rva004D1AAACursor rva004D1AAA(const unsigned short &key) const;
};

Rva004D1AAACursor Rva004D1AAA::rva004D1AAA(const unsigned short &key) const
{
	return Rva004D1AAACursor(_M_find(key));
}

// --- 0x004D6B29 (17B, cdecl): the arc tangent.
float Rva004D6B29(float value)
{
	return atan(value);
}

// --- 0x004D729D (40B): clear the +0x20 / +0x34 words and three floats and
// set the +0x30 bound to FLT_MAX.
class Rva004D729D
{
public:
	void rva004D729D();
private:
	char m_pad[0x20];
	int m_20;
	float m_24;
	float m_28;
	float m_2C;
	float m_30;
	int m_34;
};

void Rva004D729D::rva004D729D()
{
	m_20 = 0;
	m_34 = 0;
	m_24 = 0.0f;
	m_28 = 0.0f;
	m_2C = 0.0f;
	m_30 = 3.402823466e+38f;
}

// --- 0x004D82CA (12B): stamp the logic frame at +0x34.
class Rva004D82CA
{
public:
	void rva004D82CA();
private:
	char m_pad[0x34];
	unsigned m_34;
};

void Rva004D82CA::rva004D82CA()
{
	m_34 = TheGameLogic->getFrame();
}

// --- 0x004DD6B2 (29B): three words and a cleared +0x10 word.
class Rva004DD6B2
{
public:
	Rva004DD6B2(int a, int b, int c);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

Rva004DD6B2::Rva004DD6B2(int a, int b, int c) : m_00(a), m_04(b), m_08(c), m_10(0)
{
}

// --- 0x004DE563 (65B): from the head (also stored as the cursor) walk the
// +0x10 chain to the keyed (+0x0C) node and erase the value from its pointer
// vector (rowed vector<void*>::erase 0x001FF51F); 1 when erased.
namespace _STL {
template <> class vector<void *, allocator<void *> >
{
public:
	void **erase(void **position);
	void **m_start;
	void **m_finish;
	void **m_end;
};
}

struct Rva004DE563Node
{
	_STL::vector<void *> m_values;
	int m_key;												// +0x0C
	Rva004DE563Node *m_next;								// +0x10
};

class Rva004DE563
{
public:
	int rva004DE563(int key, void *value);
private:
	Rva004DE563Node *m_cursor;
	Rva004DE563Node *m_head;
};

int Rva004DE563::rva004DE563(int key, void *value)
{
	m_cursor = m_head;
	for (Rva004DE563Node *node = m_cursor; node; node = node->m_next)
	{
		if (node->m_key == key)
		{
			for (void **it = node->m_values.m_start; it != node->m_values.m_finish; ++it)
			{
				if (*it == value)
				{
					node->m_values.erase(it);
					return 1;
				}
			}
		}
	}
	return 0;
}

// --- 0x004E077D (19B, cdecl): the +0x38 word of the rowed 0x0052B225
// lookup's record, 0 without one.
unsigned Rva0052B225(unsigned key);							// 0x0052B225

struct Rva004E077DRecord
{
	char m_pad[0x38];
	int m_38;
};

int Rva004E077D(unsigned key)
{
	Rva004E077DRecord *record = (Rva004E077DRecord *)Rva0052B225(key);
	if (!record)
		return 0;
	return record->m_38;
}
