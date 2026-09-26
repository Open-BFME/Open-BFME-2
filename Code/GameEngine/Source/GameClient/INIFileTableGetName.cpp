// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// INI per-file record accessors: filename and file-id lookups behind the
// INIFileTable at INI +0x838 (see INILineAccessors.cpp for the callers).
//
// Identity: INI::getFilename (rowed 0x002C005) forwards its hidden
// AsciiString slot straight into INIFileTable::getName (0x00601903); the
// getName body range-checks the file index against (m_end - m_begin) / 12
// and delegates to the record table's unchecked worker (0x0060188C), which
// copies the indexed AsciiString out of the name table through the rowed
// StringBase copy constructor (0x00365F0). 0x006018B6 is the matching
// integer accessor over the same 12-byte records (field +0) with the same
// count check. Ghidra boundaries: 0x60188C/42, 0x6018B6/38, 0x601903/62.
//
// Layout (retail-owned): the table object lives at INIFileTable +0x04. It
// carries the 12-byte record range (m_begin +0x00, m_end +0x04, indices
// into the AsciiString table m_names +0x0C through the record's +0x08
// field) plus the count divisor sizeof(INIFileRecord). The +0x08 word and
// the outer +0x00 word are never read by these bodies and stay reserved.
// The record's +0x04 word is the line number (see INIFileTableGetLine.cpp);
// the +0x08 word doubles as the name-table index here.
//
// The getName count idiom is load-then-add (mov eax,[ecx+8]; add ecx,4;
// sub eax,[ecx]): the m_end load hoists above the &m_records formation,
// which then doubles as the worker call's instance (no reload). Spelling
// it with a table pointer over the nested table reproduces the schedule;
// spelling the count through flat members loses the add (getFileId, which
// calls nothing, shows the plain mov/mov/sub form instead).
//
// Out-of-range getName copies the empty AsciiString singleton (0xDE0878,
// same extern idiom as the Upgrade module-data constructor units); the
// gate DIR32-fills its address. /G7 keeps the imul form and the signed
// division shape (getLine precedent); /EHsc provides the hidden-slot
// RVO guard (and [ebp-4],0) with no funclet.

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
};

struct INIFileRecord
{
	unsigned int m_fileId;		// +0x00
	int m_line;					// +0x04
	int m_nameIndex;			// +0x08
};

class INIFileRecordTable
{
	friend class INIFileTable;

public:
	AsciiString getRecordName( int fileIndex ) const;

private:
	INIFileRecord *m_begin;		// +0x00
	INIFileRecord *m_end;		// +0x04
	unsigned int m_reserved;	// +0x08
	AsciiString *m_names;		// +0x0C
};

class INIFileTable
{
public:
	int getFileId( int fileIndex ) const;
	AsciiString getName( int fileIndex ) const;

private:
	unsigned int m_reserved;		// +0x00
	INIFileRecordTable m_records;	// +0x04
};

extern const AsciiString g_emptyAsciiString;


// ?getRecordName@INIFileRecordTable@@QBE?AVAsciiString@@H@Z
AsciiString INIFileRecordTable::getRecordName( int fileIndex ) const
{
	int nameIndex = m_begin[ fileIndex ].m_nameIndex;
	return m_names[ nameIndex ];
}


// ?getFileId@INIFileTable@@QBEHH@Z
int INIFileTable::getFileId( int fileIndex ) const
{
	int count = ((int)m_records.m_end - (int)m_records.m_begin) / (int)sizeof( INIFileRecord );
	if ( fileIndex < count )
		return (*(INIFileRecord * volatile *)&m_records.m_begin)[ fileIndex ].m_fileId;
	return 0;
}
