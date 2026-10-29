// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?Rva003C0425Do@@YGXABVAsciiString@@_N0HV1@H@Z, retail 0x003C0425 (269 bytes,
// EH, RET 0x18). Script audio action with a speech-style tail: finds the named
// event (TheAudio slot 0x12C, no null guard), clamps the count to at least 1
// (-12345 passes through), flags the event, stamps the local player, appends
// the script-engine path join of the text when it is not empty and posts it
// through TheAudio slot 0x84 with the overlap flag inverted. Honest address
// name: the WorldBuilder name is not proven.
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

class AudioEventInfoRef
{
public:
	~AudioEventInfoRef()
	{
		if (m_info)
			m_info->Release_Ref();
	}

	OpaqueRefCounted *m_info;
};

class Rva003C0425AudioView
{
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(0) AUDIO_SLOT(1) AUDIO_SLOT(2) AUDIO_SLOT(3) AUDIO_SLOT(4)
	AUDIO_SLOT(5) AUDIO_SLOT(6) AUDIO_SLOT(7) AUDIO_SLOT(8) AUDIO_SLOT(9)
	AUDIO_SLOT(10) AUDIO_SLOT(11) AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14)
	AUDIO_SLOT(15) AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24)
#undef AUDIO_SLOT
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event);
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
	AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32)
#undef AUDIO_SLOT
	virtual void addAudioEventSlot33(const BfmeAudioEventPrefix136 *event, int flag);
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(34)
#undef AUDIO_SLOT
	virtual void slot35(int a, int b, int c);
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38)
	AUDIO_SLOT(39) AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43)
	AUDIO_SLOT(44) AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48)
	AUDIO_SLOT(49) AUDIO_SLOT(50) AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53)
	AUDIO_SLOT(54) AUDIO_SLOT(55) AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58)
	AUDIO_SLOT(59) AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63)
	AUDIO_SLOT(64) AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68)
	AUDIO_SLOT(69) AUDIO_SLOT(70) AUDIO_SLOT(71) AUDIO_SLOT(72) AUDIO_SLOT(73)
	AUDIO_SLOT(74)
#undef AUDIO_SLOT
	virtual AudioEventInfoRef findAudioEvent(const AsciiString &name);
};

class Rva0033F15DDwordSlot
{
public:
	void set(int value);
};

class Weapon
{
public:
	void setLeechRangeActive(bool);
};

class Player
{
public:
	unsigned char m_pad00[0x54];
	int m_playerIndex;
};

class PlayerList
{
public:
	unsigned char m_pad00[0x10];
	Player *m_localPlayer;
};
extern PlayerList *ThePlayerList;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C0425Do(const AsciiString &eventName, bool allowOverlap, bool leech,
	int count, const AsciiString &text, int extra)
{
	if (count < 1 && count != -12345)
		count = 1;
	AudioEventInfoRef info = reinterpret_cast<Rva003C0425AudioView *>(TheAudio)->findAudioEvent(eventName);
	BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4 *>(&info), 0);
	reinterpret_cast<Weapon *>(&event)->setLeechRangeActive(leech);
	reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(ThePlayerList->m_localPlayer->m_playerIndex);
	event.m_int78 = extra;
	event.m_int7C = count;
	if (!text.isEmpty())
		event.m_string84 = TheScriptEngine->rva00205CE7(text);
	int post = !allowOverlap;
	reinterpret_cast<Rva003C0425AudioView *>(TheAudio)->addAudioEventSlot33(&event, post);
}

// 0x003C0308 (285 bytes, EH, RET 0x18): the same action with a TheAudio slot 0x8C
// pre-call (0, extra, overlap flag inverted) and the plain addAudioEvent post.
void ScriptActions::Rva003C0308Do(const AsciiString &eventName, bool allowOverlap, bool leech,
	int count, const AsciiString &text, int extra)
{
	int post = !allowOverlap;
	reinterpret_cast<Rva003C0425AudioView *>(TheAudio)->slot35(0, extra, post);
	if (count < 1 && count != -12345)
		count = 1;
	AudioEventInfoRef info = reinterpret_cast<Rva003C0425AudioView *>(TheAudio)->findAudioEvent(eventName);
	BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4 *>(&info), 0);
	reinterpret_cast<Weapon *>(&event)->setLeechRangeActive(leech);
	reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(ThePlayerList->m_localPlayer->m_playerIndex);
	event.m_int78 = extra;
	event.m_int7C = count;
	if (!text.isEmpty())
		event.m_string84 = TheScriptEngine->rva00205CE7(text);
	reinterpret_cast<Rva003C0425AudioView *>(TheAudio)->addAudioEvent(&event);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
