// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x00434AAE (220 bytes), reached on the AptSaveLoad screen after its
// FileNameTextEntry is set. The target reads the field at +0x290, gets the
// selected list item through 0x00433F7F, and either converts that item's
// StringBase buffer through the indirect slot at 0x00BBA4EC or supplies a
// fallback string from 0x0037D55E / GameState method 0x002DD282. The indirect
// slot is kept address-qualified: its raw value currently points inside a
// different body, so its semantic identity is unresolved.
#include "unicode_string.h"
// MSVCR71 _wsplitpath (import slot VA 0x00BBA4EC; hint/name at RVA 0x00A7429C).
#include <stdlib.h>

class GameWindow;
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);


UnicodeString __cdecl Rva0037D55EGet();

struct TreeHintOpaque0043671B;
class GameState
{
public:
	void *rva002DBC97Get(int saveType);
	int determineCurrentGameSaveFileMode();
	UnicodeString rva002DD282(int mode);
	void rva002DDE43(const UnicodeString &name, const UnicodeString &text, int save, int confirm);
	int rva002DE3C1(TreeHintOpaque0043671B info);
};
extern GameState *TheGameState;

class AptSaveLoad
{
public:
	int rva00433F7F();
	void SetDefaultFileName();

private:
	unsigned char m_pad000[0x290];
	int m_290;
	unsigned char m_pad294[0x2A0 - 0x294];
	int m_2A0;
};

void AptSaveLoad::SetDefaultFileName()
{
	if (m_290 == 0)
		return;

	int selected = rva00433F7F();
	if (selected != 0)
	{
		const unsigned short *source = ((UnicodeString *)selected)->str();
		unsigned short nameBuffer[0x100];
		_wsplitpath(source, 0, 0, nameBuffer, 0);
		UnicodeString name(nameBuffer);
		GadgetTextEntrySetText((GameWindow *)m_290, name);
		return;
	}

	if (m_2A0 == 4)
		GadgetTextEntrySetText((GameWindow *)m_290, Rva0037D55EGet());
	else
		GadgetTextEntrySetText((GameWindow *)m_290,
			TheGameState->rva002DD282(TheGameState->determineCurrentGameSaveFileMode()));
}
