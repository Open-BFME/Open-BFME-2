#pragma once
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <list>

class GameFont;
struct FieldParse;

// Native template ctor 0x201998 and creation 0x201C39 prove a 20-byte
// allocation. The font-refresh worker 0x201B05 reads these same fields.
class HeaderTemplate
{
public:
	GameFont *m_font;
	AsciiString m_name;
	AsciiString m_fontName;
	int m_point;
	bool m_bold;
};
typedef char HeaderTemplateSizeCheck[(sizeof(HeaderTemplate) == 20) ? 1 : -1];

// Native list sentinel at +0; nodes link at +0 and store the template at +8.
// Keep the existing STLport list member used by creation and font refresh.
class HeaderTemplateManager
{
public:
	HeaderTemplate *findHeaderTemplate(AsciiString name);
	HeaderTemplate *newHeaderTemplate(AsciiString name);
	GameFont *getFontFromTemplate(AsciiString name);
	void populateGameFonts();
	void init();
	void headerNotifyResolutionChange();
	static const FieldParse m_headerFieldParseTable[];
	const FieldParse *getFieldParse() const { return m_headerFieldParseTable; }
private:
	typedef _STL::list<HeaderTemplate *> HeaderTemplateList;
	HeaderTemplateList m_headerTemplateList;
};
