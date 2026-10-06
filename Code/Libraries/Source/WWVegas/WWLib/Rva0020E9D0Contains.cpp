// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0020E9D0@Rva0020E9D0@@QAE_NPAVCreateAHeroData@@@Z, retail 0x0020E9D0,
// 34 bytes. Contains check over vector at +0x2C/+0x30 via rowed find
// 0x0020E873 returning find != end. Caller at 0x0020F116.
#include <vector>

class CreateAHeroData;

class Rva0020E9D0
{
public:
	bool rva0020E9D0(CreateAHeroData *p);

private:
	unsigned char m_pad[0x2C];
	_STL::vector<CreateAHeroData *> m_vec;
};

bool Rva0020E9D0::rva0020E9D0(CreateAHeroData *p)
{
	return _STL::find(m_vec.begin(), m_vec.end(), p) != m_vec.end();
}
