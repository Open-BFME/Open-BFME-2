// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva003F1241@Rva003F1241@@QAE?AVUnicodeString@@XZ retail 0x003F1241 767B
// Evidence: LINK BONUS via 0x003F15D1; callers at 0x002BA700 0x003F1629 0x003F171E; strings LW:ListSeparator LW:RegionBonusArmy LW:RegionAttackBonus LW:RegionDefenseBonus LW:RegionExperienceBonus LW:RegionBonusResource LW:RegionLegendaryBonus LW:NoBonus via rowed fetch slot 0x3C; rowed set 0x37150 release 0x36E70 concat 0x6A2A format 0x6CB660 copyctor 0x37050; prev 0x003F11EC next 0x003F1540.
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class Rva003F1241
{
public:
	UnicodeString rva003F1241();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

UnicodeString Rva003F1241::rva003F1241()
{
	UnicodeString result;
	UnicodeString tmp;
	UnicodeString sep = TheGameText->fetch("LW:ListSeparator");
	int n = 0;
	if (m_08 > 0) {
		n++;
		tmp.set(TheGameText->fetch("LW:RegionBonusArmy"));
		tmp.format(&tmp, m_08);
		result.concat(tmp);
	}
	if (m_10 > 0) {
		if (n++ > 0)
			result.concat(sep);
		tmp.set(TheGameText->fetch("LW:RegionAttackBonus"));
		tmp.format(&tmp, m_10);
		result.concat(tmp);
	}
	if (m_14 > 0) {
		if (n++ > 0)
			result.concat(sep);
		tmp.set(TheGameText->fetch("LW:RegionDefenseBonus"));
		tmp.format(&tmp, m_14);
		result.concat(tmp);
	}
	if (m_18 > 0) {
		if (n++ > 0)
			result.concat(sep);
		tmp.set(TheGameText->fetch("LW:RegionExperienceBonus"));
		tmp.format(&tmp, m_18);
		result.concat(tmp);
	}
	if (m_04 > 0) {
		if (n++ > 0)
			result.concat(sep);
		tmp.set(TheGameText->fetch("LW:RegionBonusResource"));
		tmp.format(&tmp, m_04);
		result.concat(tmp);
	}
	if (m_0C > 0) {
		if (n > 0)
			result.concat(sep);
		tmp.set(TheGameText->fetch("LW:RegionLegendaryBonus"));
		tmp.format(&tmp, m_0C);
		result.concat(tmp);
	}
	if (!*(int *)&result || *(unsigned short *)(*(int *)&result + 4) == 0)
		result.set(TheGameText->fetch("LW:NoBonus"));
	return result;
}
