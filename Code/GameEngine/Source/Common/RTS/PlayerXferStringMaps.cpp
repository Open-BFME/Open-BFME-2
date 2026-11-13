// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva002AF33B@Player@@QAEXPAVXfer@@PAVRva002AE4C5@@@Z
// r27 2026-10-20: exact 253/253. Retail's frame packing needs every callee that
// receives &it to be visible all the way down: next 0x00411084 -> advance
// 0x003F7925 -> bucketIndex 0x00223149 -> Rva00055041AsciiHash 0x00055041 ->
// _STL::__stl_hash_string 0x0002BA61 (STLport <stl/_hash_fun.h> inline; any opaque call in that chain makes `it`
// escape, so it cannot share the load value's slot). With the chain visible,
// the WB C22A00 declaration shape (save: value, count, it; key in the loop)
// places count/value/begin temp exactly as retail.
// stlport
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
#include <vector>
#include <stl/_hash_fun.h>

// Preserve inlined bucket access and bind outlined copies to the shared retail helpers.
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<void *>::iterator vector<void *>::begin()
{ return this->_M_start; }
template <> __declspec(dllimport) __forceinline
vector<void *>::size_type vector<void *>::size() const
{ return size_type(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
vector<void *>::reference vector<void *>::operator[](size_type index)
{ return *(this->_M_start + index); }
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

// Iterator home for the table walk: current node then owning table.
class GameWindow;
class WindowVideo;
#include "../../../Include/GameClient/WindowVideoManagerClass.h"
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
	_Ht_iterator(void *cur, void *ht) : _M_cur(cur), _M_ht(ht) {}
	_Ht_iterator(const _Ht_iterator &other) : _M_cur(other._M_cur), _M_ht(other._M_ht) {}
	void *_M_cur;
	void *_M_ht;
};
}
typedef _STL::pair<GameWindow const *const, WindowVideo *> WVPair;
typedef _STL::_Ht_iterator<WVPair, _STL::_Nonconst_traits<WVPair>, const GameWindow *, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<WVPair>, _STL::equal_to<const GameWindow *>, _STL::allocator<WVPair> > WVIter;
__declspec(noinline) unsigned int __stdcall Rva00055041AsciiHash(const AsciiString *name)
{
	const StringBase<char> *data = *(const StringBase<char> * const *)name;
	const char *chars = data != 0 ? (const char *)data + 8 : "";
	return _STL::__stl_hash_string(chars);
}
#include "../../../Include/GameLogic/Rva000427195.h"
int Rva000427195::bucketIndex(const AsciiString *name)
{
	unsigned hash = Rva00055041AsciiHash(name);
	unsigned count = (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2);
	return hash % count;
}
#include "../../../Include/GameClient/Rva000411084.h"

__declspec(noinline) inline void *Rva000411084::next()					// 0x00411084
{
	void *node = *(void **)m_current;
	if (node == 0)
		node = advance();
	m_current = node;
	return this;
}
__declspec(noinline) inline void *Rva000411084::advance()				// 0x003F7925
{
	struct Table
	{
		void *m_unused00;
		union {
			void **m_beginBuckets;
			void ** volatile m_beginBucketsVolatile;
		};
		void **m_endBuckets;
		int bucketIndex(const AsciiString *name);
	};
	Table *table = (Table *)m_owner;
	unsigned index = (unsigned)((Rva000427195 *)table)->bucketIndex((const AsciiString *)((char *)m_current + 4));
	unsigned count = (unsigned)(((char *)table->m_endBuckets - (char *)table->m_beginBuckets) >> 2);
	void *head = 0;
	do {
		++index;
		if (index >= count)
			break;
		head = table->m_beginBucketsVolatile[index];
	} while (head == 0);
	return head;
}


namespace _STL
{
template <class V, class K, class HF, class ExK, class EqK, class A>
class hashtable
{
public:
	__declspec(noinline) _Ht_iterator<V, _Nonconst_traits<V>, K, HF, ExK, EqK, A> begin()	// 0x00427195
	{
		for (unsigned n = 0; n < m_buckets.size(); ++n)
			if (m_buckets[n])
				return _Ht_iterator<V, _Nonconst_traits<V>, K, HF, ExK, EqK, A>(m_buckets[n], this);
		return _Ht_iterator<V, _Nonconst_traits<V>, K, HF, ExK, EqK, A>(0, this);
	}
	int bucketIndex(const AsciiString *name);
	void *m_unused00;
	vector<void *> m_buckets;
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

#include "../../../Include/Common/Rva001FDE3F.h"
struct Rva002AF236Node
{
	Rva002AF236Node *m_next;
	AsciiString m_key;
	float m_value;
};
#include "../../../Include/Common/Player.h"

void Player::rva002AF236(Xfer *xfer, Rva001FDE3F *map)
{
	if (xfer->IsStoring())
	{
		float value;
		UnsignedInt count = ((Rva002AE4C5 *)map)->m_numElements;
		(*xfer == count);
		Rva000411084 it;
		{
			WVIter first = ((WVMap *)map)->begin();
			it.m_current = first._M_cur;
			it.m_owner = first._M_ht;
		}
		for (; it.m_current != 0; it.next())
		{
			AsciiString key = ((Rva002AF236Node *)it.m_current)->m_key;
			value = ((Rva002AF236Node *)it.m_current)->m_value;
			(*xfer == key);
			(*xfer == value);
		}
	}
	else
	{
		UnsignedInt count = 0;
		(*xfer == count);
		AsciiString key;
		float value;
		for (UnsignedInt i = 0; i < count; ++i)
		{
			(*xfer == key);
			(*xfer == value);
			map->rva001FDE3F(key) = value;
		}
	}
}

void Player::rva002AF33B(Xfer *xfer, Rva002AE4C5 *map)
{
	if (xfer->IsStoring())
	{
		Int value;
		UnsignedInt count = map->m_numElements;
		(*xfer == count);
		Rva000411084 it;
		{
			WVIter first = ((WVMap *)map)->begin();
			it.m_current = first._M_cur;
			it.m_owner = first._M_ht;
		}
		for (; it.m_current != 0; it.next())
		{
			AsciiString key = ((Rva002AF33BNode *)it.m_current)->m_key;
			value = ((Rva002AF33BNode *)it.m_current)->m_value;
			(*xfer == key);
			(*xfer == value);
		}
	}
	else
	{
		UnsignedInt count = 0;
		(*xfer == count);
		AsciiString key;
		Int value;
		for (UnsignedInt i = 0; i < count; ++i)
		{
			(*xfer == key);
			(*xfer == value);
			map->rva002AE4C5(&key) = value;
		}
	}
}
