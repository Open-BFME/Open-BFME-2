// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::GetTooltipText (WorldBuilder
// StrategicInGameUIGetTypeImage.cpp, matched by call site only; the name is
// not confirmed by a retail string). Target facts for 0x005F027D (cdecl,
// hidden UnicodeString return): looks the unit archetype up in the
// six-entry table at 0x00878C3C (archetype, "STRATEGICHUD:...Tooltip"
// label) and fetches that label from TheGameText (vslot 15, no exists
// flag); an unknown archetype gives the empty UnicodeString. Called by
// StrategicInGameUI::ArmyHeroIcon::DoUpdate 0x005F42FF.
#include "ascii_string.h"
#include "unicode_string.h"

// TheGameText viewed by slot: fetch(label, exists) at +0x3C.
class GameTextInterface
{
public:
	virtual ~GameTextInterface();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual UnicodeString fetch(const char *label, bool *exists) = 0;
};
extern GameTextInterface *TheGameText;

namespace StrategicInGameUI {

struct ArchetypeTooltip
{
	int archetype;
	const char *label;
};

static const ArchetypeTooltip s_archetypeTooltips[] = {
	{ 0, "STRATEGICHUD:InfantryUnitArchetypeTooltip" },
	{ 1, "STRATEGICHUD:ArcherUnitArchetypeTooltip" },
	{ 2, "STRATEGICHUD:PikemanUnitArchetypeTooltip" },
	{ 3, "STRATEGICHUD:CavalryUnitArchetypeTooltip" },
	{ 5, "STRATEGICHUD:HeroUnitArchetypeTooltip" },
	{ 6, "STRATEGICHUD:FortressStructureArchetypeTooltip" },
};

UnicodeString __cdecl GetTooltipText(int archetype)
{
	for (unsigned int i = 0; i < sizeof(s_archetypeTooltips) / sizeof(s_archetypeTooltips[0]); ++i)
	{
		if (s_archetypeTooltips[i].archetype == archetype)
			return TheGameText->fetch(s_archetypeTooltips[i].label, 0);
	}
	return UnicodeString::TheEmptyString;
}

// The living-world building type (WorldBuilder's assert names
// LIVING_WORLD_BUILDING_TYPE_COUNT); the values below are the four the
// retail table at 0x00878B48 lists.
enum LivingWorldBuildingType
{
	LIVING_WORLD_BUILDING_TYPE_COUNT = 5
};

struct BuildingTooltip
{
	int buildingType;
	const char *label;
};

static const BuildingTooltip s_buildingTooltips[] = {
	{ 1, "STRATEGICHUD:FortressStructureArchetypeTooltip" },
	{ 2, "STRATEGICHUD:ArmoryStructureArchetypeTooltip" },
	{ 3, "STRATEGICHUD:FarmStructureArchetypeTooltip" },
	{ 4, "STRATEGICHUD:BarracksStructureArchetypeTooltip" },
};

// Retail 0x005F0236, 71 bytes: the building-type overload (WorldBuilder
// StrategicInGameUIGetTypeImage.cpp lines 265..266; wb-name-unverified).
UnicodeString __cdecl GetTooltipText(LivingWorldBuildingType buildingType)
{
	for (unsigned int i = 0; i < sizeof(s_buildingTooltips) / sizeof(s_buildingTooltips[0]); ++i)
	{
		if (s_buildingTooltips[i].buildingType == buildingType)
			return TheGameText->fetch(s_buildingTooltips[i].label, 0);
	}
	return UnicodeString::TheEmptyString;
}

}
