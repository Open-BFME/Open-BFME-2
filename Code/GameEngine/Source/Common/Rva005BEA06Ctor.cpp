// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005BEA06@@QAE@XZ @0x005BEA06 28B
// Evidence: unlock ctor clears +0x00 then vector<ushort> +0x04 with 3 via rowed 0x002339F3 clears +0x10 +0x14 returns this; caller 0x0052038A; precedent Rva0058062BCtor same vector init list.
#include <vector>

class Rva005BEA06
{
public:
	Rva005BEA06();
private:
	void *m_00;
	_STL::vector<unsigned short> m_04;
	int m_10;
	bool m_14;
};

Rva005BEA06::Rva005BEA06() : m_00(0), m_04(3), m_10(0), m_14(false)
{
}
