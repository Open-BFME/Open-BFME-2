// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva00211541@Rva00211541@@QAEXPAVCreateAHeroData@@@Z, RVA 0x00211541, 47 bytes.
// Vector find-and-erase on +0x258 like Rva00223D02: rowed find 0x0020E873 then
// rowed voidptr erase 0x001FF51F. Evidence: caller 0x003FCE78 unclaimed.
#include <vector>
#include <algorithm>

class CreateAHeroData;

struct Rva00211541
{
	unsigned char m_pad[0x258];
	_STL::vector<CreateAHeroData *> m_vec; // +0x258
	void rva00211541(CreateAHeroData *val);
};

void Rva00211541::rva00211541(CreateAHeroData *val)
{
	_STL::vector<CreateAHeroData *>::iterator found = _STL::find(m_vec.begin(), m_vec.end(), val);
	if (found != m_vec.end())
		((_STL::vector<void *> *)&m_vec)->erase((void **)found);
}
