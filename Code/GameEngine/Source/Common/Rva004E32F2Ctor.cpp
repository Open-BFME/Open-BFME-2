// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport46
// ??0Rva004E32F2@@QAE@ABV0@@Z, retail 0x0052D477, 43 bytes.
// Copy ctor of Rva004E32F2: vptr store plus int at +4 plus byte at +8 plus tree copy at +0xC.
// Evidence: chain lane calls just-landed Rb_tree copy 0x0052D25D; vtable 0x00861F68 stored at [this] matches dtor 0x004E32F2 class; caller 0x0052D4BE.
// Tree member uses 24B private AsciiString so its copy call mangles to the landed Rb_tree<int AsciiString> row; size not in mangling.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_node<pair<int const, AsciiString> > * _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::_M_clone_node(_Rb_tree_node<pair<int const, AsciiString> > *); }
namespace _STL { template <> _Rb_tree_node<pair<int const, AsciiString> > * _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::_M_create_node(pair<int const, AsciiString> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBHVAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBHVAsciiStrin:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> _Rb_tree_base<pair<const int, AsciiString>, allocator<pair<const int, AsciiString> > >::_Rb_tree_base(const allocator<pair<const int, AsciiString> > &); }

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
typedef _STL::_Rb_tree<int, _STL::pair<const int, AsciiString>, _STL::_Select1st<_STL::pair<const int, AsciiString> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, AsciiString> > > HAsciiStringMapTree;
class Rva004E32F2
{
public:
	Rva004E32F2(const Rva004E32F2 &that);
	virtual ~Rva004E32F2();
private:
	int m_unk04;
	unsigned char m_unk08;
	HAsciiStringMapTree m_tree0C;
};
Rva004E32F2::Rva004E32F2(const Rva004E32F2 &that) : m_unk04(that.m_unk04), m_unk08(that.m_unk08), m_tree0C(that.m_tree0C)
{
}
