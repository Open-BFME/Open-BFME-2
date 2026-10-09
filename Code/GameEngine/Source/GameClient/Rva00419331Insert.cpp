// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// stlport
// ?rva00419331@Rva000427195@@QAE?AUInsertRet00419331@@PBX@Z, retail 0x00419331 124B.
// Hashtable insert_unique same shape as rowed 0x00212A5A/0x0041539F/0x001F8F2A (124B).
// Buckets at +4/+8 (proven by rowed bucketIndex 0x00223149), count at +0x10 (inc).
// Walks bucket chain with rowed StringBase compare 0x000069D6; on miss allocates
// via rowed _M_new_node 0x0041930C and links it; fills 9-byte pair<iterator,bool>
// out-param and returns it in eax. Evidence: ret-8 thiscall with hidden return
// at +8 and key at +0xC (pair* doubling as AsciiString*).
#include "ascii_string.h"

struct BfmePod20 { int a[5]; };
class Rva004198C6Host { public: void *newNode(const void *value); };

class Rva000427195;

namespace _STL
{
template <class T1, class T2> struct pair
{
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

typedef _STL::pair<const int, BfmePod20> Pod20Pair;
typedef _STL::hashtable<Pod20Pair, int, _STL::hash<int>, _STL::_Select1st<Pod20Pair>, _STL::equal_to<int>, _STL::allocator<Pod20Pair> > Pod20Table;

#pragma pack(push, 1)
struct InsertRet00419331
{
	InsertRet00419331(void *node, void *owner, unsigned char found)
		: m_node(node), m_owner(owner), m_found(found) {}
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};
#pragma pack(pop)

class Rva000427195
{
public:
	int bucketIndex(const AsciiString *name);
	void rva00212858(unsigned int newSize);
	InsertRet00419331 rva00419331(const void *key);
	InsertRet00419331 rva004193AD(const void *key);
	InsertRet00419331 rva004198EB(const void *key);
	InsertRet00419331 rva00419967(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet00419331 Rva000427195::rva00419331(const void *key)
{
	int bucket = bucketIndex((const AsciiString *)key);
	void *head = m_beginBuckets[bucket];
	void *cur = head;
	if (cur != 0)
	{
		do
		{
			if (((const StringBase<char> *)((const char *)cur + 4))->compare(*(const StringBase<char> *)key) == 0)
				return InsertRet00419331(cur, this, 0);
			cur = *(void **)cur;
		} while (cur != 0);
	}
	void *node = (void *)((Pod20Table *)this)->_M_new_node(*(const Pod20Pair *)key);
	*(void **)node = head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return InsertRet00419331(node, this, 1);
}

InsertRet00419331 Rva000427195::rva004193AD(const void *key)
{
	rva00212858(m_numElements + 1);
	return rva00419331(key);
}

InsertRet00419331 Rva000427195::rva004198EB(const void *key)
{
	int bucket = bucketIndex((const AsciiString *)key);
	void *head = m_beginBuckets[bucket];
	void *cur = head;
	if (cur != 0)
	{
		do
		{
			if (((const StringBase<char> *)((const char *)cur + 4))->compare(*(const StringBase<char> *)key) == 0)
				return InsertRet00419331(cur, this, 0);
			cur = *(void **)cur;
		} while (cur != 0);
	}
	void *node = reinterpret_cast<Rva004198C6Host *>(this)->newNode(key);
	*(void **)node = head;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return InsertRet00419331(node, this, 1);
}

InsertRet00419331 Rva000427195::rva00419967(const void *key)
{
	rva00212858(m_numElements + 1);
	return rva004198EB(key);
}
