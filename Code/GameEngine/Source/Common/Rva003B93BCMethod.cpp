// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003B93BC@Rva003B93BC@@QAEPAUBfmePod104@@XZ retail 0x003B93BC 68 bytes.
// Leaf: temp 0x68 via rowed ctor 0x0040E3EE push into vector at +0x20 via
// rowed 0x003B9369 destroy via pinned 0x0040E499 return last element.
// Evidence: callees rowed/pinned; caller 0x0040F0FA; BfmePod104 stride 0x68.
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

struct BfmePod104
{
	int a[26];
};

class ArmySummary
{
public:
	ArmySummary();
	virtual ~ArmySummary();
private:
	char m_pad[0x64];
};

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
