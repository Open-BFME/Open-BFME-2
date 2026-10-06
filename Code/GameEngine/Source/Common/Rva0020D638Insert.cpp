// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0020D638@Rva000427195@@QAEPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x0020D638 68B hashtable insert via resize plus bucketIndex plus node alloc.
// Evidence: unlock lane all callees rowed or pinned; caller at 0x0020D6C3 in 0x0020D67C; neighbours 0x0020D613 and 0x0020D7A6.
#include "ascii_string.h"
#include <map>
struct NoCaseTreeValue4
{
	char m_body[4];
};
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;
class Rva000427195
{
public:
	void *rva0020D638(const NocasePair &src);
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
