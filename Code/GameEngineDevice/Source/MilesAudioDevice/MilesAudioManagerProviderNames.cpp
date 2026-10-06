// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /DWIN32 /MD /EHsc
// Two MilesAudioManager AsciiString-returning accessors over the 3D provider
// table proven by createListener/getGlobalReverbMultiplier (ProviderInfo[64] of 12 bytes at
// +0x6CC, count +0x9CC, selection +0x9D0).
//
// ?getProviderName@MilesAudioManager@@QBE?AVAsciiString@@I@Z @0x000547F3 70B:
// ZH MilesAudioManager::getProviderName -- the provider's name while isOn
// (slot 56, 0xE0) reports AudioAffect_Sound3D (4) and the index is in range,
// else AsciiString::TheEmptyString (0x00DE0878).
//
// ?rva00054243@MilesAudioManager@@QBE?AVAsciiString@@XZ @0x00054243 65B: the
// display name (rowed getEnvironmentName 0x00050F7D) of the EAX room type the
// selected provider reports through IAT AIL_3D_room_type, or of 0 when no
// provider is selected. BFME 1's counterpart is MilesAudioManagerRoomTypeName
// (0x0069D240), which does not range-check; the method name is unknown.

#include "ascii_string.h"

extern "C" __declspec(dllimport) int __stdcall AIL_3D_room_type(unsigned int provider);

const char *getEnvironmentName(int environment);

enum { AudioAffect_Sound3D = 0x04 };

struct ProviderInfo
{
	AsciiString name;
	unsigned int id;
	bool isValid;
};

enum { MAXPROVIDERS = 64 };

class MilesAudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual bool isOn(int which) const;

	AsciiString getProviderName(unsigned int providerNum) const;
	AsciiString rva00054243() const;

private:
	char m_pad004[0x6cc - 4];
	ProviderInfo m_provider3D[MAXPROVIDERS];
	unsigned int m_providerCount;
	unsigned int m_selectedProvider;
};

AsciiString MilesAudioManager::getProviderName(unsigned int providerNum) const
{
	if (isOn(AudioAffect_Sound3D) && providerNum < m_providerCount)
		return m_provider3D[providerNum].name;

	return AsciiString::TheEmptyString;
}

AsciiString MilesAudioManager::rva00054243() const
{
	unsigned int selected = m_selectedProvider;
	if (selected >= m_providerCount)
		return AsciiString(getEnvironmentName(0));
	return AsciiString(getEnvironmentName(AIL_3D_room_type(m_provider3D[selected].id)));
}
