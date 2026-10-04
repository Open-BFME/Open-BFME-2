// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0005A0EE@Rva00058D4A@@QAEPAUPair00058D4A@@PAU2@ABUBfmeStringRecord00054F57@@@Z @0x0005A0EE 36B reserve-then-insert wrapper for BfmeStringRecord table.
// Evidence: callees pin reserve 0x00212858 rowed insert 0x00058D4A in stlport_hashtable_str_insert.cpp; m_size at +0x10; callers 0x0005B52C 0x0005B8E5; precedent Rva001DE84FReserveInsert.cpp.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include "ascii_string.h"

struct BfmeStringRecord00054F57 { void *m_a; void *m_b; };
struct HashNode00056E8C { HashNode00056E8C *m_next; BfmeStringRecord00054F57 m_val; };
struct Pair00058D4A { HashNode00056E8C *m_node; void *m_table; bool m_new; };

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
};

class Rva00058D4A
{
public:
	Pair00058D4A *rva00058D4A(Pair00058D4A *out, const BfmeStringRecord00054F57 &key);
	Pair00058D4A *rva0005A0EE(Pair00058D4A *out, const BfmeStringRecord00054F57 &key);
private:
	void *m_00;
	HashNode00056E8C **m_buckets04;
	void *m_08;
	void *m_0C;
	int m_size10;
};

Pair00058D4A *Rva00058D4A::rva0005A0EE(Pair00058D4A *out, const BfmeStringRecord00054F57 &key)
{
	((Rva000427195 *)this)->rva00212858((unsigned int)m_size10 + 1);
	rva00058D4A(out, key);
	return out;
}
