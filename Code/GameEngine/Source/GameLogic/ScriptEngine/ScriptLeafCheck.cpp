// cl: /DNDEBUG /MD /EHsc
//
// ?check@Rva003B489CHolder@@QBE_NPBX@Z,
// retail 0x003B489C, 27 bytes. Dedicated TU.
//
// Opaque leaf predicate in the Script writer cluster (called by the 43B
// skip-check at 0x3B48B9): indexes the holder's +0x38 table of 20-byte
// entries (signed-short currency at +0x0E) by the record's word at +4 and
// reports whether it equals the record's word at +8. Clone of the landed
// ScriptGroup leaf recipe (ScriptGroupLeafCheck.cpp), only the table base
// differs (+0x38 here vs +0x18 there).

typedef int Int;
typedef short Short;
typedef unsigned char Byte;
typedef bool Bool;

struct Rva003B489CEntry
{
	Byte m_pad[0x0E];
	Short m_word; // +0x0E
	Int m_val10; // +0x10
};

class Rva003B489CHolder
{
public:
	Bool check(const void *arg) const;
	Int rva003B4885(const void *arg) const;

private:
	Byte m_pad[0x38];
	Rva003B489CEntry *m_table; // +0x38
};

// ?check@Rva003B489CHolder@@QBE_NPBX@Z
Bool Rva003B489CHolder::check(const void *arg) const
{
	const char *p = (const char *)arg;
	Int index = *(const Int *)(p + 4);
	Int other = *(const Int *)(p + 8);
	Short word = m_table[index].m_word;
	return (word - other) == 0;
}

Int Rva003B489CHolder::rva003B4885(const void *arg) const
{
	const char *p = (const char *)arg;
	Int index = *(const Int *)(p + 4);
	return m_table[index].m_val10 + 4;
}
