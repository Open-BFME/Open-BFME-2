// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?rva00410E23@Rva000427195@@QAEPAU?$pair@$$CBVAsciiString@@UTreeHintPayload00410E23@@@_STL@@PBU23@@Z, retail 0x00410E23 68B. Hashtable insert
// over the Eva bucket vector for the AsciiString-keyed 12-byte node family.
// Buckets at +4 count at +0x10 (same layout as rowed erase 0x00223429 and
// bucketIndex 0x00223149). Resizes via pin 0x00212858 with count+1 hashes key
// via rowed 0x00223149 allocates node via rowed _M_new_node 0x00410956 (12B
// Pod44 node, ICF twin: plain 8B pair copy) links old head bumps count returns
// value at +4. Same shape as landed 0x00410DDF/0x00410E67 68B inserts.
// Caller 0x00411258 in 0x00411205.
#include "ascii_string.h"

struct TreeHintPayload00410E23
{
	unsigned char m_body[4];
};

struct BfmePod44
{
	unsigned char m_body[4];
};

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

typedef _STL::pair<const int, BfmePod44> Pod44Pair;
typedef _STL::hashtable<Pod44Pair, int, _STL::hash<int>, _STL::_Select1st<Pod44Pair>, _STL::equal_to<int>, _STL::allocator<Pod44Pair> > Pod44Table;

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *key);
	_STL::pair<const AsciiString, TreeHintPayload00410E23> *rva00410E23(const _STL::pair<const AsciiString, TreeHintPayload00410E23> *arg);
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

_STL::pair<const AsciiString, TreeHintPayload00410E23> *Rva000427195::rva00410E23(const _STL::pair<const AsciiString, TreeHintPayload00410E23> *arg)
{
	rva00212858(m_numElements + 1);
	int b = bucketIndex(&arg->first);
	void *old = m_beginBuckets[b];
	void *n = (void *)((Pod44Table *)this)->_M_new_node(*(const Pod44Pair *)(const void *)arg);
	*(void **)n = old;
	m_beginBuckets[b] = n;
	++m_numElements;
	return (_STL::pair<const AsciiString, TreeHintPayload00410E23> *)((char *)n + 4);
}
