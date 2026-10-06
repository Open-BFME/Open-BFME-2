// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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

#include "ascii_string.h"


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
	AsciiString getFilename( void ) const;
	int rva0002BBDE( void ) const;
	AsciiString rva0002BFE5( void ) const;

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


// ?getFilename@INI@@QBE?AVAsciiString@@XZ
AsciiString INI::getFilename( void ) const
{
	return m_fileTable.getName( m_fileIndex );
}

int INI::rva0002BBDE( void ) const
{
	return m_fileTable.getLine( m_head[ 3 ] );
}

AsciiString INI::rva0002BFE5( void ) const
{
	return m_fileTable.getName( m_head[ 3 ] );
}
