// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0040AF1D@@QAE@XZ @ 0x0040AF1D 73B: default ctor for class at 0x0040AF66 family
// vectors at +0x4/+0x10 (BfmeE16) plus 0x1C-byte members at +0x1C/+0x38 plus
// zeros at +0x0/+0x54/+0x58/+0x5C/+0x60 and byte +0x64. Evidence: adjacent copy
// ctor 0x0040AF66 plus rowed Vector_base 0x00211E58 plus rowed member ctor
// 0x0024C7B3 plus caller 0x0040BC7C.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member() throw();
	unsigned char m_data[0x1C];
};

class Rva0040AF1D
{
public:
	Rva0040AF1D();

private:
	int m_0000;
	_STL::vector<BfmeE16> m_0004;
	_STL::vector<BfmeE16> m_0010;
	Rva0024C7B3Member m_001C;
	Rva0024C7B3Member m_0038;
	int m_0054;
	int m_0058;
	int m_005C;
	int m_0060;
	unsigned char m_0064;
};

Rva0040AF1D::Rva0040AF1D()
	: m_0000(0)
	, m_0004()
	, m_0010()
	, m_001C()
	, m_0038()
	, m_0054(0)
	, m_0058(0)
	, m_005C(0)
	, m_0060(0)
	, m_0064(0)
{
}
