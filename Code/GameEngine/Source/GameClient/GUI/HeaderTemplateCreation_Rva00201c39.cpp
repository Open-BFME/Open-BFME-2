// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include "ascii_string.h"

extern "C" unsigned int __cdecl strlen( const char *text );
#pragma intrinsic(strlen)

typedef char AsciiStringSizeCheck[(sizeof(AsciiString) == 4) ? 1 : -1];

struct FieldParse;

class GameFont;
extern const FieldParse g_010F9830[];

class HeaderTemplate
{
public:
	GameFont *m_font;
	AsciiString m_name;
	AsciiString m_fontName;
	int m_point;
	unsigned char m_bold;
};

typedef char HeaderTemplateSizeCheck[(sizeof(HeaderTemplate) == 20) ? 1 : -1];

// Row owner of the HeaderTemplate ctor body at 0x00201998
// (??0Rva0048C200Owner@@QAE@XZ): same 0x14-byte layout, called by retail.
class Rva0048C200Owner
{
public:
	Rva0048C200Owner( void );
private:
	char m_pad[0x14];
};

typedef char Rva0048C200OwnerSizeCheck[(sizeof(Rva0048C200Owner) == 20) ? 1 : -1];

class HeaderTemplateManager
{
public:
	HeaderTemplate *findHeaderTemplate( AsciiString name );
	HeaderTemplate *newHeaderTemplate( AsciiString name );

	// The owning table uses BFME's Font/Point/Bold offsets at +8/+C/+10.
	const FieldParse *getFieldParse( void ) const
	{
		return g_010F9830;
	}

private:
	typedef std::list<HeaderTemplate *> HeaderTemplateList;
	HeaderTemplateList m_headerTemplateList;
};

extern HeaderTemplateManager *TheHeaderTemplateManager;

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *instance, const FieldParse *fieldParse );
	static void parseHeaderTemplateDefinition( INI *ini );
};

// ?newHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z
HeaderTemplate *HeaderTemplateManager::newHeaderTemplate( AsciiString name )
{
	HeaderTemplate *headerTemplate = (HeaderTemplate *)new Rva0048C200Owner;
	if( !headerTemplate )
		return 0;

	headerTemplate->m_name = name;
	m_headerTemplateList.push_front( headerTemplate );
	return headerTemplate;
}
