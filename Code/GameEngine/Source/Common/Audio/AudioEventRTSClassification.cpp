// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
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

struct AudioEventInfo
{
	unsigned char m_pad00[0x48];
	unsigned char m_type;
	unsigned char m_pad49[0x67];
	unsigned int m_soundType;
};

class AudioEventRTS
{
public:
	unsigned int getSoundClass(void) const;
	bool isPositionalAudio(void) const;

private:
	void *m_vftable;
	void *m_filenameToLoad;
	const AudioEventInfo *m_eventInfo;
	char m_pad0C[0x28];
	unsigned int m_ownerID;
	int m_ownerType;
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
