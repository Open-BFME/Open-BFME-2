// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/game/GameEngine/Source/Common/INI

// clearVeterancyLevelFlag is an inline in Common/GameCommon.h:
//     inline VeterancyLevelFlags clearVeterancyLevelFlag(VeterancyLevelFlags flags, VeterancyLevel dt)
//     { return (flags & ~(1UL << (dt - 1))); }
// The BFME1 donor INI_stl.cpp only odr-uses it, so it has no donor .cpp
// definition to copy. The header body is emitted out-of-line here; retail
// 0x003389AC is that body.
typedef unsigned int UnsignedInt;
typedef UnsignedInt VeterancyLevelFlags;

enum VeterancyLevel
{
	VETERANCY_LEVEL_FIRST = 1
};

VeterancyLevelFlags clearVeterancyLevelFlag(VeterancyLevelFlags flags, VeterancyLevel dt)
{
	return (flags & ~(1UL << (dt - 1)));
}

// Reference guide: BFME1 f98983a7 GameCommon.h inline flag setters,
// emitted by Common/INI/ini.cpp under O1/SSE/G6. Their VeterancyLevel
// and DeathType spellings are ambiguous at the placed target. Retail
// 003389CE..003389DD is independently complete after RET at 003389CD:
// two raw stack words, flags OR (1u << (index - 1)), EAX result, RET0.
// Original name and enum identity remain unknown.
unsigned int rva003389ce(unsigned int flags, unsigned int index)
{
    return flags | (1u << (index - 1u));
}
