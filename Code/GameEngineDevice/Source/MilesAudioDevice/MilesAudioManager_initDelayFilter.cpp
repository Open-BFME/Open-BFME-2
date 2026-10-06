// cl: /Oy- /DNDEBUG /MD /EHsc /Oi-

#include <string.h>
//
// ?initDelayFilter@MilesAudioManager@@IAEXXZ,
// retail 0x0005178D, 83 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp,
// MilesAudioManager::initDelayFilter): cache the Mono Delay Filter provider by
// enumerating the Miles filters. Verbatim shape; the retail member sits at
// +0x9E4 (BFME1's build has it at +0x968) and the name compare goes through
// the 0x6291C6 strcmp slot. The Miles import hoists out of the loop.

typedef void *HPROENUM;
typedef void *HPROVIDER;
#define HPROENUM_FIRST NULL
#define NULL 0

extern "C" __declspec(dllimport) int __stdcall AIL_enumerate_filters(
	HPROENUM *next, HPROVIDER *provider, char **name);

int strcmp(const char *a, const char *b);

class MilesAudioManager
{
protected:
	void initDelayFilter(void);

private:
	unsigned char m_pad[0x9E4];
	HPROVIDER m_delayFilter; // +0x9E4
};

// ?initDelayFilter@MilesAudioManager@@IAEXXZ
void MilesAudioManager::initDelayFilter(void)
{
	if (m_delayFilter != NULL) {
		return;
	}

	char *filterName;
	HPROENUM enumFLTs = HPROENUM_FIRST;
	HPROVIDER currentProvider;

	while (AIL_enumerate_filters(&enumFLTs, &currentProvider, &filterName)) {
		if (strcmp(filterName, "Mono Delay Filter") == 0) {
			m_delayFilter = currentProvider;
			break;
		}
	}
}
