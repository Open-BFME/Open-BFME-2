// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_gamelod /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/gamelod /Ireference/open-bfme-1/reference/shims/ini_noinline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc
// platformsdk
// stlport
// ?findStaticLODLevel@GameLODManager@@QAE?AW4StaticGameLODLevel@@XZ
// Retail 0x00203288..0x002034C4 (572 bytes).
// BFME 2 GameLODManager::findStaticLODLevel (Zero Hour Common/GameLOD.cpp
// and the Open-BFME-1 donor GameLODManagerFindStaticLODLevel.cpp): on the
// first call (+0x17C4 unknown) the ideal level starts at 0, the video chip
// type comes from the rowed testMinimumRequirements (0x000768F5; unknown ->
// 1) and the presets of levels 4..1 (+0x228 + level*0x400, counts at
// +0x17AC + level*4) are matched against the CPU type, CPU MHz, video chip and
// RAM (within 0.94) to pick the ideal level and its resolution (default
// 800x600); Windows 2000 drops it one notch; the option preferences store the
// ideal level (rowed 0x002E537B) and, while no static level was chosen
// (+0x1768), the static level (rowed 0x002E52FC); TheGlobalData's resolution
// (+0x30/+0x34) and the "Resolution" preference ("%d %d") are set and the
// preferences are written. Returns the ideal level.
// Evidence (target): rowed callees above plus OptionPreferences ctor
// 0x002E434E / dtor 0x002E4272 UserPreferences::write 0x003B1BF3
// AsciiString::format 0x00038150 map<AsciiString AsciiString>::operator[]
// 0x002031FB StringBase<char> set / ctor / releaseBuffer and
// GetVersionExA; BFME 2 deltas against the donor (four preset levels, the
// two preference setters, GlobalData +0x30) are read from the retail body.
#include "PreRTS.h"
#include "Common/GameLOD.h"
#include "Common/UserPreferences.h"
#include <map>
#include <windows.h>
#include <string.h>
#include "ascii_string.h"

typedef int Int;
typedef float Real;

bool Rva000768F5(ChipsetType *chipset, CpuType *cpu, int *mhz, unsigned __int64 *ram, float *a, float *b, float *c);

namespace _STL
{
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

struct LODGlobalDataView {
 char gap0[0x1C];
 bool m_showProps;
 char gap1D[0x7];
 bool field24;
 bool field25;
 char gap26[0xA];
 int m_xResolution; // +0x30
 int m_yResolution; // +0x34
 char gap38[0x11];
 bool field49;
 bool field4A;
 char gap4B[0x13];
 bool field5E;
 char gap5F[0x1];
 bool m_useShadowVolumes;
 bool m_useShadowDecals;
 bool m_useShadowMapping;
 char gap63[0x21];
 bool m_showSoftWaterEdge;
 char gap85[0x8B];
 int m_maxTankTrackEdges;
 int m_maxTankTrackOpaqueEdges;
 int m_maxTankTrackFadeDelay;
 char gap11C[0x889];
 bool m_showSelectedUnitMarker;
 char gap9A6[0x1];
 bool m_useSimpleMergeDecals;
 char gap9A8[0x16];
 bool m_showAllHealthBars;
 char gap9BF[0x25];
 bool m_forceBenchmark; // +0x9E4
 char gap9E5[0xE3];
 int m_maxParticleCount;
 char gapACC[0x24];
 bool m_shellMapOn;
 bool m_shellMapOffByCommandArgument;
};
extern GlobalData *TheWritableGlobalData;

#define PROFILE_ERROR_LIMIT 0.94f

StaticGameLODLevel GameLODManager::findStaticLODLevel()
{
	if (m_idealDetailLevel == STATIC_GAME_LOD_UNKNOWN)
	{
		m_idealDetailLevel = (StaticGameLODLevel)0;
		Rva000768F5(&m_videoChipType, 0, 0, 0, 0, 0, 0);
		if (m_videoChipType == DC_UNKNOWN)
			m_videoChipType = (ChipsetType)1;

		Int numMBRam = (Int)(m_numRAM >> 20);
		Int xres = 800;
		Int yres = 600;

		for (Int i = 4; i >= 1; i--)
		{
			LODPresetInfo *preset = &m_lodPresets[i][0];
			for (Int j = 0; j < m_numLevelPresets[i]; j++)
			{
				if (m_cpuType == preset->m_cpuType &&
					((Real)m_cpuFreq / (Real)preset->m_mhz >= PROFILE_ERROR_LIMIT) &&
					m_videoChipType >= preset->m_videoType &&
					((Real)numMBRam / (Real)preset->m_memory >= PROFILE_ERROR_LIMIT))
				{
					m_idealDetailLevel = (StaticGameLODLevel)i;
					xres = preset->m_xResolution;
					yres = preset->m_yResolution;
					break;
				}
				preset++;
			}
			if (m_idealDetailLevel >= i)
				break;
		}

		OSVERSIONINFOA osvi;
		memset(&osvi, 0, sizeof(osvi));
		osvi.dwOSVersionInfoSize = sizeof(osvi);
		if (GetVersionExA(&osvi) &&
			osvi.dwPlatformId == 2 &&
			osvi.dwMajorVersion == 5 &&
			osvi.dwMinorVersion == 0 &&
			m_idealDetailLevel >= 1 &&
			m_idealDetailLevel <= 4)
		{
			m_idealDetailLevel = (StaticGameLODLevel)(m_idealDetailLevel - 1);
		}

		OptionPreferences optionPref;
		optionPref.rva002E537B(m_idealDetailLevel);
		if (m_currentStaticLOD == STATIC_GAME_LOD_UNKNOWN)
			optionPref.rva002E52FC(m_idealDetailLevel);
		if (TheWritableGlobalData)
		{
			((LODGlobalDataView *)TheWritableGlobalData)->m_xResolution = xres;
			((LODGlobalDataView *)TheWritableGlobalData)->m_yResolution = yres;
		}
		AsciiString resolution;
		resolution.format("%d %d", xres, yres);
		optionPref["Resolution"] = resolution;
		optionPref.write();
	}
	return m_idealDetailLevel;
}
