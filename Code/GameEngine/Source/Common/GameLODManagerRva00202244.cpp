// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_gamelod /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/gamelod /Ireference/open-bfme-1/reference/shims/ini_noinline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc
// stlport
#include "PreRTS.h"
#include "Common/UserPreferences.h"
//
// ?rva00202244@Rva00DFE144Globals@@QAEXHPAVOptionPreferences@@@Z, retail
// 0x00202244..0x002022E9 (165 bytes, RET 8): a method of the object at
// 0x00DFE144 (TheGameLODManager, viewed as Rva00DFE144Globals, the spelling
// its caller AptOptions pinned). It writes the 0x4C-byte preset the first
// argument selects into nine OptionPreferences settings (rowed setSetting):
// the +0x00, +0x34, +0x04 and +0x10 words; 2 when the +0x14 flag is set, else
// the +0x15 flag; the +0x18 word; the +0x2C mode mapped 2 -> 0, 1 -> 1,
// anything else -> 2; and the +0x38 and +0x40 words.


struct Rva00202244Preset
{
	int m_modelLOD;
	int m_effectsLOD;
	unsigned char m_pad08[0x10 - 0x08];
	int m_shadowLOD;
	bool m_useTerrainNormalMap;
	bool m_useDistanceDependantTerrainTextures;
	unsigned char m_pad16[0x18 - 0x16];
	int m_waterLOD;
	unsigned char m_pad1C[0x2C - 0x1C];
	int m_textureReduction;
	unsigned char m_pad30[0x34 - 0x30];
	int m_animationDetail;
	int m_shaderLOD;
	unsigned char m_pad3C[0x40 - 0x3C];
	int m_decalLOD;
	unsigned char m_pad44[0x4C - 0x44];
};

class Rva00DFE144Globals
{
public:
	void rva00202244(int preset, OptionPreferences *prefs);
	void rva002022E9(int level);
private:
	Rva00202244Preset m_presets[1];
};

void Rva00DFE144Globals::rva00202244(int preset, OptionPreferences *prefs)
{
	const Rva00202244Preset &lodInfo = m_presets[preset];
	prefs->setSetting(0, lodInfo.m_modelLOD);
	prefs->setSetting(1, lodInfo.m_animationDetail);
	prefs->setSetting(2, lodInfo.m_effectsLOD);
	prefs->setSetting(3, lodInfo.m_shadowLOD);
	prefs->setSetting(4, lodInfo.m_useTerrainNormalMap ? 2 : (lodInfo.m_useDistanceDependantTerrainTextures != 0));
	prefs->setSetting(5, lodInfo.m_waterLOD);
	prefs->setSetting(6, lodInfo.m_textureReduction == 2 ? 0 : (lodInfo.m_textureReduction == 1 ? 1 : 2));
	prefs->setSetting(7, lodInfo.m_shaderLOD);
	prefs->setSetting(8, lodInfo.m_decalLOD);
}
