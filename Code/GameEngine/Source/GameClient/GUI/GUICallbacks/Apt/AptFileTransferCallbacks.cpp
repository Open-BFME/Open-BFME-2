// cl: /DNDEBUG /MD
//
// BFME2's map file transfer screen Apt query bound as
// "FileTransfer:PlayerColor:%d" for each slot index by the screen's
// registration (0x0058343A); that binding is its only reference. The class
// is named for the string's prefix (the screen whose destructor is the
// rowed ??1Rva00582FC1).

extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

class GameSlot
{
public:
	int getApparentColor() const;
};

class GameInfo
{
public:
	const GameSlot *getConstSlot(int index) const;
};

class MultiplayerColorDefinition
{
public:
	unsigned char m_pad00[0x10];
	int m_color; // +0x10
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int which);
};

extern MultiplayerSettings *TheMultiplayerSettings;

class FileTransfer
{
public:
	void PlayerColor(int slot, char *result, bool skip);

private:
	unsigned char m_pad00[0x58];
	GameInfo *m_game; // +0x58
};

// Retail 0x00583034, 94 bytes: "FileTransfer:PlayerColor:%d", an Apt query
// answering the slot's apparent color ("0" when out of range).
void FileTransfer::PlayerColor(int slot, char *result, bool skip)
{
	if (skip)
		return;
	strcpy(result, "0");
	if (slot >= 0 && slot < 8)
	{
		const GameSlot *gameSlot = m_game->getConstSlot(slot);
		sprintf(result, "%d", TheMultiplayerSettings->getColor(gameSlot->getApparentColor())->m_color);
	}
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
