// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
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
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
class ArmorTemplateSet {
public:
    // Retail's 0x002CA82C copies the three words one by one: a user-declared
    // (memberwise) copy, as STLport's pair has; inferred from those bytes.
    ArmorTemplateSet(const ArmorTemplateSet &o) : m_types(o.m_types), m_template(o.m_template), m_fx(o.m_fx) {}
    unsigned int m_types; const void *m_template; const void *m_fx;
};
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@2@@Z
typedef _STL::_Rb_tree<AsciiString, _STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::_Select1st<_STL::pair<const AsciiString, NoCaseTreeValue4> >, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > VAsciiStringUNoCaseTreeValue4MapTree;
void __cdecl Rva0022112DConstruct(void *dest, const void *source);
template <>
VAsciiStringUNoCaseTreeValue4MapTree::_Link_type VAsciiStringUNoCaseTreeValue4MapTree::_M_create_node(const VAsciiStringUNoCaseTreeValue4MapTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<VAsciiStringUNoCaseTreeValue4MapTree::value_type>), 0);
	Rva0022112DConstruct(&node->_M_value_field, &value);
	return node;
}
template VAsciiStringUNoCaseTreeValue4MapTree::_Link_type VAsciiStringUNoCaseTreeValue4MapTree::_M_create_node(const VAsciiStringUNoCaseTreeValue4MapTree::value_type &);

// ?_M_create_node@?$_Rb_tree@VArmorTemplateSet@@V1@U?$_Identity@VArmorTemplateSet@@@_STL@@U?$less@VArmorTemplateSet@@@3@V?$allocator@VArmorTemplateSet@@@3@@_STL@@IAEPAU?$_Rb_tree_node@VArmorTemplateSet@@@2@ABVArmorTemplateSet@@@Z
typedef _STL::_Rb_tree<ArmorTemplateSet, ArmorTemplateSet, _STL::_Identity<ArmorTemplateSet>, _STL::less<ArmorTemplateSet>, _STL::allocator<ArmorTemplateSet> > VArmorTemplateSetSetTree;
namespace _STL { template <> void _Construct<ArmorTemplateSet, ArmorTemplateSet>(ArmorTemplateSet *, const ArmorTemplateSet &); }
template <>
VArmorTemplateSetSetTree::_Link_type VArmorTemplateSetSetTree::_M_create_node(const VArmorTemplateSetSetTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<VArmorTemplateSetSetTree::value_type>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}
template VArmorTemplateSetSetTree::_Link_type VArmorTemplateSetSetTree::_M_create_node(const VArmorTemplateSetSetTree::value_type &);

