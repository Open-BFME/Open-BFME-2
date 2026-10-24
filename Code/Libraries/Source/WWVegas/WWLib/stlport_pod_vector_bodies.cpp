// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector members instantiated with code-generation element
// views. BfmePodN names only an element size (the BfmeE16/Rva..Element
// convention); it is not an application-type claim. Some direct callers and
// non-trivial element copy/destruction paths are now target-backed, but a
// concrete identity is recorded only where that independent evidence supports
// it. char likewise stands for any 1-byte element.
//
// BfmePodN (BfmeShortPodN: 2-byte aligned) is a placeholder for the real
// N-byte element type at each site.
// Where retail's copy construct for that element is non-trivial (it calls a
// copy constructor), _Construct<BfmePodN> is pinned in symbols.csv at the
// address the byte-true call site proves; that body is not compiled from here.
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
#include <algorithm>
// These elements copy through real copy constructors; their _Construct
// bodies are rowed under the real element names, so call those.
struct BfmePod128;
class BuildListInfo;
struct BfmePod32;
class Gen_005e9a20;
struct BfmePod40;
class Rva0052BD59;
struct BfmePod76;
class WeaponTemplateSetHead;
namespace _STL {
template <> void _Construct<BuildListInfo, BuildListInfo>(BuildListInfo *, const BuildListInfo &) throw();
template <> void _Construct<Gen_005e9a20, Gen_005e9a20>(Gen_005e9a20 *, const Gen_005e9a20 &) throw();
template <> void _Construct<Rva0052BD59, Rva0052BD59>(Rva0052BD59 *, const Rva0052BD59 &) throw();
template <> void _Construct<WeaponTemplateSetHead, WeaponTemplateSetHead>(WeaponTemplateSetHead *, const WeaponTemplateSetHead &) throw();
// 0x0032A2AF
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod128, BfmePod128>(BfmePod128 *p, const BfmePod128 &v) throw()
{ _Construct((BuildListInfo *)p, (const BuildListInfo &)v); }
// 0x00421D16
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod32, BfmePod32>(BfmePod32 *p, const BfmePod32 &v) throw()
{ _Construct((Gen_005e9a20 *)p, (const Gen_005e9a20 &)v); }
// 0x0052C320
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod40, BfmePod40>(BfmePod40 *p, const BfmePod40 &v) throw()
{ _Construct((Rva0052BD59 *)p, (const Rva0052BD59 &)v); }
// 0x000CF418
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod76, BfmePod76>(BfmePod76 *p, const BfmePod76 &v) throw()
{ _Construct((WeaponTemplateSetHead *)p, (const WeaponTemplateSetHead &)v); }
}
// Native 0x00025AD0 is supplied by stlport_vector_voidptr.cpp.
// Keep this profile from emitting a competing allocator-proxy swap.
namespace _STL {
template <> void swap(_STLP_alloc_proxy<char *, char, allocator<char> > &,
                     _STLP_alloc_proxy<char *, char, allocator<char> > &);
}
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
// bfme link decl-only begin
namespace _STL { template <> unsigned char * allocator<unsigned char>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?fill@_STL@@YAXPAD0ABD@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void fill(char *,char *,char const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@IAEXPAUBfm:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod28;
namespace _STL { template <> void vector<BfmePod28,allocator<BfmePod28> >::_M_insert_overflow(BfmePod28 *,BfmePod28 const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAUBfmePod248@@@_STL@@YAXPAUBfmePod248@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod248;
namespace _STL { template <> void _Destroy<BfmePod248 *>(BfmePod248 *,BfmePod248 *); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmePod248@@V?$allocator@UBfmePod248@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<BfmePod248,allocator<BfmePod248> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_M_allocate_and_copy@PBUBfmePod128@@@?$vector@UBfmePod128@@V?$allocator@UBfmePod128@@@_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod128;
namespace _STL { template <> template <> BfmePod128 * vector<BfmePod128,allocator<BfmePod128> >::_M_allocate_and_copy<BfmePod128 const *>(unsigned int,BfmePod128 const *,BfmePod128 const *); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmePod252@@V?$allocator@UBfmePod252@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod252;
namespace _STL { template <> void vector<BfmePod252,allocator<BfmePod252> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??0?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod28;
namespace _STL { template <> vector<BfmePod28,allocator<BfmePod28> >::vector(vector<BfmePod28,allocator<BfmePod28> > const &); }
// Suppress this TU's non-retail copy of ??0?$vector@UBfmePod32@@V?$allocator@UBfmePod32@@@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod32;
namespace _STL { template <> vector<BfmePod32,allocator<BfmePod32> >::vector(vector<BfmePod32,allocator<BfmePod32> > const &); }
// Suppress this TU's non-retail copy of ?resize@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::resize(size_t); }
// Suppress this TU's non-retail copy of ?erase@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEPAUBfmePod44@@PAU3@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> BfmePod44 *vector<BfmePod44, allocator<BfmePod44> >::erase(BfmePod44 *, BfmePod44 *); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod20@@V?$allocator@UBfmePod20@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod20;
namespace _STL { template <> void vector<BfmePod20, allocator<BfmePod20> >::_M_fill_insert(BfmePod20 *, size_t, const BfmePod20 &); }
// Native overflow is owned by stlport_pod_noexc_bodies.cpp (RVA 0x001DE402).
struct BfmePod52;
namespace _STL { template <> void vector<BfmePod52, allocator<BfmePod52> >::_M_insert_overflow(BfmePod52 *, BfmePod52 const &, __false_type const &, unsigned int, bool); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod52@@V?$allocator@UBfmePod52@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> void vector<BfmePod52, allocator<BfmePod52> >::_M_fill_insert(BfmePod52 *, size_t, const BfmePod52 &); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::_M_fill_insert(BfmePod44 *, size_t, const BfmePod44 &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@IAEXPAUBfm:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::_M_insert_overflow(BfmePod44 *, const BfmePod44 &, const __false_type &, size_t, bool); }
struct BfmePod20 { int a[5]; };
struct BfmePod24 { int a[6]; };
// Keep the no-EH 24-byte helpers in their existing retail owners.
namespace _STL {
template <> void vector<BfmePod24>::push_back(const BfmePod24 &);
template <> void vector<BfmePod24>::_M_insert_overflow(BfmePod24 *, const BfmePod24 &, const __false_type &, unsigned int, bool);
template <> template <> BfmePod24 *vector<BfmePod24>::_M_allocate_and_copy<const BfmePod24 *>(unsigned int, const BfmePod24 *, const BfmePod24 *);
}
// The dedicated no-EH provider owns this type's allocation/copy helper.
// Assignment is unrowed here; leave it uninstantiated in this EH profile.
namespace _STL { template <> vector<BfmePod24, allocator<BfmePod24> > &
vector<BfmePod24, allocator<BfmePod24> >::operator=(
    const vector<BfmePod24, allocator<BfmePod24> > &); }
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] < y.a[0]; }
struct BfmePod28 { int a[7]; };
// bfme link decl-only BfmePod28
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *, BfmePod28 *); }
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *); }
inline bool operator==(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] < y.a[0]; }
struct BfmePod32 { int a[8]; };
// The overflow provider uses STLport's growth path without exception rollback
// (stlport_pod_noexc_bodies.cpp); spell that body so this copy is retail's.
namespace _STL {
template <> inline void vector<BfmePod32, allocator<BfmePod32> >::_M_insert_overflow(
    BfmePod32 *__position, const BfmePod32 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}
// bfme link decl-only BfmePod32
namespace _STL { template <> vector<BfmePod32, allocator<BfmePod32> >::~vector(); }
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod32> has its own pin; declare that specialization so
// this unit calls it rather than emitting a second, non-retail copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod32, BfmePod32>(BfmePod32 *__p, const BfmePod32 &__val); }
struct BfmePod36 { int a[9]; };
inline bool operator==(const BfmePod36 &x, const BfmePod36 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod36 &x, const BfmePod36 &y) { return x.a[0] < y.a[0]; }
struct BfmePod40 { int a[10]; };
// The overflow provider uses STLport's growth path without exception rollback.
namespace _STL {
template <> void vector<BfmePod40, allocator<BfmePod40> >::_M_clear();
template <> inline void vector<BfmePod40, allocator<BfmePod40> >::_M_insert_overflow(
    BfmePod40 *__position, const BfmePod40 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}

// bfme link decl-only BfmePod40
namespace _STL { template <> vector<BfmePod40, allocator<BfmePod40> >::~vector(); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *, BfmePod40 *); }
inline bool operator==(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod40> is pinned elsewhere; declare that
// specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod40, BfmePod40>(BfmePod40 *__p, const BfmePod40 &__val); }
struct BfmePod44 { int a[11]; };
// Retail's vector<BfmePod44> copy constructor (0x00414490) copies through the
// rowed 44-byte worker at 0x00414359 and its placement copy at 0x0041432C,
// not this view's own copy (0x0007EB6E).
struct Rva00414BA4Element { int a[11]; };
namespace _STL {
template <> __declspec(nothrow) void _Construct<Rva00414BA4Element, Rva00414BA4Element>(Rva00414BA4Element *__p, const Rva00414BA4Element &__val);
template <> void _Destroy<Rva00414BA4Element *>(Rva00414BA4Element *, Rva00414BA4Element *);
template <> inline vector<BfmePod44, allocator<BfmePod44> >::vector(const vector<BfmePod44, allocator<BfmePod44> > &__x)
    : _Vector_base<BfmePod44, allocator<BfmePod44> >(__x.size(), __x.get_allocator())
{
    this->_M_finish = (BfmePod44 *)__uninitialized_copy((Rva00414BA4Element *)__x._M_start,
        (Rva00414BA4Element *)__x._M_finish, (Rva00414BA4Element *)this->_M_start, __false_type());
}
}
// The dedicated no-EH provider owns this type's allocation/copy helper.
// Assignment is unrowed here; leave it uninstantiated in this EH profile.
namespace _STL { template <> vector<BfmePod44, allocator<BfmePod44> > &
vector<BfmePod44, allocator<BfmePod44> >::operator=(
    const vector<BfmePod44, allocator<BfmePod44> > &); }
inline bool operator==(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] < y.a[0]; }
struct BfmePod48 { int a[12]; };
inline bool operator==(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] < y.a[0]; }
// Retail calls the rowed _Construct<Rva003F610FElement>; forward this view to it.
struct Rva003F610FElement;
namespace _STL {
template <> void _Construct<Rva003F610FElement, Rva003F610FElement>(Rva003F610FElement *, const Rva003F610FElement &) throw();
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod48, BfmePod48>(BfmePod48 *p, const BfmePod48 &v) throw()
{ _Construct((Rva003F610FElement *)p, (const Rva003F610FElement &)v); }
}
// _M_clear is protected; this view only re-exposes it so a placeholder
// vector's growth can call the real element's rowed clear.
template <class _Tp> struct BfmeOverflowAccess : _STL::vector<_Tp, _STL::allocator<_Tp> > {
    using _STL::vector<_Tp, _STL::allocator<_Tp> >::_M_clear;
};
// Retail grows this view with the no-EH body below; it frees through the
// rowed vector<Rva003F610FElement>::_M_clear.
namespace _STL {
template <> void vector<Rva003F610FElement, allocator<Rva003F610FElement> >::_M_clear();
template <> inline void vector<BfmePod48, allocator<BfmePod48> >::_M_insert_overflow(
    BfmePod48 *__position, const BfmePod48 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy((const BfmePod48 *)this->_M_start, (const BfmePod48 *)__position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy((const BfmePod48 *)__position, (const BfmePod48 *)this->_M_finish, __new_finish, __false_type());
    ((BfmeOverflowAccess<Rva003F610FElement> *)this)->_M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}
struct BfmePod52 { int a[13]; };
inline bool operator==(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod52> is rowed in stlport_construct_pod52_rva.cpp
// (0x001DD2DC); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod52, BfmePod52>(BfmePod52 *__p, const BfmePod52 &__val); }
// Retail's vector<BfmePod52> copy constructor (0x004F9E76) copies through the
// rowed 52-byte worker at 0x002BADB2 and its placement copy at 0x002B91ED.
struct Rva002BBC7ARecord { int a[13]; };
namespace _STL {
template <> __declspec(nothrow) void _Construct<Rva002BBC7ARecord, Rva002BBC7ARecord>(Rva002BBC7ARecord *__p, const Rva002BBC7ARecord &__val);
template <> void _Destroy<Rva002BBC7ARecord *>(Rva002BBC7ARecord *, Rva002BBC7ARecord *);
template <> inline vector<BfmePod52, allocator<BfmePod52> >::vector(const vector<BfmePod52, allocator<BfmePod52> > &__x)
    : _Vector_base<BfmePod52, allocator<BfmePod52> >(__x.size(), __x.get_allocator())
{
    this->_M_finish = (BfmePod52 *)__uninitialized_copy((Rva002BBC7ARecord *)__x._M_start,
        (Rva002BBC7ARecord *)__x._M_finish, (Rva002BBC7ARecord *)this->_M_start, __false_type());
}
}
struct BfmePod60 { int a[15]; };
inline bool operator==(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod60> is pinned elsewhere; declare that
// specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod60, BfmePod60>(BfmePod60 *__p, const BfmePod60 &__val); }
struct BfmePod68 { int a[17]; };
// The overflow provider uses STLport's growth path without exception rollback
// (stlport_pod_noexc_bodies.cpp); spell that body so this copy is retail's.
namespace _STL {
template <> inline void vector<BfmePod68, allocator<BfmePod68> >::_M_insert_overflow(
    BfmePod68 *__position, const BfmePod68 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}
// bfme link decl-only BfmePod68
namespace _STL { template <> BfmePod68 * vector<BfmePod68, allocator<BfmePod68> >::erase(BfmePod68 *, BfmePod68 *); }
namespace _STL { template <> BfmePod68 * vector<BfmePod68, allocator<BfmePod68> >::erase(BfmePod68 *); }
inline bool operator==(const BfmePod68 &x, const BfmePod68 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod68 &x, const BfmePod68 &y) { return x.a[0] < y.a[0]; }
struct BfmePod76 { int a[19]; };
// The overflow provider uses STLport's growth path without exception rollback
// (stlport_pod_noexc_bodies.cpp); spell that body so this copy is retail's.
namespace _STL {
template <> inline void vector<BfmePod76, allocator<BfmePod76> >::_M_insert_overflow(
    BfmePod76 *__position, const BfmePod76 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}
inline bool operator==(const BfmePod76 &x, const BfmePod76 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod76 &x, const BfmePod76 &y) { return x.a[0] < y.a[0]; }
struct BfmePod80 { int a[20]; };
inline bool operator==(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod80> is rowed in stlport_construct_pod80_rva.cpp
// (0x0051F920); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod80, BfmePod80>(BfmePod80 *__p, const BfmePod80 &__val); }
struct BfmePod88 { int a[22]; };
// bfme link decl-only BfmePod88
namespace _STL { template <> vector<BfmePod88, allocator<BfmePod88> >::~vector(); }
// _Construct<BfmePod88> is rowed at 0x004E3706 in stlport_construct_pod88_rva.cpp
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod88, BfmePod88>(BfmePod88 *__p, const BfmePod88 &__val); }
inline bool operator==(const BfmePod88 &x, const BfmePod88 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod88 &x, const BfmePod88 &y) { return x.a[0] < y.a[0]; }
struct BfmePod92 { int a[23]; };
inline bool operator==(const BfmePod92 &x, const BfmePod92 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod92 &x, const BfmePod92 &y) { return x.a[0] < y.a[0]; }
// Retail calls the rowed _Construct<BfmeContainerRecord00048139>; forward this view to it.
struct BfmeContainerRecord00048139;
namespace _STL {
template <> void _Construct<BfmeContainerRecord00048139, BfmeContainerRecord00048139>(BfmeContainerRecord00048139 *, const BfmeContainerRecord00048139 &) throw();
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod92, BfmePod92>(BfmePod92 *p, const BfmePod92 &v) throw()
{ _Construct((BfmeContainerRecord00048139 *)p, (const BfmeContainerRecord00048139 &)v); }
}
// Retail grows this view with the no-EH body below; it frees through the
// rowed vector<Rva0004B22EElement>::_M_clear.
struct Rva0004B22EElement;
// Retail's growth frees through the rowed range destructor at 0x0004B205.
struct BfmeRecordRange004B205 { int *m_start; int *m_finish; int *m_end; ~BfmeRecordRange004B205(); };
namespace _STL {
template <> inline void vector<BfmePod92, allocator<BfmePod92> >::_M_insert_overflow(
    BfmePod92 *__position, const BfmePod92 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy((const BfmePod92 *)this->_M_start, (const BfmePod92 *)__position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy((const BfmePod92 *)__position, (const BfmePod92 *)this->_M_finish, __new_finish, __false_type());
    ((BfmeRecordRange004B205 *)this)->~BfmeRecordRange004B205();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}
struct BfmePod104 { int a[26]; };
// Retail push_back calls the rowed no-EH _M_insert_overflow; its body is spelled below.
// The dedicated no-EH provider owns this type's allocation/copy helper.
// Assignment is unrowed here; leave it uninstantiated in this EH profile.
namespace _STL { template <> vector<BfmePod104, allocator<BfmePod104> > &
vector<BfmePod104, allocator<BfmePod104> >::operator=(
    const vector<BfmePod104, allocator<BfmePod104> > &); }
inline bool operator==(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod104> is rowed in StlportConstructFamily.cpp
// (0x003B8AD8); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod104, BfmePod104>(BfmePod104 *__p, const BfmePod104 &__val); }
struct BfmePod128 { int a[32]; };
namespace _STL {
template <> void vector<BfmePod128>::_M_clear();
}
inline bool operator==(const BfmePod128 &x, const BfmePod128 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod128 &x, const BfmePod128 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod128> is pinned elsewhere; declare that
// specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod128, BfmePod128>(BfmePod128 *__p, const BfmePod128 &__val); }
// This growth path uses STLport's no-exception allocation and copy sequence.
namespace _STL {
template <> inline void vector<BfmePod128>::_M_insert_overflow(
    BfmePod128 *__position, const BfmePod128 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else {
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    }
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}

struct BfmePod144 { int a[36]; };
inline bool operator==(const BfmePod144 &x, const BfmePod144 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod144 &x, const BfmePod144 &y) { return x.a[0] < y.a[0]; }
// Retail calls the rowed _Construct<BfmeStringTailRecord144>; forward this view to it.
struct BfmeStringTailRecord144;
namespace _STL {
template <> void _Construct<BfmeStringTailRecord144, BfmeStringTailRecord144>(BfmeStringTailRecord144 *, const BfmeStringTailRecord144 &) throw();
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod144, BfmePod144>(BfmePod144 *p, const BfmePod144 &v) throw()
{ _Construct((BfmeStringTailRecord144 *)p, (const BfmeStringTailRecord144 &)v); }
}
// Retail grows this view with the no-EH body below; it frees through the
// rowed vector<BfmeStringTailRecord144>::_M_clear.
namespace _STL {
template <> void vector<BfmeStringTailRecord144, allocator<BfmeStringTailRecord144> >::_M_clear();
template <> inline void vector<BfmePod144, allocator<BfmePod144> >::_M_insert_overflow(
    BfmePod144 *__position, const BfmePod144 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy((const BfmePod144 *)this->_M_start, (const BfmePod144 *)__position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy((const BfmePod144 *)__position, (const BfmePod144 *)this->_M_finish, __new_finish, __false_type());
    ((BfmeOverflowAccess<BfmeStringTailRecord144> *)this)->_M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}
struct BfmePod148 { int a[37]; };
inline bool operator==(const BfmePod148 &x, const BfmePod148 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod148 &x, const BfmePod148 &y) { return x.a[0] < y.a[0]; }
// Retail calls the rowed _Construct<BfmeStringHeadRecord148>; forward this view to it.
struct BfmeStringHeadRecord148;
namespace _STL {
template <> void _Construct<BfmeStringHeadRecord148, BfmeStringHeadRecord148>(BfmeStringHeadRecord148 *, const BfmeStringHeadRecord148 &) throw();
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod148, BfmePod148>(BfmePod148 *p, const BfmePod148 &v) throw()
{ _Construct((BfmeStringHeadRecord148 *)p, (const BfmeStringHeadRecord148 &)v); }
}
// Retail grows this view with the no-EH body below; it frees through the
// rowed vector<BfmeStringHeadRecord148>::_M_clear.
namespace _STL {
template <> void vector<BfmeStringHeadRecord148, allocator<BfmeStringHeadRecord148> >::_M_clear();
template <> inline void vector<BfmePod148, allocator<BfmePod148> >::_M_insert_overflow(
    BfmePod148 *__position, const BfmePod148 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy((const BfmePod148 *)this->_M_start, (const BfmePod148 *)__position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy((const BfmePod148 *)__position, (const BfmePod148 *)this->_M_finish, __new_finish, __false_type());
    ((BfmeOverflowAccess<BfmeStringHeadRecord148> *)this)->_M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}
struct BfmePod160 { int a[40]; };
inline bool operator==(const BfmePod160 &x, const BfmePod160 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod160 &x, const BfmePod160 &y) { return x.a[0] < y.a[0]; }
// Retail calls the rowed _Construct<BfmeContainerRecord003A451B>; forward this view to it.
struct BfmeContainerRecord003A451B;
namespace _STL {
template <> void _Construct<BfmeContainerRecord003A451B, BfmeContainerRecord003A451B>(BfmeContainerRecord003A451B *, const BfmeContainerRecord003A451B &) throw();
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod160, BfmePod160>(BfmePod160 *p, const BfmePod160 &v) throw()
{ _Construct((BfmeContainerRecord003A451B *)p, (const BfmeContainerRecord003A451B &)v); }
}
// Retail grows this view with the no-EH body below; it frees through the
// rowed vector<BfmeStringHeadRecord160>::_M_clear.
struct BfmeStringHeadRecord160;
namespace _STL {
template <> void vector<BfmeStringHeadRecord160, allocator<BfmeStringHeadRecord160> >::_M_clear();
template <> inline void vector<BfmePod160, allocator<BfmePod160> >::_M_insert_overflow(
    BfmePod160 *__position, const BfmePod160 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy((const BfmePod160 *)this->_M_start, (const BfmePod160 *)__position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy((const BfmePod160 *)__position, (const BfmePod160 *)this->_M_finish, __new_finish, __false_type());
    ((BfmeOverflowAccess<BfmeStringHeadRecord160> *)this)->_M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}
struct BfmePod172 { int a[43]; };
// The dedicated no-EH provider owns this type's allocation/copy helper.
// Assignment is unrowed here; leave it uninstantiated in this EH profile.
namespace _STL { template <> vector<BfmePod172, allocator<BfmePod172> > &
vector<BfmePod172, allocator<BfmePod172> >::operator=(
    const vector<BfmePod172, allocator<BfmePod172> > &); }
inline bool operator==(const BfmePod172 &x, const BfmePod172 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod172 &x, const BfmePod172 &y) { return x.a[0] < y.a[0]; }
// _Construct<BfmePod172> has its own row (stlport_construct_pod172.cpp, 0x001EB9E6): declare that
// specialization so this unit calls it rather than emitting a second, duplicate copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod172, BfmePod172>(BfmePod172 *__p, const BfmePod172 &__val); }
struct BfmePod180 { int a[45]; };
inline bool operator==(const BfmePod180 &x, const BfmePod180 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod180 &x, const BfmePod180 &y) { return x.a[0] < y.a[0]; }
// Retail calls the rowed _Construct<BfmeContainerRecord000C0B85>; forward this view to it.
struct BfmeContainerRecord000C0B85;
namespace _STL {
template <> void _Construct<BfmeContainerRecord000C0B85, BfmeContainerRecord000C0B85>(BfmeContainerRecord000C0B85 *, const BfmeContainerRecord000C0B85 &) throw();
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod180, BfmePod180>(BfmePod180 *p, const BfmePod180 &v) throw()
{ _Construct((BfmeContainerRecord000C0B85 *)p, (const BfmeContainerRecord000C0B85 &)v); }
}
// Retail grows this view with the no-EH body below; it frees through the
// rowed vector<Rva000C828CElement>::_M_clear.
struct Rva000C828CElement;
namespace _STL {
template <> void vector<Rva000C828CElement, allocator<Rva000C828CElement> >::_M_clear();
template <> inline void vector<BfmePod180, allocator<BfmePod180> >::_M_insert_overflow(
    BfmePod180 *__position, const BfmePod180 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy((const BfmePod180 *)this->_M_start, (const BfmePod180 *)__position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy((const BfmePod180 *)__position, (const BfmePod180 *)this->_M_finish, __new_finish, __false_type());
    ((BfmeOverflowAccess<Rva000C828CElement> *)this)->_M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}
// The 216-byte element is CreateAHeroManager::CreateAHeroSubClass: its vector
// is CreateAHeroClass +0x14 (parseCreateAHeroSubClass push_back, CreateAHeroClass
// copy 0x0021F876); this unit keeps only its 216-byte footprint.
class CreateAHeroManager
{
public:
    class CreateAHeroSubClass { public: int a[54]; ~CreateAHeroSubClass(); };
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline vector<CreateAHeroManager::CreateAHeroSubClass,allocator<CreateAHeroManager::CreateAHeroSubClass> >::~vector() { _Destroy(this->_M_start, this->_M_finish); } }
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Destroy(CreateAHeroManager::CreateAHeroSubClass *value)
{ value->~CreateAHeroSubClass(); }
}
// Retail's _Construct<CreateAHeroSubClass> is rowed in stlport_construct_pod216.cpp
// (0x0021EF66); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<CreateAHeroManager::CreateAHeroSubClass, CreateAHeroManager::CreateAHeroSubClass>(CreateAHeroManager::CreateAHeroSubClass *__p, const CreateAHeroManager::CreateAHeroSubClass &__val); }
inline bool operator==(const CreateAHeroManager::CreateAHeroSubClass &x, const CreateAHeroManager::CreateAHeroSubClass &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const CreateAHeroManager::CreateAHeroSubClass &x, const CreateAHeroManager::CreateAHeroSubClass &y) { return x.a[0] < y.a[0]; }
struct BfmePod248 { int a[62]; ~BfmePod248(); };
namespace _STL {template<> vector<BfmePod248,allocator<BfmePod248> >::~vector();}
inline bool operator==(const BfmePod248 &x, const BfmePod248 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod248 &x, const BfmePod248 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod248> is rowed in StlportConstructFamily.cpp
// (0x000C78F3); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod248, BfmePod248>(BfmePod248 *__p, const BfmePod248 &__val); }
struct BfmePod252 { int a[63]; };
// Native calls bind the non-trivial copy helper owned at RVA 000C3717.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod252, BfmePod252>(BfmePod252 *, const BfmePod252 &); }
namespace _STL {template<> vector<BfmePod252,allocator<BfmePod252> >::~vector();}
inline bool operator==(const BfmePod252 &x, const BfmePod252 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod252 &x, const BfmePod252 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod252> is rowed in StlportConstructFamily.cpp
// (0x000C3717); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod252, BfmePod252>(BfmePod252 *__p, const BfmePod252 &__val); }
struct BfmePod260 { int a[65]; };
inline bool operator==(const BfmePod260 &x, const BfmePod260 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod260 &x, const BfmePod260 &y) { return x.a[0] < y.a[0]; }
struct BfmePod340 { int a[85]; };
// The dedicated no-EH provider owns this type's allocation/copy helper.
// Assignment is unrowed here; leave it uninstantiated in this EH profile.
namespace _STL { template <> vector<BfmePod340, allocator<BfmePod340> > &
vector<BfmePod340, allocator<BfmePod340> >::operator=(
    const vector<BfmePod340, allocator<BfmePod340> > &); }
inline bool operator==(const BfmePod340 &x, const BfmePod340 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod340 &x, const BfmePod340 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod340> is rowed in StlportConstructFamily.cpp
// (0x004D9B98); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod340, BfmePod340>(BfmePod340 *__p, const BfmePod340 &__val); }
// Retail grows this view with the no-EH body below; it frees through the
// rowed vector<Rva004DA181Element>::_M_clear.
struct Rva004DA181Element;
namespace _STL {
template <> void vector<Rva004DA181Element, allocator<Rva004DA181Element> >::_M_clear();
template <> inline void vector<BfmePod340, allocator<BfmePod340> >::_M_insert_overflow(
    BfmePod340 *__position, const BfmePod340 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy((const BfmePod340 *)this->_M_start, (const BfmePod340 *)__position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy((const BfmePod340 *)__position, (const BfmePod340 *)this->_M_finish, __new_finish, __false_type());
    ((BfmeOverflowAccess<Rva004DA181Element> *)this)->_M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}

// These allocation helpers use the no-catch bodies owned by the POD providers.
namespace _STL {
template <> template <> inline
BfmePod32 *vector<BfmePod32>::_M_allocate_and_copy<BfmePod32 *>(
    size_t __n, BfmePod32 *__first, BfmePod32 *__last)
{
    BfmePod32 *__result = this->_M_end_of_storage.allocate(__n);
    __uninitialized_copy(__first, __last, __result, __false_type());
    return __result;
}

template <> template <> inline
BfmePod44 *vector<BfmePod44>::_M_allocate_and_copy<BfmePod44 *>(
    size_t __n, BfmePod44 *__first, BfmePod44 *__last)
{
    BfmePod44 *__result = this->_M_end_of_storage.allocate(__n);
    __uninitialized_copy(__first, __last, __result, __false_type());
    return __result;
}

}

// Keep the shared destruction workers in their existing retail providers.
namespace _STL {
template <> void vector<BfmePod248>::_M_clear();

template <> __declspec(dllimport) __forceinline
void __destroy_aux<BfmePod252 *>(BfmePod252 *__first, BfmePod252 *__last, const __false_type &)
{
    for (; __first != __last; ++__first)
        _Destroy(&*__first);
}

template <> __declspec(dllimport) __forceinline
void _Destroy<BfmePod252 *>(BfmePod252 *__first, BfmePod252 *__last)
{ __destroy(__first, __last, (BfmePod252 *)0); }

template <> void vector<BfmePod252>::_M_clear();

}

// Keep header operations inline without emitting unused external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void vector<BfmePod88>::_M_clear()
{
    _Destroy(this->_M_start, this->_M_finish);
    this->_M_end_of_storage.deallocate(this->_M_start,
        this->_M_end_of_storage._M_data - this->_M_start);
}

template <> __declspec(dllimport) __forceinline
void vector<BfmePod104>::_M_clear()
{
    _Destroy(this->_M_start, this->_M_finish);
    this->_M_end_of_storage.deallocate(this->_M_start,
        this->_M_end_of_storage._M_data - this->_M_start);
}

template <> __declspec(dllimport) __forceinline
char *_STLP_alloc_proxy<char *, char, allocator<char> >::allocate(size_t __n)
{ return __stl_alloc_rebind(static_cast<allocator<char> &>(*this), (char *)0).allocate(__n, 0); }

template <> __declspec(dllimport) __forceinline
char *uninitialized_fill_n<char *, unsigned int, char>(char *__first, unsigned int __n, const char &__x)
{ return __uninitialized_fill_n(__first, __n, __x, __true_type()); }
}

// Retail's growth calls the rowed out-of-line clear at 0x003B90BD, the
// vector<BfmeAssignRecord104> instance of the same 104-byte element.
struct BfmeAssignRecord104 { int a[26]; };
namespace _STL { template <> void vector<BfmeAssignRecord104, allocator<BfmeAssignRecord104> >::_M_clear(); }
// The overflow provider uses STLport's growth path without exception rollback
// (stlport_pod_noexc_bodies.cpp); spell that body so this copy is retail's.
namespace _STL {
template <> inline void vector<BfmePod104, allocator<BfmePod104> >::_M_insert_overflow(
    BfmePod104 *__position, const BfmePod104 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    ((BfmeOverflowAccess<BfmeAssignRecord104> *)this)->_M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}

// Retail growth uses the no-catch sequence and out-of-line cleanup.
namespace _STL {
template <> void vector<CreateAHeroManager::CreateAHeroSubClass>::_M_clear();
template <> inline void vector<BfmePod252>::_M_insert_overflow(
    BfmePod252 *__position, const BfmePod252 &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else {
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    }
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
template <> inline void vector<CreateAHeroManager::CreateAHeroSubClass>::_M_insert_overflow(
    CreateAHeroManager::CreateAHeroSubClass *__position, const CreateAHeroManager::CreateAHeroSubClass &__x, const __false_type &,
    size_type __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else {
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    }
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}
}

// Retail growth constructs and releases the non-trivial element without a catch.
namespace _STL {
template <> inline void vector<BfmePod248>::_M_insert_overflow(
    pointer position, const BfmePod248 &value, const __false_type &,
    size_type fillCount, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillCount);
    pointer newStart = this->_M_end_of_storage.allocate(length);
    pointer newFinish = newStart;
    newFinish = __uninitialized_copy(this->_M_start, position, newStart, __false_type());
    if (fillCount == 1) {
        _Construct(newFinish, value);
        ++newFinish;
    } else
        newFinish = __uninitialized_fill_n(newFinish, fillCount, value, __false_type());
    if (!atEnd)
        newFinish = __uninitialized_copy(position, this->_M_finish, newFinish, __false_type());
    _M_clear();
    _M_set(newStart, newFinish, newStart + length);
}
}

// The 28-byte growth worker is likewise retail's body without a catch.
namespace _STL {
template <> inline void vector<BfmePod28>::_M_insert_overflow(
    pointer position, const BfmePod28 &value, const __false_type &,
    size_type fillCount, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillCount);
    pointer newStart = this->_M_end_of_storage.allocate(length);
    pointer newFinish = newStart;
    newFinish = __uninitialized_copy(this->_M_start, position, newStart, __false_type());
    if (fillCount == 1) {
        _Construct(newFinish, value);
        ++newFinish;
    } else
        newFinish = __uninitialized_fill_n(newFinish, fillCount, value, __false_type());
    if (!atEnd)
        newFinish = __uninitialized_copy(position, this->_M_finish, newFinish, __false_type());
    _M_clear();
    _M_set(newStart, newFinish, newStart + length);
}
}

// The 88-byte growth worker also omits the STL catch/rethrow path in retail.
// Keep its body visible to push_back, which otherwise materializes the unused
// dispatch tag. Native 0x4E3973 calls the existing 0x4E2227 destruction owner.
struct Rva004E2227 { void rva004E2227(); };
template <> inline void _STL::vector<BfmePod88>::_M_insert_overflow(
    BfmePod88 *__position, const BfmePod88 &__x, const _STL::__false_type &,
    unsigned int __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    reinterpret_cast<Rva004E2227 *>(this)->rva004E2227();
    _M_set(__new_start, __new_finish, __new_start + __len);
}


// The size-only element view must retain the nontrivial retail destruction.
// Native clear 0x1EB9C8 destroys the existing 172-byte record range.
struct BfmeAssignRecord172;
namespace _STL {
template <> void _Destroy<BfmeAssignRecord172 *>(BfmeAssignRecord172 *, BfmeAssignRecord172 *);
template <> inline void vector<BfmePod172>::_M_clear()
{
    _Destroy(reinterpret_cast<BfmeAssignRecord172 *>(this->_M_start),
        reinterpret_cast<BfmeAssignRecord172 *>(this->_M_finish));
    this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
}
}
template <> inline void _STL::vector<BfmePod172>::_M_insert_overflow(
    BfmePod172 *__position, const BfmePod172 &__x, const _STL::__false_type &,
    unsigned int __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}


// The 20-byte growth worker is the complete no-catch retail body at
// 0x59B809. Other element copies in this TU retain their native EH paths.
// Keep STLport 4.5.3 growth/copy/fill/release semantics for this specialization.
template <> inline void _STL::vector<BfmePod20>::_M_insert_overflow(
    BfmePod20 *__position, const BfmePod20 &__x, const _STL::__false_type &,
    unsigned int __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}

// Target boundary 0x0007EA1F/136 is vector<char>::_M_insert_overflow for the
// true_type path: matched _M_fill_insert at 0x0007FE65 calls it with the five
// overflow arguments and the target returns with ret 0x14. The STLport 4.5.3
// donor omits retail's zero-length allocation guard (128B here); this explicit
// specialization adds that target-observed branch while retaining the donor's
// copy/fill/capacity semantics. Helpers are target-resolved as allocator<char>
// 0x307F0, __copy_trivial 0x179B0, FillN 0x24970 and _free 0x30830.
template <> void _STL::vector<char, _STL::allocator<char> >::_M_insert_overflow(
    char *position, const char &value, const _STL::__true_type &,
    unsigned int fill_len, bool at_end)
{
    const unsigned int old_size = this->_M_finish - this->_M_start;
    char *new_start;
    const unsigned int new_len = old_size + (max)(old_size, fill_len);
    if (new_len != 0)
        new_start = this->_M_end_of_storage.allocate(new_len);
    else
        new_start = 0;
    char *new_finish = (char *)_STL::__copy_trivial(this->_M_start, position, new_start);
    new_finish = _STL::fill_n(new_finish, fill_len, value);
    if (!at_end)
        new_finish = (char *)_STL::__copy_trivial(position, this->_M_finish, new_finish);
    this->_M_clear();
    this->_M_set(new_start, new_finish, new_start + new_len);
}

// Target 0x000AFB2E/136 is the byte-vector overflow sibling of 0x0007EA1F.
// Retail calls the independently rowed unsigned-char fill_n at 0x000AD829;
// allocation, trivial copying and checked free match the char specialization.
// The unsigned-byte template view follows that typed fill helper; the containing
// application type remains unknown. The zero-allocation guard is target evidence.
template <> void _STL::vector<unsigned char, _STL::allocator<unsigned char> >::_M_insert_overflow(
    unsigned char *position, const unsigned char &value, const _STL::__true_type &,
    unsigned int fill_len, bool at_end)
{
    const unsigned int old_size = this->_M_finish - this->_M_start;
    unsigned char *new_start;
    const unsigned int new_len = old_size + (max)(old_size, fill_len);
    if (new_len != 0)
        new_start = (unsigned char *)_STL::allocator<char>::allocate(new_len, 0);
    else
        new_start = 0;
    unsigned char *new_finish = (unsigned char *)_STL::__copy_trivial(this->_M_start, position, new_start);
    new_finish = _STL::fill_n(new_finish, fill_len, value);
    if (!at_end)
        new_finish = (unsigned char *)_STL::__copy_trivial(position, this->_M_finish, new_finish);
    this->_M_clear();
    this->_M_set(new_start, new_finish, new_start + new_len);
}

// Target boundary 0x00307641/63 is _Vector_base<char>::_Vector_base(count, alloc):
// ??0?$_Vector_base@DV?$allocator@D@_STL@@@_STL@@QAE@IABV?$allocator@D@1@@Z,
// pinned name, called at 0x00307C51 by vector<char> ctor 0x00307C43 (rowed
// in this TU). The STLport 4.5.3 donor emits unconditional allocate (57B via
// template class); retail skips allocate when count==0 (63B with xor-eax,
// cmp ebx,eax and je). This explicit specialization adds that target-observed
// guard while retaining donor semantics. Callees are alloc proxy 0x00007410
// and byte allocator 0x000307F0, both settled. tmp starts as the current
// (null) _M_finish to reproduce retail's eax zeroing.
template <> _STL::_Vector_base<char, _STL::allocator<char> >::_Vector_base(unsigned int __n, const _STL::allocator<char> &__a)
    : _M_start(0), _M_finish(0), _M_end_of_storage(__a, 0)
{
    char *tmp = _M_finish;
    if (__n != 0)
        tmp = _M_end_of_storage.allocate(__n);
    else
        tmp = 0;
    _M_start = tmp;
    _M_finish = tmp;
    _M_end_of_storage._M_data = tmp + __n;
}

// Rowed in stlport_byte_vector_resize_value.cpp; declared here so the
// explicit instantiation below emits no competing copy.
template <> void _STL::vector<char, _STL::allocator<char> >::resize(size_type);

namespace _STL { template <> BfmePod52 *vector<BfmePod52, allocator<BfmePod52> >::erase(BfmePod52 *, BfmePod52 *); }
// insert/resize call _M_fill_insert out of line: bind it to the rowed retail copy
// (0x005B1748, StlportVectorFillInsertRva005B1748.cpp) instead of emitting this unit's own.
namespace _STL { template <> void vector<BfmePod20, allocator<BfmePod20> >::_M_fill_insert(BfmePod20 *, size_t, const BfmePod20 &); }
// This size-only view retains allocation and plain assignment operations.
// Only allocation and plain assignment are claimed for this size-only view.
// Instantiate matched members without this profile's unrelated allocation/copy
// body; the no-EH provider owns retail 0x004D9C1C.
// ??$__find@PAUBfmePod20@@U1@@_STL@@YAPAUBfmePod20@@PAU1@0ABU1@ABUrandom_access_iterator_tag@0@@Z @0x002194CC 118B
// Unrolled random-access __find over 20-byte elements comparing a[0]; caller
// 0x002198BE is the 27B find wrapper that becomes ready on landing.
// ??$find@PAUBfmePod20@@U1@@_STL@@YAPAUBfmePod20@@PAU1@0ABU1@@Z @0x002198AD 27B
// find wrapper over the rowed __find 0x002194CC via tag local; callers
// 0x0021EAA6 0x004EDD71.
// ??$__find@PAUBfmePod40@@U1@@_STL@@YAPAUBfmePod40@@PAU1@0ABU1@ABUrandom_access_iterator_tag@0@@Z @0x0040A68F 118B
// Unrolled random-access __find over 40-byte elements comparing a[0]; caller
// 0x0040A891 is the 27B find wrapper that becomes ready on landing.
// ??$find@PAUBfmePod40@@U1@@_STL@@YAPAUBfmePod40@@PAU1@0ABU1@@Z @0x0040A891 27B
// find wrapper over __find 0x0040A68F via tag local.
// ?rva0040AAD5@Rva0040AAD5@@QAEPAUBfmePod40@@H@Z @0x0040AAD5 35B
// Searches vector<BfmePod40> at +0xC by first-field key via rowed find
// 0x0040A891; caller 0x0040C0FE passes [edi] int key and tests for null.
class Rva0040AAD5 {
    int _pad[3];
    BfmePod40 *_first;
    BfmePod40 *_last;
public:
    BfmePod40 *rva0040AAD5(int key);
};
BfmePod40 *Rva0040AAD5::rva0040AAD5(int key)
{
    BfmePod40 *found = _STL::find(_first, _last, (const BfmePod40 &)key);
    return found == _last ? 0 : found;
}
// ??$__find@PAUBfmePod104@@U1@@_STL@@YAPAUBfmePod104@@PAU1@0ABU1@ABUrandom_access_iterator_tag@0@@Z @0x0040A705 118B
// Unrolled random-access __find over 104-byte elements comparing a[0]; stride
// 0x68 in retail; caller 0x0040A8AC is the 27B find wrapper it unlocks.
// ??$find@PAUBfmePod104@@U1@@_STL@@YAPAUBfmePod104@@PAU1@0ABU1@@Z @0x0040A8AC 27B
// find wrapper over __find 0x0040A705 via tag local.

// Instantiate the matched members without unrelated container operations.
template void _STL::_Construct<BfmePod20,BfmePod20>(BfmePod20 *,BfmePod20 const &);

template void _STL::_Construct<BfmePod24,BfmePod24>(BfmePod24 *,BfmePod24 const &);

template void _STL::_Construct<BfmePod28,BfmePod28>(BfmePod28 *,BfmePod28 const &);

template void _STL::_Construct<BfmePod36,BfmePod36>(BfmePod36 *,BfmePod36 const &);

template void _STL::_Construct<BfmePod44,BfmePod44>(BfmePod44 *,BfmePod44 const &);

template void _STL::_Construct<BfmePod68,BfmePod68>(BfmePod68 *,BfmePod68 const &);

template _STL::vector<char,_STL::allocator<char> >::vector(unsigned int);

template void _STL::vector<BfmePod44,_STL::allocator<BfmePod44> >::reserve(unsigned int);

template void _STL::vector<BfmePod32,_STL::allocator<BfmePod32> >::reserve(unsigned int);

template _STL::vector<BfmePod40,_STL::allocator<BfmePod40> >::vector(_STL::vector<BfmePod40,_STL::allocator<BfmePod40> > const &);

template _STL::vector<BfmePod44,_STL::allocator<BfmePod44> >::vector(_STL::vector<BfmePod44,_STL::allocator<BfmePod44> > const &);

template _STL::vector<BfmePod48,_STL::allocator<BfmePod48> >::vector(_STL::vector<BfmePod48,_STL::allocator<BfmePod48> > const &);

template _STL::vector<BfmePod52,_STL::allocator<BfmePod52> >::vector(_STL::vector<BfmePod52,_STL::allocator<BfmePod52> > const &);

template _STL::_Vector_base<BfmePod32,_STL::allocator<BfmePod32> >::_Vector_base(unsigned int,_STL::allocator<BfmePod32> const &);

template _STL::_Vector_base<BfmePod44,_STL::allocator<BfmePod44> >::_Vector_base(unsigned int,_STL::allocator<BfmePod44> const &);

template _STL::_Vector_base<BfmePod52,_STL::allocator<BfmePod52> >::_Vector_base(unsigned int,_STL::allocator<BfmePod52> const &);

// The no-EH provider owns push_back together with its overflow callee.

template BfmePod44 * _STL::__copy_backward<BfmePod44 *,BfmePod44 *,int>(BfmePod44 *,BfmePod44 *,BfmePod44 *,_STL::random_access_iterator_tag const &,int *);

template BfmePod52 * _STL::__copy_backward<BfmePod52 *,BfmePod52 *,int>(BfmePod52 *,BfmePod52 *,BfmePod52 *,_STL::random_access_iterator_tag const &,int *);

template BfmePod60 * _STL::__copy_backward<BfmePod60 *,BfmePod60 *,int>(BfmePod60 *,BfmePod60 *,BfmePod60 *,_STL::random_access_iterator_tag const &,int *);

template void _STL::fill<BfmePod44 *,BfmePod44>(BfmePod44 *,BfmePod44 *,BfmePod44 const &);

template void _STL::fill<BfmePod52 *,BfmePod52>(BfmePod52 *,BfmePod52 *,BfmePod52 const &);

template void _STL::fill<BfmePod60 *,BfmePod60>(BfmePod60 *,BfmePod60 *,BfmePod60 const &);

template BfmePod44 * _STL::allocator<BfmePod44>::allocate(unsigned int,void const *)const ;

template BfmePod52 * _STL::allocator<BfmePod52>::allocate(unsigned int,void const *)const ;

template BfmePod60 * _STL::allocator<BfmePod60>::allocate(unsigned int,void const *)const ;

template _STL::vector<BfmePod104,_STL::allocator<BfmePod104> >::vector(_STL::vector<BfmePod104,_STL::allocator<BfmePod104> > const &);

template _STL::vector<BfmePod88,_STL::allocator<BfmePod88> >::vector(_STL::vector<BfmePod88,_STL::allocator<BfmePod88> > const &);

template _STL::vector<BfmePod128,_STL::allocator<BfmePod128> >::vector(_STL::vector<BfmePod128,_STL::allocator<BfmePod128> > const &);

template _STL::_Vector_base<BfmePod104,_STL::allocator<BfmePod104> >::_Vector_base(unsigned int,_STL::allocator<BfmePod104> const &);

template _STL::_Vector_base<BfmePod128,_STL::allocator<BfmePod128> >::_Vector_base(unsigned int,_STL::allocator<BfmePod128> const &);

template _STL::_Vector_base<BfmePod88,_STL::allocator<BfmePod88> >::_Vector_base(unsigned int,_STL::allocator<BfmePod88> const &);

template void _STL::vector<BfmePod128,_STL::allocator<BfmePod128> >::push_back(BfmePod128 const &);

template void _STL::vector<BfmePod144,_STL::allocator<BfmePod144> >::push_back(BfmePod144 const &);

template void _STL::vector<BfmePod148,_STL::allocator<BfmePod148> >::push_back(BfmePod148 const &);

template void _STL::vector<BfmePod160,_STL::allocator<BfmePod160> >::push_back(BfmePod160 const &);

template void _STL::vector<BfmePod172,_STL::allocator<BfmePod172> >::push_back(BfmePod172 const &);

template void _STL::vector<BfmePod180,_STL::allocator<BfmePod180> >::push_back(BfmePod180 const &);

template void _STL::vector<BfmePod68,_STL::allocator<BfmePod68> >::push_back(BfmePod68 const &);

template void _STL::vector<BfmePod76,_STL::allocator<BfmePod76> >::push_back(BfmePod76 const &);

template void _STL::vector<BfmePod88,_STL::allocator<BfmePod88> >::push_back(BfmePod88 const &);

template void _STL::vector<BfmePod92,_STL::allocator<BfmePod92> >::push_back(BfmePod92 const &);

template BfmePod128 * _STL::__uninitialized_fill_n<BfmePod128 *,unsigned int,BfmePod128>(BfmePod128 *,unsigned int,BfmePod128 const &,_STL::__false_type const &);

template BfmePod144 * _STL::__uninitialized_fill_n<BfmePod144 *,unsigned int,BfmePod144>(BfmePod144 *,unsigned int,BfmePod144 const &,_STL::__false_type const &);

template BfmePod148 * _STL::__uninitialized_fill_n<BfmePod148 *,unsigned int,BfmePod148>(BfmePod148 *,unsigned int,BfmePod148 const &,_STL::__false_type const &);

template BfmePod160 * _STL::__uninitialized_fill_n<BfmePod160 *,unsigned int,BfmePod160>(BfmePod160 *,unsigned int,BfmePod160 const &,_STL::__false_type const &);

template BfmePod172 * _STL::__uninitialized_fill_n<BfmePod172 *,unsigned int,BfmePod172>(BfmePod172 *,unsigned int,BfmePod172 const &,_STL::__false_type const &);

template BfmePod180 * _STL::__uninitialized_fill_n<BfmePod180 *,unsigned int,BfmePod180>(BfmePod180 *,unsigned int,BfmePod180 const &,_STL::__false_type const &);

template BfmePod68 * _STL::__uninitialized_fill_n<BfmePod68 *,unsigned int,BfmePod68>(BfmePod68 *,unsigned int,BfmePod68 const &,_STL::__false_type const &);

template BfmePod88 * _STL::__uninitialized_fill_n<BfmePod88 *,unsigned int,BfmePod88>(BfmePod88 *,unsigned int,BfmePod88 const &,_STL::__false_type const &);

template BfmePod92 * _STL::__uninitialized_fill_n<BfmePod92 *,unsigned int,BfmePod92>(BfmePod92 *,unsigned int,BfmePod92 const &,_STL::__false_type const &);

template BfmePod148 * _STL::allocator<BfmePod148>::allocate(unsigned int,void const *)const ;

template BfmePod172 * _STL::allocator<BfmePod172>::allocate(unsigned int,void const *)const ;

template BfmePod180 * _STL::allocator<BfmePod180>::allocate(unsigned int,void const *)const ;

template BfmePod104 * _STL::allocator<BfmePod104>::allocate(unsigned int,void const *)const ;

template BfmePod128 * _STL::allocator<BfmePod128>::allocate(unsigned int,void const *)const ;

template BfmePod76 * _STL::allocator<BfmePod76>::allocate(unsigned int,void const *)const ;

template BfmePod92 * _STL::allocator<BfmePod92>::allocate(unsigned int,void const *)const ;

template BfmePod80 * _STL::__uninitialized_fill_n<BfmePod80 *,unsigned int,BfmePod80>(BfmePod80 *,unsigned int,BfmePod80 const &,_STL::__false_type const &);

template _STL::vector<CreateAHeroManager::CreateAHeroSubClass,_STL::allocator<CreateAHeroManager::CreateAHeroSubClass> >::vector(_STL::vector<CreateAHeroManager::CreateAHeroSubClass,_STL::allocator<CreateAHeroManager::CreateAHeroSubClass> > const &);

template _STL::vector<BfmePod248,_STL::allocator<BfmePod248> >::vector(_STL::vector<BfmePod248,_STL::allocator<BfmePod248> > const &);

template _STL::vector<BfmePod252,_STL::allocator<BfmePod252> >::vector(_STL::vector<BfmePod252,_STL::allocator<BfmePod252> > const &);

template _STL::_Vector_base<CreateAHeroManager::CreateAHeroSubClass,_STL::allocator<CreateAHeroManager::CreateAHeroSubClass> >::_Vector_base(unsigned int,_STL::allocator<CreateAHeroManager::CreateAHeroSubClass> const &);

template _STL::_Vector_base<BfmePod248,_STL::allocator<BfmePod248> >::_Vector_base(unsigned int,_STL::allocator<BfmePod248> const &);

template _STL::_Vector_base<BfmePod252,_STL::allocator<BfmePod252> >::_Vector_base(unsigned int,_STL::allocator<BfmePod252> const &);

template void _STL::vector<BfmePod248,_STL::allocator<BfmePod248> >::push_back(BfmePod248 const &);

template void _STL::vector<BfmePod252,_STL::allocator<BfmePod252> >::push_back(BfmePod252 const &);

template void _STL::vector<BfmePod340,_STL::allocator<BfmePod340> >::push_back(BfmePod340 const &);

template BfmePod248 * _STL::__uninitialized_fill_n<BfmePod248 *,unsigned int,BfmePod248>(BfmePod248 *,unsigned int,BfmePod248 const &,_STL::__false_type const &);

template BfmePod252 * _STL::__uninitialized_fill_n<BfmePod252 *,unsigned int,BfmePod252>(BfmePod252 *,unsigned int,BfmePod252 const &,_STL::__false_type const &);

template BfmePod340 * _STL::__uninitialized_fill_n<BfmePod340 *,unsigned int,BfmePod340>(BfmePod340 *,unsigned int,BfmePod340 const &,_STL::__false_type const &);

template CreateAHeroManager::CreateAHeroSubClass * _STL::allocator<CreateAHeroManager::CreateAHeroSubClass>::allocate(unsigned int,void const *)const ;

template BfmePod248 * _STL::allocator<BfmePod248>::allocate(unsigned int,void const *)const ;

template BfmePod252 * _STL::allocator<BfmePod252>::allocate(unsigned int,void const *)const ;

template BfmePod260 * _STL::allocator<BfmePod260>::allocate(unsigned int,void const *)const ;

template BfmePod340 * _STL::allocator<BfmePod340>::allocate(unsigned int,void const *)const ;

template BfmePod68 * _STL::allocator<BfmePod68>::allocate(unsigned int,void const *)const ;

template BfmePod88 * _STL::allocator<BfmePod88>::allocate(unsigned int,void const *)const ;

template BfmePod40 * _STL::__uninitialized_copy<BfmePod40 const *,BfmePod40 *>(BfmePod40 const *,BfmePod40 const *,BfmePod40 *,_STL::__false_type const &);

template void _STL::vector<BfmePod20,_STL::allocator<BfmePod20> >::push_back(BfmePod20 const &);

template void _STL::vector<BfmePod28,_STL::allocator<BfmePod28> >::push_back(BfmePod28 const &);

template void _STL::vector<BfmePod32,_STL::allocator<BfmePod32> >::push_back(BfmePod32 const &);

template void _STL::vector<BfmePod40,_STL::allocator<BfmePod40> >::push_back(BfmePod40 const &);

template BfmePod92 * _STL::__uninitialized_copy<BfmePod92 const *,BfmePod92 *>(BfmePod92 const *,BfmePod92 const *,BfmePod92 *,_STL::__false_type const &);

template BfmePod144 * _STL::__uninitialized_copy<BfmePod144 const *,BfmePod144 *>(BfmePod144 const *,BfmePod144 const *,BfmePod144 *,_STL::__false_type const &);

template BfmePod44 * _STL::__copy<BfmePod44 *,BfmePod44 *,int>(BfmePod44 *,BfmePod44 *,BfmePod44 *,_STL::random_access_iterator_tag const &,int *);

template BfmePod44 * _STL::__uninitialized_fill_n<BfmePod44 *,unsigned int,BfmePod44>(BfmePod44 *,unsigned int,BfmePod44 const &,_STL::__false_type const &);

template BfmePod44 * _STL::__uninitialized_copy<BfmePod44 const *,BfmePod44 *>(BfmePod44 const *,BfmePod44 const *,BfmePod44 *,_STL::__false_type const &);

template void _STL::vector<char,_STL::allocator<char> >::_M_fill_insert(char *,unsigned int,char const &);

template BfmePod36 * _STL::__uninitialized_fill_n<BfmePod36 *,unsigned int,BfmePod36>(BfmePod36 *,unsigned int,BfmePod36 const &,_STL::__false_type const &);

template BfmePod36 * _STL::__uninitialized_copy<BfmePod36 const *,BfmePod36 *>(BfmePod36 const *,BfmePod36 const *,BfmePod36 *,_STL::__false_type const &);

template BfmePod24 * _STL::__uninitialized_copy<BfmePod24 const *,BfmePod24 *>(BfmePod24 const *,BfmePod24 const *,BfmePod24 *,_STL::__false_type const &);

template BfmePod24 * _STL::__uninitialized_fill_n<BfmePod24 *,unsigned int,BfmePod24>(BfmePod24 *,unsigned int,BfmePod24 const &,_STL::__false_type const &);

template BfmePod180 * _STL::__uninitialized_copy<BfmePod180 const *,BfmePod180 *>(BfmePod180 const *,BfmePod180 const *,BfmePod180 *,_STL::__false_type const &);

template BfmePod248 * _STL::__uninitialized_copy<BfmePod248 const *,BfmePod248 *>(BfmePod248 const *,BfmePod248 const *,BfmePod248 *,_STL::__false_type const &);

template BfmePod76 * _STL::__uninitialized_copy<BfmePod76 const *,BfmePod76 *>(BfmePod76 const *,BfmePod76 const *,BfmePod76 *,_STL::__false_type const &);

template BfmePod76 * _STL::__uninitialized_fill_n<BfmePod76 *,unsigned int,BfmePod76>(BfmePod76 *,unsigned int,BfmePod76 const &,_STL::__false_type const &);

template BfmePod68 * _STL::__uninitialized_copy<BfmePod68 const *,BfmePod68 *>(BfmePod68 const *,BfmePod68 const *,BfmePod68 *,_STL::__false_type const &);

template BfmePod68 * _STL::__copy<BfmePod68 *,BfmePod68 *,int>(BfmePod68 *,BfmePod68 *,BfmePod68 *,_STL::random_access_iterator_tag const &,int *);

template BfmePod52 * _STL::__copy<BfmePod52 *,BfmePod52 *,int>(BfmePod52 *,BfmePod52 *,BfmePod52 *,_STL::random_access_iterator_tag const &,int *);

template BfmePod52 * _STL::__uninitialized_fill_n<BfmePod52 *,unsigned int,BfmePod52>(BfmePod52 *,unsigned int,BfmePod52 const &,_STL::__false_type const &);

template BfmePod172 * _STL::__uninitialized_copy<BfmePod172 const *,BfmePod172 *>(BfmePod172 const *,BfmePod172 const *,BfmePod172 *,_STL::__false_type const &);

template BfmePod28 * _STL::__uninitialized_copy<BfmePod28 const *,BfmePod28 *>(BfmePod28 const *,BfmePod28 const *,BfmePod28 *,_STL::__false_type const &);

template BfmePod28 * _STL::__uninitialized_fill_n<BfmePod28 *,unsigned int,BfmePod28>(BfmePod28 *,unsigned int,BfmePod28 const &,_STL::__false_type const &);

template BfmePod260 * _STL::__copy<BfmePod260 *,BfmePod260 *,int>(BfmePod260 *,BfmePod260 *,BfmePod260 *,_STL::random_access_iterator_tag const &,int *);

template BfmePod128 * _STL::__uninitialized_copy<BfmePod128 const *,BfmePod128 *>(BfmePod128 const *,BfmePod128 const *,BfmePod128 *,_STL::__false_type const &);

template BfmePod148 * _STL::__uninitialized_copy<BfmePod148 const *,BfmePod148 *>(BfmePod148 const *,BfmePod148 const *,BfmePod148 *,_STL::__false_type const &);

template BfmePod160 * _STL::__uninitialized_copy<BfmePod160 const *,BfmePod160 *>(BfmePod160 const *,BfmePod160 const *,BfmePod160 *,_STL::__false_type const &);

template BfmePod32 * _STL::__uninitialized_copy<BfmePod32 const *,BfmePod32 *>(BfmePod32 const *,BfmePod32 const *,BfmePod32 *,_STL::__false_type const &);

template BfmePod32 * _STL::__uninitialized_fill_n<BfmePod32 *,unsigned int,BfmePod32>(BfmePod32 *,unsigned int,BfmePod32 const &,_STL::__false_type const &);

template BfmePod340 * _STL::__uninitialized_copy<BfmePod340 const *,BfmePod340 *>(BfmePod340 const *,BfmePod340 const *,BfmePod340 *,_STL::__false_type const &);

template BfmePod88 * _STL::__uninitialized_copy<BfmePod88 const *,BfmePod88 *>(BfmePod88 const *,BfmePod88 const *,BfmePod88 *,_STL::__false_type const &);

template BfmePod252 * _STL::__uninitialized_copy<BfmePod252 const *,BfmePod252 *>(BfmePod252 const *,BfmePod252 const *,BfmePod252 *,_STL::__false_type const &);

template BfmePod80 * _STL::__uninitialized_copy<BfmePod80 const *,BfmePod80 *>(BfmePod80 const *,BfmePod80 const *,BfmePod80 *,_STL::__false_type const &);

template BfmePod40 * _STL::__uninitialized_fill_n<BfmePod40 *,unsigned int,BfmePod40>(BfmePod40 *,unsigned int,BfmePod40 const &,_STL::__false_type const &);

template BfmePod60 * _STL::__copy<BfmePod60 *,BfmePod60 *,int>(BfmePod60 *,BfmePod60 *,BfmePod60 *,_STL::random_access_iterator_tag const &,int *);

template BfmePod20 * _STL::__uninitialized_fill_n<BfmePod20 *,unsigned int,BfmePod20>(BfmePod20 *,unsigned int,BfmePod20 const &,_STL::__false_type const &);

template BfmePod20 * _STL::__uninitialized_copy<BfmePod20 const *,BfmePod20 *>(BfmePod20 const *,BfmePod20 const *,BfmePod20 *,_STL::__false_type const &);

template BfmePod44 * _STL::uninitialized_fill_n<BfmePod44 *,unsigned int,BfmePod44>(BfmePod44 *,unsigned int,BfmePod44 const &);

template BfmePod36 * _STL::uninitialized_fill_n<BfmePod36 *,unsigned int,BfmePod36>(BfmePod36 *,unsigned int,BfmePod36 const &);

template BfmePod52 * _STL::uninitialized_fill_n<BfmePod52 *,unsigned int,BfmePod52>(BfmePod52 *,unsigned int,BfmePod52 const &);

template BfmePod172 * _STL::uninitialized_fill_n<BfmePod172 *,unsigned int,BfmePod172>(BfmePod172 *,unsigned int,BfmePod172 const &);

template BfmePod80 * _STL::uninitialized_fill_n<BfmePod80 *,unsigned int,BfmePod80>(BfmePod80 *,unsigned int,BfmePod80 const &);

template BfmePod20 * _STL::uninitialized_fill_n<BfmePod20 *,unsigned int,BfmePod20>(BfmePod20 *,unsigned int,BfmePod20 const &);

template BfmePod44 * _STL::__copy_backward_ptrs<BfmePod44 *,BfmePod44 *>(BfmePod44 *,BfmePod44 *,BfmePod44 *,_STL::__false_type const &);

template CreateAHeroManager::CreateAHeroSubClass * _STL::__uninitialized_copy<CreateAHeroManager::CreateAHeroSubClass const *,CreateAHeroManager::CreateAHeroSubClass *>(CreateAHeroManager::CreateAHeroSubClass const *,CreateAHeroManager::CreateAHeroSubClass const *,CreateAHeroManager::CreateAHeroSubClass *,_STL::__false_type const &);

template BfmePod48 * _STL::__uninitialized_copy<BfmePod48 const *,BfmePod48 *>(BfmePod48 const *,BfmePod48 const *,BfmePod48 *,_STL::__false_type const &);

template void _STL::vector<CreateAHeroManager::CreateAHeroSubClass,_STL::allocator<CreateAHeroManager::CreateAHeroSubClass> >::push_back(CreateAHeroManager::CreateAHeroSubClass const &);

template void _STL::vector<char,_STL::allocator<char> >::_M_insert_overflow(char *,char const &,_STL::__true_type const &,unsigned int,bool);

template void _STL::vector<BfmePod104,_STL::allocator<BfmePod104> >::push_back(BfmePod104 const &);

template void _STL::vector<BfmePod48,_STL::allocator<BfmePod48> >::push_back(BfmePod48 const &);

template _STL::_Vector_base<char,_STL::allocator<char> >::_Vector_base(unsigned int,_STL::allocator<char> const &);

template BfmePod20 * _STL::__find<BfmePod20 *,BfmePod20>(BfmePod20 *,BfmePod20 *,BfmePod20 const &,_STL::random_access_iterator_tag const &);

template BfmePod20 * _STL::find<BfmePod20 *,BfmePod20>(BfmePod20 *,BfmePod20 *,BfmePod20 const &);

template BfmePod40 * _STL::__find<BfmePod40 *,BfmePod40>(BfmePod40 *,BfmePod40 *,BfmePod40 const &,_STL::random_access_iterator_tag const &);

template BfmePod40 * _STL::find<BfmePod40 *,BfmePod40>(BfmePod40 *,BfmePod40 *,BfmePod40 const &);

template BfmePod104 * _STL::__find<BfmePod104 *,BfmePod104>(BfmePod104 *,BfmePod104 *,BfmePod104 const &,_STL::random_access_iterator_tag const &);

template BfmePod104 * _STL::find<BfmePod104 *,BfmePod104>(BfmePod104 *,BfmePod104 *,BfmePod104 const &);

template void _STL::vector<unsigned char,_STL::allocator<unsigned char> >::_M_insert_overflow(unsigned char *,unsigned char const &,_STL::__true_type const &,unsigned int,bool);

template _STL::allocator<CreateAHeroManager::CreateAHeroSubClass> _STL::vector<CreateAHeroManager::CreateAHeroSubClass,_STL::allocator<CreateAHeroManager::CreateAHeroSubClass> >::get_allocator(void)const ;

template void _STL::vector<char,_STL::allocator<char> >::insert(char *,unsigned int,char const &);

template BfmePod52 * _STL::__uninitialized_copy<BfmePod52 *,BfmePod52 *>(BfmePod52 *,BfmePod52 *,BfmePod52 *,_STL::__false_type const &);

// Shared header destructor used by the char-vector callers.
template _STL::vector<char>::~vector();

// ?swap@?$vector@DV?$allocator@D@_STL@@@_STL@@QAEXAAV12@@Z @0x003079C1 44B: swaps the three
// pointers and calls the proxy swap 0x00025AD0; the byte-vector loader 0x00307EDC calls it.
template void _STL::vector<char>::swap(_STL::vector<char> &);
