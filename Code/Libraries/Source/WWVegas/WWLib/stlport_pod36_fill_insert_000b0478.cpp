// cl: /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_fill_insert@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QAEXPAUBfmePod36@@IABU3@@Z @0x000B0478 232B. vector<BfmePod36> fill-insert false_type path.
// Evidence: rowed Pod36 helpers 0x000ADEA8 0x000ADEEB plus overflow 0x000AFF6B; StringRecord helpers 0x000ADECE 0x000AD806 share 0x24 stride; /Ob0 keeps copy-backward wrapper and /G7 fixes registers vs O1 sibling.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct BfmePod36 { int a[9]; };

template void _STL::vector<BfmePod36>::_M_fill_insert(
	BfmePod36 *, unsigned int, const BfmePod36 &);
