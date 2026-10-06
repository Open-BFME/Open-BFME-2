// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0060CB2B@Rva0060CB2B@@QBEPAURva0060CB2BNode@@ABQBD@Z at retail 0x0060CB2B (54B).
// Hashtable _M_find with const char* key: hashes the string via rowed
// __stl_hash_string 0x0002BA61, mods by bucket count from +4/+8, then walks
// the chain comparing node key pointers at +4 (interned/static keys, so
// pointer equality is the whole compare). Caller 0x0060CB7C wraps the node
// into an iterator; caller 0x0060CEA5. Sibling of string bktnum 0x0060CD16.
// Honest-address name; key arrives by reference (pointer to char* at +0).

namespace _STL
{
unsigned int __stl_hash_string(const char *str);
}

struct Rva0060CB2BNode
{
	void *m_next;
	const char *m_key;
};

struct Rva0060CB2BIterator
{
	Rva0060CB2BNode *m_cur;
	const void *m_ht;

	Rva0060CB2BIterator(Rva0060CB2BNode *cur, const void *ht)
		: m_cur(cur), m_ht(ht)
	{
	}
};

struct Rva0060CB2BBuckets
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

class Rva0060CB2B
{
public:
	Rva0060CB2BNode *rva0060CB2B(const char * const &key) const;
	Rva0060CB2BIterator rva0060CB7C(const char * const &key);

private:
	int m_00;
	Rva0060CB2BBuckets m_buckets;
};

Rva0060CB2BNode *Rva0060CB2B::rva0060CB2B(const char * const &key) const
{
	const char *k = key;
	unsigned int h = _STL::__stl_hash_string(k);
	unsigned int n = h % m_buckets.size();
	Rva0060CB2BNode *first = (Rva0060CB2BNode *)m_buckets[n];
	for (; first && first->m_key != k; first = (Rva0060CB2BNode *)first->m_next)
	{
	}
	return first;
}

Rva0060CB2BIterator Rva0060CB2B::rva0060CB7C(const char * const &key)
{
	return Rva0060CB2BIterator(rva0060CB2B(key), this);
}
