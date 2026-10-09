// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
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
#include <map>
#include "ascii_string.h"

typedef int Int;
typedef float Real;

enum StaticGameLODLevel
{
	STATIC_GAME_LOD_UNKNOWN = -1
};

struct BfmeOSVersionInfo
{
	unsigned long dwOSVersionInfoSize, dwMajorVersion, dwMinorVersion, dwBuildNumber, dwPlatformId;
	char szCSDVersion[128];
};
extern "C" __declspec(dllimport) int __stdcall GetVersionExA(BfmeOSVersionInfo *info);
extern "C" void *__cdecl memset(void *dst, int value, unsigned int count);

enum ChipsetType { DC_UNKNOWN = 0 };
enum CpuType { XX = 0 };
bool Rva000768F5(ChipsetType *chipset, CpuType *cpu, int *mhz, unsigned __int64 *ram, float *a, float *b, float *c);

namespace _STL
{
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

class UserPreferences : public _STL::map<AsciiString, AsciiString>
{
public:
	virtual ~UserPreferences();
	virtual bool write();
private:
	AsciiString m_filename;
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
	void rva002E537B(Int level);
	void rva002E52FC(Int level);
};

class GlobalData
{
public:
	unsigned char m_pad00[0x30];
	Int m_xResolution; // +0x30
	Int m_yResolution; // +0x34
};
extern GlobalData *TheWritableGlobalData;

struct LODPresetInfo
{
	Int m_cpuType;
	Int m_mhz;
	Real m_cpuPerfIndex;
	Int m_videoType;   // +0x0C
	Int m_memory;      // +0x10
	Int m_pad14;
	Int m_xResolution; // +0x18
	Int m_yResolution; // +0x1C
};

class GameLODManager
{
public:
	StaticGameLODLevel findStaticLODLevel();

private:
	unsigned char m_pad000[0x228];
	LODPresetInfo m_lodPresets[5][32];        // +0x228
	unsigned char m_pad1628[0x1768 - 0x1628];
	Int m_currentStaticLOD;                   // +0x1768
	unsigned char m_pad176c[0x17AC - 0x176C];
	Int m_numLevelPresets[5];                 // +0x17AC
	unsigned char m_pad17c0[0x17C4 - 0x17C0];
	StaticGameLODLevel m_idealDetailLevel;    // +0x17C4
	ChipsetType m_videoChipType;              // +0x17C8
	CpuType m_cpuType;                        // +0x17CC
	unsigned __int64 m_numRAM;                // +0x17D0
	Int m_cpuFreq;                            // +0x17D8
};

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

		BfmeOSVersionInfo osvi;
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
			TheWritableGlobalData->m_xResolution = xres;
			TheWritableGlobalData->m_yResolution = yres;
		}
		AsciiString resolution;
		resolution.format("%d %d", xres, yres);
		optionPref["Resolution"] = resolution;
		optionPref.write();
	}
	return m_idealDetailLevel;
}
