// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
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

#include <stdio.h>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

enum ChipsetType
{
	DC_UNKNOWN = 0
};

enum CpuType
{
	XX = 0,
	P3 = 1
};

enum StaticGameLODLevel
{
	STATIC_GAME_LOD_UNKNOWN = -1,
	STATIC_GAME_LOD_LOW = 1,
	STATIC_GAME_LOD_HIGH = 3,
	STATIC_GAME_LOD_CUSTOM = 5
};

enum INILoadType
{
	INI_LOAD_OVERWRITE = 1
};

#define PROFILE_ERROR_LIMIT 0.94f

class Xfer;

class INI
{
public:
	INI();
	~INI();
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);
private:
	char m_data[0x87C];
};

bool Rva000768F5(ChipsetType *videoChipType, CpuType *cpuType, int *cpuFreq,
	unsigned __int64 *numRAM, float *intBenchIndex, float *floatBenchIndex,
	float *memBenchIndex);
#define testMinimumRequirements Rva000768F5

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual Bool write(void);
private:
	char m_body[0x10];
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
	Int getStaticGameDetail();
	Int getIdealStaticGameDetail();
	Int getAudioLOD();
	void rva002E53FA(Int audioLOD);
};

class GlobalData
{
public:
	char m_pad[0x9E4];
	Bool m_forceBenchmark;
};
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

extern const char *CPUNames[];

struct LODPresetInfo
{
	CpuType m_cpuType;
	Int m_mhz;
	char m_pad08[0x20 - 0x08];
};

struct BenchProfile
{
	CpuType m_cpuType;
	Int m_mhz;
	Real m_intBenchIndex;
	Real m_floatBenchIndex;
	Real m_memBenchIndex;
};

class Rva00202058
{
public:
	void rva00202058(OptionPreferences *prefs);
};

class Rva00202739
{
public:
	Bool rva00202739(Int level);
};

class Rva00202790
{
public:
	void rva00202790(Int audioLOD);
};

class GameLODManager
{
public:
	void init(Int staticLevel);

private:
	char m_pad0000[0x228];
	LODPresetInfo m_lodPresets[5][32];
	BenchProfile m_benchProfiles[16];
	char m_pad1768[0x17AA - 0x1768];
	Bool m_memPassed;
	char m_pad17AB;
	Int m_numLevelPresets[5];
	Int m_numBenchProfiles;
	StaticGameLODLevel m_idealDetailLevel;
	char m_pad17C8[4];
	CpuType m_cpuType;
	unsigned __int64 m_numRAM;
	Int m_cpuFreq;
	Real m_intBenchIndex;
	Real m_floatBenchIndex;
	Real m_memBenchIndex;
	Real m_compositeBenchIndex;
	char m_pad17EC[4];
	Int m_audioLODMHz;
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
		audioLOD = m_cpuFreq >= m_audioLODMHz;
		optionPref.rva002E53FA(audioLOD);
		optionPref.write();
	}
	reinterpret_cast<Rva00202790 *>(this)->rva00202790(audioLOD);
}
