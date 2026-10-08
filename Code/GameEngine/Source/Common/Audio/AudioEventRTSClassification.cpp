// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS
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
#include "Common/BfmeAudioEventPrefix136.h"

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

// Match the already verified AudioEventInfo.cpp accessor signatures. These
// return a reference to the native three-pointer vector at +0x50/60/70.
// WeightedSoundRange is the existing read-only view of that same storage;
// no vector body or competing accessor is instantiated by these declarations.
namespace _STL { template<class T> class allocator; template<class T, class A> class vector; }
struct RvaPair001D9F62;

struct AudioEventInfo
{
    typedef _STL::vector<RvaPair001D9F62, _STL::allocator<RvaPair001D9F62> > SoundsList;
    const SoundsList &getSoundsVector() const;
    const SoundsList &getAttackSoundsVector() const;
    const SoundsList &getDecaySoundsVector() const;
	const AsciiString *getFilename() const { return (const AsciiString *)((const Rva001DBA69LeaField *)this)->get(); }
	const WeightedSoundRange *getSounds() const { return (const WeightedSoundRange *)&getSoundsVector(); }
	const WeightedSoundRange *getAttackSounds() const { return (const WeightedSoundRange *)&getAttackSoundsVector(); }
	const WeightedSoundRange *getDecaySounds() const { return (const WeightedSoundRange *)&getDecaySoundsVector(); }

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

// Inline boundaries carried from BFME1's AudioEventRTSWeightedChoice.cpp:
// reading the sound type through retainAudioType and the event info through
// peekEventInfo reproduces retail's register choices for those chains.
__forceinline unsigned int retainAudioType(unsigned int type)
{
	return type;
}

class AudioEventRTS
{
public:
	__forceinline const AudioEventInfo *peekEventInfo(void) const
	{
		return m_eventInfo;
	}

