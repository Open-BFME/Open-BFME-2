// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva003FA681@Rva003FA681@@QAEXHABH@Z @0x003FA681 51B add Upgrades pair if science not present; calls rowed contains 0x003FA430 plus Upgrades ctor 0x003FA38C plus push_back 0x003FA5F4
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class CashHackSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		int m_science;
		int m_amount;
		Upgrades(int science, const int &amount);
	};
};

class Rva003FA430
{
public:
	bool rva003FA430(int science);
};

class Rva003FA681
{
public:
	int m_pad0;
	_STL::vector<CashHackSpecialPowerModuleData::Upgrades> m_vec;
	void rva003FA681(int science, const int &amount);
};

void Rva003FA681::rva003FA681(int science, const int &amount)
{
	if (((Rva003FA430 *)this)->rva003FA430(science))
		return;
	CashHackSpecialPowerModuleData::Upgrades tmp(science, amount);
	m_vec.push_back(tmp);
}
