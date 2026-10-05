// cl: /O2 /MD /EHsc
// ?rva006d7a60@@YAPAVAptString@@PAVBfmeAptValue006DCD20@@HH@Z @ 0x006D7A60 (242B).
// Apt two-operand string builder, the same family as the recovered 0x006D74E0
// in Rva006D74E0Cluster.cpp and the matched 0x006D7350 in Rva006D7350Finish.cpp,
// which supply the /O2 /MD /EHsc flags and the EAStringC / AptString /
// AptBasePtrStack views. /EHsc is required: retail installs an SEH frame
// (push -1 / handler 0x00BA8940 / fs:[0] chain) so the EAStringC temporaries
// unwind correctly.
//
// Read from the retail bytes:
//  * index0 = g_aptValueStackAtE182E0.At(0)->toInteger() (0x006FE580, 0x006DD360)
//    and index1 = the same pair at index 1. The second read is guarded by
//    `cmp esi,2` / `jl`, so a count below 2 skips it, which is why the second
//    integer's seed is the constant 0x98967f rather than -1.
//  * A count of 0 returns the default global at VA 0x00E18078 directly. Retail
//    emits that as a short `jne +0x0f` forward over the default block, so the
//    source spells it as an early `if (count == 0) return ...` rather than an
//    enclosing if/else; nesting the whole body in `if (count != 0) {...}` makes
//    the branch long and the body 3 bytes longer.
//  * The AptValue argument is converted into the EAStringC temporary at
//    [esp+0x0C] through the pinned 0x006DD6C0, then run through 0x006D5EC0.
//  * The temporary is sliced with the rowed EAStringC::Mid 0x006D5F30 over
//    [index0, index1), copied into a pooled AptString::Create 0x006D7210 at
//    +8 and returned, with the temporary destructor 0x006D3010.
//
// Three details are structural, not stylistic, and each one is load-bearing:
//  * `text` is declared BEFORE start/end so the constructor call lands at
//    0x006D7A7D immediately after the four-register push, where retail has it.
//  * The constructor is __declspec(noinline) and defined in this TU as
//    `{ clear(); }`. Retail calls 0x006D2F90 there, the ICF fold of that ctor
//    with clear(); declaring it inline, or letting MSVC inline the out-of-line
//    definition, drops the call and shifts every later offset.
//  * 0x006D5EC0 returns int, not void. Its body is `mov eax,[ecx] / add eax,8 /
//    push eax / call 0x006D4D80 / add esp,4 / ret`, and retail consumes that
//    count in eax with `add edi,eax` at 0x006D7AF8 for the negative-start
//    fixup. Declaring it void lets the optimizer fold it to `return 0`, which
//    deletes both the call and the fixup. It is deliberately NOT defined in
//    this TU: the body is unrowed, so only the call is emitted here.
//
// 0x006D5EC0 and 0x006D7210 remain unrowed retail bodies; both are pinned
// address-derived in reverse/symbols.csv. Their identities are not proven.
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
	int rva006D5EC0();

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
// is a plain cdecl return and the body reads only the first two -- the argument
// at [esp+0x20] feeds 0x006DD6C0 and the one at [esp+0x24] is the count -- so
// the third is named to say it is unused rather than left looking like a bug.
AptString *rva006d7a60(BfmeAptValue006DCD20 *value, int count, int unused)
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
	value->rva006DD6C0(text);
	int len = text.rva006D5EC0();
	if (start < 0)
		start += len;
	AptString *result = AptString::Create();
	result->m_str = text.rva006d5f30(start, end);
	return result;
}
