// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0041E732@@QAE@XZ @0x0041E732 50B: honest ctor over 3 dwords plus two vectors.
// Retail zeroes +0/+4/+8, constructs vector at +0xC, sets byte +0x18 to 1,
// constructs vector at +0x1C and returns this. No vtable, no base, no EH.
// Both vectors bind the rowed Vector_base BfmeE16 0x00211E58 (ICF-folded
// stand-in; any 12B Vector_base emits the same call). Caller new(0x28) at
// 0x0041EC84 proves the 0x28 size; init order in the list reproduces the
// retail store/call order. Evidence: callers at 0x0041EC90, prev/next rows.

#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva0041E732
{
public:
	Rva0041E732();
private:
	int m_a;
	int m_b;
	int m_c;
	_STL::vector<BfmeE16> m_vec1;
	bool m_flag;
	char m_pad[3];
	_STL::vector<BfmeE16> m_vec2;
};

Rva0041E732::Rva0041E732() : m_a(0), m_b(0), m_c(0), m_flag(true)
{
}
