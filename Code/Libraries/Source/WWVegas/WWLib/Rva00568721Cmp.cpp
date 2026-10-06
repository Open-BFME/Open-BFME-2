// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The void* STLport sort family uses this thiscall comparator at 0x00568721.
// The rowed Rva00568721Less body establishes the +0x44 word and +0x47 high
// nibble ordering, and the family callers confirm those key fields.
struct Rva00568721Key
{
	char m_lead[0x44];
	unsigned short m_word;
	unsigned char m_pad46;
	unsigned char m_byte47;
};

struct Rva00568721Cmp
{
	bool operator()(const void *a, const void *b) const;
};

// ??RRva00568721Cmp@@QBE_NPBX0@Z @0x00568721 53B
bool Rva00568721Cmp::operator()(const void *a_, const void *b_) const
{
	const Rva00568721Key *a = (const Rva00568721Key *)a_;
	const Rva00568721Key *b = (const Rva00568721Key *)b_;
	if (a->m_word > b->m_word)
		return true;
	if (a->m_word < b->m_word)
		return false;
	return (a->m_byte47 & 0xF0) < (b->m_byte47 & 0xF0);
}
