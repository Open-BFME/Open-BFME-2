// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector/deque members for placeholder POD elements
// in the _STLP_NO_EXCEPTIONS configuration (no try/catch around the
// reallocation paths), each placed by a single masked whole-.text hit whose
// own bytes carry the element size. BfmePodN stands for the real N-byte
// element; a non-trivial copy construct is pinned by call-site address, not
// compiled here. No retail caller is claimed.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <deque>
// These elements copy through real copy constructors; their _Construct
// bodies are rowed under the real element names, so call those.
struct BfmePod32;
class Gen_005e9a20;
struct BfmePod76;
class WeaponTemplateSetHead;
namespace _STL {
template <> void _Construct<Gen_005e9a20, Gen_005e9a20>(Gen_005e9a20 *, const Gen_005e9a20 &) throw();
template <> void _Construct<WeaponTemplateSetHead, WeaponTemplateSetHead>(WeaponTemplateSetHead *, const WeaponTemplateSetHead &) throw();
// 0x00421D16
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod32, BfmePod32>(BfmePod32 *p, const BfmePod32 &v) throw()
{ _Construct((Gen_005e9a20 *)p, (const Gen_005e9a20 &)v); }
// 0x000CF418
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod76, BfmePod76>(BfmePod76 *p, const BfmePod76 &v) throw()
{ _Construct((WeaponTemplateSetHead *)p, (const WeaponTemplateSetHead &)v); }
}
// Suppress this TU's non-retail copy of ?erase@?$vector@UBfmePod68@@V?$allocator@UBfmePod68@@@_STL@@@_STL@@QAEPAUBfmePod68@@PAU3@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod68;
namespace _STL { template <> BfmePod68 * vector<BfmePod68,allocator<BfmePod68> >::erase(BfmePod68 *); }
// Suppress this TU's non-retail copy of ??0?$vector@UBfmePod40@@V?$allocator@UBfmePod40@@@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod40;
namespace _STL { template <> vector<BfmePod40,allocator<BfmePod40> >::vector(vector<BfmePod40,allocator<BfmePod40> > const &); }
// Suppress this TU's non-retail copy of ??$_Construct@UBfmePod52@@U1@@_STL@@YAXPAUBfmePod52@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> void _Construct<BfmePod52,BfmePod52>(BfmePod52 *,BfmePod52 const &); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@U?$_Deque_iterator@UBfmePod16@@U?$_Nonconst_traits@UBfmePod16@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod16;
// The non-trivial range helper is supplied by StlportDequePod16Dtor.cpp.
namespace _STL { template <> void __destroy<_Deque_iterator<BfmePod16, _Nonconst_traits<BfmePod16> >, BfmePod16>(_Deque_iterator<BfmePod16, _Nonconst_traits<BfmePod16> >, _Deque_iterator<BfmePod16, _Nonconst_traits<BfmePod16> >, BfmePod16 *); }
namespace _STL { template <> void __destroy_aux<_Deque_iterator<BfmePod16,_Nonconst_traits<BfmePod16> > >(_Deque_iterator<BfmePod16,_Nonconst_traits<BfmePod16> >,_Deque_iterator<BfmePod16,_Nonconst_traits<BfmePod16> >,__false_type const &); }
// Suppress this TU's non-retail copy of ??0?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> vector<BfmePod44, allocator<BfmePod44> >::vector(const vector<BfmePod44, allocator<BfmePod44> > &); }
// Suppress this TU's non-retail copy of ?resize@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::resize(size_t); }
// Suppress this TU's non-retail copy of ?erase@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEPAUBfmePod44@@PAU3@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> BfmePod44 *vector<BfmePod44, allocator<BfmePod44> >::erase(BfmePod44 *, BfmePod44 *); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod52@@V?$allocator@UBfmePod52@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> void vector<BfmePod52, allocator<BfmePod52> >::_M_fill_insert(BfmePod52 *, size_t, const BfmePod52 &); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::_M_fill_insert(BfmePod44 *, size_t, const BfmePod44 &); }
struct BfmePod8 { int a[2]; };
struct BfmePod16 { int a[4]; };
struct BfmePod20 { int a[5]; };
struct BfmePod28 { int a[7]; };
// bfme link decl-only BfmePod28
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *, BfmePod28 *); }
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *); }
struct BfmePod32 { int a[8]; };
// bfme link decl-only BfmePod32
namespace _STL { template <> vector<BfmePod32, allocator<BfmePod32> >::~vector(); }
struct BfmePod40 { int a[10]; };
// bfme link decl-only BfmePod40
namespace _STL { template <> vector<BfmePod40, allocator<BfmePod40> >::~vector(); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *, BfmePod40 *); }
struct BfmePod44 { int a[11]; };
struct BfmePod52 { int a[13]; };
struct BfmePod68 { int a[17]; };
struct BfmePod76 { int a[19]; };
struct BfmePod492 { int a[123]; };
struct BfmePod840 { int a[210]; };
// 696 = 0x2B8 is BuddyRequest, as in stlport_pod_large_bodies.cpp.
class BuddyRequest
{
	char m_bfmeBody[0x2B8];
};
namespace _STL { template <> BfmePod52 *vector<BfmePod52, allocator<BfmePod52> >::erase(BfmePod52 *, BfmePod52 *); }

