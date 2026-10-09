// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BFME 2 INI block parsers for a saved/working settings pair, reached only
// through the block-parse registrations (Rva007ABBF6BlockParseInits.cpp lists
// each token with its parse address), so Ghidra never started a function at
// them. Each copies the saved settings over the working copy, initFromINI's
// the working copy, saves it back unless the INI load type (+0x08) is 2
// (create overrides) or 4, then notifies the owning manager through its
// virtual slot 14 when one exists. BFME 1's parseCloudEffect is the same
// body; its retail (lotrbfme.exe 0x0040BAF0) only differs by BFME 2's /O1
// register caching of the working address.
//
// The copies are compiler-generated copy assignments: with a user-declared
// operator= the compiler also caches the saved address and the parser no
// longer matches, and the implicit operator= emitted here byte-matches the
// retail callee. The tokens are target facts read from the registrations;
// the class and parser names are not known, so they keep address names, and
// the settings globals are named for their token.
#include "ascii_string.h"

typedef int Int;

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
	Int getLoadType() const { return m_loadType; }

private:
	char m_unreconstructed_00[0x08];
	Int m_loadType;
};

struct S12
{
	int a;
	int b;
	int c;
};

// 0x0030AFFB (81B): "Fire" (registration VA 0x00DBD9AC). Saved settings at
// 0x00DFF4B8, working settings at 0x00DFF4F8 (the copy Rva00985E4 slot 14 at
// 0x0030AE42 reads), field table VA 0x00C08708, manager TheFireManager
// (0x00DFF4B4). The copy is Rva0030ADED's implicit operator= (0x0030ADED,
// 85B): two AsciiString sets, then the plain members.
class Rva0030ADED
{
public:
	AsciiString m_00;
	AsciiString m_04;
	S12 m_08;
	S12 m_14;
	unsigned char m_20;
	S12 m_24;
	S12 m_30;
	int m_3C;
};

class FireManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void slot14();
};

extern Rva0030ADED TheFireSettings;
extern Rva0030ADED TheFireSettingsSaved;
extern const FieldParse FireSettingsFields[];
extern FireManager *TheFireManager;

void Rva0030AFFBParse(INI *ini)
{
	TheFireSettings = TheFireSettingsSaved;
	ini->initFromINI(&TheFireSettings, FireSettingsFields);
	Int loadType = ini->getLoadType();
	if (loadType != 2 && loadType != 4)
		TheFireSettingsSaved = TheFireSettings;
	if (TheFireManager)
		TheFireManager->slot14();
}
