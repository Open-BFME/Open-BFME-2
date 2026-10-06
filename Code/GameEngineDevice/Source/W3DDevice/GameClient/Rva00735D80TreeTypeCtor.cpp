// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/shims/stringinline
//
// Byte-twin of ??0TTreeType@@QAE@XZ at 0x0071EAC0
// (W3DTreeTypeLifecycle.cpp): identical 113 bytes once relocations are
// masked. Both array-construct calls go through the same generic
// ??_L@YGXPAXIHP6EX0@Z1@Z helper with the same Coord2D ctor/dtor function
// pointers, so the callees do not depend on the class name; no real name is
// provable for this record, so it is claimed address-derived.

#include "coord2d.h"

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString();
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
	static AsciiString TheEmptyString;
	void format( const char *format, ... );
	bool isEmpty( void ) const;
	bool isNotEmpty( void ) const;
	int compareNoCase( const AsciiString &other ) const;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	UnicodeString &operator=( const UnicodeString &other );
	void __cdecl format( UnicodeString format, ... );
	const unsigned short *str( void ) const;
	static UnicodeString TheEmptyString;
	int getLength( void ) const;
	int compareNoCase( const UnicodeString &other ) const;
};

class Rva00735D80TreeType
{
public:
	Rva00735D80TreeType();
	~Rva00735D80TreeType();

private:
	unsigned char m_treeData[0x24];
	Coord2D m_primaryTextureCoords[2];
	Coord2D m_secondaryTextureCoords[2];
	unsigned char m_textureFlags[4];
	AsciiString m_modelName;
	AsciiString m_textureName;
	AsciiString m_shadowName;
	AsciiString m_animationName;
};

Rva00735D80TreeType::Rva00735D80TreeType()
{
}

// Rva00735D80TreeType::~Rva00735D80TreeType: defined in Rva00735D80TreeTypeDtor.cpp (its row's unit).

// ??0Rva000EC67F@@QAE@XZ, retail 0x000EC67F, 98 bytes: the same construction for a
// sibling class of this layout; only the EH handler record differs from
// ??0Rva00735D80TreeType's bytes. It directly precedes the destructor rowed at
// 0x000EC6E1. Identity is not recovered.
class Rva000EC67F
{
public:
	Rva000EC67F();
	~Rva000EC67F();
private:
	unsigned char m_treeData[0x24];
	Coord2D m_primaryTextureCoords[2];
	Coord2D m_secondaryTextureCoords[2];
	unsigned char m_textureFlags[4];
	AsciiString m_modelName;
	AsciiString m_textureName;
	AsciiString m_shadowName;
	AsciiString m_animationName;
};

Rva000EC67F::Rva000EC67F()
{
}
