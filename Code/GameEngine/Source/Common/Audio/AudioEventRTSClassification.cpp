// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS
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

#include "ascii_string.h"

#define AUDIO_EVENT_RTS_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\Common\\Audio\\AudioEventRTS.cpp"

int GetGameAudioRandomValue(int lo, int hi, char *file, int line);
float GetGameAudioRandomValueReal(float lo, float hi, char *file, int line);

// Rowed address-named helpers of this unit: the filename prefix lookup
// (returns a string owned by TheAudio) and the filename extension builder.
const AsciiString *Rva002D9622Get(int audioType);
AsciiString Rva002DA398Get(int audioType);

enum ObjectID
{
	INVALID_ID
};

enum OwnerType
{
	OT_Positional,
	OT_Drawable,
	OT_Object
};

enum AudioType
{
	AT_Music,
	AT_Streaming,
	AT_SoundEffect
};

enum PortionToPlay
{
	PP_Attack,
	PP_Sound,
	PP_Decay,
	PP_Done
};

struct WeightedSound
{
	AsciiString m_name;
	unsigned int m_weight;
};

struct WeightedSoundRange
{
	WeightedSound *m_begin;
	WeightedSound *m_end;
	WeightedSound *m_capacity;

	unsigned int size() const { return m_end - m_begin; }
	bool empty() const { return m_begin == m_end; }
};

// Shared lea-field getters the event info's members are read through
// (+0x0C filename, +0x50 sounds, +0x60 attack sounds, +0x70 decay sounds).
class Rva001DBA69LeaField { public: void *get() const; };
class Rva001D96ECLeaField { public: void *get() const; };
class Rva001D96F0LeaField { public: void *get() const; };
class Rva001D96F4LeaField { public: void *get() const; };

struct AudioEventInfo
{
	const AsciiString *getFilename() const { return (const AsciiString *)((const Rva001DBA69LeaField *)this)->get(); }
	const WeightedSoundRange *getSounds() const { return (const WeightedSoundRange *)((const Rva001D96ECLeaField *)this)->get(); }
	const WeightedSoundRange *getAttackSounds() const { return (const WeightedSoundRange *)((const Rva001D96F0LeaField *)this)->get(); }
	const WeightedSoundRange *getDecaySounds() const { return (const WeightedSoundRange *)((const Rva001D96F4LeaField *)this)->get(); }

	unsigned char m_pad00[0x14];
	float m_volumeShift;			// +0x14
	float m_volumeShift2;			// +0x18
	unsigned char m_pad1C[0x04];
	float m_pitchShiftMin;			// +0x20
	float m_pitchShiftMax;			// +0x24
	float m_pitchShift2Min;			// +0x28
	float m_pitchShift2Max;			// +0x2C
	unsigned char m_pad30[0x04];
	int m_delayMin;				// +0x34
	int m_delayMax;				// +0x38
	unsigned char m_pad3C[0x04];
	int m_lastPlayedIndex;			// +0x40
	unsigned char m_pad44[0x04];
	unsigned char m_type;			// +0x48
	unsigned char m_pad49[0x03];
	unsigned int m_control;			// +0x4C
	unsigned char m_pad50[0x0C];
	unsigned int m_soundsTotalWeight;	// +0x5C
	unsigned char m_pad60[0x0C];
	unsigned int m_attackTotalWeight;	// +0x6C
	unsigned char m_pad70[0x0C];
	unsigned int m_decayTotalWeight;	// +0x7C
	unsigned char m_pad80[0x30];
	unsigned int m_soundType;		// +0xB0
};

class AudioEventRTS
{
public:
	unsigned int getSoundClass(void) const;
	bool isPositionalAudio(void) const;
	bool hasMoreLoops(void) const;
	void advanceNextPlayPortion(void);
	ObjectID getObjectID(void);
	void rva002D9ADC(void);
	void generateFilename(void);
	AsciiString getFilename(void);
	void generatePlayInfo(void);
	void rva002DAAD5(void);

private:
	void *m_vftable;
	AsciiString m_filenameToLoad;		// +0x04
	AudioEventInfo *m_eventInfo;		// +0x08
	char m_pad0C[0x10];
	AsciiString m_attackName;		// +0x1C
	AsciiString m_decayName;		// +0x20
	char m_pad24[0x10];
	unsigned int m_ownerID;			// +0x34
	int m_ownerType;			// +0x38
	char m_pad3C[0x10];
	unsigned char m_bypassLoops;		// +0x4C
	unsigned char m_filenameDirty;		// +0x4D
	unsigned char m_filenameGenerated;	// +0x4E
	unsigned char m_pad4F;
	unsigned char m_regenerateFilename;	// +0x50
	unsigned char m_pad51[0x02];
	unsigned char m_sequential;		// +0x53
	float m_pitchShift;			// +0x54
	float m_pitchShift2;			// +0x58
	float m_volumeShift;			// +0x5C
	float m_volumeShift2;			// +0x60
	float m_delay;				// +0x64
	int m_playingAudioIndex;		// +0x68
	char m_pad6C[0x08];
	PortionToPlay m_portionToPlayNext;	// +0x74
};

// ?getObjectID@AudioEventRTS@@QAE?AW4ObjectID@@XZ
ObjectID AudioEventRTS::getObjectID(void)
{
	if (m_ownerType == OT_Object)
		return (ObjectID)m_ownerID;
	return INVALID_ID;
}

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
			m_portionToPlayNext = ((const StringBase<char> *)&m_decayName)->isEmpty() ? PP_Done : PP_Decay;
		break;
	case PP_Decay:
		m_portionToPlayNext = PP_Done;
		break;
	}
}

// ?rva002D9ADC@AudioEventRTS@@QAEXXZ
void AudioEventRTS::rva002D9ADC(void)
{
	if (!m_eventInfo)
		return;

	int maximumDelay = m_eventInfo->m_delayMax;
	int minimumDelay = m_eventInfo->m_delayMin;
	m_delay = GetGameAudioRandomValueReal((float)minimumDelay, (float)maximumDelay, AUDIO_EVENT_RTS_FILE, 413);
	m_pitchShift2 = GetGameAudioRandomValueReal(m_eventInfo->m_pitchShift2Min * 0.01f + 1.0f, m_eventInfo->m_pitchShift2Max * 0.01f + 1.0f, AUDIO_EVENT_RTS_FILE, 415);
	m_volumeShift2 = GetGameAudioRandomValueReal(m_eventInfo->m_volumeShift2 + 1.0f, 1.0f, AUDIO_EVENT_RTS_FILE, 418);

	if (m_regenerateFilename)
	{
		m_filenameDirty = true;
		m_regenerateFilename = false;
	}
}
