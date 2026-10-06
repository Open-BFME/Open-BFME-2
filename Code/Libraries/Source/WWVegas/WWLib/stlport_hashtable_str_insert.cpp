// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00058D4A@Rva00058D4A@@QAEPAUPair00058D4A@@PAU2@ABUBfmeStringRecord00054F57@@@Z @0x00058D4A 124B: hashtable find-or-create for BfmeStringRecord00054F57; bucketIndex plus chain compare plus pinned New method prepend plus out pair; caller 0x0005A105 in 0x0005A0EE; callees rowed bucketIndex compare plus pinned rva00056E8C ICF twin of free New.
class AsciiString;
class Rva000427195 { public: int bucketIndex(const AsciiString *s); };
template <class T> class StringBase { public: int compare(const StringBase &o) const; };
struct BfmeStringRecord00054F57 { void *m_a; void *m_b; };
struct HashNode00056E8C { HashNode00056E8C *m_next; BfmeStringRecord00054F57 m_val; };
struct Pair00058D4A { HashNode00056E8C *m_node; void *m_table; bool m_new; };
class Rva00058D4A {
public:
	HashNode00056E8C *rva00056E8C(const BfmeStringRecord00054F57 &v);
	Pair00058D4A *rva00058D4A(Pair00058D4A *ret, const BfmeStringRecord00054F57 &key);
private:
	void *m_00;
	HashNode00056E8C **m_buckets;
	void *m_08; void *m_0C;
	unsigned int m_size;
};
Pair00058D4A *Rva00058D4A::rva00058D4A(Pair00058D4A *ret, const BfmeStringRecord00054F57 &key)
{
	int b = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)&key);
	HashNode00056E8C *head = m_buckets[b];
	HashNode00056E8C *cur = head;
	while (cur != 0) {
		if (((const StringBase<char> *)&cur->m_val)->compare((const StringBase<char> &)key) == 0)
			goto found;
		cur = cur->m_next;
	}
	{
		HashNode00056E8C *n = rva00056E8C(key);
		n->m_next = head;
		m_buckets[b] = n;
		++m_size;
		ret->m_node = n;
		ret->m_table = this;
		ret->m_new = true;
		return ret;
	}
found:
	ret->m_node = cur;
	ret->m_table = this;
	ret->m_new = false;
	return ret;
}
