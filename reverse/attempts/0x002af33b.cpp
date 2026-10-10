// ?rva002AF33B@Player@@QAEXPAVXfer@@PAVRva002AE4C5@@@Z
// partial score=0.975902 date=2026-10-10
// ?rva002AF33B@Player@@QAEXPAVXfer@@PAVRva002AE4C5@@@Z
// partial score=0.95 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva002AF33B@Player@@QAEXPAVXfer@@PAVRva002AE4C5@@@Z, retail
// 0x002AF33B..0x002AF438 (253B), thiscall ret 8 (this unused).
//
// Xfers a name-keyed int table (STLport hash_map of AsciiString to int).
// Saving writes the element count (+0x10) then every node's key and value
// walking the table with the first/next iterator helpers; loading reads the
// count then that many key/value pairs and stores each through the table's
// subscript.
//
// Evidence (target): the only caller is Player::xfer (unrowed 0x002B1522;
// WorldBuilder twin 0xC205C0 is Player::DoXfer) at 0x002B207E with ecx =
// the Player and the table at Player+0x2BC. WorldBuilder twin 0xC22A00
// (callgraph lead) keeps this in a local so the method is a member. Xfer
// virtual slots: +0x08 isSaving / +0x6C xferAsciiString / +0x78
// xferUnsignedInt / +0x7C xferInt (as rowed in XferAsciiStringVector.cpp).
// Callees read at the retail REL32s: pinned first 0x00427195 and rowed
// next 0x00411084 (node {next; key +4; value +8}) / StringBase copy ctor
// 0x000365F0 / rowed subscript 0x002AE4C5 / releaseBuffer 0x00036410.
// Float-valued twin 0x002AF236 (xferReal at +0x70) sits right above it.
// The method name stays address-derived.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString &value);
	virtual void slot28();
	virtual void slot29();
	virtual void xferUnsignedInt(UnsignedInt &value);
	virtual void xferInt(Int &value);
};

// Iterator home for the table walk: current node then owning table.
class GameWindow;
class WindowVideo;
class WindowVideoManager
{
public:
	struct hashConstGameWindowPtr;
};
namespace _STL
{
template <class T1, class T2> struct pair;
template <class P> struct _Select1st;
template <class T> struct equal_to;
template <class T> class allocator;
template <class V> struct _Nonconst_traits;
template <class V, class Tr, class K, class HF, class ExK, class EqK, class A>
struct _Ht_iterator
{
	_Ht_iterator() {}
	void *_M_cur;
	void *_M_ht;
};
}
typedef _STL::pair<GameWindow const *const, WindowVideo *> WVPair;
typedef _STL::_Ht_iterator<WVPair, _STL::_Nonconst_traits<WVPair>, const GameWindow *, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<WVPair>, _STL::equal_to<const GameWindow *>, _STL::allocator<WVPair> > WVIter;
class Rva000411084
{
public:
	Rva000411084() {}
	Rva000411084 &operator=(const WVIter &o) { m_current = o._M_cur; m_owner = o._M_ht; return *this; }
	Rva000411084(const WVIter &o) : m_current(o._M_cur), m_owner(o._M_ht) {}
	void *next();

	void *m_current;
	void *m_owner;
};

namespace _STL
{
template <class V, class K, class HF, class ExK, class EqK, class A>
class hashtable
{
public:
	_Ht_iterator<V, _Nonconst_traits<V>, K, HF, ExK, EqK, A> begin();
};
}
typedef _STL::hashtable<WVPair, const GameWindow *, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<WVPair>, _STL::equal_to<const GameWindow *>, _STL::allocator<WVPair> > WVTable;
struct WVMap
{
	WVIter begin() { return m_ht.begin(); }
	WVTable m_ht;
};


// One table node: chain link then the key/value pair.
struct Rva002AF33BNode
{
	Rva002AF33BNode *m_next;
	AsciiString m_key;
	Int m_value;
};

// The hash_map<AsciiString, Int> itself; only the element count is read.
class Rva002AE4C5
{
public:
	Int &rva002AE4C5(const AsciiString *key);

	char m_pad00[0x10];
	UnsignedInt m_numElements;	// +0x10
};

struct CountValue{Int value;UnsignedInt count;};
class Player
{
public:
	void rva002AF33B(Xfer *xfer, Rva002AE4C5 *map);
};

void Player::rva002AF33B(Xfer *xfer, Rva002AE4C5 *map)
{
	if (xfer->isSaving())
	{
		CountValue cv;cv.count=map->m_numElements;
		xfer->xferUnsignedInt(cv.count);
		Rva000411084 it = ((WVMap *)map)->begin();
		Rva002AF33BNode *node;
		for (; (node = (Rva002AF33BNode *)it.m_current) != 0; it.next())
		{
			AsciiString key = node->m_key;
			cv.value = node->m_value;
			xfer->xferAsciiString(key);
			xfer->xferInt(cv.value);
		}
	}
	else
	{
		UnsignedInt count = 0;
		xfer->xferUnsignedInt(count);
		AsciiString key;
		Int value;
		for (UnsignedInt i = 0; i < count; ++i)
		{
			xfer->xferAsciiString(key);
			xfer->xferInt(value);
			map->rva002AE4C5(&key) = value;
		}
	}
}
