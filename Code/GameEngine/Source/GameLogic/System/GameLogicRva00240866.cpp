template<class T> static __forceinline T p4Operand(const T &v) { return *(const volatile T*)&v; }
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /I.
// stlport
//
// ?rva00240866@GameLogic@@QAEXPAVRva0023E928@@_N@Z @0x00240866 961B.
// Multiplayer save-request handler (message 0x1E, called by 0x0025E661); the
// per-kind behaviour is documented at the definition below.
// Codegen finding (retail order "mov [ebp+8],esp" BEFORE "mov ecx,esp" for the
// by-value prompt-callback temp): the callback argument must be built through an
// INLINE derived wrapper (Rva0023E8D8Arg) that calls the out-of-line rowed ctor
// 0x0023E8D8; the extern "C" prompt helper 0x00437F61 takes the wrapper by value
// (its C name carries no parameter types). With the plain class the compiler
// emits the two instructions in the opposite order. (O1 round 11)

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;
class GameInfo;
extern GameInfo *TheGameInfo;
class NetworkInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d(); virtual void v0e();
	virtual void slot3C(int arg);                                        // +0x3C
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
	virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
	virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void slot90(void);                                           // +0x90
	virtual void slot94(void);                                           // +0x94
	virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v2a();
	virtual bool slotAC(void);                                           // +0xAC
	virtual void v2c();
	virtual int slotB4(void);                                            // +0xB4
 virtual int slotB8();

};

extern NetworkInterface *TheNetwork;

class GameState
{
	char m_pad00[0x2c];
public:
 void rva002DDE43(const UnicodeString&,const UnicodeString&,int,int);

	AsciiString m_pristineMapName;                                       // +0x2C
};
extern GameState *TheGameState;

class GameTextInterface
{
public:
	virtual void g00(void) = 0;
	virtual void g01(void) = 0;
	virtual void g02(void) = 0;
	virtual void g03(void) = 0;
	virtual void g04(void) = 0;
	virtual void g05(void) = 0;
	virtual void g06(void) = 0;
	virtual void g07(void) = 0;
	virtual void g08(void) = 0;
	virtual void g09(void) = 0;
	virtual void g10(void) = 0;
	virtual void g11(void) = 0;
	virtual void g12(void) = 0;
	virtual void g13(void) = 0;
	virtual void g14(void) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0; // +0x3C
	virtual void g16(void) = 0;
	virtual void g17(void) = 0;
	virtual void g18(void) = 0;
	virtual void initMapStringFile(const AsciiString &filename) = 0;  // +0x4C
};

extern GameTextInterface *TheGameText;

// The network request 0x00240866 answers: the sending player at +0x0C, the
// request kind at +0x1C, an argument at +0x20 and the save name through the
// rowed RVO getter 0x0023E928.
class Rva0023E928
{
public:
	UnicodeString rva0023E928(void) const;

	unsigned char m_pad00[0x0c];
	int m_player;                                                        // +0x0C
	unsigned char m_pad10[0x1c - 0x10];
	int m_kind;                                                          // +0x1C
	int m_20;                                                            // +0x20
};

// The save screen (0x00E032E0 while the saved-game prompt is up) and its
// rowed members.
class AptSaveLoad
{
public:
	void MultiplayerSaveGameDenied(int reason);
};

class Rva00433FDD
{
public:
	void rva00433D96(void);
};

extern int g_Va00E032E0;
extern UnicodeString g_Va00E032E8;
void __cdecl Rva004341D8(int button);
void __cdecl Rva00435CCC(void);

// TheGameState's rowed save-directory free-space check and save-exists test.
class Rva002DC267
{
public:
	bool rva002DC681(void) const;
};

class Rva002DCCFB
{
public:
	bool rva002DCCFB(UnicodeString name);
};


// The refcounted prompt callback (0x0023E8D8 builds it from a pointer to
// the function pointer) and the two prompt forwarders.
struct TargetRef00217D4C;
extern void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

