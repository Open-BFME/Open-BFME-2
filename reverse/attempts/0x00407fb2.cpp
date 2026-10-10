// ??A?$map@I_NU?$less@I@_STL@@V?$allocator@U?$pair@$$CBI_N@_STL@@@2@@_STL@@QAEAA_NABI@Z
// partial score=0.964163 date=2026-10-10
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// BANK only: native407FB2..407FF7 RET4. Existing bool map signature is
// retained. Native unsigned key loads at node+10 and byte result+14.
// Pure key lower-bound borrows the existing unsigned/void* tree ABI view
// (never reads its value); lower37 at4FF3B6 is exact, while the canonical
// bool lower38 at61F660 is a different body. Do not dual-pin that name.
// Emitted69B differs only in scheduling the byte-zero store before iterator
// copy/hidden-result push; retail does it after. Generated insert29/294/136/134
// require their own full relocation proof before any alias/admission.
// Native create_node34 at2D464E is already the proper UIntBool specialization.
#include <map>
typedef _STL::pair<const unsigned,void*> NativeLowerPair;
typedef _STL::_Rb_tree<unsigned,NativeLowerPair,_STL::_Select1st<NativeLowerPair>,_STL::less<unsigned>,_STL::allocator<NativeLowerPair> > NativeUnsignedLower;
namespace _STL{template<>NativeUnsignedLower::_Link_type NativeUnsignedLower::_M_lower_bound(const unsigned&)const;}
typedef _STL::pair<const unsigned,bool> NativeBoolPair;
typedef _STL::_Rb_tree<unsigned,NativeBoolPair,_STL::_Select1st<NativeBoolPair>,_STL::less<unsigned>,_STL::allocator<NativeBoolPair> > NativeBoolTree;
namespace _STL{template<>NativeBoolTree::_Link_type NativeBoolTree::_M_create_node(const NativeBoolPair&);}
namespace _STL{
template<>__forceinline map<unsigned,bool>::iterator map<unsigned,bool>::lower_bound(const unsigned&key){
 return iterator((_Rb_tree_node<value_type>*)((const NativeUnsignedLower*)this)->lower_bound(key)._M_node);
}
}
template bool&_STL::map<unsigned,bool>::operator[](const unsigned&);
