// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Target evidence at 0x00434220: chooses a localized multiplayer save-denied
// message, displays it with the SaveGameProgress title, then sets screen state
// +0x27C to 22. The neighboring AptSaveLoad callbacks establish the screen.
#include "unicode_string.h"

class AsciiString;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;
void __cdecl Rva00437EAC(int flags, const UnicodeString &title,
	const UnicodeString &message);

class AptSaveLoad
{
public:
	void MultiplayerSaveGameDenied(int result);

private:
	unsigned char m_pad000[0x27C];
	int m_state;
};

void AptSaveLoad::MultiplayerSaveGameDenied(int result)
{
	UnicodeString message;
	switch (result)
	{
	// Keep this order: MSVC assigns the observed cleanup-state bytes in
	// lexical case order even though it lays the dispatch blocks out by value.
	case 3:
		message = TheGameText->fetch("APT:MultiplayerSaveDeniedAutoDenied", 0);
		break;
	case 1:
		message = TheGameText->fetch("APT:MultiplayerSaveDeniedNoSpace", 0);
		break;
	case 2:
		message = TheGameText->fetch("APT:MultiplayerSaveDenied", 0);
		break;
	}
	Rva00437EAC(0, TheGameText->fetch("APT:SaveGameProgress", 0), message);
	m_state = 22;
}
