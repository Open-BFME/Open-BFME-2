// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_gamelod /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/gamelod /Ireference/open-bfme-1/reference/shims/ini_noinline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc
// stlport
// ?init@GameLODManager@@QAEXH@Z, retail 0x002027EA, 864 bytes.
//
// Identity: the existing pin (GameEngine::init's REL32 call). Donor: Zero Hour
// GameLOD.cpp GameLODManager::init: load GameLOD.ini and GameLODPresets.ini,
// read the user's and ideal static detail from OptionPreferences, probe the
// machine (testMinimumRequirements, BFME2 0x000768F5), flag 256 MB of RAM,
// and when the ideal level is unknown or a benchmark is forced, benchmark the
// CPU, optionally dump the numbers to Benchmark.txt and map the result to the
// closest preset CPU. BFME2 differences taken from the target body: the custom
// detail level (5) applies its option preferences through 0x00202058 right
// away; an unknown audio LOD also forces the benchmark; the final static level
// is applied (0x00202739) only when the caller passes -1; an unknown audio LOD
// is derived from the CPU speed against +0x17F0, saved to the preferences and
// applied through 0x00202790. Offsets are the BFME2 manager layout.

#include "PreRTS.h"
#include "Common/GameLOD.h"
#include "Common/UserPreferences.h"
#include <stdio.h>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

#define PROFILE_ERROR_LIMIT 0.94f

class Xfer;

bool Rva000768F5(ChipsetType *videoChipType, CpuType *cpuType, int *cpuFreq,
	unsigned __int64 *numRAM, float *intBenchIndex, float *floatBenchIndex,
	float *memBenchIndex);
#define testMinimumRequirements Rva000768F5

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
#define TheGlobalData ((LODGlobalDataView *)TheWritableGlobalData)

// Retail's CPU-name table at RVA 0x9B96B8 (.data): XX/P3/P4/K7 plus null,
// in retail's index order, that Benchmark.txt writing indexes by CPU type.
// GameLOD.cpp keeps its own static copy for INI parsing; this TU defines the
// global the benchmark writer references instead of leaving it external.
extern const char BfmeCpuNameXX[];
const char BfmeCpuNameXX[] = "XX";
extern const char BfmeCpuNameP3[];
const char BfmeCpuNameP3[] = "P3";
extern const char BfmeCpuNameP4[];
const char BfmeCpuNameP4[] = "P4";
extern const char BfmeCpuNameK7[];
const char BfmeCpuNameK7[] = "K7";
const char *CPUNames[] = {BfmeCpuNameXX, BfmeCpuNameP3, BfmeCpuNameP4, BfmeCpuNameK7, NULL};

class Rva00202058
{
public:
	void rva00202058(OptionPreferences *prefs);
};

class Rva00202739
{
public:
	bool rva00202739(int level);
	char m_pad00[0x1768];
	int m_1768; // +0x1768
};

class Rva00202790
{
public:
	void rva00202790(int v);
	char m_pad00[0x1770];
	int m_1770; // +0x1770
};

void GameLODManager::init(Int staticLevel)
{
	INI ini;
	ini.loadFile(AsciiString("Data\\INI\\GameLOD.ini"), INI_LOAD_OVERWRITE, 0);
	ini.loadFile(AsciiString("Data\\INI\\GameLODPresets.ini"), INI_LOAD_OVERWRITE, 0);

	OptionPreferences optionPref;
	StaticGameLODLevel userSetDetail = (StaticGameLODLevel)optionPref.getStaticGameDetail();
	m_idealDetailLevel = (StaticGameLODLevel)optionPref.getIdealStaticGameDetail();
	if (userSetDetail == STATIC_GAME_LOD_CUSTOM)
		reinterpret_cast<Rva00202058 *>(this)->rva00202058(&optionPref);

	testMinimumRequirements(0, &m_cpuType, &m_cpuFreq, &m_numRAM, 0, 0, 0);

	// BFME2 keeps the RAM size as unsigned __int64 and divides in double.
	if ((double)m_numRAM / (double)(256 * 1024 * 1024) >= PROFILE_ERROR_LIMIT)
		m_memPassed = true;

	Int audioLOD = optionPref.getAudioLOD();
	if (m_idealDetailLevel == STATIC_GAME_LOD_UNKNOWN || TheGlobalData->m_forceBenchmark || audioLOD == -1)
	{
		if (m_cpuType == XX || TheGlobalData->m_forceBenchmark)
		{
			testMinimumRequirements(0, 0, 0, 0, &m_intBenchIndex, &m_floatBenchIndex, &m_memBenchIndex);

			if (TheGlobalData->m_forceBenchmark)
			{
				FILE *fp = fopen("Benchmark.txt", "w");
				if (fp)
				{
					fprintf(fp, "BenchProfile = %s %d %f %f %f", CPUNames[m_cpuType], m_cpuFreq,
						m_intBenchIndex, m_floatBenchIndex, m_memBenchIndex);
					fclose(fp);
				}
			}

			m_compositeBenchIndex = m_intBenchIndex + m_floatBenchIndex;

			StaticGameLODLevel currentLevel = STATIC_GAME_LOD_LOW;
			BenchProfile *prof = m_benchProfiles;
			m_cpuType = P3;
			m_cpuFreq = 1000;

			for (Int k = 0; k < m_numBenchProfiles; k++)
			{
				if (m_intBenchIndex / prof->m_intBenchIndex >= PROFILE_ERROR_LIMIT &&
					m_floatBenchIndex / prof->m_floatBenchIndex >= PROFILE_ERROR_LIMIT &&
					m_memBenchIndex / prof->m_memBenchIndex >= PROFILE_ERROR_LIMIT)
				{
					for (Int i = STATIC_GAME_LOD_HIGH; i >= STATIC_GAME_LOD_LOW; i--)
					{
						LODPresetInfo *preset = &m_lodPresets[i][0];
						for (Int j = 0; j < m_numLevelPresets[i]; j++)
						{
							if (prof->m_cpuType == preset->m_cpuType &&
								((Real)prof->m_mhz / (Real)preset->m_mhz >= PROFILE_ERROR_LIMIT))
							{
								currentLevel = (StaticGameLODLevel)i;
								m_cpuType = prof->m_cpuType;
								m_cpuFreq = prof->m_mhz;
								break;
							}
							preset++;
						}
						if (currentLevel >= i)
							break;
					}
				}
				prof++;
			}
		}
	}

	if (staticLevel == -1)
		reinterpret_cast<Rva00202739 *>(this)->rva00202739(userSetDetail);

	if (audioLOD == -1)
	{
		audioLOD = m_cpuFreq >= m_reallyLowMHz;
		optionPref.rva002E53FA(audioLOD);
		optionPref.write();
	}
	reinterpret_cast<Rva00202790 *>(this)->rva00202790(audioLOD);
}
