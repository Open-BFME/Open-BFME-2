// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0060CAEA@Rva0060CAEA@@QBEPAURva0060CAEANode@@ABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z at retail 0x0060CAEA (65B).
// Hashtable _M_find with string key: hashes via rowed __stl_string_hash
// 0x0060C9F0, mods by bucket count from +4/+8, then walks the chain calling
// rowed string operator== 0x00007780 on ([node+4], key). Caller 0x0060CB61
// wraps the node into an iterator; caller 0x0060D326. Sibling of bktnum
// 0x0060CD16 which shares layout and flags. Honest-address name; key by
// reference. Previous wall (ecx vs esi plus push source) solved by the
// nested bucket-vector form that keeps this in esi like the char-pointer
// sibling 0x0060CB2B.

#include <string>

namespace _STL
{
unsigned int __stl_string_hash(const string &s);
// Declare the string equality specialization so this TU calls retail's /O2
// repe-cmpsb body in w3d_dep.cpp instead of emitting its own /O1 copy.
// This also drops the char_traits compare and string size/data copies that
// only the inline instantiation needed.
template<> bool operator==(const string &x, const string &y);
}

struct Rva0060CAEANode
{
	void *m_next;
	_STL::string m_key;
};

struct Rva0060CAEAIterator
{
	Rva0060CAEANode *m_cur;
	const void *m_ht;

	Rva0060CAEAIterator(Rva0060CAEANode *cur, const void *ht)
		: m_cur(cur), m_ht(ht)
	{
	}
};

struct Rva0060CAEABuckets
{
	void **_M_start;
	void **_M_finish;
	void **_M_end;

	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}
	void *operator[](unsigned int n) const
	{
		return _M_start[n];
	}
};

class Rva0060CAEA
{
public:
	Rva0060CAEANode *rva0060CAEA(const _STL::string &key) const;
	Rva0060CAEAIterator rva0060CB61(const _STL::string &key);

private:
	int m_00;
	Rva0060CAEABuckets m_buckets;
};

Rva0060CAEANode *Rva0060CAEA::rva0060CAEA(const _STL::string &key) const
{
	unsigned int h = _STL::__stl_string_hash(key);
	unsigned int n = h % m_buckets.size();
	Rva0060CAEANode *first = (Rva0060CAEANode *)m_buckets[n];
	for (; first && !(first->m_key == key); first = (Rva0060CAEANode *)first->m_next)
	{
	}
	return first;
}

Rva0060CAEAIterator Rva0060CAEA::rva0060CB61(const _STL::string &key)
{
	return Rva0060CAEAIterator(rva0060CAEA(key), this);
}
