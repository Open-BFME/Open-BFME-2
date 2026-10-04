// ?rva006D5DA0@EAStringC@@QAE_NPBD@Z
// partial score=0.85 date=2026-10-04
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
	// installs the SEH frame this body opens with.
	class Sub
	{
	public:
		StringDataC *m_pData;
		~Sub();
	};

	// 0x006D55B0: the substring helper, (this, count, out) returning out.
	EAStringC *rva006D55B0(unsigned int count, EAStringC *out);

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
	int size = data->m_uSize;

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
	int len = (int)(p - ahead);

	if (size < len)
		return false;

	const char *chars = (const char *)data + sizeof(StringDataC) + (size - len);
	if (memcmp(chars, pStrText, len) != 0)
		return false;

	{
		Sub sub;
		rva006D55B0(size - len, (EAStringC *)&sub);
		*this = *(const EAStringC *)&sub;
		FreeData(sub.m_pData);
	}
	return true;
}