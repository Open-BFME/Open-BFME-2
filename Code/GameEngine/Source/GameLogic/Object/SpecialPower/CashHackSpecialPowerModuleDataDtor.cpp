// cl: /O1 /MD /DNDEBUG /arch:SSE /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??1CashHackSpecialPowerModuleData@@UAE@XZ, retail 0x004C28DD, 59 bytes.
// Vector dtor over the matched ctor 0x004C2889 layout (0x7C base plus vector
// at +0x7C plus int at +0x88 for 0x8C total): frees the vector buffer through
// _free at 0x00030830 then calls the SpecialPower base dtor at 0x0049334F.
// BFME1 donor: CashHackSpecialPowerModuleDataDestructorThunk.cpp (vector plus
// out-of-line base call with novtable suppressing the vptr store). Identity:
// vtable 0x00C5C688 installed by the ctor plus the ??_G caller at 0x004C28C1
// (slot 0) plus table 0x00C5C724 plus factory 0x0025197B news 0x8C.
#include <vector>

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
};

struct CashHackUpgrades
{
	int m_science;
	int m_amountToSteal;
};

class __declspec(novtable) CashHackSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~CashHackSpecialPowerModuleData();

private:
	_STL::vector<CashHackUpgrades> m_upgrades; // +0x7C
	int m_defaultAmountToSteal; // +0x88
};

CashHackSpecialPowerModuleData::~CashHackSpecialPowerModuleData()
{
}
