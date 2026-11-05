// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?rva00410E23@Rva000427195@@QAEPAU?$pair@$$CBVAsciiString@@UTreeHintPayload00410E23@@@_STL@@PBU23@@Z, retail 0x00410E23 68B. Hashtable insert
// over the Eva bucket vector for the AsciiString-keyed 12-byte node family.
// Buckets at +4 count at +0x10 (same layout as rowed erase 0x00223429 and
// bucketIndex 0x00223149). Resizes via pin 0x00212858 with count+1 hashes key
// via rowed 0x00223149 allocates node via rowed _M_new_node 0x00410956 of the
// AsciiString -> Rva0045EF90Object hashtable (stlport_pod_hash_bodies.cpp)
// links old head bumps count returns value at +4. Same shape as landed 0x00410DDF/0x00410E67 68B inserts.
// Caller 0x00411258 in 0x00411205.
#include "ascii_string.h"

struct TreeHintPayload00410E23
{
	unsigned char m_body[4];
};

class Rva0045EF90Object;

namespace rts {
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
}

class Rva000427195;

namespace _STL {
template <class T1, class T2> struct pair
{
	~pair();
	T1 first;
	T2 second;
};
template <class T> struct hash
{
};
template <class T> struct _Select1st
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class V> struct _Hashtable_node
{
	_Hashtable_node<V> *_M_next;
	V _M_val;
};
class _BucketVector
{
public:
	void **_M_start;
	void **_M_finish;
	void **_M_end;
};
template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
class hashtable
{
	friend class ::Rva000427195;
public:
	typedef unsigned int size_type;
	typedef _Hashtable_node<Value> _Node;
private:
	_Node *_M_new_node(const Value &obj);
	HashFcn _M_hash;
	EqualKey _M_equals;
	ExtractKey _M_get_key;
	_BucketVector _M_buckets;
	size_type _M_num_elements;
};
}

typedef _STL::pair<const AsciiString, Rva0045EF90Object> Rva00461BF0Value;
typedef _STL::hashtable<Rva00461BF0Value, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<Rva00461BF0Value>, rts::equal_to<AsciiString>, _STL::allocator<Rva00461BF0Value> > Rva00461BF0Table;

#include "../../Include/GameLogic/Rva000427195.h"

_STL::pair<const AsciiString, TreeHintPayload00410E23> *Rva000427195::rva00410E23(const _STL::pair<const AsciiString, TreeHintPayload00410E23> *entry)
{
	rva00212858(m_numElements + 1);
	int bucket = bucketIndex(&entry->first);
	void *old = m_beginBuckets[bucket];
	void *newNode = (void *)((Rva00461BF0Table *)this)->_M_new_node(*(const Rva00461BF0Value *)(const void *)entry);
	*(void **)newNode = old;
	m_beginBuckets[bucket] = newNode;
	++m_numElements;
	return (_STL::pair<const AsciiString, TreeHintPayload00410E23> *)((char *)newNode + 4);
}
