// cl: /O1 /G7 /DNDEBUG /MD /EHs-
//
// BFME2's in-game player status screen Apt callback
// "AptPlayerStatus::InitGadgets", 0x004E40C7, bound by that name as a
// member pointer by the screen's registration; that binding is its only
// reference. The class is named for the string's prefix.
//
// Built /G7 (the bool goes out as mov al without the P6 xor) and without
// EH (the static's guard carries no frame), as retail.

extern "C" unsigned int __cdecl strlen(const char *text);
extern "C" __declspec(dllimport) int __cdecl strncmp(const char *left, const char *right, unsigned int count);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

class GameWindow
{
public:
	int winHide(bool hide);
};

void GadgetCheckBoxSetChecked(GameWindow *checkBox, bool checked);

class GameSlot
{
public:
	bool isAI() const;

	unsigned char m_pad00[0x0A];
	bool m_muted; // +0x0A
};

class GameInfo
{
public:
	const GameSlot *getConstSlot(int index) const;
};

// The game being played (LANAPIRemoveGame.cpp's g_Rva00E02EEC).
struct LANGameInfo;
extern LANGameInfo *g_Rva00E02EEC;

class AptPlayerStatus
{
public:
	void InitGadgets(const char *name, void *argument, GameWindow *window);

private:
	unsigned char m_pad000[0x28C];
	GameWindow *m_mute[8]; // +0x28C
	signed char m_slot[8]; // +0x2AC
};

// Retail 0x004E40C7, 178 bytes: "AptPlayerStatus::InitGadgets" keeps each
// "PlayerStatus::Mute<n>" check box, shown checked by the slot's mute flag
// for a human player and hidden otherwise.
void AptPlayerStatus::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	static int prefixLength = strlen("PlayerStatus::Mute");
	if (strncmp(name, "PlayerStatus::Mute", prefixLength) != 0)
		return;
	name += prefixLength;
	int index = atoi(name);
	if (index < 0 || index >= 8)
		return;
	m_mute[index] = window;
	window->winHide(true);
	signed char slot = m_slot[index];
	if (slot < 0)
		return;
	const GameSlot *gameSlot = ((GameInfo *)g_Rva00E02EEC)->getConstSlot(slot);
	if (gameSlot && !gameSlot->isAI())
	{
		window->winHide(false);
		GadgetCheckBoxSetChecked(window, gameSlot->m_muted);
	}
}
