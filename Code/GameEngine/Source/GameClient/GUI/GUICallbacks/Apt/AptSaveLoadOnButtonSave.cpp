// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// AptSaveLoad::OnButtonSave, retail 0x0043566A (357 bytes). WorldBuilder
// names it (WB 0x012ADE90, AptSaveLoad.cpp:893). It takes the name typed in
// the filename entry (+0x290); an empty name goes straight to the save
// prompt 0x00435224. Otherwise it asks whether the file already exists: in
// replay mode (+0x2A0 == 4) the replay extension 0x0037BA48 is appended, the
// replay directory 0x0037B9D4 put in front and the wide file system asked
// (0x0060068A); for a saved game the mode's extension (0x002DBC97 of
// 0x002DBE62) is appended and the save directory asked through 0x002DCCFB.
// An existing file switches the screen to state 15 (the overwrite prompt).
// Layout, mode values and callee identities follow the sibling
// AptSaveLoadRva00435819.cpp and retail.
#include "unicode_string.h"

class GameWindow;
UnicodeString GadgetTextEntryGetText(GameWindow *entry);

UnicodeString Rva0037BA48Get();
UnicodeString Rva0037B9D4Get();

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

class Rva002DCCFB
{
public:
	bool rva002DCCFB(UnicodeString filename);
};

class BFME2FileSystemFacade
{
public:
	bool doesWideFileExist(const unsigned short *path);
};
extern class FileSystem *TheFileSystem;

struct BFME2WideConcatPair
{
	const UnicodeString *a;
	const UnicodeString *b;
	BFME2WideConcatPair(const UnicodeString &left, const UnicodeString &right)
	{
		b = &right;
		a = &left;
	}
	operator UnicodeString();
};
inline BFME2WideConcatPair operator+(const UnicodeString &left,
	const UnicodeString &right)
{
	return BFME2WideConcatPair(left, right);
}

static bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

class AptSaveLoad
{
public:
	void OnButtonSave(const char *);
	void rva00435224();

private:
	unsigned char m_pad000[0x27C];
	int m_27C;
	unsigned char m_pad280[0x290 - 0x280];
	int m_290;
	unsigned char m_pad294[0x2A0 - 0x294];
	int m_2A0;
};

void AptSaveLoad::OnButtonSave(const char *)
{
	UnicodeString name;
	if (m_290)
		name.set(GadgetTextEntryGetText((GameWindow *)m_290));

	bool exists = false;
	if (!unicodeIsEmpty(name))
	{
		if (m_2A0 == 4)
		{
			name += Rva0037BA48Get();
			name = Rva0037B9D4Get() + name;
			exists = ((BFME2FileSystemFacade *)TheFileSystem)->doesWideFileExist(name.str());
		}
		else
		{
			name += (const unsigned short *)TheGameState->rva002DBC97Get(
				TheGameState->determineCurrentGameSaveFileMode());
			exists = ((Rva002DCCFB *)TheGameState)->rva002DCCFB(name);
		}
	}

	if (!exists)
		rva00435224();
	else
		m_27C = 15;
}
