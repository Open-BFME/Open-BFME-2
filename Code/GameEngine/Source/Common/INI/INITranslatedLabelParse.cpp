// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// ?Rva0033B938_ParseTranslatedLabel@INI@@SAXPAV1@PAX1PBX@Z, retail 0x0033B938
// (153B), in the INI.cpp parse run. The {AsciiString label, UnicodeString text}
// pair at the store takes the next token as its label and the game-text
// translation of it (TheGameText, VA 0x00DFF0BC, fetch(const AsciiString &)
// at vtable +0x38, result in the store argument slot); an empty translation
// throws INIException "Label '%s' not found in game text" (argument count 3).
// FieldParse rows ReviveText / RecruitText / DisplayName / Description
// (0x00DBECE8 ..). Name address-derived.

#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34();
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);	// +0x38
};

extern GameTextInterface *TheGameText;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void Rva0033B938_ParseTranslatedLabel(INI *ini, void *instance, void *store, const void *userData);
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

struct Rva0033B938Label
{
	AsciiString m_label;		// +0x00
	UnicodeString m_text;		// +0x04
};

// ?Rva0033B938_ParseTranslatedLabel@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva0033B938_ParseTranslatedLabel(INI *ini, void *, void *store, const void *)
{
	Rva0033B938Label *label = (Rva0033B938Label *)store;
	label->m_label.set(ini->getNextToken());
	label->m_text = TheGameText->fetch(label->m_label);
	if (label->m_text.isEmpty())
		throw INIException(3, "Label '%s' not found in game text", label->m_label.str());
}
