// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// Small OnInitialized / Continue Apt callbacks of four BFME2 screens, each
// bound by the name it carries ("AptMessenger::OnInitialized" ...) as a
// member pointer by its screen's registration; that binding is the only
// reference. Each class is a one-method view named for its string's prefix.

#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

// TheLivingWorldCampaignManager (Rva002B256EThunk.cpp's g_00E02D6C); +0x2C
// is set for the evil side.
class Rva003B8BAA;
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

struct AptCampaignReviewCampaign
{
	unsigned char m_pad00[0x2C];
	bool m_evil; // +0x2C
};

class GameWindow;
class BfmeKeyLC;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48)
#undef V
	virtual int winSetFocus(GameWindow *window) = 0;
};

extern GameWindowManager *TheWindowManager;

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxLength);

// g_00E0447C: matched references place it at VA 0x00e0447c (UnicodeString kept line; dynamic init 0x007B3132).
UnicodeString g_00E0447C;

// TheShell (VA 0x00E01E48, the ledger's g_Va00A01E48).
struct GlobalA01E48
{
	unsigned char m_pad[0x54];
	bool m_54; // +0x54
	unsigned char m_pad55[0x5D - 0x55];
	bool m_5d; // +0x5D
};

extern class Shell *TheShell;

// Rva0051280EEnable.cpp's 0x0051280E.
void Rva0051280EEnable();

class AptMessenger
{
public:
	void OnInitialized(const char *unused);

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	unsigned char m_pad280[0x29C - 0x280];
	bool m_initialized; // +0x29C
};

class AptInGameChat
{
public:
	void OnInitialized(const char *unused);
	// Bound as "AptInGameChat::OnClosed" and "AptMessenger::OnClosed": one
	// body or two folded, so it keeps its address.
	void rva004E8213(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	unsigned char m_pad280[0x284 - 0x280];
	GameWindow *m_entry; // +0x284
};

class AptDisconnectScreen
{
public:
	void OnInitialized(const char *unused);

private:
	unsigned char m_pad000[0x284];
	bool m_initialized; // +0x284
};

class AptCampaignReview
{
public:
	void Continue(const char *unused);
	void playerSideType(int query, char *result, bool skip);
};

// Retail 0x00511540, 27 bytes: "AptMessenger::OnInitialized".
void AptMessenger::OnInitialized(const char *unused)
{
	m_initialized = true;
	if (m_state == 0)
		m_state = 1;
}

// Retail 0x004E81FF, 20 bytes: "AptInGameChat::OnInitialized".
void AptInGameChat::OnInitialized(const char *unused)
{
	if (m_state == 0)
		m_state = 1;
}

// Retail 0x004E8213, 13 bytes: bound as "AptInGameChat::OnClosed" and
// "AptMessenger::OnClosed".
void AptInGameChat::rva004E8213(const char *unused)
{
	m_state = 4;
}

// Retail 0x00512CDF, 10 bytes: "AptDisconnectScreen::OnInitialized".
void AptDisconnectScreen::OnInitialized(const char *unused)
{
	m_initialized = true;
}

// Retail 0x00512823, 21 bytes: "AptCampaignReview::Continue".
void AptCampaignReview::Continue(const char *unused)
{
	if ((*(GlobalA01E48 **)&TheShell))
		(*(GlobalA01E48 **)&TheShell)->m_5d = true;
	Rva0051280EEnable();
}

// Retail 0x004E84FF, 93 bytes: "AptInGameChat::InitGadgets" restores the
// kept line into "InGameChatEntry" (at most 110 characters) and focuses it.
void AptInGameChat::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!window)
		return;
	if (strcmp(name, "InGameChatEntry") == 0)
	{
		GadgetTextEntrySetText(window, g_00E0447C);
		GadgetTextEntrySetMaxChars((BfmeKeyLC *)window, 110);
		TheWindowManager->winSetFocus(window);
		m_entry = window;
	}
}

// Retail 0x00512864, 48 bytes: "playerSideType", an Apt query answering
// "evil" or "good".
void AptCampaignReview::playerSideType(int query, char *result, bool skip)
{
	if (skip)
		return;
	AptCampaignReviewCampaign *campaign = (AptCampaignReviewCampaign *)((Rva003B8BAA *)TheCampaignManager);
	if (campaign && campaign->m_evil)
		strcpy(result, "evil");
	else
		strcpy(result, "good");
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
