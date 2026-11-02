// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0060146B@@QAE@XZ @0x0060146B 16B
// Map-plus-flag ctor: builds the NameKeyType->ModuleTemplate map at +0 via the
// rowed map ctor at 0x00413727 then sets byte at +0xC to 1 and returns this.
// Evidence: callee rowed map ctor in ModuleFactory.cpp; caller 0x006015B4.

#include <map>

enum NameKeyType
{
	RvaNameKeyZero = 0
};

#include "../../../Include/Common/ModuleFactoryClass.h"

typedef _STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType> > RvaMapType;

class Rva0060146B
{
public:
	Rva0060146B();

private:
	RvaMapType m_map;
	unsigned char m_flag;
};

Rva0060146B::Rva0060146B() : m_map()
{
	m_flag = 1;
}
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate>,_STL::allocator<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::_Rb_tree_base(_STL::allocator<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > const &); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > * allocator<_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::allocate(unsigned int,void const *) const; }
// bfme link decl-only end
