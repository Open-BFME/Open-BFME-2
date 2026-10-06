// cl: /DNDEBUG /MD /EHsc
//
// ?skipScript@Rva003B48B9Holder@@QAEHPAX@Z,
// retail 0x003B48B9, 43 bytes. Dedicated TU.
//
// Skip predicate gating WriteScriptDataChunk: when the 0x3B489C leaf check
// fails the script is skipped outright, otherwise the record's word at +4
// indexes the holder's +0x38 table (20-byte entries, /G7 keeps the idx*20
// imul) and the script is skipped when the flag byte at entry +0x0C is set.
// The skip state is int-wide (xor-eax/inc-eax tails, flag compared against
// al), so the predicate returns Int, not Bool. The leaf resolves through
// its matched row, so this TU declares (never defines) its holder. Clone of
// the landed ScriptGroup skip recipe (ScriptGroupSkipCheck.cpp), only the
// table base differs (+0x38 here vs +0x18 there).

typedef int Int;
typedef unsigned char Byte;
typedef bool Bool;

class Rva003B489CHolder
{
public:
	Bool check(const void *arg) const;
};

class Rva003B48B9Holder
{
public:
	Int skipScript(void *record);

private:
	Byte m_pad[0x38];
	Byte *m_table; // +0x38
};

// ?skipScript@Rva003B48B9Holder@@QAEHPAX@Z
Int Rva003B48B9Holder::skipScript(void *record)
{
	Rva003B489CHolder *self = (Rva003B489CHolder *)this;
	Int skip;
	if (self->check(record)) {
		const char *rec = (const char *)record;
		Int index = *(const Int *)(rec + 4);
		Byte *table = m_table;
		Int off = index * 20;
		skip = 0;
		if (*(table + off + 0x0C) != 0)
			skip = 1;
	} else {
		skip = 1;
	}
	return skip;
}
