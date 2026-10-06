// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva003F20B0@Rva003F20B0@@QAEXXZ retail 0x003F20B0 53B
// Clears the ScienceType vector at +0x158 via the rowed ScienceType erase
// at 0x00532803 then zeroes three dwords at +0x14c/+0x150/+0x154 and two
// bytes at +0x1a0/+0x1a1. Evidence: retail bytes; callee row
// ?erase@?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@QAEPAW4ScienceType@@PAW43@0@Z;
// caller 0x003F3F27 same-this clear chain; honest address name.
#include <vector>

enum ScienceType
{
	SCIENCE_0 = 0
};

class Rva003F20B0
{
public:
	void rva003F20B0();

private:
	unsigned char m_pad00[0x14C];
	int m_14C;
	int m_150;
	int m_154;
	_STL::vector<ScienceType> m_vec158;
	unsigned char m_pad164[0x1A0 - 0x164];
	bool m_1A0;
	bool m_1A1;
};

// ?rva003F20B0@Rva003F20B0@@QAEXXZ
void Rva003F20B0::rva003F20B0()
{
	m_vec158.clear();
	m_14C = 0;
	m_150 = 0;
	m_154 = 0;
	m_1A0 = false;
	m_1A1 = false;
}
