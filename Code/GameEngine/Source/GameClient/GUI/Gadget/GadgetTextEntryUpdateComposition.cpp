// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?GadgetTextEntryUpdateComposition@@YA_NPAVGameWindow@@@Z
// Retail 0x00320B3C..0x00320C6F (307 bytes).
// Removes the pending IME composition span [min(charPos conCharPos)
// max(charPos conCharPos)) clamped to the text length from the entry text
// then moves the cursor to the span start through
// GadgetTextEntrySetCursorPosition 0x00320737 and drops one masked character
// per removed one from the secret display string (+4 slot 21). Returns the
// changed flag which is also ORed into drawTextFromStart (+0x13).
// Evidence: donor Open-BFME-1 GadgetTextEntryInsertCharacter.cpp
// (BFME1 0x004BE800 composition update; same call sequence) and target
// callers GadgetTextEntryInsertCharacter 0x00320C6F (cursors at +0x1C/+0x1E
// differ) and GadgetTextEntryInput 0x00320DA9 (tests al after the call so the
// BFME2 body returns bool). Callees: winGetUserData 0x005C4ACD
// DisplayString slots 1/2/3 and wide StringBase substring ctor 0x00038120
// concat 0x00006A2A copy ctor 0x00037050 and releaseBuffer 0x00036E70.
// The const-reference min/max templates give retail's address cmov selects.
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../../Include/GameClient/DisplayString.h"

struct EntryData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	UnsignedInt validation;
	short maxTextLen;
	bool receivedUnichar;
	bool drawTextFromStart;
	unsigned char m_pad14[0x1C - 0x14];
	UnsignedShort charPos;
	UnsignedShort conCharPos;
	unsigned char m_pad20[0x24 - 0x20];
	UnsignedInt drawStart;
};

template <class T> inline const T &entryMin(const T &lhs, const T &rhs)
{
	return rhs < lhs ? rhs : lhs;
}

template <class T> inline const T &entryMax(const T &lhs, const T &rhs)
{
	return rhs > lhs ? rhs : lhs;
}

void GadgetTextEntrySetCursorPosition(GameWindow *window, UnsignedInt position);

bool GadgetTextEntryUpdateComposition(GameWindow *window)
{
	EntryData *entryData = (EntryData *)window->winGetUserData();
	bool changed = false;
	UnsignedInt lower = entryMin(entryData->charPos, entryData->conCharPos);
	UnsignedInt upper = entryMax(entryData->charPos, entryData->conCharPos);

	if (upper > entryData->text->getTextLength())
		upper = entryData->text->getTextLength();

	if (upper > 0 && upper != lower)
	{
		UnicodeString current = entryData->text->getText();
		UnicodeString prefix(current, 0, lower);
		{
			UnicodeString suffix(current, upper, current.getLength() - upper);
			prefix.concat(suffix);
		}
		entryData->text->setText(prefix);
		changed = true;
		GadgetTextEntrySetCursorPosition(window, lower);
		entryData->conCharPos = lower;
		for (UnsignedInt i = 0; i < upper - lower; ++i)
			entryData->sText->removeLastChar();
	}

	entryData->drawTextFromStart |= changed;
	return changed;
}
