// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?rva0002CA72@Rva0002CA72@@QAEPAUOut0002CA72@@PAU2@PBUPair0002CA72@@@Z @0x0002CA72 124B
// Hashtable insert_unique_noresize for hash_map<AsciiString BuildableStatus rts::hash rts::equal_to>.
// Target evidence: retail calls rowed _M_bkt_num_key 0x0002C669, rowed compareNoCase 0x00006A00,
// rowed new-node 0x00223124; bucket array at +4, count at +0x10, hidden out-pointer ret 8.
// Donor: Code/GameEngine/Source/GameClient/Rva004182F8Insert.cpp (124B same shape, compare->compareNoCase).

#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <hash_map>

namespace rts
{
	template <class T> struct hash
	{
	};
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(const AsciiString &key) const;
	};
	template <class T> struct equal_to
	{
	};
	template <> struct equal_to<AsciiString>
	{
		// Expanded in place; the file emits no out-of-line copy of this functor.
		__declspec(dllimport) __forceinline bool operator()(const AsciiString &a, const AsciiString &b) const
		{
			return a.compareNoCase(b) == 0;
		}
	};
}

enum BuildableStatus
{
	BUILDABLE_STATUS_UNKNOWN = 0
};

class Rva0002CA72;

namespace _STL
{
class _BucketVector
{
public:
	unsigned size() const { return (unsigned)(_M_finish - _M_start); }
	void *&operator[](unsigned n) { return *(_M_start + n); }
	void **_M_start;
	void **_M_finish;
	void **_M_end;
};
// The members of this table the rowed insert touches: the hash key lookup and
// the bucket array at +4 and count at +0x10.
template <>
class hashtable<pair<const AsciiString, BuildableStatus>, AsciiString, rts::hash<AsciiString>,
	_Select1st<pair<const AsciiString, BuildableStatus> >, rts::equal_to<AsciiString>,
	allocator<pair<const AsciiString, BuildableStatus> > >
{
	friend class ::Rva0002CA72;
public:
	typedef unsigned size_type;
private:
	size_type _M_bkt_num_key(const AsciiString &key) const;
	rts::hash<AsciiString> _M_hash;
	rts::equal_to<AsciiString> _M_equals;
	_Select1st<pair<const AsciiString, BuildableStatus> > _M_get_key;
	_BucketVector _M_buckets;
	size_type _M_num_elements;
};
}

class Rva00223124
{
public:
	void *rva00223124(const void *obj);
};

struct Pair0002CA72
{
	const AsciiString first;
	BuildableStatus second;
};

struct Out0002CA72
{
	void *m_node;
	void *m_table;
	unsigned char m_inserted;
};

struct Node0002CA72
{
	Node0002CA72 *_M_next;
	Pair0002CA72 _M_val;
};

class Rva0002CA72
{
private:
	typedef _STL::pair<const AsciiString, BuildableStatus> TablePair;
	typedef _STL::hashtable<TablePair, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<TablePair>, rts::equal_to<AsciiString>, _STL::allocator<TablePair> > Table;
public:
	struct Out0002CA72 *rva0002CA72(struct Out0002CA72 *out, const struct Pair0002CA72 *obj);
private:
	Table m_table; // +0x00
};

Out0002CA72 *Rva0002CA72::rva0002CA72(Out0002CA72 *out, const Pair0002CA72 *obj)
{
	unsigned bucketIndex = m_table._M_bkt_num_key(*(const AsciiString *)obj);
	void *head = m_table._M_buckets[bucketIndex];
	Node0002CA72 *cur = (Node0002CA72 *)head;
	if (cur != 0) {
		do {
			const StringBase<char> &curKey = (const StringBase<char> &)cur->_M_val.first;
			if (curKey.compareNoCase((const StringBase<char> &)*(const AsciiString *)obj) == 0) {
				out->m_node = cur;
				out->m_table = this;
				out->m_inserted = 0;
				return out;
			}
			cur = cur->_M_next;
		} while (cur != 0);
	}
	Node0002CA72 *fresh = (Node0002CA72 *)((Rva00223124 *)this)->rva00223124(obj);
	fresh->_M_next = (Node0002CA72 *)head;
	m_table._M_buckets[bucketIndex] = fresh;
	++m_table._M_num_elements;
	out->m_node = fresh;
	out->m_table = this;
	out->m_inserted = 1;
	return out;
}
