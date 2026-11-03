// cl: /DNDEBUG /MD
//
// ??0ScaleWallSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x00494DB1,
// 25 bytes. ModuleData ctor over the pinned SpecialAbilityUpdateModuleData base (0x44EB54):
// clears the +0xC8 word (and-RMW) and installs vtable 0x00C5F778
// explicitly (novtable; shares the ToggleHidden vtable). Class size 0xCC
// proven by the ScaleWallSpecialAbilityUpdate data factory (news 0xCC, sole
// caller at 0x24DDEC); base size 0xC8 inferred from the +0xC8 position. Row
// supersedes the ctor pin.

extern "C" const void *const __identifier("??_7EvacuateGarrisonSpecialPowerModuleData@@6B@")[];  // folded vftable 0x00C5F778 (3 classes), by its data-ledger name

class MultiIniFieldParse;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../../Include/Common/INI/FieldParse.h"

#include "../../../../Include/Common/INI/INI.h"

// Retail VA 0x00BEF1B4 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00BEF1B4[] = {
	{ "DelayAtFootOfWall", &INI::parseDurationUnsignedInt, 0, 0xC8 },
	{ 0, 0, 0, 0 }
};


#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class __declspec(novtable) ScaleWallSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	ScaleWallSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 cleared word (ends at the rowed 0xCC instance size).
	unsigned int m_wordC8;
};

// ??0ScaleWallSpecialAbilityUpdateModuleData@@QAE@XZ @0x00494DB1
ScaleWallSpecialAbilityUpdateModuleData::ScaleWallSpecialAbilityUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	m_wordC8 &= 0;
	*(unsigned int *)this = ((unsigned int)__identifier("??_7EvacuateGarrisonSpecialPowerModuleData@@6B@"));
}

// ?buildFieldParse@ScaleWallSpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0024DD72
void ScaleWallSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00BEF1B4, 0);
}
