// cl: /MD
//
// ?rva006E3C80@Rva006E3C80@@QAEHXZ @0x006E3C80 100B
// Sprite-instance guard: null-this assert (AptCIH.h:171), then if the flags
// type field (dword at +4 sar 25, read through the rowed SarDwordField view
// Rva006DBB30SarDwordField::get) equals 0xD and the value is defined (rowed
// BfmeAptValue006DCD20::isUndefined on the same this), return m_4C.
// Otherwise assert isSpriteInst() (AptCIH.h:120) via the shared Apt assert
// triple (E17734 + DDC01C + int3) and return m_4C.
// Evidence: unlock lane, callers 0x006E4390/0x006EE16B/0x007094A2; file string
// pinned by reverse/string_xrefs.tsv (0x006E3C80 uses AptCIH.h); accessor and
// assert spellings copied from Disp8SarDwordFieldGetters.cpp,
// AptValueUndefinedBFME2.cpp and Rva006E3230Validate.cpp.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006DBB30SarDwordField
{
public:
	int get() const;
};

class BfmeAptValue006DCD20
{
public:
	bool isUndefined() const;
};

class Rva006E3C80
{
public:
	int rva006E3C80();
private:
	void *m_vptr;
	int m_flags;
	char m_pad[0x4C - 8];
	int m_4C;
};

int Rva006E3C80::rva006E3C80()
{
	if (!this) {
		g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 171);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (((const Rva006DBB30SarDwordField *)this)->get() == 0xD) {
		if (!((const BfmeAptValue006DCD20 *)this)->isUndefined())
			return m_4C;
	}
	g_bfmeAptAssertAtE17734("isSpriteInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 120);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
		__debugbreak();
	return m_4C;
}
