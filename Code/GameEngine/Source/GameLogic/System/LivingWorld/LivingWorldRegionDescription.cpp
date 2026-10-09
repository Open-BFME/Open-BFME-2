// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii
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


// Retail 0x003F15D1..0x003F1797, 454B, hidden UnicodeString result/RET4.
// AptMapPreview's rowed mouseover handler calls this after the territory
// name. Native strings and the WorldBuilder twin at 0x0103F330 identify
// the territory header, local bonus, containing-region name and unified
// bonus composition. The twin is a semantic lead; all offsets/callees
// below are independently observed in game.dat. Original method name
// remains unknown; the established address-derived symbol is retained.
// World +0xB0 -> manager +8 -> rule selector20F0EE; territory bonus+0x8C;
// selected rule bonus+4 and translated label getter20E89C. Rva0020E89C
// is an existing neutral receiver view; its use for both territory and
// rule label access does not establish their original class identity.
class CreateAHeroData;
class Rva003F1241
{
public:
    UnicodeString rva003F1241();
    int values[7];
};
class Rva0020F0EEArg;
class Rva0020E9D0
{
public:
    char prefix[4];
    Rva003F1241 bonus;
};
class Rva0020F0EE
{
public:
    Rva0020E9D0 *rva0020F0EE(Rva0020F0EEArg *);
};
class RegionDescriptionManagerView
{
public:
    char prefix[8];
    Rva0020F0EE *rules;
};
class LivingWorldLogic
{
public:
    char prefix[0xB0];
    RegionDescriptionManagerView *regions;
    RegionDescriptionManagerView *getRegions() { return regions; }
};
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0020E89C
{
public:
    UnicodeString rva0020E89C();
    UnicodeString rva003F15D1();
    char prefix[0x8C];
    Rva003F1241 bonus;
};

UnicodeString Rva0020E89C::rva003F15D1()
{
    UnicodeString result;
    result.concat(TheGameText->fetch("LW:TerritoryBonusHeader"));
    result.concat(bonus.rva003F1241());
    Rva0020F0EE *rules = TheLivingWorldLogic->getRegions()->rules;
    if (rules) {
        Rva0020E9D0 *rule = rules->rva0020F0EE((Rva0020F0EEArg *)this);
        if (rule) {
            UnicodeString text;
            text.set(TheGameText->fetch("LW:TerritoryPartOfRegion"));
            text.format(&text, ((Rva0020E89C *)rule)->rva0020E89C().str());
            result.concat(text);
            text.set(TheGameText->fetch("LW:UnifiedRegionBonus"));
            text.format(&text, rule->bonus.rva003F1241().str());
            result.concat(text);
        }
    }
    return result;
}
