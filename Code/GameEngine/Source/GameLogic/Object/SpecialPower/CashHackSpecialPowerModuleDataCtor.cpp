// cl: /O1 /MD /DNDEBUG /arch:SSE /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0CashHackSpecialPowerModuleData@@QAE@XZ, retail 0x004C2889, 56 bytes.
// SpecialPower-side ModuleData for the CashHack power: 0x7C-byte base built
// by the out-of-line 0x004930A0 constructor (pinned as Rva004930A0), vector
// of Upgrades at +0x7C built through the folded Vector_base at 0x211E58,
// cleared through erase at 0x3FA4DB, and default amount at +0x88. Table
// 0xC5C724 carries UpgradeMoneyAmount at +0x7C and MoneyAmount at +0x88;
// factory 0x251957 news 0x8C with this ctor as sole caller. Row supersedes
// the ctor pin.
#include <vector>

class Rva004930A0
{
public:
	Rva004930A0();
	virtual ~Rva004930A0();

private:
	unsigned char m_pad[0x7C - 4];
};

struct CashHackUpgrades
{
	int m_science;
	int m_amountToSteal;
};

class CashHackSpecialPowerModuleData : public Rva004930A0
{
public:
	CashHackSpecialPowerModuleData();
	virtual ~CashHackSpecialPowerModuleData() {}

private:
	_STL::vector<CashHackUpgrades> m_upgrades; // +0x7C
	int m_defaultAmountToSteal; // +0x88
};

// ??0CashHackSpecialPowerModuleData@@QAE@XZ @0x4C2889
CashHackSpecialPowerModuleData::CashHackSpecialPowerModuleData()
	: Rva004930A0()
{
	m_upgrades.clear();
	m_defaultAmountToSteal = 0;
}
