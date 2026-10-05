// ?rva006d7a60@@YAPAVAptString@@PAVBfmeAptValue006DCD20@@HH@Z
// partial score=0.85 date=2026-10-05
// cl: /O2 /MD /EHsc
// ?rva006d7a60@@YA?AV1?AUEs0@1HH@Z @ 0x006D7A60 242B
//
// Apt two-operand string builder, the same family as the recovered 0x006D74E0
// in Rva006D74E0Cluster.cpp and the matched 0x006D7350 in
// Rva006D7350Finish.cpp, which supply the /O2 /MD /EHsc flags and the
// EAStringC / AptString / AptBasePtrStack views. /EHsc is required: retail
// installs an SEH frame (push -1 / handler 0x00BA8940 / fs:[0] chain) so the
// EAStringC temporaries unwind correctly.
//
// Structure, read from the retail bytes:
//  * index0 = g_aptValueStackAtE182E0.At(0)->toInteger()  (0x006FE580,
//    0x006DD360) and index1 = the same pair at index 1. The second read is
//    guarded by `cmp esi, 2` / `jl`, so a count below 2 skips it, which is why
//    the second integer's seed is the constant 0x98967f rather than -1.
//  * A negative index0 returns the default global at VA 0x00E18078 directly --
//    the same early-out 0x006D7350 takes, and the reason [esp+0x18] is seeded
//    with -1 (edi) on that path and 0 on the normal one.
//  * The first AptValue argument is converted into the EAStringC temporary at
//    [esp+0x0C] through the pinned 0x006DD6C0, then run through the pinned
//    0x006D5EC0 (the 15-byte thiscall that hands this->m_pData + 8 to the
//    rowed codepoint-count worker 0x006D4D80).
//  * The temporary is sliced with the rowed EAStringC::Mid 0x006D5F30 over
//    [index0, index1), copied into a pooled AptString::Create 0x006D7210 at
//    +8 (0x006D3030) and returned, with the temporary destructor 0x006D3010.
//
// 0x006D5EC0 is an unrowed retail body reached only from here; it is pinned
// address-derived below. Its identity is not proven.
class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		char m_pad[2];
	};

	// The real EA header defines this out of line, and 0x006D2F90 is the ICF
	// fold of it with clear(). Retail calls it at 0x006D7A7D, so this TU emits
	// a real out-of-line call and lets the fold bind it.
	EAStringC();
	EAStringC &clear();
	EAStringC &operator=(const EAStringC &other);
	~EAStringC();
	EAStringC rva006d5f30(int start, int count) const;
	void rva006D5EC0();
private:
	StringDataC *m_pData;
};

extern EAStringC::StringDataC g_eaEmptyStringData;

EAStringC::EAStringC()
{
	m_pData = &g_eaEmptyStringData;
	++g_eaEmptyStringData.m_uRefCount;
}

// 0x006D5EC0 returns void and is 15 bytes; it hands this->m_pData + 8 to the
// rowed codepoint-count worker 0x006D4D80. Declared here so this TU emits a
// direct call; the body stays unrowed and is pinned by address.
void EAStringC::rva006D5EC0()
{
}

class BfmeAptValue006DCD20
{
public:
	void rva006DD6C0(EAStringC &out);
	int toInteger() const;
};

class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *At(int index);
};

extern AptBasePtrStack g_aptValueStackAtE182E0;	// VA 0x00E182E0
extern void *g_bfmeAptDefaultValueAtE18078;			// VA 0x00E18078

class AptString
{
public:
	static AptString *Create();
	unsigned char m_pad[8];
	EAStringC m_str;
};

// ?rva006d7a60@@YAPAVAptString@@PAVBfmeAptValue006DCD20@@HH@Z @ 0x006D7A60 (242B).
//
// The second argument is a COUNT of interpreter stack values, not an index.
// `lea ecx, [esp + 0x0C]` before the 0x006D2F90 ctor is the EAStringC
// temporary at the bottom of the frame; `mov [esp + 0x18], 0` and the
// `= edi` (: 0xffffffff) at 0x006D7AA0 are the sret slot plus the
// copy-assignment flag pair, which is why the tail stores 1 then 0 through
// 0x006D3030 and then parks 0xFFFFFFFF for the destructor.
//
// Retail pushes the Mid arguments end-first: `push ebp` (: 0x98967f or the
// second integer) then `push edi` (: -1 or the first integer), so the call is
// Mid(edi, ebp) with the sret pointer in ecx.
AptString *rva006d7a60(BfmeAptValue006DCD20 *value, int count)
{
	int start = -1;
	int end = 0x98967f;
	EAStringC text;
	if (count != 0) {
		if (count >= 1)
			start = g_aptValueStackAtE182E0.At(0)->toInteger();
		if (count >= 2)
			end = g_aptValueStackAtE182E0.At(1)->toInteger();
		value->rva006DD6C0(text);
		text.rva006D5EC0();
		if (start < 0)
			start += end;
		AptString *result = AptString::Create();
		result->m_str = text.rva006d5f30(start, end);
		return result;
	}
	return (AptString *)g_bfmeAptDefaultValueAtE18078;
}
