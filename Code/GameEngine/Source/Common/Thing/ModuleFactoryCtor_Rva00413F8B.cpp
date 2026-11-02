// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??0Rva00413F8B@@QAE@XZ @0x00413F8B 54B: thiscall ctor with vector at +0 and ModuleTemplateMap at +0xC.
// Evidence: unlock lane, EH prolog, rowed Vector_base BfmeE16 at 0x00211E58 and rowed map ctor at 0x00413727, same shape as Rva0041386B at 0x0041386B.
#include <vector>
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
#include "../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
enum NameKeyType { NK_ZERO = 0 };
#include "../../../Include/Common/ModuleFactoryClass.h"
class Rva00413F8B
{
public:
	Rva00413F8B();
private:
	_STL::vector<BfmeE16> m_vec00;
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > > m_map0C;
};
Rva00413F8B::Rva00413F8B()
{
}
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate>,_STL::allocator<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::_Rb_tree_base(_STL::allocator<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > const &); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > * allocator<_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::allocate(unsigned int,void const *) const; }
// bfme link decl-only end