	unsigned int getSoundClass(void) const;
	bool isPositionalAudio(void) const;
	bool hasMoreLoops(void) const;
	void advanceNextPlayPortion(void);
	ObjectID getObjectID(void);
	void rva002D9ADC(void);
	void generateFilename(void);
	AsciiString getFilename(void);
	void generatePlayInfo(void);
	void internalXfer(Xfer *xfer, const void *version);
	void rva002DAAD5(void);
	AsciiString rva002DA867(void);

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

// ?getRandomSoundIndexByWeight@@YAHIPBUWeightedSoundRange@@@Z
// Weighted random pick; -1 when the list carries no weight. Static, so MSVC
// passes the weight in EAX and the list in ECX as retail does.
static __declspec(noinline) int getRandomSoundIndexByWeight(unsigned int totalWeight, const WeightedSoundRange *sounds)
{
	if (!(totalWeight > 0))
		return -1;

	unsigned int remainingWeight = GetGameAudioRandomValue(0, totalWeight - 1, AUDIO_EVENT_RTS_FILE, 58);
	const WeightedSound *soundEntry = sounds->m_begin;
	const WeightedSound *end = sounds->m_end;
	while (soundEntry != end)
	{
		if (remainingWeight < soundEntry->m_weight)
			break;
		remainingWeight -= soundEntry->m_weight;
		++soundEntry;
	}

	if (soundEntry == end)
		return 0;
	return soundEntry - sounds->m_begin;
}

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

// ?generateFilename@AudioEventRTS@@QAEXXZ
void AudioEventRTS::generateFilename(void)
{
	if (!m_filenameDirty || !m_eventInfo)
		return;

	bool firstTime = !m_filenameGenerated;
	m_filenameGenerated = true;
	m_filenameDirty = false;

	bool bare = (m_eventInfo->m_control >> 6) & 1;
	if (bare)
		m_filenameToLoad.clear();
	else
		m_filenameToLoad = *Rva002D9622Get(m_eventInfo->m_soundType);

	if (retainAudioType(m_eventInfo->m_soundType) != AT_SoundEffect)
	{
		m_filenameToLoad.concat(*m_eventInfo->getFilename());
		return;
	}

	const WeightedSoundRange *sounds = m_eventInfo->getSounds();
	unsigned int totalWeight = m_eventInfo->m_soundsTotalWeight;
	if (totalWeight == 0 || sounds->empty())
	{
		m_filenameToLoad = AsciiString::TheEmptyString;
		return;
	}

	int which;
	if ((m_eventInfo->m_control & 2) == 0 && !m_sequential)
	{
		if (sounds->size() > 1)
		{
			if (firstTime)
				m_playingAudioIndex = m_eventInfo->m_lastPlayedIndex;
			do
			{
				which = getRandomSoundIndexByWeight(totalWeight, sounds);
			} while (which == m_playingAudioIndex);
			if (firstTime)
				m_eventInfo->m_lastPlayedIndex = which;
		}
		else
		{
			which = 0;
		}

		if (which == -1)
		{
			m_filenameToLoad = AsciiString::TheEmptyString;
			return;
		}
		m_playingAudioIndex = which;
	}
	else
	{
		which = (++m_playingAudioIndex) % sounds->size();
	}

	const WeightedSound *soundArray = sounds->m_begin;
	m_filenameToLoad.concat(soundArray[which].m_name);
	if (!bare)
		m_filenameToLoad.concat(Rva002DA398Get(retainAudioType(peekEventInfo()->m_soundType)));
}

// ?getFilename@AudioEventRTS@@QAE?AVAsciiString@@XZ
AsciiString AudioEventRTS::getFilename(void)
{
	if (m_filenameDirty && m_eventInfo != 0)
		generateFilename();
	return m_filenameToLoad;
}

// ?rva002DA867@AudioEventRTS@@QAE?AVAsciiString@@XZ, RVA 0x002DA867 size 72.
// Returns the string for the current play portion (+0x74 PP_Attack/Sound/Decay/Done).
// Evidence: abuts rowed getFilename 0x002DA838 in this TU; switch on +0x74 matches
// PP enum; case 1 calls rowed getFilename 0x002DA838; case 0 forwards to the rowed
// +0x1C getter rowed as ?getPath@CDDrive@@UAE?AVAsciiString@@XZ (same offset as
// m_attackName); case 2 forwards to the rowed +0x20 getter
// ?get@Rva002D9BC1AsciiField@@QBE?AVAsciiString@@XZ (same offset as m_decayName);
// default copies AsciiString::TheEmptyString. Callees called by their row names.
class CDDrive
{
public:
	virtual AsciiString getPath(void);
};

class Rva002D9BC1AsciiField
{
public:
	AsciiString get(void) const;
};

AsciiString AudioEventRTS::rva002DA867(void)
{
	switch (m_portionToPlayNext)
	{
	case PP_Attack:
		return ((CDDrive *)this)->CDDrive::getPath();
	case PP_Sound:
		return getFilename();
	case PP_Decay:
		return ((const Rva002D9BC1AsciiField *)this)->Rva002D9BC1AsciiField::get();
	default:
		return AsciiString::TheEmptyString;
	}
}

// Native 0x002DA8AF..0x002DAAD5 (550B), AudioEventRTS::generatePlayInfo.
// ZH AudioEventRTS.cpp and BFME1 AudioEventRTSWeightedChoice.cpp establish
// the pitch/volume randomization and attack/decay weighted-selection purpose.
// BFME1 donor revision: 9cbfb551fe20dae985f91f2319d8997287b6a705.
// Target deltas: percent pitch scale, bare-name control bit 6, and the fallback
// from missing attack to sound, decay, or done. The +0x54/+0x5C, +0x1C/+0x20
// and +0x74 stores and calls to the matched weighted/prefix/extension workers
// independently establish these fields. Cache weights before getter calls;
// the shared StringBase clear worker joins the temporary's cleanup tail.
void AudioEventRTS::generatePlayInfo(void)
{
	m_pitchShift = GetGameAudioRandomValueReal(m_eventInfo->m_pitchShiftMin * 0.01f + 1.0f, m_eventInfo->m_pitchShiftMax * 0.01f + 1.0f, AUDIO_EVENT_RTS_FILE, 0x243);
	m_volumeShift = GetGameAudioRandomValueReal(m_eventInfo->m_volumeShift + 1.0f, 1.0f, AUDIO_EVENT_RTS_FILE, 0x244);

	bool bare = (m_eventInfo->m_control >> 6) & 1;
	if (m_eventInfo->m_soundType == AT_SoundEffect)
	{
		m_portionToPlayNext = PP_Attack;
		unsigned attackWeight = m_eventInfo->m_attackTotalWeight;
		int which = getRandomSoundIndexByWeight(attackWeight, m_eventInfo->getAttackSounds());
		if (which >= 0)
		{
			if (bare)
			{
				const WeightedSound *soundArray = m_eventInfo->getAttackSounds()->m_begin;
				m_attackName = soundArray[which].m_name;
			}
			else
			{
				m_attackName = *Rva002D9622Get(m_eventInfo->m_soundType);
				const WeightedSound *soundArray = m_eventInfo->getAttackSounds()->m_begin;
				m_attackName.concat(soundArray[which].m_name);
				m_attackName.concat(Rva002DA398Get(retainAudioType(peekEventInfo()->m_soundType)));
			}
		}
		else
		{
			if (!m_eventInfo->getSounds()->empty())
				m_portionToPlayNext = PP_Sound;
			else
				m_portionToPlayNext = m_eventInfo->getDecaySounds()->empty() ? PP_Done : PP_Decay;
		}
		unsigned decayWeight = m_eventInfo->m_decayTotalWeight;
		which = getRandomSoundIndexByWeight(decayWeight, m_eventInfo->getDecaySounds());
		if (which >= 0)
		{
			if (bare)
			{
				const WeightedSound *soundArray = m_eventInfo->getDecaySounds()->m_begin;
				m_decayName = soundArray[which].m_name;
			}
			else
			{
				m_decayName = *Rva002D9622Get(m_eventInfo->m_soundType);
				const WeightedSound *soundArray = m_eventInfo->getDecaySounds()->m_begin;
				m_decayName.concat(soundArray[which].m_name);
				m_decayName.concat(Rva002DA398Get(retainAudioType(peekEventInfo()->m_soundType)));
			}
		}
		else
			((StringBase<char> *)&m_decayName)->clear();
	}
	else
		m_portionToPlayNext = PP_Sound;
}

// Native 0x002D9D7C..0x002D9F9F (547B, RET8). WorldBuilder BD6C40
// names AudioEventRTS::internalXfer and independently corroborates the calls.
// Retail serializes the event-info name, owner tag/ID or position, flags and
// fields gated by version bytes 2..6. The caller 2D9FD9 builds two version
// bytes (1,6); only the second byte is read here. The existing 0x88-byte
// BfmeAudioEventPrefix136 view supplies independently verified field offsets.
// The name getter's old char-pointer declaration is opaque: its result is an
// AsciiString object, proven here by retail's StringBase copy constructor.
// Audio-manager slot75 returns an owning four-byte ref; slot103 transfers
// pool10. These contracts and the temporary's release/unwind are target facts.
struct Rva002D9D7CRef : OpaqueRefElement4 {
 // ?Rva002D9D7CRef::~Rva002D9D7CRef present-unmatched
 ~Rva002D9D7CRef() { if (referent) referent->Release_Ref(); }
};
class AudioManager {
public:
 virtual void a0();
 virtual void a1();
 virtual void a2();
 virtual void a3();
 virtual void a4();
 virtual void a5();
 virtual void a6();
 virtual void a7();
 virtual void a8();
 virtual void a9();
 virtual void a10();
 virtual void a11();
 virtual void a12();
 virtual void a13();
 virtual void a14();
 virtual void a15();
 virtual void a16();
 virtual void a17();
 virtual void a18();
 virtual void a19();
 virtual void a20();
 virtual void a21();
 virtual void a22();
 virtual void a23();
 virtual void a24();
 virtual void a25();
 virtual void a26();
 virtual void a27();
 virtual void a28();
 virtual void a29();
 virtual void a30();
 virtual void a31();
 virtual void a32();
 virtual void a33();
 virtual void a34();
 virtual void a35();
 virtual void a36();
 virtual void a37();
 virtual void a38();
 virtual void a39();
 virtual void a40();
 virtual void a41();
 virtual void a42();
 virtual void a43();
 virtual void a44();
 virtual void a45();
 virtual void a46();
 virtual void a47();
 virtual void a48();
 virtual void a49();
 virtual void a50();
 virtual void a51();
 virtual void a52();
 virtual void a53();
 virtual void a54();
 virtual void a55();
 virtual void a56();
 virtual void a57();
 virtual void a58();
 virtual void a59();
 virtual void a60();
 virtual void a61();
 virtual void a62();
 virtual void a63();
 virtual void a64();
 virtual void a65();
 virtual void a66();
 virtual void a67();
 virtual void a68();
 virtual void a69();
 virtual void a70();
 virtual void a71();
 virtual void a72();
 virtual void a73();
 virtual void a74();
 virtual Rva002D9D7CRef a75(const AsciiString *name);
 virtual void a76();
 virtual void a77();
 virtual void a78();
 virtual void a79();
 virtual void a80();
 virtual void a81();
 virtual void a82();
 virtual void a83();
 virtual void a84();
 virtual void a85();
 virtual void a86();
 virtual void a87();
 virtual void a88();
 virtual void a89();
 virtual void a90();
 virtual void a91();
 virtual void a92();
 virtual void a93();
 virtual void a94();
 virtual void a95();
 virtual void a96();
 virtual void a97();
 virtual void a98();
 virtual void a99();
 virtual void a100();
 virtual void a101();
 virtual void a102();
 virtual void a103(Xfer *xfer, BfmePoolRef10 *ref);
};
extern AudioManager *TheAudio;

class Rva002D9AC3 { public: const char *rva002D9AC3(); };
class Xfer {
public:
 virtual void x0();
 virtual bool isLoad();
 virtual void x2();
 virtual void x3();
 virtual void x4();
 virtual void x5();
 virtual void x6();
 virtual void x7();
 virtual void x8();
 virtual void x9();
 virtual void x10();
 virtual void x11();
 virtual void x12();
 virtual void x13();
 virtual void x14();
 virtual void x15();
 virtual void x16();
 virtual void x17();
 virtual void x18();
 virtual void x19();
 virtual void x20();
 virtual void x21();
 virtual void x22();
 virtual void x23();
 virtual void coord(BfmeEventPositionView *value);
 virtual void x25();
 virtual void x26();
 virtual void ascii(AsciiString *value);
 virtual void real(float *value);
 virtual void x29();
 virtual void x30();
 virtual void integer(int *value);
 virtual void x32();
 virtual void x33();
 virtual void x34();
 virtual void byte(char *value);
 virtual void boolean(unsigned char *value);
};

void XferDrawableID(Xfer *xfer, int *id);
void XferObjectID(Xfer *xfer, ObjectID *id);
void XferLivingWorldUniqueID(Xfer *xfer, int *id);
void XferLivingWorldArmyID(Xfer *xfer, int *id);
void XferLivingWorldPlayerID(Xfer *xfer, int *id);
class Rva004E075FObj;
int Rva004E075FGet(Rva004E075FObj *xfer, int value);
void AudioEventRTS::internalXfer(Xfer *xfer, const void *version)
{
 BfmeAudioEventPrefix136 &event = *(BfmeAudioEventPrefix136 *)this;
 AsciiString name(*(const AsciiString *)((Rva002D9AC3 *)this)->rva002D9AC3());
 xfer->ascii(&name);
 if (xfer->isLoad()) {
  if (name.isEmpty())
   ((Rva000A8C9B *)&event.m_pool08)->clear();
  else
   *(OpaqueRefElement4 *)&event.m_pool08 = TheAudio->a75(&name);
 }
 char owner = (char)event.m_int38;
 xfer->byte(&owner);
 event.m_int38 = owner;
 switch (event.m_int38) {
 case 0: xfer->coord(&event.m_position); break;
 case 1: XferDrawableID(xfer, &event.m_int34); break;
 case 2: XferObjectID(xfer, (ObjectID *)&event.m_int34); break;
 case 3: XferLivingWorldUniqueID(xfer, &event.m_int34); break;
 case 4: XferLivingWorldArmyID(xfer, &event.m_int34); break;
 case 5: Rva004E075FGet((Rva004E075FObj *)xfer, (int)&event.m_int34); break;
 }
 const unsigned char *v = (const unsigned char *)version;
 if (v[1] >= 2) xfer->boolean(&event.m_b48);
 xfer->boolean(&event.m_b49);
 if (v[1] < 5) { unsigned char obsolete = 0; xfer->boolean(&obsolete); }
 xfer->boolean(&event.m_b4A);
 xfer->integer(&event.m_int6C);
 if (v[1] >= 4) XferLivingWorldPlayerID(xfer, &event.m_int70);
 xfer->boolean(&event.m_b4C);
 char logical = (char)event.m_int30;
 xfer->byte(&logical);
 event.m_int30 = logical;
 char portion = (char)event.m_int78;
 xfer->byte(&portion);
 event.m_int78 = portion;
 xfer->ascii(&event.m_string84);
 xfer->integer(&event.m_int7C);
 xfer->real(&event.m_f2C);
 if (v[1] >= 3) xfer->integer(&event.m_int80);
 if (v[1] >= 6) {
  xfer->integer(&event.m_int14);
  TheAudio->a103(xfer, &event.m_pool10);
 }
}
