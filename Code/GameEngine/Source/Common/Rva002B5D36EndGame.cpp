// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?ShowEndGameSplashScreen@LivingWorldLogic@@QAEXXZ @0x002B5D36 383B.
// End-game UI: PlayerTemplate evil flag at +0x1BC plus victory byte at +0x3C4
// select Gui_Victory/DefeatScreen, CheerEvil/Good, APT:EndVictorious/Defeat
// then fetch via TheGameText slot 0x38, bfmeSetText :VictoryDefeat, and
// ShowEndGame invoke with 0/1, screen and cheer strings. Evidence: callers
// jmp at 0x002B88E5, callees nameToKey 0x9FA65 findPlayerTemplate 0x1FD31B,
// StringBase ctor 0x37BA0, GameText slot 0x38, bfmeSetText 0x225301,
// releaseBuffer 0x36410/0x36E70, invoke 0x222A8B, strings Gui_VictoryScreen
// Gui_DefeatScreen Gui_VictoryCheerEvil/Good APT:EndVictorious/Defeat
// :VictoryDefeat ShowEndGame, globals TheNameKeyGenerator ThePlayerTemplateStore
// TheGameText TheRva00222A8BTarget g_Rva0107301CEmptyString g_00BBFDDC/FDE0.
#include "ascii_string.h"
#include "unicode_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerTemplate
{
public:
	char m_pad[0x1BC];
	unsigned char m_1BC;
};
class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool usePlaceholder);
};
class Rva00222A8BTarget
{
public:
	void invoke(void *level, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;

extern const char g_Rva0107301CEmptyString[];
extern const char g_00BBFDDC[];
extern const char g_00BBFDE0[];

struct Rva002B5D36Faction
{
	char m_pad[4];
	AsciiString m_name;
};
struct Rva002B5D36Player
{
	char m_pad[0x40];
	Rva002B5D36Faction *m_40;
	char m_pad44[0x3C4 - 0x44];
	unsigned char m_3C4;
};
class LivingWorldLogic
{
public:
	void ShowEndGameSplashScreen();
private:
	char m_pad[0x98];
	Rva002B5D36Player *m_98;
};

void LivingWorldLogic::ShowEndGameSplashScreen()
{
	const PlayerTemplate *tmpl = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(m_98->m_40->m_name));
	if (!tmpl)
		return;
	unsigned char isEvil = tmpl->m_1BC;
	bool isVictory = m_98->m_3C4 == 0;
	AsciiString screen(isVictory ? "Gui_VictoryScreen" : "Gui_DefeatScreen");
	AsciiString cheer(isEvil ? "Gui_VictoryCheerEvil" : "Gui_VictoryCheerGood");
	AsciiString endKey(isVictory ? "APT:EndVictorious" : "APT:EndDefeat");
	{
		AsciiString suffix(":VictoryDefeat");
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(suffix, TheGameText->fetch(endKey), false);
	}
	TheRva00222A8BTarget->invoke((void *)0xD, "ShowEndGame", 3, isEvil ? g_00BBFDDC : g_00BBFDE0, (void *)screen.str(), (void *)(isVictory ? cheer.str() : g_Rva0107301CEmptyString), 0, 0);
}
