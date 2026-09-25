// Target boundary 0x0030E7FE/225 has the STLport vector fill-insert contract:
// ECX is the vector (start/finish/end at +0/+4/+8), and stack args are position,
// count, and value. Retail uses a 4-byte stride, __copy_trivial / backward-copy,
// a 4-byte fill helper, and overflow worker 0x002DFCF6 on growth.
//
// Element identity is unresolved. Rva0030E7FEElement is an address-derived
// emitter alias; its underlying `float` spelling is used only because VC7.1
// emits the target's MOVSS bit-copy shape for this 4-byte value. This does NOT
// claim that the application's element is a float (or Drawable*, ModuleData*,
// or any other app type).
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
#include <vector>

typedef float Rva0030E7FEElement;

template void _STL::vector<Rva0030E7FEElement>::_M_fill_insert(
	Rva0030E7FEElement *, unsigned int, const Rva0030E7FEElement &);
