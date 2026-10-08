// cl: /O1 /G7 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii
// BFME1 clean donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f:
// game/GameEngine/Source/GameClient/CreditsGetUnicodeString.cpp, over ZH Credits.cpp.
// Retail 0x005B76AC..0x005B776E, 194 bytes, RET8 with hidden UnicodeString result.
// Named CreditsManager::addText (WB 0x01581450) calls this helper just as the
// reference addText does. The <BLANK> test, colon search, localization and
// literal translation establish the same helper purpose independently of bytes.
// BFME2's TheGameText at VA 0x00DFF0BC uses slot 14 and a const AsciiString
// reference here; the donor used slot 9 and a by-value parameter. Canonical
// BFME2 string headers preserve the actual one-pointer ABI and cleanup calls.

#include "ascii_string.h"
#include "unicode_string.h"

// Credits load and field-parse adaptation: native vtable slot 2 at RVA
// 5B736E returns bool; INI is 0x87C bytes; font lookup takes name by pointer,
// float size and bool. Native table/callbacks establish the scalar offsets.
class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class INI;
class Xfer;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse { const char *token; INIFieldParseProc parse; const void *userData; int offset; };
struct LookupListRec { const char *name; int value; };
enum INILoadType { INI_LOAD_OVERWRITE=1 };
class INI {
public:
 INI(); ~INI();
 void load(AsciiString, INILoadType, Xfer *, void (*)(INI *));
 void initFromINI(void *, const FieldParse *);
 static void parseCredits(INI *);
 static void parseInt(INI *, void *, void *, const void *);
 static void parseBool(INI *, void *, void *, const void *);
 static void parseColorInt(INI *, void *, void *, const void *);
 static void parseLookupList(INI *, void *, void *, const void *);
private: char m_storage[0x87C];
};
class GameFont { public: char pad00[0x10]; int height; };
class GlobalLanguage {
public: int adjustFontSize(int);
 char pad00[0xF8]; AsciiString m_creditsFontName; int m_creditsFontSize; bool m_creditsFontBold;
};
class FontLibrary {public: GameFont *getFont(const AsciiString *, float, bool);};
extern GlobalLanguage *TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;
class BfmeSinkBOE;
extern BfmeSinkBOE *g_bfmeSinkBOE;
class CreditsManager {
public:
 virtual ~CreditsManager();
 virtual void init();
 virtual bool load();
 static const FieldParse m_creditsFieldParseTable[];
 static void parseBlank(INI *, void *, void *, const void *);
private:
 UnicodeString getUnicodeString(AsciiString);
 char pad04[0x14]; int m_scrollRate,m_scrollRatePerFrames; bool m_scrollDown;
 char pad21[3]; int m_titleColor,m_positionColor,m_normalColor,m_currentStyle;
 bool m_isFinished; char pad35[3]; int m_framesSinceStarted,m_normalFontHeight;
 int m_displayWidth,m_displayHeight;
};
UnicodeString CreditsManager::getUnicodeString(AsciiString str)
{
	UnicodeString uStr;
	if (str.compare("<BLANK>") == 0)
		return UnicodeString::TheEmptyString;

	if (str.find(':'))
		uStr = TheGameText->fetch(str);
	else
		uStr.translate(str);

	return uStr;
}



// The already verified addBlank provider still has its address-based name.
// Preserve its complete existing call view; this parser supplies instance as
// the same object pointer and reads no fields itself.
struct Rva005B7DC3Block
{
	Rva005B7DC3Block *Xform();
};

struct Rva005B7DC3Sub
{
	void Consume(void **pp);
};

struct Rva005B7DC3Box
{
	char pad[0xc];
	Rva005B7DC3Sub m_0C;

	void Run();
};


void CreditsManager::parseBlank(INI *, void *instance, void *, const void *)
{
 static_cast<Rva005B7DC3Box *>(instance)->Run();
}

// Existing data-ledger name at RVA A06474. Retail initializes the pointer to
// zero. Preserve the established spelling used by Credits draw callers.
BfmeSinkBOE *g_bfmeSinkBOE = 0;

void bfmeParseD780(INI *, void *, void *, const void *);
static const LookupListRec CreditsStyleNames[] = {
 {"TITLE",0}, {"MINORTITLE",1}, {"NORMAL",2}, {"COLUMN",3}, {0,0}
};

// Every token, parser RVA, userdata pointer and offset was read from retail's
// ten 16-byte records at RVA 8737E8. The donor supplies the corresponding
// meaning; the BFME2 object prefix moves its scalar offsets by four bytes.
const FieldParse CreditsManager::m_creditsFieldParseTable[] = {
 {"ScrollRate", INI::parseInt, 0, 0x18},
 {"ScrollRateEveryFrames", INI::parseInt, 0, 0x1C},
 {"ScrollDown", INI::parseBool, 0, 0x20},
 {"TitleColor", INI::parseColorInt, 0, 0x24},
 {"MinorTitleColor", INI::parseColorInt, 0, 0x28},
 {"NormalColor", INI::parseColorInt, 0, 0x2C},
 {"Style", INI::parseLookupList, CreditsStyleNames, 0x30},
 {"Blank", CreditsManager::parseBlank, 0, 0},
 {"Text", bfmeParseD780, 0, 0},
 {0,0,0,0}
};

// Retail 0x005B72A5..0x005B72BE. Credits load passes this fourth argument
// to INI::load. The null check, Credits singleton and native field table
// reproduce the corresponding INI::parseCredits donor callback.
void INI::parseCredits(INI *ini)
{
    if (!g_bfmeSinkBOE)
        return;
    ini->initFromINI(g_bfmeSinkBOE, CreditsManager::m_creditsFieldParseTable);
}

// Retail 0x005B736E..0x005B7426, 184 bytes. The BFME2 virtual entry returns
// success, supplies the parser callback to INI::load, and uses the measured
// pointer/float/bool font ABI rather than the donor's by-value/int spelling.
bool CreditsManager::load()
{
    INI ini;
    ini.load(AsciiString("Data\\INI\\Credits.ini"), INI_LOAD_OVERWRITE, 0, INI::parseCredits);

    if (m_scrollRatePerFrames <= 0)
        m_scrollRatePerFrames = 1;
    if (m_scrollRate <= 0)
        m_scrollRate = 1;

    GameFont *font = TheFontLibrary->getFont(&TheGlobalLanguageData->m_creditsFontName,
        (float)TheGlobalLanguageData->adjustFontSize(TheGlobalLanguageData->m_creditsFontSize),
        TheGlobalLanguageData->m_creditsFontBold);
    m_normalFontHeight = font->height;
    return true;
}
