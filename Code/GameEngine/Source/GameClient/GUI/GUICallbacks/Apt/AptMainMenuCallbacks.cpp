// cl: /O1 /DNDEBUG /MD
//
// BFME2's main menu screen Apt callbacks, 0x00514A9B onward. The screen's
// registration binds each by the name it carries here ("AptMainMenu::
// LoadGame" ...) as a member pointer, which is the only reference to them,
// so the names are the binding strings' and the class is named for their
// prefix (BFME1 calls the screen BfmeAptScreenMainMenu). Most of them
// leave the menu: state +0x288 becomes 9 and +0x28C names the screen to
// open next.

extern "C" int __cdecl strcmp(const char *left, const char *right);

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

// The game mode TheGameLogic (0x00DFE78C) keeps at +0x110.
class GameLogic;
extern GameLogic *TheGameLogic;

struct AptMainMenuGameLogic
{
	unsigned char m_pad000[0x110];
	int m_mode; // +0x110
};

class AptMainMenu
{
public:
	void LoadGame(const char *unused);
	void Options(const char *value);
	void GoodCampaign(const char *value);
	void EvilCampaign(const char *value);
	void CreateAHero(const char *unused);
	void WarOfTheRing(const char *unused);
	void LoadCampaign(const char *unused);
	void Skirmish(const char *unused);
	void LoadReplay(const char *unused);
	void StopGameMovie(const char *unused);

private:
	unsigned char m_pad000[0x288];
	int m_state; // +0x288
	int m_next; // +0x28C
	unsigned char m_pad290[0x2A8 - 0x290];
	char m_side; // +0x2A8
};

// Retail 0x00514A9B, 23 bytes: "AptMainMenu::LoadGame".
void AptMainMenu::LoadGame(const char *unused)
{
	m_state = 9;
	m_next = 1;
}

// Retail 0x00514AB2, 46 bytes: "AptMainMenu::Options", 5 when the value
// is "true", else 4.
void AptMainMenu::Options(const char *value)
{
	m_state = 9;
	m_next = strcmp(value, "true") ? 4 : 5;
}

// Retail 0x00514AE0, 35 bytes: "AptMainMenu::GoodCampaign", keeping the
// value's first character.
void AptMainMenu::GoodCampaign(const char *value)
{
	m_state = 9;
	m_next = 11;
	m_side = *value;
}

// Retail 0x00514B03, 35 bytes: "AptMainMenu::EvilCampaign".
void AptMainMenu::EvilCampaign(const char *value)
{
	m_state = 9;
	m_next = 12;
	m_side = *value;
}

// Retail 0x00514B26, 18 bytes: "AptMainMenu::CreateAHero".
void AptMainMenu::CreateAHero(const char *unused)
{
	m_state = 9;
	m_next = 9;
}

// Retail 0x00514B38, 23 bytes: "AptMainMenu::WarOfTheRing".
void AptMainMenu::WarOfTheRing(const char *unused)
{
	m_state = 9;
	m_next = 8;
}

// Retail 0x00514B4F, 23 bytes: "AptMainMenu::LoadCampaign".
void AptMainMenu::LoadCampaign(const char *unused)
{
	m_state = 9;
	m_next = 2;
}

// Retail 0x00514BC9, 23 bytes: "AptMainMenu::Skirmish".
void AptMainMenu::Skirmish(const char *unused)
{
	m_state = 9;
	m_next = 7;
}

// Retail 0x00514BE0, 23 bytes: "AptMainMenu::LoadReplay".
void AptMainMenu::LoadReplay(const char *unused)
{
	m_state = 9;
	m_next = 3;
}

// Retail 0x00514BF7, 30 bytes: "AptMainMenu::StopGameMovie" (BFME1's
// AptScreenSelectorCallbacks.cpp has its own): outside game mode 9 it posts
// message 0x1D.
void AptMainMenu::StopGameMovie(const char *unused)
{
	if (((AptMainMenuGameLogic *)TheGameLogic)->m_mode != 9)
		MessageStreamSubsystem->appendMessage(0x1D);
}
