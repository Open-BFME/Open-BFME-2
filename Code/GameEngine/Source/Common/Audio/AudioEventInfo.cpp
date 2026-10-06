// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AudioEventInfo accessors at their WorldBuilder home (AudioEventInfo.cpp).
// Names: WorldBuilder diagnostics (asserts at AudioEventInfo.cpp lines 149,
// 208, 216, 224, 230 name each method). Layout: retail bytes. The INI field
// table (see INI/AudioEventInfoParseSoundLists.cpp) stores the Sounds,
// Attack and Decay lists at +0x50/+0x60/+0x70 through the weighted-token
// parser and the Subsounds list at +0x80; the element types are the
// address-derived ones that unit already recovered.
//
//   ?isTightlyCoupledSound  @0x001D982B 60B  type +0xB0 == 2, +0x34 zero,
//       +0x4C bit 0 forces true, else at least two non-empty lists.
//   ?getSoundsVector        @0x001D96EC 4B   lea +0x50
//   ?getAttackSoundsVector  @0x001D96F0 4B   lea +0x60
//   ?getDecaySoundsVector   @0x001D96F4 4B   lea +0x70
//   ?getSubsoundVector      @0x001D96F8 7B   lea +0x80
// Retail asserts (WB only) are compiled out.
#include "ascii_string.h"
#include <vector>

struct RvaPair001D9F62 { AsciiString m_key; int m_value; ~RvaPair001D9F62(); };
class BfmeStringTailRecord156;

enum AudioType
{
	AT_Music,
	AT_Streaming,
	AT_SoundEffect,
	AT_Type3,		// BFME 2 addition, name unknown
	AT_Type4,		// BFME 2 addition, name unknown
	AT_Multisound	// 5: getVolumeSlider's jump table case WB reports as multisound
};

// Zero Hour's SoundType bit for voice events.
enum { ST_VOICE = 0x0010 };

class AudioEventInfo
{
public:
	typedef _STL::vector<RvaPair001D9F62> SoundsList;
	typedef _STL::vector<BfmeStringTailRecord156> SubsoundsList;

	bool isTightlyCoupledSound() const;
	const SoundsList &getSoundsVector() const;
	const SoundsList &getAttackSoundsVector() const;
	const SoundsList &getDecaySoundsVector() const;
	const SubsoundsList &getSubsoundVector() const;
	int getVolumeSlider();

private:
	char m_pad00[0x34];
	int m_34;				// +0x34
	char m_pad38[0x48 - 0x38];
	unsigned int m_type;	// +0x48, SoundType bits

	unsigned int m_flags;	// +0x4C
	SoundsList m_sounds;	// +0x50
	char m_pad5C[0x60 - 0x5C];
	SoundsList m_attackSounds;	// +0x60
	char m_pad6C[0x70 - 0x6C];
	SoundsList m_decaySounds;	// +0x70
	char m_pad7C[0x80 - 0x7C];
	SubsoundsList m_subsounds;	// +0x80
	char m_pad8C[0xB0 - 0x8C];
	AudioType m_soundType;	// +0xB0
	int m_volumeSlider;		// +0xB4, -1 until first asked
};

const AudioEventInfo::SoundsList &AudioEventInfo::getSoundsVector() const
{
	return m_sounds;
}

const AudioEventInfo::SoundsList &AudioEventInfo::getAttackSoundsVector() const
{
	return m_attackSounds;
}

const AudioEventInfo::SoundsList &AudioEventInfo::getDecaySoundsVector() const
{
	return m_decaySounds;
}

const AudioEventInfo::SubsoundsList &AudioEventInfo::getSubsoundVector() const
{
	return m_subsounds;
}

bool AudioEventInfo::isTightlyCoupledSound() const
{
	if (m_soundType == AT_SoundEffect && m_34 == 0)
	{
		if (m_flags & 1)
			return true;
		int count = 0;
		if (!m_sounds.empty())
			++count;
		if (!m_attackSounds.empty())
			++count;
		if (!m_decaySounds.empty())
			++count;
		if (count >= 2)
			return true;
	}
	return false;
}

// AudioEventInfo::getVolumeSlider, retail 0x001D9867 (86 bytes): WB names
// it and asserts it is not asked of a multisound. The slider is chosen once:
// voice events use slider 1, otherwise the sound type decides (music 2,
// streaming 1, sound effect 0, type 3 slider 3, anything else 0).
int AudioEventInfo::getVolumeSlider()
{
	if (m_volumeSlider == -1)
	{
		if (m_type & ST_VOICE)
		{
			m_volumeSlider = 1;
		}
		else
		{
			switch (m_soundType)
			{
			case AT_Music:
				m_volumeSlider = 2;
				break;
			case AT_SoundEffect:
			case AT_Type4:
				m_volumeSlider = 0;
				break;
			case AT_Streaming:
				m_volumeSlider = 1;
				break;
			case AT_Type3:
				m_volumeSlider = 3;
				break;
			case AT_Multisound:
				m_volumeSlider = 0;
				break;
			default:
				m_volumeSlider = 0;
				break;
			}
		}
	}
	return m_volumeSlider;
}
