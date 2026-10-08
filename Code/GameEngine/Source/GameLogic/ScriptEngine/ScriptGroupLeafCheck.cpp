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

// Clean BFME 1 Rva003543C0Arr.cpp at 34f59164f6d1 supplies the keyed
// address and indexed-byte accessor leads. Native +0x18 table access and
// 20-byte stride independently establish each layout below. Keyed20 starts
// immediately after RET at 0x003B46DF and ends RET4 at 0x003B46F1;
// indexed17 starts 0x003B46F4 and ends RET4 at 0x003B4702 before 0x003B4705.
// Independent address-owned receiver views. The bytes establish the same
// physical offsets and stride, not a shared original class identity.
struct Rva003B46E0RecordBytes { unsigned char m_bytes[20]; };

class Rva003B46E0Holder
{
public:
    void *atKey(const void *arg) const;
    unsigned char m_pad[0x18];
    Rva003B46E0RecordBytes *m_table;
};

void *Rva003B46E0Holder::atKey(const void *arg) const
{
    int index = *(const int *)((const unsigned char *)arg + 4);
    return m_table[index].m_bytes + 8;
}

class Rva003B46F4Holder
{
public:
    unsigned char atIndex(int index) const;
    unsigned char m_pad[0x18];
    Rva003B46E0RecordBytes *m_table;
};

unsigned char Rva003B46F4Holder::atIndex(int index) const
{
    return m_table[index].m_bytes[0x0C];
}

// BF1 9cbfb551fe Common/Rva003543C0Arr.cpp is the clean semantic donor.
// Full native leaf 003B4705..003B4716 ends at its own RET boundary.
// Target evidence: receiver38 array pointer; stride14 hexadecimal; byte0C load; RET4.
// Original owner unresolved; the address-owned type is independent of nearby classes.
struct Rva003B4705Element { char unknown[0x0C]; unsigned char value; char tail[7]; };
class Rva003B4705Array {
public: unsigned char getByte(int index);
private: char unknown[0x38]; Rva003B4705Element *values;
};
unsigned char Rva003B4705Array::getByte(int index) { return values[index].value; }
