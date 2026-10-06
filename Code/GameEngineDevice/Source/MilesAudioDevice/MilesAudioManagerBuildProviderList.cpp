// cl: /Ireference/shims/bfme2_ascii /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Donor: Open-BFME-1 Zero Hour MilesAudioManager.cpp::buildProviderList.
// Target identity: openDevice at 0x61680 calls the provider enumerator in its
// success arm; Ghidra marks the 73-byte body at 0x51744, directly before the
// matched initDelayFilter body at 0x5178D. Target provider records begin at
// this+0x6CC and are 12 bytes; the 64-record array ends at providerCount +0x9CC.
// The record layout and enumeration semantics are carried from the donor;
// those target offsets are independently measured in createListener and the
// openDevice caller evidence.

extern "C" __declspec(dllimport) int __stdcall AIL_enumerate_3D_providers(
	void **next, unsigned int *provider, char **name);

#include "ascii_string.h"


struct ProviderInfo
{
	AsciiString name;
	unsigned int id;
	int isValid;
};

enum { MAXPROVIDERS = 64 };

class MilesAudioManager
{
	public:
	virtual void v00();

	private:
	void buildProviderList(void);

	char m_pad04[0x6A7];
	bool m_listenerFlag;
	char m_pad6AC[0x20];
	ProviderInfo m_provider3D[MAXPROVIDERS];
	unsigned int m_providerCount;
};

void MilesAudioManager::buildProviderList(void)
{
	void *next = 0;
	char *name;
	unsigned int index = 0;

	while (index < MAXPROVIDERS && AIL_enumerate_3D_providers(
		&next, &m_provider3D[index].id, &name)) {
		m_provider3D[index].name.set(name);
		++index;
	}

	m_providerCount = index;
}
