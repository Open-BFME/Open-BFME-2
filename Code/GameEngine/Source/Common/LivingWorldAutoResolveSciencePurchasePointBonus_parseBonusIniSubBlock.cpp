// cl: /Oy- /DNDEBUG /MD /GX-
// LivingWorldAutoResolveSciencePurchasePointBonus::parseBonusIniSubBlock (WorldBuilder name, lines 44..45: initFromINI then the MinSciencePurchasePointsForBonus check).
// was ?rva004135CD@Rva004135CD@@QAEXPAVINI@@@Z @0x004135CD 65B
// INI parse validator: initFromINI(this) through table 0x00839A78 (rowed
// 0x0002DE78), then throw INIException code 3 with the retail message when
// the int at +0 is negative. Throw idiom (filler 0x0002F681 plus CxxThrow
// 0x00629094 plus throwinfo anchor 0x00CFE2FC) from RankInfoParse. Evidence:
// unlock lane; caller 0x004138C7 (Duplicate message sibling in string_xrefs);
// string_xrefs full message; prev/next Common TUs.
class INI;
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
// Retail's field table at VA 0x00C39A78 (.rdata, 64 bytes), transcribed from
// retail's own bytes: three records plus the null terminator.
extern const FieldParse SciencePurchasePointBonusFieldParse[] =
{
	{ "MinSciencePurchasePointsForBonus", &INI::parseInt,  0, 0x0 },
	{ "WeaponMultiplier",                 &INI::parseReal, 0, 0x4 },
	{ "ArmorMultiplier",                  &INI::parseReal, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
class LivingWorldAutoResolveSciencePurchasePointBonus
{
public:
	void parseBonusIniSubBlock(INI *ini);
private:
	int m_value00;
};
// was ?rva004135CD@Rva004135CD@@QAEXPAVINI@@@Z
void LivingWorldAutoResolveSciencePurchasePointBonus::parseBonusIniSubBlock(INI *ini)
{
	ini->initFromINI(this, SciencePurchasePointBonusFieldParse);
	if (m_value00 < 0)
	{
		throw INIException(3, "Must provide a MinSciencePurchasePointsForBonus, and it must be >= 0");
	}
}
