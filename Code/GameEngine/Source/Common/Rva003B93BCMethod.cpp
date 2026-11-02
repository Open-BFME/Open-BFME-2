// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003B93BC@Rva003B93BC@@QAEPAUBfmePod104@@XZ retail 0x003B93BC 68 bytes.
// Leaf: temp 0x68 via rowed ctor 0x0040E3EE push into vector at +0x20 via
// rowed 0x003B9369 destroy via pinned 0x0040E499 return last element.
// Evidence: callees rowed/pinned; caller 0x0040F0FA; BfmePod104 stride 0x68.
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
// Suppress this TU's non-retail copy of ??$_Construct@UBfmePod104@@U1@@_STL@@YAXPAUBfmePod104@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod104;
namespace _STL { template <> void _Construct<BfmePod104,BfmePod104>(BfmePod104 *,BfmePod104 const &); }
// Suppress this TU's non-retail copy of ?push_back@?$vector@UBfmePod104@@V?$allocator@UBfmePod104@@@_STL@@@_STL@@QAEXABUBfmePod104:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod104;
namespace _STL { template <> void vector<BfmePod104,allocator<BfmePod104> >::push_back(BfmePod104 const &); }

// The overflow body is supplied by StlportVectorInsertOverflowFamily.cpp.
struct BfmePod104;
namespace _STL {
template <> void vector<BfmePod104, allocator<BfmePod104> >::_M_insert_overflow(BfmePod104 *, const BfmePod104 &, const __false_type &, unsigned int, bool);
}

struct BfmePod104
{
	int a[26];
};

#include "../../Include/GameLogic/ArmySummary.h"

class Rva003B93BC
{
public:
	BfmePod104 *rva003B93BC();
private:
	char m_pad[0x20];
	_STL::vector<BfmePod104> m_20;
};

BfmePod104 *Rva003B93BC::rva003B93BC()
{
	m_20.push_back(*(const BfmePod104 *)&ArmySummary());
	return &m_20.back();
}