class Rva0023E8D8
{
	void *m_ptr;
public:
	Rva0023E8D8(void *p);
	Rva0023E8D8(const Rva0023E8D8 &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++((int *)m_ptr)[1];
	}
	~Rva0023E8D8()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

void Rva00437E84(int type, const UnicodeString &title, const UnicodeString &text);
struct Rva0023E8D8Arg : Rva0023E8D8 { Rva0023E8D8Arg(void *p) : Rva0023E8D8(p) {} };
extern "C" void __cdecl Rva00437F61(int type, const UnicodeString &title,
	const UnicodeString &text, Rva0023E8D8Arg callback);

typedef void (__cdecl *Rva00240866Answer)(int button);


unsigned char __cdecl Rva0023D32DGet();

// The retail callee 0x0023D32D is a plain cdecl getter reached with a member-call shape.
static __forceinline unsigned char callRva0023D32D(GameLogic *self)
{
	typedef unsigned char (GameLogic::*Member)();
	union NativeCallView { unsigned char (__cdecl *function)(); Member member; } call;
	call.function = Rva0023D32DGet;
	return (self->*call.member)();
}

// ?rva00240866@GameLogic@@QAEXPAVRva0023E928@@_N@Z @0x00240866 961B (Ghidra
// FUN_00640866). The multiplayer save request handler 0x0025E661 calls for
// message 0x1E. Kind 1 asks to save: a remote request is refused (2, 3)
// unless 0x0023D32D allows it, then the local player confirms through the
// "APT:SaveGameMultiplayerConfirmationTitle" prompt answered by 0x004341D8,
// or refuses (2, 1) with "APT:SaveFileDiskFullMultiplayer"; kind 2 is a
// refusal the save screen reports; kind 5 saves through TheGameState.
void GameLogic::rva00240866(Rva0023E928 *msg, bool frozen)
{
	if (!TheGameInfo || !msg || !TheNetwork || !TheGameState)
		return;
	int player = msg->m_player;
	switch (msg->m_kind) {
	case 1:
		if ((msg?p4Operand(*(bool *)((char *)TheGameLogic + 0x11D)):p4Operand(*(bool *)((char *)TheGameLogic + 0x11D))))
			break;
		if (player != TheNetwork->slotB8()) {
			if (!callRva0023D32D(this)) {
				if (frozen)
					++*(unsigned int *)((char *)this + 0x40);
				rva0023D30F(2, 3, &msg->rva0023E928());
				if (frozen)
					--*(unsigned int *)((char *)this + 0x40);
				break;
			}
			if (g_Va00E032E0)
				((Rva00433FDD *)g_Va00E032E0)->rva00433D96();
		}
		*(bool *)((char *)TheGameLogic + 0x11D) = true;
		if (player == TheNetwork->slotB8() || !TheGameState)
			break;
		if (!((Rva002DC267 *)TheGameState)->rva002DC681()) {
			if (frozen)
				++*(unsigned int *)((char *)this + 0x40);
			rva0023D30F(2, 1, &msg->rva0023E928());
			if (frozen)
				--*(unsigned int *)((char *)this + 0x40);
			Rva00437E84(0, TheGameText->fetch("GUI:Error"),
				TheGameText->fetch("APT:SaveFileDiskFullMultiplayer"));
		} else {
			UnicodeString text = TheGameText->fetch("APT:ConfirmMultiplayerSave");
			if (((Rva002DCCFB *)TheGameState)->rva002DCCFB(msg->rva0023E928()))
				text = TheGameText->fetch("APT:ConfirmMultiplayerSaveWithOverwrite");
			if (text.find('%')) {
				UnicodeString name = msg->rva0023E928();
				if (name.reverseFind('.'))
					name = UnicodeString(name, 0, name.reverseFind('.') - name.str());
				text.format(&text, name.str());
			}
			g_Va00E032E8 = msg->rva0023E928();
			{
				Rva00240866Answer answer = Rva004341D8;
				Rva00437F61(2, TheGameText->fetch("APT:SaveGameMultiplayerConfirmationTitle"), text,
					Rva0023E8D8Arg(&answer));
			}
		}
		break;
	case 5:
		TheGameState->rva002DDE43(msg->rva0023E928(), msg->rva0023E928(), 0, 1);
		Rva00435CCC();
		*(bool *)((char *)TheGameLogic + 0x11D) = false;
		break;
	case 2:
		if (player != TheNetwork->slotB8() && g_Va00E032E0)
			((AptSaveLoad *)g_Va00E032E0)->MultiplayerSaveGameDenied(msg->m_20);
		*(bool *)((char *)TheGameLogic + 0x11D) = false;
		break;
	}
}
