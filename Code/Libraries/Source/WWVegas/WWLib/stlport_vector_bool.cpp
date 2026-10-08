// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

// RVA6D52A has a verified external provider; do not offer a wrong incidental copy.
namespace _STL { template<> void vector<bool>::clear(); }

template class _STL::vector<bool, _STL::allocator<bool> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Gen_dtor_007f6d20@@QAE@XZ=??0?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@_STL@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?m@Gen_00800280@@QAEPAXXZ=??0?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@_STL@@QAE@XZ")
