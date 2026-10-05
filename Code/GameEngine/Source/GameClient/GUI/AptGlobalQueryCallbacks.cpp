// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
//
// BFME2's global Apt queries, free functions bound by these names
// ("InBetaDemo", "InGame", "DoTrace" ...) through the free-function holder
// 0x004106FA by the global registration 0x00412F14; that binding is their
// only reference. Each answers into the result buffer unless the query is
// a write (skip). A body bound under several names keeps an address name.
// The same registration binds the global callbacks ("CloseWindow",
// "PlaySound", "OnClickThroughPress" ...) through the holder 0x0023E8D8.

extern "C" char *__cdecl strcpy(char *destination, const char *source);

// TheGlobalData's +0x9D4 (the demo kind the queries compare against).
class GlobalData;
extern GlobalData *TheGlobalData;

struct AptGlobalQueryData
{
	unsigned char m_pad000[0x9D4];
	int m_demoKind; // +0x9D4
};

// The trace flag GlobalByteFlagSetters.cpp's Rva004128E8SetFlag sets.
extern unsigned char g_Va00E0302C;

#include "Common/BfmeAudioEventPrefix136.h"

// The Apt window manager's rowed byte setter 0x00222479 (closing the
// current window).
class Rva00222479ByteOneSetter
{
public:
	void enable();
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

// The click-through handler (Rva0043283CDtor.cpp's singleton
// g_Va00E032C8); its unrowed press and release handlers 0x00432AA2 and
// 0x00432AC5 are pinned by address.
class Rva0043283C
{
public:
	void rva00432AA2();
	void rva00432AC5();
};

extern int g_Va00E032C8;

// TheAudio: vslot 75 looks an event up by name (a counted reference) and
// vslot 25 plays an event.
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

class AptGlobalAudioView
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24)
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event);
	V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74)
#undef V
	virtual AudioEventInfoRef findAudioEvent(const AsciiString &name);
};

extern AptGlobalAudioView *TheAudio;

// Retail 0x00412731, 11 bytes: "CloseWindow" closes the current Apt window.
void __cdecl CloseWindow(const char *unused)
{
	((Rva00222479ByteOneSetter *)TheRva00222A8BTarget)->enable();
}

// Retail 0x00412A51, 162 bytes: "PlaySound" plays the named audio event.
void __cdecl PlaySound(const char *eventName)
{
	if (!TheAudio)
		return;
	AudioEventInfoRef info = TheAudio->findAudioEvent(AsciiString(eventName));
	if (!info.m_info)
		return;
	BfmeAudioEventPrefix136 event(*(const OpaqueRefElement4 *)&info, 2);
	TheAudio->addAudioEvent(&event);
}

// Retail 0x004127D3, 11 bytes: "OnClickThroughPress".
// ?OnClickThroughPress@@YAXPBD@Z present-unmatched
void __cdecl OnClickThroughPress(const char *unused)
{
	((Rva0043283C *)g_Va00E032C8)->rva00432AA2();
}

// Retail 0x004127DE, 11 bytes: "OnClickThroughRelease".
// ?OnClickThroughRelease@@YAXPBD@Z present-unmatched
void __cdecl OnClickThroughRelease(const char *unused)
{
	((Rva0043283C *)g_Va00E032C8)->rva00432AC5();
}

// Retail 0x0041273C, 75 bytes: bound as "InBetaDemo" (query 1) and
// "InDreamMachineDemo" (query 2).
void __cdecl Rva0041273C(int query, char *result, bool skip)
{
	if (!result || skip)
		return;
	switch (query)
	{
	case 1:
		strcpy(result, ((AptGlobalQueryData *)TheGlobalData)->m_demoKind == 1 ? "1" : "0");
		break;
	case 2:
		strcpy(result, ((AptGlobalQueryData *)TheGlobalData)->m_demoKind == 2 ? "1" : "0");
		break;
	}
}

// Retail 0x00412787, 31 bytes: "InGame".
void __cdecl InGame(int query, char *result, bool skip)
{
	if (result && !skip)
		strcpy(result, "1");
}

// Retail 0x004127A6, 45 bytes: "DoTrace".
void __cdecl DoTrace(int query, char *result, bool skip)
{
	if (result && !skip)
		strcpy(result, g_Va00E0302C ? "1" : "0");
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
