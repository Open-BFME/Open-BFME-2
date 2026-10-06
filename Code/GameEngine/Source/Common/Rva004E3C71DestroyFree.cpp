// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004E3C71@Rva004E3C71@@QAEXXZ, retail 0x004E3C71, 30 bytes.
// Evidence: destroy Rva004E2382 range [begin,end) at +0/+4 via rowed _Destroy 0x004E377E then free begin via rowed _free 0x00030830; caller 0x004E3DE8; neighbours 0x004E3C32 vector dtor and 0x004E3CD0 parent dtor.
#include <vector>

class Rva004E2382
{
public:
	~Rva004E2382();
private:
	char m_pad[32];
};

extern "C" void __cdecl free(void *block);

class Rva004E3C71
{
	Rva004E2382 *m_00;
	Rva004E2382 *m_04;
public:
	void rva004E3C71();
};

void Rva004E3C71::rva004E3C71()
{
	_STL::_Destroy(m_00, m_04);
	Rva004E2382 *b = m_00;
	if (b != 0)
		free(b);
}
