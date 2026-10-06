// ?GadgetTextEntryUpdateComposition@@YA_NPAVGameWindow@@@Z
// partial score=0.85 date=2026-10-06
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
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
	void *winGetUserData();
};

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual Int getTextLength();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual Int getWidth(Int charPos);
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void removeLastChar();
	virtual void appendChar(UnsignedShort c);
};

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

template <class T> inline const T &entryMin(const T &a, const T &b)
{
	return b < a ? b : a;
}

template <class T> inline const T &entryMax(const T &a, const T &b)
{
	return b > a ? b : a;
}

void GadgetTextEntrySetCursorPosition(GameWindow *window, UnsignedInt position)
{
	EntryData *e = (EntryData *)window->winGetUserData();

	e->charPos = position;
	if (e->charPos < e->drawStart)
	{
		// back up so a few characters before the cursor stay visible
		e->drawStart = e->charPos < 5 ? 0 : e->charPos - 5;
	}
	else
	{
		Int width, height;
		window->winGetSize(&width, &height);
		if (width > 8)
			width -= 8;

		// advance until a few characters past the cursor fit
		if (e->text->getWidth(e->charPos) - e->text->getWidth(e->drawStart) > width)
		{
			Int length = e->text->getTextLength();
			Int end = e->charPos + 5;
			Int endX = e->text->getWidth(entryMin(length, end));
			while (endX - e->text->getWidth(e->drawStart) > width)
				e->drawStart++;
		}
	}
}

bool GadgetTextEntryUpdateComposition(GameWindow *window)
{
	EntryData *e = (EntryData *)window->winGetUserData();
	bool changed = false;
	UnsignedInt lower = entryMin(e->charPos, e->conCharPos);
	Int upper = entryMax(e->charPos, e->conCharPos);

	if (upper > (UnsignedInt)e->text->getTextLength())
		upper = e->text->getTextLength();

	if (upper > 0 && upper != lower)
	{
		UnicodeString current = e->text->getText();
		UnicodeString prefix(current, 0, lower);
		{
			UnicodeString suffix(current, upper, current.getLength() - upper);
			prefix.concat(suffix);
		}
		e->text->setText(prefix);
		changed = true;
		GadgetTextEntrySetCursorPosition(window, lower);
		e->conCharPos = lower;
		for (UnsignedInt i = lower; i != upper; ++i)
			e->sText->removeLastChar();
	}

	e->drawTextFromStart |= changed;
	return changed;
}

bool GadgetTextEntryInsertCharacter(GameWindow *window, UnsignedInt character)
{
	EntryData *e = (EntryData *)window->winGetUserData();

	// the validator reads only the low bytes of both arguments
	if (!((CharacterPolicy)GadgetTextEntryValidateCharacter)(character, e->validation))
		return false;

	if (e->conCharPos != e->charPos)
		GadgetTextEntryUpdateComposition(window);

	UnicodeString current = e->text->getText();
	if (current.getLength() >= e->maxTextLen)
		return false;

	UnicodeString text(current, 0, e->charPos);
	{
		UnsignedShort ch = (UnsignedShort)character;
		text.concat(&ch, 1);
	}
	text.concat(UnicodeString(current, e->charPos, current.getLength() - e->charPos));
	e->text->setText(text);

	GadgetTextEntrySetCursorPosition(window, e->charPos + 1);
	e->conCharPos = e->charPos;
	e->sText->appendChar('*');
	e->drawTextFromStart = true;

	return true;
}
