// cl: /Ireference/shims/bfme2_ascii /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Donor: Open-BFME-1 Zero Hour MilesAudioManager.cpp::getProviderIndex.
// Target identity: Ghidra boundary 0x56634/60B is called by the retail helper
// at 0x604A3 after it builds provider-name AsciiStrings; adjacent pool setup
// at 0x566B6 uses the same provider array. Target offsets are measured in the
// landed MilesAudioManager helpers: 64 12-byte records at +0x6CC and count at
// +0x9CC. The method name/loop semantics come from the donor; layout claims
// come from target accesses and the verified buildProviderList sibling.

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
	unsigned int getProviderIndex(const AsciiString &providerName) const;

private:
	char m_pad04[0x6C8];
	ProviderInfo m_provider3D[MAXPROVIDERS];
	unsigned int m_providerCount;
};

unsigned int MilesAudioManager::getProviderIndex(
	const AsciiString &providerName) const
{
	for (unsigned int i = 0; i < m_providerCount; ++i) {
		if (providerName.compare(m_provider3D[i].name) == 0)
			return i;
	}

	return 0xffffffff;
}
