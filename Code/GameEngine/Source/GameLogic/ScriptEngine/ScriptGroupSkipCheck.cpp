// cl: /DNDEBUG /MD /EHsc
//
// ?skipGroup@Rva003B485AHolder@@QAEHPAX@Z,
// retail 0x003B485A, 43 bytes. Dedicated TU.
//
// Skip predicate gating WriteGroupDataChunk: when the 0x3B483D leaf check
// fails the group is skipped outright, otherwise the record's word at +4
// indexes the holder's +0x18 table (20-byte entries, /G7 keeps the idx*20
// imul) and the group is skipped when the flag byte at entry +0x0C is set.
// The skip state is int-wide (xor-eax/inc-eax tails, flag compared against
// al), so the predicate returns Int, not Bool. The leaf resolves through
// its matched row, so this TU declares (never defines) its holder.

typedef int Int;
typedef unsigned char Byte;
typedef bool Bool;

class Rva003B483DHolder
{
public:
	Bool check(const void *arg) const;
};

class Rva003B485AHolder
{
public:
	Int skipGroup(void *record);

private:
	Byte m_pad[0x18];
	Byte *m_table; // +0x18
};

// ?skipGroup@Rva003B485AHolder@@QAEHPAX@Z
Int Rva003B485AHolder::skipGroup(void *record)
{
	Rva003B483DHolder *self = (Rva003B483DHolder *)this;
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

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?skipGroup@Rva003B485AHolder@@QAE_NPAX@Z=?skipGroup@Rva003B485AHolder@@QAEHPAX@Z")
