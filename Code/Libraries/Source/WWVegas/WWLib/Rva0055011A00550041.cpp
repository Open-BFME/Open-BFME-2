// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva00550041@Rva0055011A@@UAEXXZ @0x00550041 66B.
// Rva0055011A slot-10 method: lock m_14, clear map at +0x74.
// Evidence: vtable slot 10 of 0x0086AB90; callees rowed 0x00613A70 0x00389A4C 0x00613AC0.
#include <map>
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char,_STL::allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >::~basic_string(); }
namespace _STL { template <> pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int>::~pair(); }
namespace _STL { template <> void _String_base<char,_STL::allocator<char> >::_M_deallocate_block(); }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int> > *,_STL::_Rb_tree_node<_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int> > *,unsigned int) const; }
namespace _STL { template <> pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int>::~pair(); }
namespace _STL { template <> void _Rb_tree<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >,_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int>,_STL::_Select1st<_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int> >,_STL::less<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > >,_STL::allocator<_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int> > >::_M_erase(_STL::_Rb_tree_node<_STL::pair<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > const,int> > *); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

#include "mutex.h"

typedef _STL::map<_STL::basic_string<char>, int, _STL::less<_STL::basic_string<char> > > WordMapH;

class Rva0055011A
{
public:
	virtual ~Rva0055011A();
	virtual void rva00550041();
private:
	MutexClass m_04;
	MutexClass m_0C;
	MutexClass m_14;
	char m_pad[0x74 - 0x1C];
	WordMapH m_74;
	char m_tail[0xB4 - 0x74 - 12];
};

void Rva0055011A::rva00550041()
{
	MutexClass::LockClass lock(m_14);
	m_74.clear();
}
