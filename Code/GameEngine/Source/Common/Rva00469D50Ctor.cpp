// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??0Rva00469D50@@QAE@XZ 0x00469D50 54B evidence: caller 0x0046F39E news 0x10 then sets Target at +0 Result at +4 via set and parses InitiateVoice audio token at +8; callee row ??0Upgrades@CashHackSpecialPowerModuleData@@QAE@XZ 0x004CEE6E shared -1/0 fold also pinned as InitiateVoiceEntry
#include "ascii_string.h"

class CashHackSpecialPowerModuleData
{
public:
	class Upgrades
	{
	public:
		Upgrades();
	};
};

class Rva00469D50
{
public:
	Rva00469D50();
private:
	AsciiString m_00;
	AsciiString m_04;
	CashHackSpecialPowerModuleData::Upgrades m_08;
};

Rva00469D50::Rva00469D50()
{
}
