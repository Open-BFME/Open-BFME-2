// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// Batch _M_create_node family recovery (generated): one explicit
// specialization per sibling, each proven by its own retail call
// displacement to a rowed _Construct (true name, or a rowed dup
// twin whose object-symbol proves the value type) plus the allocate
// size fixing the value size. Custom No-exceptions MALLOC shape from
// stlport_rb_tree_hint_asciistring_set (no allocation-cleanup catch
// path); each _Construct is declared only so its call resolves
// through its own row.
#include <map>
#include <set>
#include <list>
#include <vector>

struct NoCaseTreeValue4 { public: unsigned char m_data[4]; };
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct TreeHintPayload003012F0 { public: unsigned char m_data[12]; };

// ?_M_create_node@?$list@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@IAEPAU?$_List_node@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@2@@Z
void __cdecl Rva0020596AConstruct(void *dest, const void *source);
template <>
__declspec(noinline) _STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> > *_STL::list<_STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > >::_M_create_node(_STL::pair<const AsciiString, NoCaseTreeValue4> const &__x)
{
	_STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> > *__p =
		(_STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> > *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> >), 0);
	Rva0020596AConstruct(&__p->_M_data, &__x);
	return __p;
}
template _STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> > *_STL::list<_STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > >::_M_create_node(_STL::pair<const AsciiString, NoCaseTreeValue4> const &);
