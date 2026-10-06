// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004DFB55@Rva004DFB55@@QAEXPAVCreateAHeroData@@@Z @0x004DFB55 41B.
// Vector find-and-erase on vector<CreateAHeroData*> at this+0x2c via rowed
// find 0x0020E873 and rowed voidptr erase 0x001FF51F. Evidence: same shape as
// Rva0025BF8CHeroRemover (find+erase on CreateAHeroData* vector) but frameless
// and void return; callers at 0x004EA39B 0x00597BBD 0x005990D5 pass this-0xc
// as the element and the rva002A8F24 result as this; First at +0x2c End at
// +0x30 prove the vector base. Erase binds to the rowed voidptr opt since all
// 4-byte pointer vectors share layout; find stays typed for CreateAHeroData.
#include <vector>
#include <algorithm>

class CreateAHeroData;

class Rva004DFB55
{
private:
	char m_pad[0x2c];
	_STL::vector<CreateAHeroData *> m_vec2c; // +0x2c First +0x30 Last
public:
	void rva004DFB55(CreateAHeroData *p);
};

void Rva004DFB55::rva004DFB55(CreateAHeroData *p)
{
	_STL::vector<CreateAHeroData *>::iterator it =
		_STL::find(m_vec2c.begin(), m_vec2c.end(), p);
	if (it != m_vec2c.end()) {
		((_STL::vector<void *> *)&m_vec2c)->erase((void **)it);
	}
}
