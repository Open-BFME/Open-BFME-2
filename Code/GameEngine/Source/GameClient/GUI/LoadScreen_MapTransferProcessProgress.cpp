// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?processProgress@MapTransferLoadScreen@@UAEXHHVAsciiString@@@Z, retail
// 0x00356436 (128 bytes).
// Donor (Zero Hour LoadScreen.cpp MapTransferLoadScreen::processProgress):
// skip an unchanged percentage, remember it, set the slot's progress bar,
// and set the slot's text to TheGameText's translation of stateStr.
// Target evidence: WorldBuilder lead names 0x00356436
// MapTransferLoadScreen::processProgress; retail compares and stores
// m_oldProgress[playerId] (+0x90), maps the slot through m_playerLookup
// (+0x70), calls the matched GadgetProgressBarSetProgress on m_progressBars
// (+0x10) and the matched GadgetStaticTextSetText on m_progressText (+0x50)
// with TheGameText (0x00DFF0BC) slot 14 -- fetch(const AsciiString &) --
// built straight into the argument slot, then destroys the by-value
// stateStr. The donor's debug-only range assert is gone.
// This is a call-only view of the screen, not its construction model.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;

class GameWindow;
void GadgetProgressBarSetProgress(GameWindow *g, Int progress);
void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

enum { MAX_SLOTS = 8 };

class MapTransferLoadScreen
{
public:
	virtual void processProgress(Int playerId, Int percentage, AsciiString stateStr);

private:
	char m_pad04[0x10 - 0x04];
	GameWindow *m_progressBars[MAX_SLOTS];  // +0x10
	char m_pad30[0x50 - 0x30];
	GameWindow *m_progressText[MAX_SLOTS];  // +0x50
	Int m_playerLookup[MAX_SLOTS];          // +0x70
	Int m_oldProgress[MAX_SLOTS];           // +0x90
};

void MapTransferLoadScreen::processProgress(Int playerId, Int percentage, AsciiString stateStr)
{
	if (m_oldProgress[playerId] == percentage)
		return;
	m_oldProgress[playerId] = percentage;

	Int translatedSlot = m_playerLookup[playerId];
	if (m_progressBars[translatedSlot])
		GadgetProgressBarSetProgress(m_progressBars[translatedSlot], percentage);
	if (m_progressText[translatedSlot])
		GadgetStaticTextSetText(m_progressText[translatedSlot], TheGameText->fetch(stateStr));
}
