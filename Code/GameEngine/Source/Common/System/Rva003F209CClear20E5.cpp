// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva003F20E5@Rva003F209C@@QAEXHH@Z retail 0x003F20E5 33B: clear via rowed rva003F209C plus zero dword at +0x17C plus zero byte at +0x1A3 plus pin rva003F076D. Evidence: caller 0x0020FB72 plus rowed callee 0x003F209C plus pin 0x003F076D plus same vector layout as Rva003F209CClear.
#include <vector>

enum ScienceType
{
	SCIENCE_DUMMY = 0
};

class Rva003F209C
{
public:
	void rva003F209C();
	void rva003F20E5(int a1, int a2);

private:
	char _pad[0x164];
	_STL::vector<ScienceType> m_vec164;
	char _pad170[0x17C - 0x170];
	int m_17C;
	char _pad180[0x1A3 - 0x180];
	bool m_1A3;
};

class Rva003F076D
{
public:
	void rva003F076D();
};

void Rva003F209C::rva003F20E5(int, int)
{
	rva003F209C();
	m_17C = 0;
	m_1A3 = false;
	((Rva003F076D *)this)->rva003F076D();
}
