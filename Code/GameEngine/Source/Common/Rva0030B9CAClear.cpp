// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B9CA@Rva0030B9CA@@QAEXXZ, retail 0x0030B9CA, 19 bytes.
// Holder clear via rowed vector Pod8 erase 0x003FA4DB plus flag at +0x24 set to 1.
// Evidence: caller 0x00330B34; prev reserve vector e8 /O1 /EHsc next Disp8Lea no-flags.
#include <vector>
struct BfmePod8 { int a[2]; };

struct Rva0030B9CA
{
	void rva0030B9CA();
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > m_vec;
	char m_pad[0x24 - 12];
	bool m_flag;
};

void Rva0030B9CA::rva0030B9CA()
{
	m_vec.erase(m_vec.begin(), m_vec.end());
	m_flag = true;
}
