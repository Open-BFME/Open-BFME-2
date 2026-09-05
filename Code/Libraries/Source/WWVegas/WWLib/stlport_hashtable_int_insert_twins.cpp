// cl: /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// Five more instantiations of STLport's hashtable::_M_insert, landed as
// relocation-blind twins of
// reference/open-bfme-1's
// Code/Libraries/Source/WWVegas/WWLib/stlport_hashtable_int_int_insert.cpp
// (0x000D3430), which has no counterpart in this repo.  Each differs from the model in exactly two slots: its own
// `resize` and its own out-of-line `_Construct`.  The declarations below are
// the model's, unchanged.
//
// The mapped type is spelled as a distinct one-int struct per instantiation
// rather than `Int`, purely so the five sets of template symbols do not
// collide.  Nothing in these bytes says what the mapped type actually is --
// it is copied through an out-of-line _Construct and never inspected.

// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::hashtable<pair<const Int, Int> >::_M_insert, retail
// 0x000D3430, 111 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// The layout falls out of the offsets. Three empty functors sit at +0 and pad
// to four, then the bucket vector's three pointers at +4, +8 and +0x0C, and
// the element count at +0x10.
//
// The bucket index is computed inline as a plain divide: hash<Int> is the
// identity, so the key is read straight out of the pair and taken modulo the
// bucket count. The node is 12 bytes -- one next pointer and the eight-byte
// pair -- and the value is copy-constructed through an out-of-line _Construct,
// which is why the next pointer is cleared before the call and only linked to
// the old bucket head afterwards.
//
// There is no unwind frame, so this translation unit is built without
// exceptions and STLport's try around the construct is gone.

typedef int Int;

namespace _STL
{

// The node allocator's own _M_allocate is private in STLport, so the call is
// spelled through the free-function name the ledger already pins on the same
// body at 0x0082E540.
void *__cdecl vectorSmallAllocate(unsigned int bytes);

template <class T1, class T2>
struct pair
{
	typedef T1 first_type;

	T1 first;
	T2 second;
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(const T &x) const { return (unsigned int)x; }
};

template <class T>
struct equal_to {};

template <class T>
struct _Select1st
{
	const typename T::first_type &operator()(const T &x) const { return x.first; }
};

template <class T>
class allocator {};

// _M_buckets is a vector of void*, not of node pointers, and its size and its
// indexing go through separate inline accessors -- which is why retail reloads
// the start pointer after the divide instead of keeping it live.
class _BucketVector
{
public:
	unsigned int size(void) const { return (unsigned int)(_M_finish - _M_start); }

	void *&operator[](unsigned int n) { return *(_M_start + n); }
	void *const &operator[](unsigned int n) const { return *(_M_start + n); }

	void **_M_start;					// +0x00
	void **_M_finish;					// +0x04
	void **_M_end_of_storage;				// +0x08
};

template <class V>
struct _Hashtable_node
{
	_Hashtable_node<V> *_M_next;
	V _M_val;
};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
class hashtable
{
public:
	typedef unsigned int size_type;
	typedef _Hashtable_node<Value> _Node;

	Value &_M_insert(const Value &obj);

private:
	void resize(size_type numElementsHint);			// retail 0x000D10F0

	size_type _M_bkt_num_key(const Key &key) const
	{
		return _M_hash(key) % _M_buckets.size();
	}

	size_type _M_bkt_num(const Value &obj) const
	{
		return _M_bkt_num_key(_M_get_key(obj));
	}

	_Node *_M_new_node(const Value &obj)
	{
		_Node *n = (_Node *)vectorSmallAllocate(sizeof(_Node));
		n->_M_next = 0;
		_Construct(&n->_M_val, obj);
		return n;
	}

	HashFcn _M_hash;					// +0x00
	EqualKey _M_equals;
	ExtractKey _M_get_key;
	_BucketVector _M_buckets;				// +0x04
	size_type _M_num_elements;				// +0x10
};

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
Value &hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::_M_insert(const Value &obj)
{
	resize(_M_num_elements + 1);

	size_type n = _M_bkt_num(obj);
	_Node *first = (_Node *)_M_buckets[n];
	_Node *tmp = _M_new_node(obj);
	tmp->_M_next = first;
	_M_buckets[n] = tmp;
	++_M_num_elements;
	return tmp->_M_val;
}


struct Open2MappedA { Int m_value; };

typedef pair<const Int, Open2MappedA> Open2PairA;

template Open2PairA &hashtable<Open2PairA, Int, hash<Int>,
	_Select1st<Open2PairA>, equal_to<Int>,
	allocator<Open2PairA> >::_M_insert(const Open2PairA &);


struct Open2MappedB { Int m_value; };

typedef pair<const Int, Open2MappedB> Open2PairB;

template Open2PairB &hashtable<Open2PairB, Int, hash<Int>,
	_Select1st<Open2PairB>, equal_to<Int>,
	allocator<Open2PairB> >::_M_insert(const Open2PairB &);


struct Open2MappedC { Int m_value; };

typedef pair<const Int, Open2MappedC> Open2PairC;

template Open2PairC &hashtable<Open2PairC, Int, hash<Int>,
	_Select1st<Open2PairC>, equal_to<Int>,
	allocator<Open2PairC> >::_M_insert(const Open2PairC &);


struct Open2MappedD { Int m_value; };

typedef pair<const Int, Open2MappedD> Open2PairD;

template Open2PairD &hashtable<Open2PairD, Int, hash<Int>,
	_Select1st<Open2PairD>, equal_to<Int>,
	allocator<Open2PairD> >::_M_insert(const Open2PairD &);


struct Open2MappedE { Int m_value; };

typedef pair<const Int, Open2MappedE> Open2PairE;

template Open2PairE &hashtable<Open2PairE, Int, hash<Int>,
	_Select1st<Open2PairE>, equal_to<Int>,
	allocator<Open2PairE> >::_M_insert(const Open2PairE &);

}
