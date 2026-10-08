// cl: /O1 /G7 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// BFME1 clean donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f:
// game/GameEngine/Source/GameClient/CreditsGetUnicodeString.cpp, over ZH Credits.cpp.
// Retail 0x005B76AC..0x005B776E, 194 bytes, RET8 with hidden UnicodeString result.
// Named CreditsManager::addText (WB 0x01581450) calls this helper just as the
// reference addText does. The <BLANK> test, colon search, localization and
// literal translation establish the same helper purpose independently of bytes.
// BFME2's TheGameText at VA 0x00DFF0BC uses slot 14 and a const AsciiString
// reference here; the donor used slot 9 and a by-value parameter. Canonical
// BFME2 string headers preserve the actual one-pointer ABI and cleanup calls.

// stlport
#include <list>
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
struct CreditsFontDescription { AsciiString name; int size; bool bold; };
class GlobalLanguage {
public: int adjustFontSize(int);
 char pad00[0xE0];
 CreditsFontDescription m_creditsTitleFont,m_creditsPositionFont,m_creditsNormalFont;
};
class FontLibrary {public: GameFont *getFont(const AsciiString *, float, bool);};
extern GlobalLanguage *TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;
class BfmeSinkBOE;
extern BfmeSinkBOE *g_bfmeSinkBOE;
struct ICoord2D { int x,y; };
class DisplayString {
public:
 virtual ~DisplayString();
 virtual void setText(UnicodeString);
 virtual UnicodeString getText();
 virtual int getTextLength();
 virtual void notifyTextChanged();
 virtual void reset();
 virtual void setFont(GameFont *);
 virtual GameFont *getFont();
 virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
 virtual void v12(); virtual void v13(); virtual void v14();
 virtual void getSize(int *, int *);
};
class DisplayStringManager {
public:
 virtual ~DisplayStringManager();
 virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
 virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
 virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
 virtual DisplayString *newDisplayString();
 virtual void freeDisplayString(DisplayString *);
};
extern DisplayStringManager *TheDisplayStringManager;
class CreditsLine {
public:
 int m_style; UnicodeString m_text,m_secondText; bool m_useSecond,m_done;
 DisplayString *m_displayString,*m_secondDisplayString;
 ICoord2D m_pos; int m_height,m_color;
};
enum {CREDIT_STYLE_TITLE, CREDIT_STYLE_POSITION, CREDIT_STYLE_NORMAL, CREDIT_STYLE_COLUMN, CREDIT_STYLE_BLANK};
enum {CREDIT_SPACE_OFFSET=2};
typedef int Int;
typedef bool Bool;
enum {TRUE=1,FALSE=0};
class CreditsManager {
public:
 virtual ~CreditsManager();
 virtual void init();
 virtual bool load();
 virtual void v03(); virtual void v04(); virtual void v05();
 virtual void v06(); virtual void v07(); virtual void v08();
 virtual void reset();
 virtual void update();
 typedef _STL::list<CreditsLine *> CreditsLineList;
 static const FieldParse m_creditsFieldParseTable[];
 static void parseBlank(INI *, void *, void *, const void *);
private:
 UnicodeString getUnicodeString(AsciiString);
 char pad04[8];
 CreditsLineList m_creditLineList;
 CreditsLineList::iterator m_creditLineListIt;
 CreditsLineList m_displayedCreditLineList;
 int m_scrollRate,m_scrollRatePerFrames; bool m_scrollDown;
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

    GameFont *font = TheFontLibrary->getFont(&TheGlobalLanguageData->m_creditsNormalFont.name,
        (float)TheGlobalLanguageData->adjustFontSize(TheGlobalLanguageData->m_creditsNormalFont.size),
        TheGlobalLanguageData->m_creditsNormalFont.bold);
    m_normalFontHeight = font->height;
    return true;
}

