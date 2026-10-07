// ?rva00240866@GameLogic@@QAEXPAVRva0023E928@@_N@Z
// partial score=0.93 date=2026-10-07
// Banked attempt: GameLogic::rva00240866 (0x240866, 961B) for
// Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp (cl flags of that TU).
// Residue: whole-function esi/edi swap (retail: esi=0, edi=this) plus one
// scheduling pair at 0x240BC0 (mov [ebp+8],esp / mov ecx,esp). Size and frame exact.
// A named UnicodeString for rva0023D30F(2, 1, ...) in the disk-full branch flips
// regalloc to retail's but costs 3 bytes (lea [ebp+8]).
// Needs pins: ?Rva00435CCC@@YAXXZ -> 0x435CCC, ?rva0023D32D@GameLogic@@QAE_NXZ -> 0x23D32D.
// Each hunk below is placed at the line given by its '@@' marker.

// @@ -554,0 +555,3 @@ public:
	void rva00240866(class Rva0023E928 *msg, bool frozen);
	bool rva0023D32D(void);
	void rva0023D30F(int a, int b, UnicodeString *name);
// @@ -2152,0 +2156 @@ public:
	virtual int slotB8(void);                                            // +0xB8
// @@ -3082,0 +3087,2 @@ public:

	void rva002DDE43(const UnicodeString &a, const UnicodeString &b, int c, int d);
// @@ -4024,0 +4031,149 @@ const AsciiString &GameLogic::rva0023FB58(int index)
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
extern "C" void __cdecl Rva00437F61(int type, const UnicodeString &title,
	const UnicodeString &text, Rva0023E8D8 callback);

typedef void (__cdecl *Rva00240866Answer)(int button);

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
		if (TheGameLogic->m_11d)
			break;
		if (player != TheNetwork->slotB8()) {
			if (!rva0023D32D()) {
				if (frozen)
					++m_40;
				rva0023D30F(2, 3, &msg->rva0023E928());
				if (frozen)
					--m_40;
				break;
			}
			if (g_Va00E032E0)
				((Rva00433FDD *)g_Va00E032E0)->rva00433D96();
		}
		TheGameLogic->m_11d = true;
		if (player == TheNetwork->slotB8() || !TheGameState)
			break;
		if (!((Rva002DC267 *)TheGameState)->rva002DC681()) {
			if (frozen)
				++m_40;
			rva0023D30F(2, 1, &msg->rva0023E928());
			if (frozen)
				--m_40;
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
					Rva0023E8D8(&answer));
			}
		}
		break;
	case 5:
		TheGameState->rva002DDE43(msg->rva0023E928(), msg->rva0023E928(), 0, 1);
		Rva00435CCC();
		TheGameLogic->m_11d = false;
		break;
	case 2:
		if (player != TheNetwork->slotB8() && g_Va00E032E0)
			((AptSaveLoad *)g_Va00E032E0)->MultiplayerSaveGameDenied(msg->m_20);
		TheGameLogic->m_11d = false;
		break;
	}
}

