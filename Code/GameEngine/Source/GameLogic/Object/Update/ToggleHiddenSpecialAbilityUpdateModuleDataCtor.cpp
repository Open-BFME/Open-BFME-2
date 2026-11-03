// cl: /DNDEBUG /MD
//
// ??0ToggleHiddenSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x004AE155,
// 25 bytes. ModuleData ctor over the pinned SpecialAbilityUpdateModuleData base (0x44EB54):
// installs vtable 0x00C5F778 explicitly (novtable) and zeroes the +0xC8
// flag. Class size 0xCC proven by the ToggleHiddenSpecialAbilityUpdate data
// factory (news 0xCC, sole caller at 0x24F793); base size 0xC8 inferred from
// the flag position. Row supersedes the ctor pin.

extern "C" const void *const __identifier("??_7EvacuateGarrisonSpecialPowerModuleData@@6B@")[];  // folded vftable 0x00C5F778 (3 classes), by its data-ledger name

class MultiIniFieldParse;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../../Include/Common/INI/FieldParse.h"

#include "../../../../Include/Common/INI/INI.h"

// Retail VA 0x00BEF7E4 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00BEF7E4[] = {
	{ "ShowPalantirTimer", &INI::parseBool, 0, 0xC8 },
	{ 0, 0, 0, 0 }
};


#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class __declspec(novtable) ToggleHiddenSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	ToggleHiddenSpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 flag (false).
	bool m_flagC8;
	char m_padC9[3]; // to the rowed 0xCC instance size
};

// ??0ToggleHiddenSpecialAbilityUpdateModuleData@@QAE@XZ @0x004AE155
ToggleHiddenSpecialAbilityUpdateModuleData::ToggleHiddenSpecialAbilityUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7EvacuateGarrisonSpecialPowerModuleData@@6B@"));
	m_flagC8 = false;
}

// ?buildFieldParse@ToggleHiddenSpecialAbilityUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0024F719
void ToggleHiddenSpecialAbilityUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(g_00BEF7E4, 0);
}
