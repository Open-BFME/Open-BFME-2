// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030BAA0@Rva0030BAA0@@QAEXHABUBfmeE8@@@Z, retail 0x0030BAA0, 56 bytes.
// Holder set via size check then rowed push 0x0030BA8C for append else direct 8B copy plus flag at +0x24.
// Evidence: chain from 0x0030BA8C; caller 0x00330AE6; prev push same flags next Disp8Lea no-flags.
#include <vector>
struct BfmeE8 { int a[2]; };
struct Rva0030BA8C
{
	void rva0030BA8C(const BfmeE8 &val);
};

struct Rva0030BAA0
{
	void rva0030BAA0(int i, const BfmeE8 &val);
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_vec;
	char m_pad[0x24 - 12];
	bool m_flag;
};

void Rva0030BAA0::rva0030BAA0(int i, const BfmeE8 &val)
{
	if (i == (int)m_vec.size()) {
		((Rva0030BA8C *)this)->rva0030BA8C(val);
		return;
	}
	m_vec[i] = val;
	m_flag = true;
}
