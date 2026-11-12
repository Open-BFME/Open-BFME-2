// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00357E14@Rva00357E14@@QAEXABUBfmeFloat4Record00469C61@@@Z, retail 0x00357E14 28B chain.
// Evidence: rowed list<BfmeFloat4Record> insert 0x1DD86F, begin double-deref shape.
#include <list>

#include "../../../Include/GameLogic/BfmeFloat4Record00469C61.h"

bool operator==(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);
bool operator<(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);

class Rva00357E14
{
public:
	void rva00357E14(const BfmeFloat4Record00469C61 &rec);

private:
	_STL::list<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> > m_list; // +0
};

// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmeFloat4Record00469C61,BfmeFloat4Record00469C61>(BfmeFloat4Record00469C61 *,BfmeFloat4Record00469C61 const &); }
namespace _STL { template <> _STL::_List_node<BfmeFloat4Record00469C61> * list<BfmeFloat4Record00469C61,_STL::allocator<BfmeFloat4Record00469C61> >::_M_create_node(BfmeFloat4Record00469C61 const &); }
// bfme link decl-only end
void Rva00357E14::rva00357E14(const BfmeFloat4Record00469C61 &rec)
{
	m_list.insert(m_list.begin(), rec);
}
