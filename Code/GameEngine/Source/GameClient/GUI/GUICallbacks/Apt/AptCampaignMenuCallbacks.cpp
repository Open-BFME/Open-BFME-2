// cl: /O1 /DNDEBUG /MD
//
// BFME2's campaign menu screen Apt callbacks, 0x00521172 onward, bound by
// these names ("AptCampaignMenu::OnBttnMainMenu" ...) as member pointers by
// the screen's registration; that binding is their only reference. The
// class is named for the strings' prefix.

class GameMessage;

// Zero Hour's TheMessageStream (VA 0x00E00950, the ledger's
// MessageStreamSubsystem); appendMessage is vslot 18.
class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(int type);
};

extern MessageStream *MessageStreamSubsystem;

// TheLinearCampaignManager (VA 0x00DFDC8C, the ledger's
// g_Rva0023D607Holder); its unrowed 0x001ECEF6 forwards to its +0x10
// member's 0x001ECE98 and is pinned by address.
struct Rva0023D607Holder
{
	void rva001ECEF6();
};

extern Rva0023D607Holder *g_Rva0023D607Holder;

void __cdecl Rva005210ECEnable(bool flag);
void __cdecl Rva00434160Init(int a, int b, bool c);

class AptCampaignMenu
{
public:
	void OnBttnMainMenu(const char *unused);
	void OnBttnSaveGame(const char *unused);
	void OnBttnLoadGame(const char *unused);
	void OnBttnLastMission(const char *unused);
	void OnBttnNextMission(const char *unused);
};

// Retail 0x00521172, 11 bytes: "AptCampaignMenu::OnBttnMainMenu".
void AptCampaignMenu::OnBttnMainMenu(const char *unused)
{
	Rva005210ECEnable(true);
}

// Retail 0x0052117D, 17 bytes: "AptCampaignMenu::OnBttnSaveGame".
void AptCampaignMenu::OnBttnSaveGame(const char *unused)
{
	Rva00434160Init(3, 1, false);
}

// Retail 0x0052118E, 17 bytes: "AptCampaignMenu::OnBttnLoadGame".
void AptCampaignMenu::OnBttnLoadGame(const char *unused)
{
	Rva00434160Init(2, 1, false);
}

// Retail 0x0052119F, 26 bytes: "AptCampaignMenu::OnBttnLastMission".
void AptCampaignMenu::OnBttnLastMission(const char *unused)
{
	if (g_Rva0023D607Holder)
	{
		g_Rva0023D607Holder->rva001ECEF6();
		Rva005210ECEnable(false);
	}
}

// Retail 0x005211B9, 24 bytes: "AptCampaignMenu::OnBttnNextMission" posts
// message 0x21.
void AptCampaignMenu::OnBttnNextMission(const char *unused)
{
	MessageStreamSubsystem->appendMessage(0x21);
	Rva005210ECEnable(false);
}
