// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva003FA430@Rva003FA430@@QAE_NH@Z @0x003FA430 52B search Upgrades vector at +4 for science match; caller 0x003FA681 constructs Upgrades and push_back if not found
#include <vector>

struct CashHackUpgradesPod
{
	int m_science;
	int m_amount;
};

class Rva003FA430
{
public:
	int m_pad0;
	_STL::vector<CashHackUpgradesPod> m_vec;
	bool rva003FA430(int science);
};

bool Rva003FA430::rva003FA430(int science)
{
	for (unsigned int i = 0; i < m_vec.size(); ++i)
	{
		if (m_vec[i].m_science == science)
			return true;
	}
	return false;
}
