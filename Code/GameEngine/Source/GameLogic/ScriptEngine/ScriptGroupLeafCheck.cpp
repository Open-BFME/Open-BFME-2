// cl: /DNDEBUG /MD /EHsc
//
// ?check@Rva003B483DHolder@@QBE_NPBX@Z,
// retail 0x003B483D, 29 bytes. Dedicated TU.
//
// Opaque leaf predicate in the ScriptGroup writer cluster (called by the 43B
// skip-check at 0x3B485A): indexes the holder's +0x18 table of 20-byte
// entries (signed-short currency at +0x0E) by the record's word at +4 and
// reports whether it equals the record's word at +8. Promoted from the banked
// 0.93 stash: /G7 forces the idx*20 imul (struct-index spelling suffices
// under /G7, per the landed 0x3B3F09 worker), and the neg/sbb/inc tail is
// `== 0`, not `!= 0`.

typedef int Int;
typedef short Short;
typedef unsigned char Byte;
typedef bool Bool;

struct Rva003B483DEntry
{
	Byte m_pad[0x0E];
	Short m_word; // +0x0E
	Int m_val10; // +0x10
};

class Rva003B483DHolder
{
public:
	Bool check(const void *arg) const;
	Int rva003B4826(const void *arg) const;

private:
	Byte m_pad[0x18];
	Rva003B483DEntry *m_table; // +0x18
};

// ?check@Rva003B483DHolder@@QBE_NPBX@Z
Bool Rva003B483DHolder::check(const void *arg) const
{
	const char *p = (const char *)arg;
	Int index = *(const Int *)(p + 4);
	Int other = *(const Int *)(p + 8);
	Short word = m_table[index].m_word;
	return (word - other) == 0;
}

Int Rva003B483DHolder::rva003B4826(const void *arg) const
{
	const char *p = (const char *)arg;
	Int index = *(const Int *)(p + 4);
	return m_table[index].m_val10 + 4;
}