// Instantiate the matched members without unrelated container operations.
template void _STL::deque<BfmePod28,_STL::allocator<BfmePod28> >::_M_reallocate_map(unsigned int,bool);

template void _STL::vector<BfmePod44,_STL::allocator<BfmePod44> >::_M_insert_overflow(BfmePod44 *,BfmePod44 const &,_STL::__false_type const &,unsigned int,bool);

template void _STL::vector<BfmePod52,_STL::allocator<BfmePod52> >::_M_insert_overflow(BfmePod52 *,BfmePod52 const &,_STL::__false_type const &,unsigned int,bool);

template void _STL::vector<BfmePod68,_STL::allocator<BfmePod68> >::_M_insert_overflow(BfmePod68 *,BfmePod68 const &,_STL::__false_type const &,unsigned int,bool);

template void _STL::vector<BfmePod76,_STL::allocator<BfmePod76> >::_M_insert_overflow(BfmePod76 *,BfmePod76 const &,_STL::__false_type const &,unsigned int,bool);

template void _STL::vector<BfmePod32,_STL::allocator<BfmePod32> >::_M_insert_overflow(BfmePod32 *,BfmePod32 const &,_STL::__false_type const &,unsigned int,bool);

template void _STL::_Deque_base<BfmePod16,_STL::allocator<BfmePod16> >::_M_initialize_map(unsigned int);

template void _STL::_Deque_base<BfmePod8,_STL::allocator<BfmePod8> >::_M_initialize_map(unsigned int);

template void _STL::_Deque_base<BfmePod28,_STL::allocator<BfmePod28> >::_M_initialize_map(unsigned int);



template void _STL::_Deque_base<BfmePod28,_STL::allocator<BfmePod28> >::_M_create_nodes(BfmePod28 * *,BfmePod28 * *);

template void _STL::_Deque_base<BfmePod492,_STL::allocator<BfmePod492> >::_M_initialize_map(unsigned int);

template void _STL::_Deque_base<BfmePod840,_STL::allocator<BfmePod840> >::_M_initialize_map(unsigned int);

template void _STL::_Deque_base<BuddyRequest,_STL::allocator<BuddyRequest> >::_M_initialize_map(unsigned int);

template void _STL::_Deque_base<BfmePod492,_STL::allocator<BfmePod492> >::_M_create_nodes(BfmePod492 * *,BfmePod492 * *);

template void _STL::_Deque_base<BfmePod840,_STL::allocator<BfmePod840> >::_M_create_nodes(BfmePod840 * *,BfmePod840 * *);

template void _STL::_Deque_base<BuddyRequest,_STL::allocator<BuddyRequest> >::_M_create_nodes(BuddyRequest * *,BuddyRequest * *);


template _STL::deque<BfmePod28,_STL::allocator<BfmePod28> >::deque(_STL::allocator<BfmePod28> const &);

template _STL::deque<BfmePod16,_STL::allocator<BfmePod16> >::deque(_STL::allocator<BfmePod16> const &);

template _STL::deque<BfmePod8,_STL::allocator<BfmePod8> >::deque(_STL::allocator<BfmePod8> const &);

template _STL::deque<BfmePod20,_STL::allocator<BfmePod20> >::deque(_STL::allocator<BfmePod20> const &);

template _STL::deque<BuddyRequest,_STL::allocator<BuddyRequest> >::deque(_STL::allocator<BuddyRequest> const &);

template void _STL::_Destroy<_STL::_Deque_iterator<BfmePod16,_STL::_Nonconst_traits<BfmePod16> > >(_STL::_Deque_iterator<BfmePod16,_STL::_Nonconst_traits<BfmePod16> >,_STL::_Deque_iterator<BfmePod16,_STL::_Nonconst_traits<BfmePod16> >);

template BfmePod32 * _STL::vector<BfmePod32,_STL::allocator<BfmePod32> >::_M_allocate_and_copy<BfmePod32 *>(unsigned int,BfmePod32 *,BfmePod32 *);

template _STL::_Bit_iter<_STL::_Bit_reference,_STL::_Bit_reference *> & _STL::_Bit_iter<_STL::_Bit_reference,_STL::_Bit_reference *>::operator++(void);

template void _STL::vector<BfmePod40,_STL::allocator<BfmePod40> >::clear(void);


// Keep the native push_back with its compiler-visible no-EH overflow body.
template void _STL::vector<BfmePod52>::push_back(const BfmePod52 &);
