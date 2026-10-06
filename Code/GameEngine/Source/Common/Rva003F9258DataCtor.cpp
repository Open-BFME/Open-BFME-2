// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva003F9258Data@@QAE@XZ @0x003F8DF8 40B.
// Default ctor: member at +4 via rowed Rva00330757Member 0x00330757,
// vector<BfmeE16> at +0x14 via rowed Vector_base 0x00211E58, vptr
// 0x0083731C at +0 and byte 0 at +0x20. Layout from retail (member
// 0x10 bytes so vector lands at +0x14) and caller 0x003F9278 in
// Rva003F9258Siblings.cpp. Flags copied from Rva003F8ED6Ctor sibling.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva00330757Member
{
public:
	Rva00330757Member();
private:
	char m_pad[0x10];
};

struct Rva003F9258DataBase
{
	Rva003F9258DataBase() : m_00() {}
	Rva00330757Member m_00;
};

class Rva003F9258Data : public Rva003F9258DataBase
{
public:
	Rva003F9258Data();
	virtual ~Rva003F9258Data();
private:
	_STL::vector<BfmeE16> m_14;
	bool m_20;
};

Rva003F9258Data::Rva003F9258Data()
	: Rva003F9258DataBase()
	, m_14()
	, m_20(false)
{
}
