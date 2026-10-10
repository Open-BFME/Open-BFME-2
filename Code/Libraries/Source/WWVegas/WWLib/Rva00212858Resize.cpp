// cl: /O1 /G7 /arch:SSE /EHs-c- /DNDEBUG /MD
// ?rva00212858@Rva000427195@@QAEXI@Z, retail 0x00212858, 199 bytes.
// Bucket-table grower of the AsciiString-keyed STLport 4.5.3 hashtable that the
// Eva bucket helpers wrap: hashtable::resize(size_type __num_elements_hint),
// the donor stl/_hashtable.c loop verbatim (while (__first) relink into
// __tmp[_M_bkt_num(...)], reload _M_buckets[__bucket]).
// Target facts: old bucket count from the vector<void*> at +4 (sar 2); the
// private _M_next_size 0x0005571B (thiscall, rowed under the Rva001FDCE1Record
// hashtable spelling); a vector<void*>(n, 0, get_allocator()) temporary
// (0x00023B50 / 0x00026A40); _M_bkt_num inlined: the hasher at 0x00055041 is
// called with ecx reloaded from the saved this (a thiscall functor member at
// offset 0) and the remainder by div; swap 0x00026B60; then the temporary's
// inlined destructor frees its storage through free 0x00030830. No EH frame.
// Codegen: retail keeps &_M_buckets[__bucket] and &__tmp[__new_bucket] live
// across the hash call, which VC7.1 does only when it sees the hasher's body
// (and the __stl_hash_string leaf it calls) and knows neither writes memory:
// STLport's hash functor and _hash_fun.h are header inlines. Both copies this
// unit emits are retail's bytes (0x00055041 30B, 0x0002BA61 24B).
// Callers: the insert-with-resize wrappers that spell this name (EvaBucketEnsure
// 0x003F797C, Rva00418374, Rva002234BAInsert, ... 31 units); the value type
// stays address-derived (ICF folds every AsciiString-keyed copy).

class AsciiString;
extern "C" void __cdecl free(void *);

struct Rva001FDCE1Record;
class Rva000427195;

namespace _STL
{
	template <class T> class allocator
	{
	public:
		allocator();
		allocator(const allocator &);
	};

	// Declaration-only view: the three members retail calls out of line,
	// the fields, and no inline bodies (this unit emits no vector COMDATs).
	template <class T, class A = allocator<T> > class vector
	{
	public:
		vector(unsigned int n, const T &value, const A &a);
		A get_allocator() const;
		void swap(vector &other);

		T *_M_start;
		T *_M_finish;
		T *_M_end_of_storage;
	};

	template <class T1, class T2> struct pair {};
	template <class T> struct hash {};
	template <class P> struct _Select1st {};
	template <class T> struct equal_to {};

	template <class V, class K, class HF, class ExK, class EqK, class A> class hashtable
	{
		friend class ::Rva000427195;
		unsigned int _M_next_size(unsigned int n) const;
	};

	// Donor stl/_hash_fun.h verbatim (see stlport_hash_string.cpp, its row).
	inline unsigned int __cdecl __stl_hash_string(const char *__s)
	{
		unsigned long __h = 0;
		for (; *__s; ++__s)
			__h = 5 * __h + *__s;

		return static_cast<unsigned int>(__h);
	}
}

typedef _STL::pair<const int, Rva001FDCE1Record> Rva00212858Pair;
typedef _STL::hashtable<Rva00212858Pair, int, _STL::hash<int>, _STL::_Select1st<Rva00212858Pair>,
	_STL::equal_to<int>, _STL::allocator<Rva00212858Pair> > Rva00212858NextSize;

// The AsciiString hash functor (retail 0x00055041, the same 30 bytes as the
// stdcall row ?Rva00055041AsciiHash@@YGIPBVAsciiString@@@Z in EvaAsciiHash.cpp:
// ret 4, ecx unused): the chars 8 past the StringBase header, or "".
struct Rva00055041AsciiHash
{
	unsigned int operator()(const AsciiString &key) const
	{
		const char *data = *(const char * const *)&key;
		return _STL::__stl_hash_string(data != 0 ? data + 8 : "");
	}
};

struct Rva00212858Node
{
	Rva00212858Node *m_next;
	AsciiString *m_key; // first word of the stored pair
};

class Rva000427195
{
public:
	void rva00212858(unsigned int n);

private:
	Rva00055041AsciiHash m_hash;
	_STL::vector<void *> m_buckets;
	unsigned int m_numElements;
};

void Rva000427195::rva00212858(unsigned int n)
{
	const _STL::vector<void *> &buckets = m_buckets;
	const unsigned int oldCount = (unsigned int)(buckets._M_finish - buckets._M_start);
	if (n > oldCount)
	{
		const unsigned int count = reinterpret_cast<const Rva00212858NextSize *>(this)->_M_next_size(n);
		if (count > oldCount)
		{
			_STL::vector<void *> tmp(count, (void *)0, m_buckets.get_allocator());
			for (unsigned int bucket = 0; bucket < oldCount; ++bucket)
			{
				Rva00212858Node *first = (Rva00212858Node *)m_buckets._M_start[bucket];
				while (first)
				{
					unsigned int newBucket = m_hash(*(const AsciiString *)&first->m_key) % count;
					m_buckets._M_start[bucket] = first->m_next;
					void *&dst = tmp._M_start[newBucket];
					first->m_next = (Rva00212858Node *)dst;
					dst = first;
					first = (Rva00212858Node *)m_buckets._M_start[bucket];
				}
			}
			m_buckets.swap(tmp);
			if (tmp._M_start)
				free(tmp._M_start);
		}
	}
}
