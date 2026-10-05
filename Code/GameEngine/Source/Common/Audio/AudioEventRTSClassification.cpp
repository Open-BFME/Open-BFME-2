// cl: /Ireference/shims/bfme2_ascii /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// AudioEventRTS sound-class mapper and its positional-audio test.
//
// Target: Ghidra 0x002D9D39 (67B) is pinned ?getSoundClass@AudioEventRTS@@QBEIXZ
// from MilesAudioManager::stopAudio's event+0x1C call; it maps event info
// +0xB0 (0..5) to the AudioAffect flags 1/8/2/4/16. Its case 2 calls Ghidra
// 0x002D9C37 (67B), which tests event info +0xB0/+0x48 and then the owner
// type +0x38 / owner ID +0x34 and returns a bool.
// Donor: reference/open-bfme-1/game/GameEngine/Source/Common/Audio/
// AudioEventRTSClassification.cpp at 6583b3c1ff21db4a561285717028fdafc780b7db
// supplies both identities (case 2 of getSoundClass calls isPositionalAudio)
// and the switch structure; BFME 2 moves the class field to +0xB0, adds a
// class-gated world-bit test and accepts owner types 1..5. Field names are
// carried from the donor / GeneralsMD, not recovered from BFME 2.
//
// Ghidra 0x002DA08C (67B) switches on the portion field +0x74 exactly like
// GeneralsMD AudioEventRTS::advanceNextPlayPortion and, for PP_Sound, calls
// Ghidra 0x002D9C07 (40B), whose body is the donor's hasMoreLoops (bypass
// byte +0x4C, sound type +0xB0, control bit 0 at info +0x4C). The decay name
// is the AsciiString at +0x20 tested with the out-of-line isEmpty.

#include "string_base.h"

enum PortionToPlay
{
	PP_Attack,
	PP_Sound,
	PP_Decay,
	PP_Done
};

struct AudioEventInfo
{
	unsigned char m_pad00[0x48];
	unsigned char m_type;
	unsigned char m_pad49[0x03];
	unsigned char m_control;
	unsigned char m_pad4D[0x63];
	unsigned int m_soundType;
};

class AudioEventRTS
{
public:
	unsigned int getSoundClass(void) const;
	bool isPositionalAudio(void) const;
	bool hasMoreLoops(void) const;
	void advanceNextPlayPortion(void);

private:
	void *m_vftable;
	void *m_filenameToLoad;
	const AudioEventInfo *m_eventInfo;
	char m_pad0C[0x14];
	StringBase<char> m_decayName;
	char m_pad24[0x10];
	unsigned int m_ownerID;
	int m_ownerType;
	char m_pad3C[0x10];
	unsigned char m_bypassLoops;
	char m_pad4D[0x27];
	PortionToPlay m_portionToPlayNext;
};

// ?isPositionalAudio@AudioEventRTS@@QBE_NXZ
bool AudioEventRTS::isPositionalAudio(void) const
{
	if (m_eventInfo != 0)
	{
		switch (m_eventInfo->m_soundType)
		{
		case 2:
			if ((m_eventInfo->m_type & 2) == 0)
				goto not_positional;
			break;
		case 3:
			break;
		case 4:
			goto not_positional;
		default:
			return false;
		}
	}

	switch (m_ownerType)
	{
	case 0:
		return true;
	case 1:
		if (m_ownerID != 0)
			return true;
		break;
	case 2:
		if (m_ownerID != 0)
			return true;
		break;
	case 3:
		if (m_ownerID != 0)
			return true;
		break;
	case 4:
		if (m_ownerID != 0)
			return true;
		break;
	case 5:
		if (m_ownerID != 0)
			return true;
		break;
	}

not_positional:
	return false;
}

// ?getSoundClass@AudioEventRTS@@QBEIXZ
unsigned int AudioEventRTS::getSoundClass(void) const
{
	if (!m_eventInfo)
		return 0;

	switch (m_eventInfo->m_soundType)
	{
	case 0:
		return 1;
	case 3:
		return 16;
	case 1:
		return 8;
	case 4:
		return 2;
	case 2:
		return isPositionalAudio() ? 4 : 2;
	case 5:
		return 0;
	default:
		return 0;
	}
}

// ?hasMoreLoops@AudioEventRTS@@QBE_NXZ
bool AudioEventRTS::hasMoreLoops(void) const
{
	if (m_bypassLoops != 0)
		return false;

	const AudioEventInfo *eventInfo = m_eventInfo;
	if (eventInfo == 0)
		return true;

	unsigned int soundType = eventInfo->m_soundType;
	if (soundType == 0 || soundType == 3 || (eventInfo->m_control & 1) != 0)
		return true;

	return false;
}

// ?advanceNextPlayPortion@AudioEventRTS@@QAEXXZ
void AudioEventRTS::advanceNextPlayPortion(void)
{
	switch (m_portionToPlayNext)
	{
	case PP_Attack:
		m_portionToPlayNext = PP_Sound;
		break;
	case PP_Sound:
		if (!hasMoreLoops())
			m_portionToPlayNext = m_decayName.isEmpty() ? PP_Done : PP_Decay;
		break;
	case PP_Decay:
		m_portionToPlayNext = PP_Done;
		break;
	}
}
