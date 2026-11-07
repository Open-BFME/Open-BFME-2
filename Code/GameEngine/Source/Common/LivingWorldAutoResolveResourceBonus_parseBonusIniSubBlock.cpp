// cl: /Oy- /DNDEBUG /MD /GX-
// LivingWorldAutoResolveResourceBonus::parseBonusIniSubBlock (WorldBuilder name, lines 44..45: initFromINI then the MinResourceBonus check).
// was ?rva00413DCC@Rva00413DCC@@QAEXPAVINI@@@Z @0x00413DCC 65B
// INI parse validator: initFromINI(this) through table 0x00839E58 (rowed
// 0x0002DE78), then throw INIException code 3 with the retail message when
// the int at +0 is negative. Same recipe as Rva004135CDParse (filler
// 0x0002F681 plus CxxThrow 0x00629094 plus throwinfo anchor 0x00CFE2FC).
// Evidence: unlock lane; caller 0x00414009; packet message; drain sibling of
// 0x004135CD.
class INI;
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
// Retail's field table at VA 0x00C39E58 (.rdata, 64 bytes), transcribed from
// retail's own bytes: three records plus the null terminator.
extern const FieldParse ResourceBonusFieldParse[] =
{
	{ "MinResourceBonus", &INI::parseInt,  0, 0x0 },
	{ "WeaponMultiplier", &INI::parseReal, 0, 0x4 },
	{ "ArmorMultiplier",  &INI::parseReal, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
class LivingWorldAutoResolveResourceBonus
{
public:
	void parseBonusIniSubBlock(INI *ini);
private:
	int m_value00;
};
// was ?rva00413DCC@Rva00413DCC@@QAEXPAVINI@@@Z
void LivingWorldAutoResolveResourceBonus::parseBonusIniSubBlock(INI *ini)
{
	ini->initFromINI(this, ResourceBonusFieldParse);
	if (m_value00 < 0)
	{
		throw INIException(3, "Must provide a MinResourceBonus, and it must be >= 0");
	}
}
