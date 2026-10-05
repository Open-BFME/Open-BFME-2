// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003B93BC@Rva003B93BC@@QAEPAUBfmePod104@@XZ retail 0x003B93BC 68 bytes.
// Leaf: temp 0x68 via rowed ctor 0x0040E3EE push into vector at +0x20 via
// rowed 0x003B9369 destroy via pinned 0x0040E499 return last element.
// Evidence: callees rowed/pinned; caller 0x0040F0FA; BfmePod104 stride 0x68.
#include <vector>

struct BfmePod104
{
	int a[26];
};

class Rva0040E3EE
{
public:
	Rva0040E3EE();
	virtual ~Rva0040E3EE();
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
	m_20.push_back(*(const BfmePod104 *)&Rva0040E3EE());
	return &m_20.back();
}
