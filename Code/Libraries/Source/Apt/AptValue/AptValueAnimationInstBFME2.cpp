// cl: /DNDEBUG /MD
//
// ?rva006CD650@Rva006CD650@@QAEPAXXZ,
// retail 0x006CD650, 103 bytes. AptCIH animation-inst getter with AptCIH.h
// asserts (this at line 211, isAnimationInst() at line 155) returning the
// +0x4c member. Type check is get()==0x12 plus !isUndefined() via the rowed
// getters 0x6DBB30 and 0x6DC010. Precedent is AptValueCheckedCastsBFME2
// (__asm int 3 barrier, g_bfmeApt globals, /O2).

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *condition, const char *file, int line);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

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

class Rva006CD650
{
public:
	void *rva006CD650();

private:
	char m_pad00[0x04];
	int m_flags04;
	char m_pad08[0x4c - 0x08];
	void *m_member4C;
};

// ?rva006CD650@Rva006CD650@@QAEPAXXZ
void *Rva006CD650::rva006CD650()
{
	if (!this)
	{
		g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xD3);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm int 3
	}
	if (((const Rva006DBB30SarDwordField *)this)->get() != 0x12 || ((const BfmeAptValue006DCD20 *)this)->isUndefined())
	{
		g_bfmeAptAssertAtE17734("isAnimationInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x9B);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm int 3
	}
	return m_member4C;
}
