// cl: /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z, retail 0x0033987B, 133 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseAndTranslateLabel (Common/INI/INI.cpp): fetch the
// token's translation from TheGameText (0x00DFF0BC, vtable slot 0x3C) and store
// it. BFME2 turns the missing-label assert into an INIException(3, ...) throw.
// The emptiness test reads the string data header directly: a 16-bit length
// at +4, characters from +8.

#include "../../../../../reference/shims/bfme2_ascii/unicode_string.h"

// StringBase<unsigned short>::isEmpty, inline here as retail expands it (the
// exported out-of-line copy 0x00035740 is not called from this body).
static inline bool parseAndTranslateLabelIsEmpty(const UnicodeString &text)
{
	const char *data = *(const char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

class GameTextInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);	// +0x3C
};

extern GameTextInterface *TheGameText;

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/INI/FieldParse.h"

// ?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseAndTranslateLabel(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	UnicodeString translated = TheGameText->fetch(token);
	if (parseAndTranslateLabelIsEmpty(translated))
		throw INIException(3, "Label '%s' not found in game text", token);
	((UnicodeString *)store)->set(translated.str());
}
