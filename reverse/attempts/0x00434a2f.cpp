// ?rva00434A2F@AptSaveLoad@@QAEXXZ
// partial score=0.9 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Retail 0x00434A2F trims the text-entry value and invokes the current-filename
// Apt callback with the selected screen owner and whether the value is nonempty.
#include "unicode_string.h"

class GameWindow;
class Rva00222A8BTarget;

struct UnicodeStringBufferHeader
{
	int m_references;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_text[1];
};

UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
GameWindow *Rva00222547Get(GameWindow *window);
int __cdecl Rva002D4531Invoke(Rva00222A8BTarget *target, void *owner,
	const char *name, const int &value);
extern Rva00222A8BTarget *TheRva00222A8BTarget;

class AptSaveLoad
{
public:
	void rva00434A2F();

private:
	unsigned char m_pad000[0x27C];
	int m_state;
	void *m_pending;
	unsigned char m_pad284[4];
	GameWindow *m_gameList;
	GameWindow *m_autoSaveList;
	GameWindow *m_fileName;
};

void AptSaveLoad::rva00434A2F()
{
	UnicodeString text = GadgetTextEntryGetText(m_fileName);
	text.trim();
	UnicodeStringBufferHeader *header =
		*(UnicodeStringBufferHeader **)&text;
	int hasText;
	if (header && header->m_length != 0)
		hasText = 1;
	else
		hasText = 0;
	Rva002D4531Invoke(TheRva00222A8BTarget,
		Rva00222547Get((GameWindow *)this), "APT:CurrentFilename", hasText);
}
