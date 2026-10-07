// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc /Os /G7 -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// stlport
// ?populateGameFonts@HeaderTemplateManager@@QAEXXZ @0x00201B05 76B
// HeaderTemplateManager font refresh loop. Evidence: caller 0x00201BD0 loads
// HeaderTemplate.ini then calls here; prev 0x00201AE2 getNextHeader and next
// 0x00201C39 newHeaderTemplate prove HeaderTemplateManager owner; rowed callees
// adjustFontSize 0x001EA40D and getFont 0x002189E1 with globals TheGlobalLanguageData
// 0x009FDC84 and TheFontLibrary 0x009FE33C; layout from HeaderTemplateCreation
// (m_font +0 m_name +4 m_fontName +8 m_point +0xC m_bold +0x10 size 20).
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include "ascii_string.h"
#include "HeaderTemplateView.h"

class GameFont;
class GlobalLanguage
{
public:
	int adjustFontSize(int value);
};
class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, float size, bool bold);
};

extern GlobalLanguage *TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;

class Xfer;
enum INILoadType
{
	INI_LOAD_OVERWRITE = 1
};

class INI
{
public:
	INI();
	~INI();
	unsigned char loadFile(AsciiString filename, INILoadType type, Xfer *xfer);	// 0x0002DC75 returns 1
private:
	char m_pad[0x87C];
};

typedef char INISizeCheck[(sizeof(INI) == 0x87C) ? 1 : -1];

void HeaderTemplateManager::populateGameFonts()
{
	for (HeaderTemplateList::iterator it = m_headerTemplateList.begin(); it._M_node != m_headerTemplateList.end()._M_node; ++it)
	{
		HeaderTemplate *ht = *it;
		int adjusted = TheGlobalLanguageData->adjustFontSize(ht->m_point);
		ht->m_font = TheFontLibrary->getFont(&ht->m_fontName, (float)adjusted, ht->m_bold);
	}
}

void HeaderTemplateManager::init()
{
	INI ini;
	ini.loadFile("HeaderTemplate.ini", INI_LOAD_OVERWRITE, NULL);
	populateGameFonts();
}
