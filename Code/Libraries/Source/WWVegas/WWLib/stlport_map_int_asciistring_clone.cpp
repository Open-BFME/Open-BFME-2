// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_clone_node@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHVAsciiString@@@_STL@@@2@PAU32@@Z 0x005041D8 30B evidence: Rb_tree map int to AsciiString clone 30B via rowed Record create_node 0x005041B6 plus color copy plus null links; callers 0x0050428C 0x005042BC in rowed _M_copy 0x0050427F
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

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
// Suppress this TU's non-retail copy of ??$_Construct@VRva00064640Record@@V1@@_STL@@YAXPAVRva00064640Record@@ABV1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva00064640Record;
namespace _STL { template <> void _Construct<Rva00064640Record,Rva00064640Record>(Rva00064640Record *,Rva00064640Record const &); }
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@VRva00064640Record@@V1@U?$_Identity@VRva00064640Record@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva00064640Record;
namespace _STL { template <> _Rb_tree_node<Rva00064640Record> * _Rb_tree<Rva00064640Record,Rva00064640Record,_Identity<Rva00064640Record>,less<Rva00064640Record>,allocator<Rva00064640Record> >::_M_create_node(Rva00064640Record const &); }
#include "../../../../GameEngine/Include/Common/Rva00064640Record.h"

typedef _STL::_Rb_tree<int, _STL::pair<const int, AsciiString>, _STL::_Select1st<_STL::pair<const int, AsciiString> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, AsciiString> > > HAsciiStringMapTree;
typedef _STL::_Rb_tree<Rva00064640Record, Rva00064640Record, _STL::_Identity<Rva00064640Record>, _STL::less<Rva00064640Record>, _STL::allocator<Rva00064640Record> > VRva00064640RecordSetTree;

// Access shim: _M_create_node is protected, so the cross-tree call below
// goes through a derived helper. It inlines, leaving a direct call that
// resolves through the rowed 0x005041B6 body.
struct RecordCreateCaller : public VRva00064640RecordSetTree
{
	__forceinline _Link_type createFrom(const value_type &value)
	{
		return _M_create_node(value);
	}
};

// ?_M_clone_node@?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHVAsciiString@@@_STL@@@2@PAU32@@Z
template <>
HAsciiStringMapTree::_Link_type HAsciiStringMapTree::_M_clone_node(HAsciiStringMapTree::_Link_type __x)
{
	_Link_type __tmp = (_Link_type)((RecordCreateCaller *)this)->createFrom((const VRva00064640RecordSetTree::value_type &)__x->_M_value_field);
	__tmp->_M_color = __x->_M_color;
	__tmp->_M_left = 0;
	__tmp->_M_right = 0;
	return __tmp;
}
template HAsciiStringMapTree::_Link_type HAsciiStringMapTree::_M_clone_node(HAsciiStringMapTree::_Link_type);
