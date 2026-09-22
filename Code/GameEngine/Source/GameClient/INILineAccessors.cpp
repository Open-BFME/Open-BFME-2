// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// INI file/line accessors used by subtitle parsing (parseSubtitle.cpp).
// Retail INI keeps a table of per-file records behind member +0x838: the
// small getters below index it with the dword at +0x10 and forward to its
// bounds-checked accessors (pins). The sibling getters reading +0x0C live
// in the INI core unit, not here. /O1 is the lever: /O2 spills the index
// through eax (mov+push) where retail pushes the member directly.

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[ 1 ];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	const char *str( void ) const
	{
		return (const char *)m_data;
	}

	operator const char *( void ) const
	{
		return (const char *)m_data;
	}
};

struct FieldParse;

// Per-file record table behind INI +0x838. Layout is retail-owned (defined
// by the pinned bodies); only the indexed behavior is known: getLine
// returns the record's line number or 0 when out of range, getName copies
// the record's filename or "" when out of range.
class INIFileTable
{
public:
	int getLine( int fileIndex ) const;
	AsciiString getName( int fileIndex ) const;
};

class INI
{
public:
	int getLineNum( void ) const;

private:
	int m_head[ 4 ];
	int m_fileIndex;
	char m_mid[ 0x838 - 0x14 ];
	INIFileTable m_fileTable;
};


// ?getLineNum@INI@@QBEHXZ
int INI::getLineNum( void ) const
{
	return m_fileTable.getLine( m_fileIndex );
}
