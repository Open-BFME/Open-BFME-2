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
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include <algorithm>
struct BfmePod20 { int a[5]; };
struct BfmePod24 { int a[6]; };
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] < y.a[0]; }
struct BfmePod28 { int a[7]; };
inline bool operator==(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] < y.a[0]; }
struct BfmePod32 { int a[8]; };
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] < y.a[0]; }
struct BfmePod36 { int a[9]; };
inline bool operator==(const BfmePod36 &x, const BfmePod36 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod36 &x, const BfmePod36 &y) { return x.a[0] < y.a[0]; }
struct BfmePod40 { int a[10]; };
inline bool operator==(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] < y.a[0]; }
struct BfmePod44 { int a[11]; };
inline bool operator==(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] < y.a[0]; }
struct BfmePod48 { int a[12]; };
inline bool operator==(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] < y.a[0]; }
struct BfmePod52 { int a[13]; };
inline bool operator==(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] < y.a[0]; }
struct BfmePod60 { int a[15]; };
inline bool operator==(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] < y.a[0]; }
struct BfmePod68 { int a[17]; };
inline bool operator==(const BfmePod68 &x, const BfmePod68 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod68 &x, const BfmePod68 &y) { return x.a[0] < y.a[0]; }
struct BfmePod76 { int a[19]; };
inline bool operator==(const BfmePod76 &x, const BfmePod76 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod76 &x, const BfmePod76 &y) { return x.a[0] < y.a[0]; }
struct BfmePod80 { int a[20]; };
inline bool operator==(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] < y.a[0]; }
struct BfmePod88 { int a[22]; };
inline bool operator==(const BfmePod88 &x, const BfmePod88 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod88 &x, const BfmePod88 &y) { return x.a[0] < y.a[0]; }
struct BfmePod92 { int a[23]; };
inline bool operator==(const BfmePod92 &x, const BfmePod92 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod92 &x, const BfmePod92 &y) { return x.a[0] < y.a[0]; }
struct BfmePod104 { int a[26]; };
inline bool operator==(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] < y.a[0]; }
struct BfmePod128 { int a[32]; };
inline bool operator==(const BfmePod128 &x, const BfmePod128 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod128 &x, const BfmePod128 &y) { return x.a[0] < y.a[0]; }
struct BfmePod144 { int a[36]; };
inline bool operator==(const BfmePod144 &x, const BfmePod144 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod144 &x, const BfmePod144 &y) { return x.a[0] < y.a[0]; }
struct BfmePod148 { int a[37]; };
inline bool operator==(const BfmePod148 &x, const BfmePod148 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod148 &x, const BfmePod148 &y) { return x.a[0] < y.a[0]; }
struct BfmePod160 { int a[40]; };
inline bool operator==(const BfmePod160 &x, const BfmePod160 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod160 &x, const BfmePod160 &y) { return x.a[0] < y.a[0]; }
struct BfmePod172 { int a[43]; };
inline bool operator==(const BfmePod172 &x, const BfmePod172 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod172 &x, const BfmePod172 &y) { return x.a[0] < y.a[0]; }
// _Construct<BfmePod172> has its own row (stlport_construct_pod172.cpp, 0x001EB9E6): declare that
// specialization so this unit calls it rather than emitting a second, duplicate copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod172, BfmePod172>(BfmePod172 *__p, const BfmePod172 &__val); }
struct BfmePod180 { int a[45]; };
inline bool operator==(const BfmePod180 &x, const BfmePod180 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod180 &x, const BfmePod180 &y) { return x.a[0] < y.a[0]; }
struct BfmePod216 { int a[54]; };
inline bool operator==(const BfmePod216 &x, const BfmePod216 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod216 &x, const BfmePod216 &y) { return x.a[0] < y.a[0]; }
struct BfmePod248 { int a[62]; };
inline bool operator==(const BfmePod248 &x, const BfmePod248 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod248 &x, const BfmePod248 &y) { return x.a[0] < y.a[0]; }
struct BfmePod252 { int a[63]; };
inline bool operator==(const BfmePod252 &x, const BfmePod252 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod252 &x, const BfmePod252 &y) { return x.a[0] < y.a[0]; }
struct BfmePod260 { int a[65]; };
inline bool operator==(const BfmePod260 &x, const BfmePod260 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod260 &x, const BfmePod260 &y) { return x.a[0] < y.a[0]; }
struct BfmePod340 { int a[85]; };
inline bool operator==(const BfmePod340 &x, const BfmePod340 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod340 &x, const BfmePod340 &y) { return x.a[0] < y.a[0]; }

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