// BFME1 donor ba7ddda7: complete Credits.cpp update, also present in ZH.
// Target identity: Credits vtable slot 10 and the named addText/update subsystem.
// Retail 0x005B78A4..0x005B7DC3 establishes dimensions +40/+44, the positive
// dimension guard, font ABI, line fields, and all five style destinations.
// The four-byte list erase/push_back names passed pin_admission's recursive
// byte-and-relocation fold proof against the native STLport providers.
void CreditsManager::update( void )
{
	if(m_isFinished)
		return;
	if (m_displayWidth<=0 || m_displayHeight<=0) return;
	m_framesSinceStarted++;
	
	if(m_framesSinceStarted%m_scrollRatePerFrames != 0)
		return;
	

	Int y = 0;
	Int yTest = 0;
	Int lastHeight = 0;
	Int start = m_scrollDown? 0:m_displayHeight;
	Int end =m_scrollDown? m_displayHeight:0;
	Int offsetStartMultiplyer = m_scrollDown? -1:0;  // if we're scrolling from the top, we need to subtract the height
	Int offsetEndMultiplyer = m_scrollDown? 0:1;
	Int directionMultiplyer = m_scrollDown? 1:-1;
	CreditsLineList::iterator drawIt = m_displayedCreditLineList.begin();
	while (drawIt != m_displayedCreditLineList.end())
	{
		CreditsLine *cLine = *drawIt;
		y = cLine->m_pos.y = cLine->m_pos.y + (m_scrollRate * directionMultiplyer);
		lastHeight = cLine->m_height;
		yTest = y + ((lastHeight + CREDIT_SPACE_OFFSET) * offsetEndMultiplyer);
		if(((m_scrollDown && (yTest > end)) || (!m_scrollDown && (yTest < end))))
		{
			TheDisplayStringManager->freeDisplayString(cLine->m_displayString);
			TheDisplayStringManager->freeDisplayString(cLine->m_secondDisplayString);
			cLine->m_displayString = NULL;
			cLine->m_secondDisplayString = NULL;
			drawIt = m_displayedCreditLineList.erase(drawIt);
		}
		else
			drawIt++;
	}
	
	y= y + ((lastHeight + CREDIT_SPACE_OFFSET) * offsetStartMultiplyer);
	
	// is it time to add a new string?
	if(!((m_scrollDown && (yTest >= start)) || (!m_scrollDown && (yTest  <= start))))
		return;
	
	if(m_displayedCreditLineList.size() == 0 && m_creditLineListIt == m_creditLineList.end())
		m_isFinished = TRUE;
	
	if(m_creditLineListIt == m_creditLineList.end())
		return;

	CreditsLine *cLine = *m_creditLineListIt;
	ICoord2D pos;
	switch (cLine->m_style) 
	{
	case CREDIT_STYLE_TITLE:
		{
			cLine->m_color = m_titleColor;
			
			if(TheGlobalLanguageData&& !cLine->m_text.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(TheFontLibrary->getFont(&TheGlobalLanguageData->m_creditsTitleFont.name,
														(float)TheGlobalLanguageData->adjustFontSize(TheGlobalLanguageData->m_creditsTitleFont.size),
														TheGlobalLanguageData->m_creditsTitleFont.bold));
				ds->setText(cLine->m_text);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = m_displayWidth/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_displayString = ds;
			}
		}
		break;
	case CREDIT_STYLE_POSITION:
		{
			cLine->m_color = m_positionColor;
			
			if(TheGlobalLanguageData && !cLine->m_text.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(TheFontLibrary->getFont(&TheGlobalLanguageData->m_creditsPositionFont.name,
														(float)TheGlobalLanguageData->adjustFontSize(TheGlobalLanguageData->m_creditsPositionFont.size),
														TheGlobalLanguageData->m_creditsPositionFont.bold));
				ds->setText(cLine->m_text);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = m_displayWidth/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_displayString = ds;
			}
		}
		break;
	case CREDIT_STYLE_NORMAL:
	 {
			cLine->m_color = m_normalColor;
			
			if(TheGlobalLanguageData && !cLine->m_text.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(TheFontLibrary->getFont(&TheGlobalLanguageData->m_creditsNormalFont.name,
														(float)TheGlobalLanguageData->adjustFontSize(TheGlobalLanguageData->m_creditsNormalFont.size),
														TheGlobalLanguageData->m_creditsNormalFont.bold));
				ds->setText(cLine->m_text);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = m_displayWidth/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_displayString = ds;
			}
		}
		break;
	case CREDIT_STYLE_COLUMN:
		{
			cLine->m_color = m_normalColor;
			
			if(TheGlobalLanguageData && !cLine->m_text.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(TheFontLibrary->getFont(&TheGlobalLanguageData->m_creditsNormalFont.name,
														(float)TheGlobalLanguageData->adjustFontSize(TheGlobalLanguageData->m_creditsNormalFont.size),
														TheGlobalLanguageData->m_creditsNormalFont.bold));
				ds->setText(cLine->m_text);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = m_displayWidth/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_displayString = ds;
			}
			if(TheGlobalLanguageData && !cLine->m_secondText.isEmpty())
			{
				DisplayString *ds = TheDisplayStringManager->newDisplayString();
				if(!ds)
					return;
				ds->setFont(TheFontLibrary->getFont(&TheGlobalLanguageData->m_creditsNormalFont.name,
														(float)TheGlobalLanguageData->adjustFontSize(TheGlobalLanguageData->m_creditsNormalFont.size),
														TheGlobalLanguageData->m_creditsNormalFont.bold));
				ds->setText(cLine->m_secondText);
				ds->getSize(&pos.x,&pos.y);
				cLine->m_height = pos.y;
				cLine->m_pos.x = m_displayWidth/2 - pos.x/2 ;
				cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
				cLine->m_secondDisplayString = ds;
				
			}
		}
		break;
	case CREDIT_STYLE_BLANK:
		{
			cLine->m_height = m_normalFontHeight;
			cLine->m_pos.y = start + (cLine->m_height * offsetStartMultiplyer);
		}
		break;
	}

	m_displayedCreditLineList.push_back(cLine);

	if(m_creditLineListIt != m_creditLineList.end())
		m_creditLineListIt++;
	
}
