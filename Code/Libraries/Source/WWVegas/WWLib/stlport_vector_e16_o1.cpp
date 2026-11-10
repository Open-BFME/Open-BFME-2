// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site.
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
#include "../../../Include/Lib/BfmeE16.h"
// Native stride-16 range copies construct through the rowed 0x0052C404 helper.
void Rva0052C404Construct(void *, const void *);
namespace _STL {
template <> inline BfmeE16 *__uninitialized_copy<const BfmeE16 *, BfmeE16 *>(
    const BfmeE16 *first, const BfmeE16 *last, BfmeE16 *result, const __false_type &)
{
    BfmeE16 *cur = result;
    for (; first != last; ++first, ++cur)
        Rva0052C404Construct(cur, first);
    return cur;
}
// Assignment is not used by this instantiation's rowed members.
template <> vector<BfmeE16> &vector<BfmeE16>::operator=(const vector<BfmeE16> &);
}

// Native parent 52D555 copies its nontrivial stride-16 member at +90.
class Rva004E1A04 {
public:
    ~Rva004E1A04();
private:
    char m_data[16];
};
namespace _STL {
template <> vector<BfmeE16>::vector(const vector<BfmeE16> &);
template <> inline Rva004E1A04 *__uninitialized_copy<const Rva004E1A04 *, Rva004E1A04 *>(
    const Rva004E1A04 *first, const Rva004E1A04 *last, Rva004E1A04 *result, const __false_type &)
{
    Rva004E1A04 *cur = result;
    for (; first != last; ++first, ++cur)
        Rva0052C404Construct(cur, first);
    return cur;
}
}
template _STL::vector<Rva004E1A04>::vector(const _STL::vector<Rva004E1A04> &);

// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmeE16, BfmeE16>(BfmeE16 *, BfmeE16 const &); }
namespace _STL { template <> void vector<BfmeE16, allocator<BfmeE16> >::_M_fill_insert(BfmeE16 *, unsigned int, BfmeE16 const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$uninitialized_fill_n@PAUBfmeE16@@IU1@@_STL@@YAPAUBfmeE16@@PAU1@IABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE16;
namespace _STL { template <> BfmeE16 * uninitialized_fill_n<BfmeE16 *,unsigned int,BfmeE16>(BfmeE16 *,unsigned int,BfmeE16 const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAUBfmeE16@@PAU1@@_STL@@YAPAUBfmeE16@@PAU1@00ABU__false_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE16;
namespace _STL { template <> BfmeE16 * __uninitialized_copy<BfmeE16 *,BfmeE16 *>(BfmeE16 *,BfmeE16 *,BfmeE16 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAUBfmeE16@@IU1@@_STL@@YAPAUBfmeE16@@PAU1@IABU1@ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE16;
namespace _STL { template <> BfmeE16 * __uninitialized_fill_n<BfmeE16 *,unsigned int,BfmeE16>(BfmeE16 *,unsigned int,BfmeE16 const &,__false_type const &); }
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// The verified reserve at 0x0022118F supplies the native allocator/copy
// chain. Declaring it here avoids this EH-profile's competing helper copy.
namespace _STL {
template <> void vector<BfmeE16, allocator<BfmeE16> >::reserve(unsigned int);
}
template class _STL::vector<BfmeE16, _STL::allocator<BfmeE16 > >;
template BfmeE16 *_STL::__copy<const BfmeE16 *, BfmeE16 *, int>(
    const BfmeE16 *, const BfmeE16 *, BfmeE16 *, const _STL::random_access_iterator_tag &, int *);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0?$_Vector_base@VRva004BA1C8@@V?$allocator@VRva004BA1C8@@@_STL@@@_STL@@QAE@ABV?$allocator@VRva004BA1C8@@@1@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
#pragma comment(linker, "/alternatename:??0?$_Vector_base@VRva00297360Element@@V?$allocator@VRva00297360Element@@@_STL@@@_STL@@QAE@ABV?$allocator@VRva00297360Element@@@1@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
#pragma comment(linker, "/alternatename:??0?$_Vector_base@UQuantityModifier@@V?$allocator@UQuantityModifier@@@_STL@@@_STL@@QAE@ABV?$allocator@UQuantityModifier@@@1@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
#pragma comment(linker, "/alternatename:??0AICommandCoordVector@@QAE@ABUAICommandCoordAlloc@@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")

// Existing uint consumers call the same empty-base fold at 00211E58. Emit
// its complete native body here so link selection has a certified provider.
template _STL::_Vector_base<unsigned int, _STL::allocator<unsigned int> >::_Vector_base(
    const _STL::allocator<unsigned int> &);
