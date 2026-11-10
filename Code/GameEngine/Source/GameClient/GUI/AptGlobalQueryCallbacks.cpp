// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
//
// BFME2's global Apt queries, free functions bound by these names
// ("InBetaDemo", "InGame", "DoTrace" ...) through the free-function holder
// 0x004106FA by the global registration 0x00412F14; that binding is their
// only reference. Each answers into the result buffer unless the query is
// a write (skip). A body bound under several names keeps an address name.
// The same registration binds the global callbacks ("CloseWindow",
// "PlaySound", "OnClickThroughPress" ...) through the holder 0x0023E8D8.

// TheGlobalData's +0x9D4 (the demo kind the queries compare against).
class GlobalData;
extern class GlobalData *TheWritableGlobalData;

struct AptGlobalQueryData
{
	unsigned char m_pad000[0x9D4];
	int m_demoKind; // +0x9D4
};

// The trace flag GlobalByteFlagSetters.cpp's Rva004128E8SetFlag sets.
extern unsigned char g_Va00E0302C;

// Retail calls _mbscpy through the import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include "Common/BfmeAudioEventPrefix136.h"
#include <string.h>

// The Apt window manager's rowed byte setter 0x00222479 (closing the
// current window).
#include "../../../Include/Common/Rva00222479ByteOneSetter.h"

class Rva00222A8BTarget;
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// The click-through handler (Rva0043283CDtor.cpp's singleton
// g_Va00E032C8); its unrowed press and release handlers 0x00432AA2 and
// 0x00432AC5 are pinned by address.
// Both native handlers pick between the constructor's twenty 24-byte
// records at +8. The selected entry uses the existing payload prefix.
struct Rva00432931Entry {
 int m_00,m_04,m_08,m_0C;
 unsigned int m_10;
 unsigned char m_14;
 char m_pad15[3];
};
Rva00432931Entry *Rva00432931Pick(Rva00432931Entry *,Rva00432931Entry *);
struct Rva004328D8Payload;
void __stdcall Rva004328D8Emit(Rva004328D8Payload *);

class AptTranslator
{
public:
	void rva00432AA2();
	void rva00432AC5();
private:
 unsigned char m_prefix00[8];
 Rva00432931Entry m_entries08[20];
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

class AudioManager;
extern AudioManager *TheAudio;

// Retail 0x00412731, 11 bytes: "CloseWindow" closes the current Apt window.
void __cdecl CloseWindow(const char *unused)
{
	((Rva00222479ByteOneSetter *)g_bfmeAptWindowManager)->enable();
}

// Retail 0x00412A51, 162 bytes: "PlaySound" plays the named audio event.
void __cdecl PlaySound(const char *eventName)
{
	if (!TheAudio)
		return;
	AudioEventInfoRef info = ((AptGlobalAudioView *)TheAudio)->findAudioEvent(AsciiString(eventName));
	if (!info.m_info)
		return;
	BfmeAudioEventPrefix136 event(*(const OpaqueRefElement4 *)&info, 2);
	((AptGlobalAudioView *)TheAudio)->addAudioEvent(&event);
}

// Retail 0x004127D3, 11 bytes: "OnClickThroughPress".
void __cdecl OnClickThroughPress(const char *unused)
{
	((AptTranslator *)g_Va00E032C8)->rva00432AA2();
}

// Retail 0x004127DE, 11 bytes: "OnClickThroughRelease".
void __cdecl OnClickThroughRelease(const char *unused)
{
	((AptTranslator *)g_Va00E032C8)->rva00432AC5();
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
		_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>(((AptGlobalQueryData *)TheWritableGlobalData)->m_demoKind == 1 ? "1" : "0"));
		break;
	case 2:
		_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>(((AptGlobalQueryData *)TheWritableGlobalData)->m_demoKind == 2 ? "1" : "0"));
		break;
	}
}

// Retail 0x00412787, 31 bytes: "InGame".
void __cdecl InGame(int query, char *result, bool skip)
{
	if (result && !skip)
		_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>("1"));
}

// Retail 0x004127A6, 45 bytes: "DoTrace".
void __cdecl DoTrace(int query, char *result, bool skip)
{
	if (result && !skip)
		_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>(g_Va00E0302C ? "1" : "0"));
}

// Retail 432AA2..432AC5 and432AC5..432AEB: choose press/release records
// 4/14 and6/16, then emit once. The existing emitter ignores the incoming
// ECX and pops one payload word. This projection retains native's receiver
// load and reuses that complete row without asserting a second identity.
void AptTranslator::rva00432AA2()
{
 Rva00432931Entry *entry=Rva00432931Pick(&m_entries08[4],&m_entries08[14]);
 if(entry) {
  union {
   void (__stdcall *provider)(Rva004328D8Payload *);
   void (AptTranslator::*caller)(Rva004328D8Payload *);
  } emit;
  emit.provider=&Rva004328D8Emit;
  (this->*emit.caller)(reinterpret_cast<Rva004328D8Payload *>(entry));
 }
}
void AptTranslator::rva00432AC5()
{
 Rva00432931Entry *entry=Rva00432931Pick(&m_entries08[6],&m_entries08[16]);
 if(entry) {
  union {
   void (__stdcall *provider)(Rva004328D8Payload *);
   void (AptTranslator::*caller)(Rva004328D8Payload *);
  } emit;
  emit.provider=&Rva004328D8Emit;
  (this->*emit.caller)(reinterpret_cast<Rva004328D8Payload *>(entry));
 }
}
