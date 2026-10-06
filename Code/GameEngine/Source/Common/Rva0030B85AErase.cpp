// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B85A@Rva0030B92C@@QAEXH@Z @0x0030B85A 28B
// Erase vector element by index via rowed Pod8 erase then set flag 1.
// Evidence: lea [eax+ecx*8] then rowed erase 0x00054B3F; flag 0x24=1; caller 0x00330B1E; same layout as 0x0030B92C.
#include <vector>
struct BfmePod8 { float x; float y; };
struct Rva0030B92C
{
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > m_vec;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
	unsigned char m_24;
	void rva0030B85A(int i);
};
void Rva0030B92C::rva0030B85A(int i)
{
	m_vec.erase(m_vec.begin() + i);
	m_24 = 1;
}
