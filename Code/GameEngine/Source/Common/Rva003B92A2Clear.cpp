// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003B92A2@Rva003B92A2@@QAEXXZ @0x003B92A2 23B.
// Calls the unrowed member 0x003B9132 (pinned by its REL32 at 0x003B92A6) on
// this, then erases the whole vector<BfmeAssignRecord104> held at +0x20 through
// the matched range erase 0x003B908A (STLport vector::erase(first, last)).
// Evidence: target only. Owner class identity is unproven; the names are
// address-derived. Retail's `lea ecx,[esi+0x20]` and the push order
// [ecx+4] then [ecx] are the erase(begin, end) argument shape.
#include <vector>

struct BfmeAssignRecord104
{
	int a[26];
};

class Rva003B92A2
{
	char m_pad[0x20];
	_STL::vector<BfmeAssignRecord104> m_vec20;

public:
	void rva003B92A2();
	void rva003B9132();
};

void Rva003B92A2::rva003B92A2()
{
	rva003B9132();
	_STL::vector<BfmeAssignRecord104> *vec = &m_vec20;
	vec->erase(vec->begin(), vec->end());
}
