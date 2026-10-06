// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva000BCA55@Rva000BCA55@@QAEXH@Z retail 0x000BCA55 28B
// Set-insert discard wrapper: set<int> at +0x9c via rowed insert 0x000BC15D,
// pair return discarded via stack temp. No callers; leaf.
// Evidence: callee 0x000BC15D plus prev row 0x000BC834 in same page.
#include <set>

struct Rva000BCA55
{
	void rva000BCA55(int x);

	char m_pad[0x9c];
	_STL::set<int> m_set;
};

void Rva000BCA55::rva000BCA55(int x)
{
	m_set.insert(x);
}
