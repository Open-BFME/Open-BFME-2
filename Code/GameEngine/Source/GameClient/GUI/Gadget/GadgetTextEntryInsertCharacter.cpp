// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME2 text-entry editing helpers, beside GadgetTextEntryInput 0x00320DA9.
// Donor: Open-BFME-1 GadgetTextEntryInsertCharacter.cpp (retail 0x004BE9C0
// insert, 0x004BE800 composition update, and the cursor helper they call,
// pinned there as GadgetTextEntrySetCursorPosition at ILT 0x000148A8).
//
// GadgetTextEntrySetCursorPosition 0x00320737 (190B, Ghidra boundary). Name
// carried from the donor; target facts: both BFME2 counterparts of the donor
// callers (0x00320B3C, 0x00320C6F) call it at the donor's positions with the
// window and the new cursor (charPos + 1 after an insert). It stores the
// cursor at entry +0x1C and keeps it visible through a first-drawn character
// index at +0x24 (new in BFME2's 0x28-byte EntryData): backing up to five
// characters before the cursor, or advancing while the text width from that
// index to five characters past the cursor exceeds the window width less 8.
// Widths come from DisplayString slot 16 (0x40), the length from slot 3.
//
// GadgetTextEntryInsertCharacter 0x00320C6F (314B), the donor's insert body.
// Target facts: it validates through 0x0035C872 with the flags at +0xC,
// updates a pending composition (cursors at +0x1C/+0x1E differ) through
// 0x00320B3C, refuses at the maxTextLen short at +0x10, splices the character
// in at the cursor, advances it through 0x00320737 and appends '*' to the
// secret display string at +4.
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

typedef bool (*CharacterPolicy)(UnsignedInt character, UnsignedInt flags);
bool GadgetTextEntryValidateCharacter(UnsignedShort character, signed char flags);

template <class T> inline const T &entryMin(const T &lhs, const T &rhs)
{
	return rhs < lhs ? rhs : lhs;
}

void GadgetTextEntrySetCursorPosition(GameWindow *window, UnsignedInt position)
{
	EntryData *entryData = (EntryData *)window->winGetUserData();

	entryData->charPos = position;
	if (entryData->charPos < entryData->drawStart)
	{
		// back up so a few characters before the cursor stay visible
		entryData->drawStart = entryData->charPos < 5 ? 0 : entryData->charPos - 5;
	}
	else
	{
		Int width, height;
		window->winGetSize(&width, &height);
		if (width > 8)
			width -= 8;

		// advance until a few characters past the cursor fit
		if (entryData->text->getWidth(entryData->charPos) - entryData->text->getWidth(entryData->drawStart) > width)
		{
			Int length = entryData->text->getTextLength();
			Int end = entryData->charPos + 5;
			Int endX = entryData->text->getWidth(entryMin(length, end));
			while (endX - entryData->text->getWidth(entryData->drawStart) > width)
				entryData->drawStart++;
		}
	}
}

// GadgetTextEntryUpdateComposition 0x00320B3C is pinned for the call below;
// its reconstruction is banked in reverse/attempts (register allocation open).
// It returns whether it deleted anything; GadgetTextEntryInput tests that.
bool GadgetTextEntryUpdateComposition(GameWindow *window);

bool GadgetTextEntryInsertCharacter(GameWindow *window, UnsignedInt character)
{
	EntryData *entryData = (EntryData *)window->winGetUserData();

	// the validator reads only the low bytes of both arguments
	if (!((CharacterPolicy)GadgetTextEntryValidateCharacter)(character, entryData->validation))
		return false;

	if (entryData->conCharPos != entryData->charPos)
		GadgetTextEntryUpdateComposition(window);

	UnicodeString current = entryData->text->getText();
	if (current.getLength() >= entryData->maxTextLen)
		return false;

	UnicodeString text(current, 0, entryData->charPos);
	{
		UnsignedShort ch = (UnsignedShort)character;
		text.concat(&ch, 1);
	}
	text.concat(UnicodeString(current, entryData->charPos, current.getLength() - entryData->charPos));
	entryData->text->setText(text);

	GadgetTextEntrySetCursorPosition(window, entryData->charPos + 1);
	entryData->conCharPos = entryData->charPos;
	entryData->sText->appendChar('*');
	entryData->drawTextFromStart = true;

	return true;
}
