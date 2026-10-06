// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
//
// Westwood WWLib SimpleVecClass / SimpleDynVecClass members (this
// directory's simplevec.h) for a placeholder 4-byte element, each
// placed by a single masked whole-.text hit whose own bytes carry the element
// size. BfmePod4 stands for the real 4-byte element folded here (any POD of
// that size compiles the same). No retail caller is claimed.
#include "always.h"
#include "simplevec.h"
struct BfmePod4 { int a[1]; };
inline bool operator==(const BfmePod4 &x, const BfmePod4 &y) { return x.a[0] == y.a[0]; }
inline bool operator!=(const BfmePod4 &x, const BfmePod4 &y) { return x.a[0] != y.a[0]; }
template class SimpleVecClass<BfmePod4>;
template class SimpleDynVecClass<BfmePod4>;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Grow@?$SimpleDynVecClass@VVector3@@@@QAE_NH@Z=?Grow@?$SimpleDynVecClass@UBfmePod4@@@@IAE_NH@Z")
