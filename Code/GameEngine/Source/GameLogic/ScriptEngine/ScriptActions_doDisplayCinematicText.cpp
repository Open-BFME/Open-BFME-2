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

class GlobalLanguage
{
public:
	Int adjustFontSize(Int pointSize);
};

class Display
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void slot79() = 0;
	virtual void slot80() = 0;
	virtual void slot81() = 0;
	virtual void slot82() = 0;
	virtual void slot83() = 0;
	virtual void slot84() = 0;
	virtual void slot85() = 0;
	virtual void slot86() = 0;
	virtual void slot87() = 0;
	virtual void slot88() = 0;
	virtual void setCinematicText(AsciiString string) = 0;
	virtual void setCinematicFont(GameFont *font) = 0;
	virtual void setCinematicTextFrames(Int frames) = 0;
};

extern GameTextInterface *TheGameText;
extern FontLibrary *TheFontLibrary;
extern GlobalLanguage *TheGlobalLanguageData;
extern Display *TheDisplay;
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
