// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Retail 0x00434AAE (220 bytes), reached on the AptSaveLoad screen after its
// FileNameTextEntry is set. The target reads the field at +0x290, gets the
// selected list item through 0x00433F7F, and either converts that item's
// StringBase buffer through the indirect slot at 0x00BBA4EC or supplies a
// fallback string from 0x0037D55E / GameState method 0x002DD282. The indirect
// slot is kept address-qualified: its raw value currently points inside a
// different body, so its semantic identity is unresolved.
#include "unicode_string.h"

class GameWindow;
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);

typedef int (__cdecl *Rva007BA4ECProc)(const unsigned short *source,
		int sourceOffset, int sourceLength, unsigned short *destination,
		int flags);
extern "C" Rva007BA4ECProc rva007BA4EC;

UnicodeString __cdecl Rva0037D55EGet();

class GameState
{
public:
	int rva002DBE62Get();
	UnicodeString rva002DD282(int mode);
};
extern GameState *TheGameState;

class AptSaveLoad
{
public:
	int rva00433F7F();
	void rva00434AAE();

private:
	unsigned char m_pad000[0x290];
	GameWindow *m_fileName;
	unsigned char m_pad294[0x2A0 - 0x294];
	int m_mode;
};

void AptSaveLoad::rva00434AAE()
{
	if (m_fileName == 0)
		return;

	int selected = rva00433F7F();
	if (selected != 0)
	{
		const unsigned short *source = ((UnicodeString *)selected)->str();
		unsigned short nameBuffer[0x100];
		rva007BA4EC(source, 0, 0, nameBuffer, 0);
		UnicodeString name(nameBuffer);
		GadgetTextEntrySetText(m_fileName, name);
		return;
	}

	if (m_mode == 4)
		GadgetTextEntrySetText(m_fileName, Rva0037D55EGet());
	else
		GadgetTextEntrySetText(m_fileName,
			TheGameState->rva002DD282(TheGameState->rva002DBE62Get()));
}
