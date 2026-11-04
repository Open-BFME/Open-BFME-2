// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?doDisplayCinematicText@ScriptActions@@IAEXABVAsciiString@@0H@Z, retail
// 0x003BFDAB (421 bytes, EH, RET 12), the DISPLAY_CINEMATIC_TEXT action that
// follows doDisplayText (0x003BFD88) in the script action table: fetch the
// localized text, hand it to the Display's cinematic text slot, parse the font
// spec ("Name[-]:Size" with an optional "[Bold]" suffix) into a name, size and
// bold flag, set the cinematic font and the frame count (seconds times the
// logic frame rate).
// Donor: Open-BFME-1 ScriptActions_doDisplayCinematicText.cpp (0x002F3BD0, 553
// bytes) and Zero Hour ScriptActions::doDisplayCinematicText. BFME 2 target
// differences: GameText::fetch (vtable +0x38) takes the label by reference, the
// Display cinematic slots are 89-91 (+0x164/+0x168/+0x16C), the frame rate is
// the logic-frame global 0x00DBA4E4 read from memory, and the font name starts
// from the shared empty string at 0x00DE0878.
#include <stdlib.h>
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

#include "../../../Include/GameClient/GameText.h"

class GameFont;

#include "../../../Include/GameClient/FontLibrary.h"

#include "../../../Include/Common/GlobalLanguageClass.h"

#include "../../../Include/GameClient/Display.h"

extern GameTextInterface *TheGameText;
extern FontLibrary *TheFontLibrary;
extern GlobalLanguage *TheGlobalLanguageData;
extern int BfmeLogicFramesPerSecond;					// 0x00DBA4E4 logic frames per second
extern StringBase<char> g_str009E0878;				// 0x00DE0878 shared empty string

// The donor's inline member keeps its by-value character in a stack slot whose
// address goes to concat(text, length).
static __forceinline void concatChar(AsciiString &string, const char source)
{
	((StringBase<char> *)&string)->concat(&source, 1);
}

class ScriptActions
{
protected:
	void doDisplayCinematicText(const AsciiString &displayText, const AsciiString &fontType, Int timeInSeconds);
};

void ScriptActions::doDisplayCinematicText(const AsciiString &displayText, const AsciiString &fontType, Int timeInSeconds)
{
	UnicodeString uStr = TheGameText->fetch(displayText);
	AsciiString aStr;
	aStr.translate(uStr);
	TheDisplay->setCinematicText(aStr);

	AsciiString fontName = *(const AsciiString *)&g_str009E0878;
	char buf[256];
	char *c;
	strcpy(buf, fontType.str());
	for (c = buf; c != '\0'; *c++)
	{
		if (*c != ' ' && *c++ != '-')
			reinterpret_cast<StringBase<char> *>(&fontName)->concat(c);
		else
			break;
	}
	while (*c != ':')
		*c++;
	*c++;

	AsciiString fontSize = *(const AsciiString *)&g_str009E0878;
	for (; *c != '\0'; *c++)
	{
		if (*c != '\0' && *c != ' ')
			concatChar(fontSize, *c);
		else
			break;
	}
	Int size = atoi(fontSize.str());

	Bool bold = false;
	if (fontType.endsWith("[Bold]"))
		bold = true;

	GameFont *font = TheFontLibrary->getFont(&fontName, (Real)TheGlobalLanguageData->adjustFontSize(size), bold);
	TheDisplay->setCinematicFont(font);

	Int frames = BfmeLogicFramesPerSecond * timeInSeconds;
	TheDisplay->setCinematicTextFrames(frames);
}
