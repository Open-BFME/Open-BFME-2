// ?rva0020D67C@Rva000427195@@QAEPAPAXABVAsciiString@@@Z
// partial score=0.97136 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0020D638@Rva000427195@@QAEPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x0020D638 68B hashtable insert via resize plus bucketIndex plus node alloc.
// Evidence: unlock lane all callees rowed or pinned; caller at 0x0020D6C3 in 0x0020D67C; neighbours 0x0020D613 and 0x0020D7A6.
#include "ascii_string.h"
#include <map>
struct NoCaseTreeValue4
{
	void *m_value;
    NoCaseTreeValue4(void *value=0):m_value(value){}
};
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;
class Rva000427195
{
public:
	void *rva0020D638(const NocasePair &src);
    void **rva0020D67C(const AsciiString &key);
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *name);
	void *rva0020D613(const NocasePair &src);
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void *m_pad0C;
	unsigned int m_count;
};
void *Rva000427195::rva0020D638(const NocasePair &src)
{
	rva00212858(m_count + 1);
	int idx = bucketIndex((const AsciiString *)&src);
	void *old = m_beginBuckets[idx];
	void *nn = rva0020D613(src);
	*(void **)nn = old;
	m_beginBuckets[idx] = nn;
	++m_count;
	return (char *)nn + 4;
}

class Rva00056F61;
struct Rva0041534BIter {
    void *node;
    Rva00056F61 *table;
    Rva0041534BIter(void *n,Rva00056F61*t):node(n),table(t){}
};
class Rva00056F61 {public:Rva0041534BIter rva0041534B(const AsciiString *key);};
void **Rva000427195::rva0020D67C(const AsciiString &key)
{
    Rva0041534BIter it = ((Rva00056F61 *)this)->rva0041534B(&key);
    return it.node == 0 ?
        (void **)((char *)rva0020D638(NocasePair(key,NoCaseTreeValue4())) + 4) :
        (void **)((char *)it.node + 8);
}
