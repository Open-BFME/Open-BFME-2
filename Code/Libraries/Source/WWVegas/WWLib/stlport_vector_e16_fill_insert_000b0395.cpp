// cl: /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_fill_insert@?$vector@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAEXPAUBfmeE16@@IABU3@@Z @0x000B0395 227B. vector<BfmeE16> fill-insert POD false_type path.
// Evidence: rowed BfmeE16 helpers 0x000ADE67 0x005B2B1E 0x004218D5 0x000ADE8D plus overflow 0x005B3970; /Ob0 keeps copy-backward wrapper and /G7 fixes registers vs o1 sibling.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
template void _STL::vector<BfmeE16>::_M_fill_insert(
	BfmeE16 *, unsigned int, const BfmeE16 &);
