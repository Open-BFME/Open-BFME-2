// ?rva006D5DA0@EAStringC@@QAE_NPBD@Z
// partial score=0.93 date=2026-10-05
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva006D5DA0@EAStringC@@QAE_NPBD@Z @0x006D5DA0 201B (thiscall, ret 4).
//
// EAStringC prefix compare against a C string, sitting in the same Apt/string
// group as EAString.cpp and EAStringCRemoveRange.cpp, which establishes the
// class view (m_pData at +0, StringDataC's m_uRefCount/m_uSize), the
// empty-singleton at 0x00DDC020 and the FreeData / operator= spellings reused
// here.
//
// Retail body: asserts the text pointer, then measures the C string with a
// hand-rolled strlen loop (ebp = p+1, scanning until the NUL) and compares that
// length against the string's own m_uSize. A shorter store or a byte mismatch
// returns false. On a full-length match it takes the substring of the remaining
// `size - len` bytes through the sibling helper 0x006D55B0 into a scoped
// EAStringC, assigns that into `this` through operator= 0x006D3030, releases the
// scoped copy's data with FreeData 0x006D2EB0, and returns true.
//
// The strings are pinned by reverse/string_xrefs.tsv-era retail bytes read here
// directly from game.dat: "pStrText != NULL" at 0x00CE9E68 and the EAString.cpp
// path at 0x00CE9EA0, which fixes the Apt/string subsystem.
//
// The SEH frame belongs to the scoped EAStringC temporary and is left to the
// compiler's automatic unwinder rather than written as __try: MSVC rejects a
// __try in a function that requires object unwinding (C2712), and retail's
// prologue here reads fs:[0] ahead of the push -1 pair, the ordering the
// automatic unwinder produces.
//
// The length shortfall is tested UNSIGNED. Retail's 0x6D5DFB is `jb`, a compare
// against the zero-extended word at m_uSize+2, so size and len are unsigned
// ints; declared `int` MSVC emits `jl` instead and drops the zero-extension.

//
// 0x006D55B0 is an address-derived sibling of this body -- the same substring
// helper, sharing this function's SEH handler at 0x00BA87E1 -- whose own body
// remains unclaimed; only the call is reproduced here.

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	static void FreeData(StringDataC *data);

	StringDataC *m_pData;

	EAStringC(const EAStringC &other);
	EAStringC &operator=(const EAStringC &other);
	~EAStringC();

	// The scoped substring holder. Retail allocates it as a bare four-byte
	// slot the helper fills in place -- there is no constructor call before the
	// helper -- but it does carry a destructor, and that destructor is what
	// installs the SEH frame this body opens with. Its body is empty because the
	// release is written explicitly below: MSVC only emits the frame when the
	// destructor has code, and the release itself is what retail reads out of the
	// holder (mov edx,[esp+0x20]) rather than out of `this`.
	class Sub
	{
	public:
		StringDataC *m_pData;
		Sub() {}
		~Sub() { FreeData(m_pData); }
	};

	// 0x006D55B0: the substring helper. Retail enters it with ecx = this and
	// TWO stack arguments -- lea eax,[esp+0x24]; push eax; push edx -- and it
	// ends in `ret 8`, so the signature is (this, EAStringC *out, unsigned
	// count) with both stack arguments caller-cleaned. Its own body reads the
	// second stack slot as the holder address (mov [eax],0xddc020 on the
	// count<=0 path) and the third as the count, which fixes the order.
	EAStringC *rva006D55B0(EAStringC *out, unsigned int count);

public:
	bool rva006D5DA0(const char *pStrText);
};

bool EAStringC::rva006D5DA0(const char *pStrText)
{
	if (pStrText == 0)
	{
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp",
			0x64F);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

StringDataC *data = m_pData;
	// Retail tests the length shortfall with `jb` (0x6D5DFB), an UNSIGNED
	// compare against the zero-extended word read from m_uSize, so both the size
	// and the computed length are unsigned. Signed locals make MSVC emit `jl`,
	// which is the wrong instruction and also drops the zero-extension.
	unsigned int size = data->m_uSize;

	// The hand-rolled strlen. `ahead` is pinned once at p + 1 before the loop
	// while `p` advances past each byte, so `p` ends one past the NUL and the
	// closing subtraction is the length. The character is read into a named
	// `char` and then tested, which is what keeps retail's two-instruction
	// `mov cl` / `test cl` form instead of one compare against the byte.
	const char *p = pStrText;
	const char *const ahead = p + 1;
	char c;
	do
	{
		c = *p++;
	} while (c != 0);
	unsigned int len = (unsigned int)(p - ahead);

	if (size < len)
		return false;

	// Retail folds `data` back by the measured length (sub esi,eax) and the
	// SHORTFALL size - len then indexes it (lea esi,[esi+edx*1+8]), so both the
	// folded pointer and the shortfall stay live across the compare. Naming the
	// shortfall as its own unsigned local is what makes MSVC keep the size in
	// edx there; folding the subtraction straight into the memcmp first argument
	// instead makes it re-index from `data` and drop the folding.
	unsigned int rest = size - len;
	if (memcmp((const char *)data - len + rest + (int)sizeof(StringDataC),
		pStrText, len) != 0)
		return false;

	if (true)
	{
		// Retail allocates the holder as a BARE four-byte slot the helper fills
		// in place: there is no constructor call before 0x006D55B0 and no
		// `mov dword ptr [esp+0x20],0` initialiser either. A class member with a
		// user-declared destructor is POD-initialised by MSVC here, which is the
		// extra store; the destructor stays because it is what drives the SEH
		// frame retail opens with.
		Sub sub;
		const EAStringC *p = this->rva006D55B0((EAStringC *)&sub, size - len);
		*this = *p;
	}
	return true;
}