template class _STL::vector<unsigned char, _STL::allocator<unsigned char> >;
template class _STL::vector<char, _STL::allocator<char > >;
template class _STL::vector<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::vector<BfmePod24, _STL::allocator<BfmePod24 > >;
template class _STL::vector<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::vector<BfmePod32, _STL::allocator<BfmePod32 > >;
template class _STL::vector<BfmePod36, _STL::allocator<BfmePod36 > >;
template class _STL::vector<BfmePod40, _STL::allocator<BfmePod40 > >;
template class _STL::vector<BfmePod44, _STL::allocator<BfmePod44 > >;
template class _STL::vector<BfmePod48, _STL::allocator<BfmePod48 > >;
template class _STL::vector<BfmePod52, _STL::allocator<BfmePod52 > >;
// This size-only view retains allocation and plain assignment operations.
template class _STL::allocator<BfmePod60>;
template BfmePod60* _STL::__copy<BfmePod60*, BfmePod60*, int>(
    BfmePod60*, BfmePod60*, BfmePod60*, const _STL::random_access_iterator_tag&, int*);
template BfmePod60* _STL::__copy_backward<BfmePod60*, BfmePod60*, int>(
    BfmePod60*, BfmePod60*, BfmePod60*, const _STL::random_access_iterator_tag&, int*);
template void _STL::fill<BfmePod60*, BfmePod60>(BfmePod60*, BfmePod60*, const BfmePod60&);
template class _STL::vector<BfmePod68, _STL::allocator<BfmePod68 > >;
template class _STL::vector<BfmePod76, _STL::allocator<BfmePod76 > >;
template class _STL::vector<BfmePod80, _STL::allocator<BfmePod80 > >;
template class _STL::vector<BfmePod88, _STL::allocator<BfmePod88 > >;
template class _STL::vector<BfmePod92, _STL::allocator<BfmePod92 > >;
template class _STL::vector<BfmePod104, _STL::allocator<BfmePod104 > >;
template class _STL::vector<BfmePod128, _STL::allocator<BfmePod128 > >;
template class _STL::vector<BfmePod144, _STL::allocator<BfmePod144 > >;
template class _STL::vector<BfmePod148, _STL::allocator<BfmePod148 > >;
template class _STL::vector<BfmePod160, _STL::allocator<BfmePod160 > >;
template class _STL::vector<BfmePod172, _STL::allocator<BfmePod172 > >;
template class _STL::vector<BfmePod180, _STL::allocator<BfmePod180 > >;
template class _STL::vector<BfmePod216, _STL::allocator<BfmePod216 > >;
template class _STL::vector<BfmePod248, _STL::allocator<BfmePod248 > >;
template class _STL::vector<BfmePod252, _STL::allocator<BfmePod252 > >;
// Only allocation and plain assignment are claimed for this size-only view.
template class _STL::allocator<BfmePod260>;
template BfmePod260* _STL::__copy<BfmePod260*, BfmePod260*, int>(
    BfmePod260*, BfmePod260*, BfmePod260*,
    const _STL::random_access_iterator_tag&, int*);
template class _STL::vector<BfmePod340, _STL::allocator<BfmePod340 > >;
// ??$__find@PAUBfmePod20@@U1@@_STL@@YAPAUBfmePod20@@PAU1@0ABU1@ABUrandom_access_iterator_tag@0@@Z @0x002194CC 118B
// Unrolled random-access __find over 20-byte elements comparing a[0]; caller
// 0x002198BE is the 27B find wrapper that becomes ready on landing.
template BfmePod20* _STL::__find(BfmePod20*, BfmePod20*, const BfmePod20&, const _STL::random_access_iterator_tag&);
// ??$find@PAUBfmePod20@@U1@@_STL@@YAPAUBfmePod20@@PAU1@0ABU1@@Z @0x002198AD 27B
// find wrapper over the rowed __find 0x002194CC via tag local; callers
// 0x0021EAA6 0x004EDD71.
template BfmePod20* _STL::find(BfmePod20*, BfmePod20*, const BfmePod20&);
// ??$__find@PAUBfmePod40@@U1@@_STL@@YAPAUBfmePod40@@PAU1@0ABU1@ABUrandom_access_iterator_tag@0@@Z @0x0040A68F 118B
// Unrolled random-access __find over 40-byte elements comparing a[0]; caller
// 0x0040A891 is the 27B find wrapper that becomes ready on landing.
template BfmePod40* _STL::__find(BfmePod40*, BfmePod40*, const BfmePod40&, const _STL::random_access_iterator_tag&);
// ??$find@PAUBfmePod40@@U1@@_STL@@YAPAUBfmePod40@@PAU1@0ABU1@@Z @0x0040A891 27B
// find wrapper over __find 0x0040A68F via tag local.
template BfmePod40* _STL::find(BfmePod40*, BfmePod40*, const BfmePod40&);
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
template BfmePod104* _STL::find(BfmePod104*, BfmePod104*, const BfmePod104&);
