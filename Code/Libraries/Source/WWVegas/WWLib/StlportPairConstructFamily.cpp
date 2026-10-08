// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport _Construct<pair<const int, T>, ...> placement copies (45 bytes:
// EH-guarded placement new calling the pair's out-of-line copy constructor)
// for four int-keyed hash maps whose _M_new_node rows already pin these
// names at these addresses (stlport_pod_hash_bodies.cpp views), with the
// flags of StlportConstructFamily.cpp, whose 45-byte shape these share.
// The mapped records are declared with just the copy constructor the pair
// copy calls; only their sizes are claimed.
//
//   _Construct  _M_new_node  pair copy   mapped view
//   0x002E00CC  0x002E0273   0x002DFD82  BfmePod72
//   0x00418985  0x004189ED   0x0041890F  BfmePod32
//   0x004192A4  0x0041930C   0x0041922E  BfmePod20
//   0x0041985E  0x004198C6   0x004197E8  BfmePod60
//
// The BfmePod72 pair copy at 0x002DFD82 (first int, then the record's copy
// constructor at 0x002DFC1B) is this unit's own implicit copy and is landed
// from it too; the other three pair copies copy string members differently
// and stay pinned only.
#include <memory>
#include <utility>

struct BfmePod72 { int a[18]; BfmePod72(const BfmePod72 &); };
struct BfmePod32 { int a[8]; BfmePod32(const BfmePod32 &); };
struct BfmePod20 { int a[5]; BfmePod20(const BfmePod20 &); };
struct BfmePod60 { int a[15]; BfmePod60(const BfmePod60 &); };

typedef _STL::pair<const int, BfmePod72> IntPod72Pair;
typedef _STL::pair<const int, BfmePod32> IntPod32Pair;
typedef _STL::pair<const int, BfmePod20> IntPod20Pair;
typedef _STL::pair<const int, BfmePod60> IntPod60Pair;

template void _STL::_Construct<IntPod72Pair, IntPod72Pair>(IntPod72Pair *, const IntPod72Pair &);
template void _STL::_Construct<IntPod20Pair, IntPod20Pair>(IntPod20Pair *, const IntPod20Pair &);
template void _STL::_Construct<IntPod60Pair, IntPod60Pair>(IntPod60Pair *, const IntPod60Pair &);
template _STL::pair<const int, BfmePod72>::pair(const int &, const BfmePod72 &);
