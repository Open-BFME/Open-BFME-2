// cl: /O2 /MD /EHsc
// ?rva006d7b60@@YAPAVAptString@@PAVBfmeAptValue006DCD20@@HH@Z @ 0x006D7B60 (285B).
// Apt clamped two-operand string builder, sibling of the rowed 0x006D7A60
// (242B, Rva006D7A60Finish.cpp) which supplies the /O2 /MD /EHsc flags and the
// EAStringC / AptString / AptBasePtrStack views below, reused verbatim.
// /EHsc is required: retail installs an SEH frame (push -1 / handler
// 0x00BA8940 / fs:[0] chain) read from this body's OWN prolog bytes
// (6a ff 68 40 89 ba 00 ...) via build.read_target_bytes; the twin pooled
// factory 0x006D7090 pushes 0x00BA887F and 0x006D6EF0 pushes 0x00BA8860, so no
// borrowed twin handler is cited. The BA8940 value is shared with rowed 7A60
// as a retail-byte observation, not as identity proof.
//
// Read from the retail bytes (all callees rowed except pinned 0x006DD6C0):
//  * count == 0 returns the default global at VA 0x00E18078 directly, emitted
//    as a short `jne` forward over the default block, hence the early return.
//  * index0 = At(0)->toInteger() (0x006FE580, 0x006DD360) guarded by
//    `cmp count,1` / `jl`, index1 the same pair at index 1 guarded by
//    `cmp count,2` / `jl`; the unread seed is 0x98967f for end, -1 for start.
//  * The two indices are ordered (cmp/jle swap), clamped at zero
//    (test/jge/xor), and ordered again -- no 0x006D5EC0 length fixup unlike
//    7A60, which is why this body is 43B larger, not a fold.
//  * The AptValue argument is converted into the EAStringC temporary through
//    the pinned 0x006DD6C0, a pooled AptString::Create 0x006D7210 follows,
//    and the temporary is sliced with the rowed EAStringC::Mid 0x006D5F30
//    over (start, end-start), copied into the new AptString at +8 via the
//    rowed operator= 0x006D3030, and both temporaries are destroyed through
//    the rowed dtor 0x006D3010. The function returns the Create pointer.
//
// Structural notes inherited from the 7A60 recipe (each load-bearing there):
//  * `text` is declared BEFORE start/end so the clear call lands immediately
//    after the register pushes, where retail has it.
//  * The EAStringC constructor is __declspec(noinline) and defined in this TU
//    as `{ clear(); }`; retail calls 0x006D2F90 there.
//  * The third parameter is unused by retail (plain cdecl ret, only the first
//    two stack slots are read) and is named to say so.
// Unrowed 0x006DD6C0 / 0x006D7210 are address-derived pins, not proven
// identities; the row name itself is address-derived.
class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		char m_pad[2];
	};

	__declspec(noinline) EAStringC();
	EAStringC &clear();
	EAStringC &operator=(const EAStringC &other);
	~EAStringC();
	EAStringC rva006d5f30(int start, int count) const;

private:
	StringDataC *m_pData;
};

extern void *g_bfmeAptDefaultValueAtE18078;	// VA 0x00E18078

EAStringC::EAStringC()
{
	clear();
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

class AptString
{
public:
	static AptString *Create();
	unsigned char m_pad[8];
	EAStringC m_str;
};

// The declared symbol carries three arguments (ptr, int, int). Retail's `ret`
// is a plain cdecl return and the body reads only the first two -- the value
// at [esp+0x20] feeds 0x006DD6C0 and the one at [esp+0x24] is the count -- so
// the third is named to say it is unused rather than left looking like a bug.
AptString *rva006d7b60(BfmeAptValue006DCD20 *value, int count, int unused)
{
	EAStringC text;
	int start = -1;
	int end = 0x98967f;
	if (count == 0)
		return (AptString *)g_bfmeAptDefaultValueAtE18078;
	if (count >= 1)
		start = g_aptValueStackAtE182E0.At(0)->toInteger();
	if (count >= 2)
		end = g_aptValueStackAtE182E0.At(1)->toInteger();
	if (start > end) {
		int tmp = end;
		end = start;
		start = tmp;
	}
	if (start < 0)
		start = 0;
	if (end < 0)
		end = 0;
	if (start > end) {
		int tmp = end;
		end = start;
		start = tmp;
	}
	value->rva006DD6C0(text);
	AptString *result = AptString::Create();
	result->m_str = text.rva006d5f30(start, end - start);
	return result;
}
