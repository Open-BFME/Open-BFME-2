// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
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
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct NoCaseTreeValue4 { public: unsigned char m_data[4]; };
class AsciiString { public: void *m_data; };
struct TreeHintPayload003012F0 { public: unsigned char m_data[12]; };

// ?_M_create_node@?$list@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@IAEPAU?$_List_node@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@2@@Z
void __cdecl dup_0020596A(void);
typedef void (__cdecl *VAsciiStringUNoCaseTreeValue4ListConstructFn)(_STL::pair<const AsciiString, NoCaseTreeValue4> *, _STL::pair<const AsciiString, NoCaseTreeValue4> const &);
template <>
_STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> > *_STL::list<_STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > >::_M_create_node(_STL::pair<const AsciiString, NoCaseTreeValue4> const &__x)
{
	_STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> > *__p =
		(_STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> > *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> >), 0);
	((VAsciiStringUNoCaseTreeValue4ListConstructFn)&dup_0020596A)(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<_STL::pair<const AsciiString, NoCaseTreeValue4> > *_STL::list<_STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > >::_M_create_node(_STL::pair<const AsciiString, NoCaseTreeValue4> const &);

// ?_M_create_node@?$list@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@@2@@_STL@@IAEPAU?$_List_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@2@@Z
void __cdecl dup_002057A8(void);
typedef void (__cdecl *VAsciiStringUTreeHintPayload003012F0ListConstructFn)(_STL::pair<const AsciiString, TreeHintPayload003012F0> *, _STL::pair<const AsciiString, TreeHintPayload003012F0> const &);
template <>
_STL::_List_node<_STL::pair<const AsciiString, TreeHintPayload003012F0> > *_STL::list<_STL::pair<const AsciiString, TreeHintPayload003012F0>, _STL::allocator<_STL::pair<const AsciiString, TreeHintPayload003012F0> > >::_M_create_node(_STL::pair<const AsciiString, TreeHintPayload003012F0> const &__x)
{
	_STL::_List_node<_STL::pair<const AsciiString, TreeHintPayload003012F0> > *__p =
		(_STL::_List_node<_STL::pair<const AsciiString, TreeHintPayload003012F0> > *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<_STL::pair<const AsciiString, TreeHintPayload003012F0> >), 0);
	((VAsciiStringUTreeHintPayload003012F0ListConstructFn)&dup_002057A8)(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<_STL::pair<const AsciiString, TreeHintPayload003012F0> > *_STL::list<_STL::pair<const AsciiString, TreeHintPayload003012F0>, _STL::allocator<_STL::pair<const AsciiString, TreeHintPayload003012F0> > >::_M_create_node(_STL::pair<const AsciiString, TreeHintPayload003012F0> const &);
