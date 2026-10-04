// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// stlport
// class-gate: allow AsciiString donor TU-local StringBase-derived 4-byte view emits the retail 118B body at 0x00201C39; the shared header force-inlines the copy assignment instead of the out-of-line StringBase::set call retail makes
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

extern "C" unsigned int __cdecl strlen( const char *text );
#pragma intrinsic(strlen)

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( void ) : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();
	void set( const StringBase<T> &other );
	void set( const T *text, int length );

	struct Header;
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( void ) : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	void set( const char *text, int length )
	{
		StringBase<char>::set( text, length );
	}
	AsciiString &operator=( const AsciiString &other )
	{
		StringBase<char>::set( other );
		return *this;
	}
};

typedef char AsciiStringSizeCheck[(sizeof(AsciiString) == 4) ? 1 : -1];

struct FieldParse;

class GameFont;
extern const FieldParse g_010F9830[];

class HeaderTemplate
{
public:
	HeaderTemplate( void );
	GameFont *m_font;
	AsciiString m_name;
	AsciiString m_fontName;
	int m_point;
	unsigned char m_bold;
};

typedef char HeaderTemplateSizeCheck[(sizeof(HeaderTemplate) == 20) ? 1 : -1];

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
	HeaderTemplate *headerTemplate = new HeaderTemplate;
	if( !headerTemplate )
		return 0;

	headerTemplate->m_name = name;
	m_headerTemplateList.push_front( headerTemplate );
	return headerTemplate;
}
