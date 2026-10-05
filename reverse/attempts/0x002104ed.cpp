// ?rva002104ED@Rva002104ED@@QAEAAUNoCaseTreeValue4@@PBVAsciiString@@@Z
// partial score=0.97 date=2026-10-05
// ?rva002104ED@Rva002104ED@@QAEAAUNoCaseTreeValue4@@PBVAsciiString@@@Z
// partial score=0.97 date=2026-10-02
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002104ED@Rva002104ED@@QAEAAUNoCaseTreeValue4@@PBVAsciiString@@@Z @0x002104ED 121B find-or-insert returning mapped value
// Evidence: calls rowed find 0x0041534B then on miss copy-constructs key plus zero value and calls just-landed insert 0x00210347 returning pair then +4; on hit returns node+8; caller 0x002106C0; buckets via Rva00056F61 and Rva00210347 views.
struct NoCaseTreeValue4
{
	int m_value;
	NoCaseTreeValue4() : m_value(0) {}
	NoCaseTreeValue4(int v) : m_value(v) {}
};
#include "ascii_string.h"
#include <map>

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;

struct Rva00210347Node
{
	Rva00210347Node *m_next;
	NocasePair m_value;
};

class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};

class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

class Rva00210347
{
public:
	NocasePair &rva00210347(const NocasePair &value);
};

class Rva002104ED
{
public:
	NoCaseTreeValue4 &rva002104ED(const AsciiString *key);
private:
	char m_pad[0];
};

// ?rva002104ED@Rva002104ED@@QAEAAUNoCaseTreeValue4@@PBVAsciiString@@@Z present-unmatched
NoCaseTreeValue4 &Rva002104ED::rva002104ED(const AsciiString *key)
{
	Rva0041534BIter it = ((Rva00056F61 *)this)->rva0041534B(key);
	return it.m_node == 0 ? ((Rva00210347 *)this)->rva00210347(NocasePair(*key, NoCaseTreeValue4())).second
		: *(NoCaseTreeValue4 *)((char *)it.m_node + 8);
}
