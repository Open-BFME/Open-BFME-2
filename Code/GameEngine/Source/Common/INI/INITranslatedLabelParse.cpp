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

#include "../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void Rva0033B938_ParseTranslatedLabel(INI *ini, void *instance, void *store, const void *userData);
};

#include "../../../Include/Common/INI/FieldParse.h"

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
