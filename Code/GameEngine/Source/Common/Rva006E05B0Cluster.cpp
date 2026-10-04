// cl: /O2 /DNDEBUG /MD
//
// Refcount release helper from the 0x006E05B0 neighbourhood. A __thiscall
// member that asserts nRefCount > 0 (AptCIH.cpp:631), then returns early when
// the +0x5C flags select the 0x40000 case and the count is exactly one,
// otherwise tail-calls its own rva006DCB20 method (pinned at 0x006DCB20). The
// tail callee is a member of the same object, which is what keeps ecx live for
// the jump. Identity is not recovered; the class and method names are
// address-derived. The __asm int 3 is the established AptValue assert shape (it
// keeps a single shared return under /O2).

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class AptValue
{
public:
	unsigned int getRefCount() const;
	virtual void AddRef();
	virtual void Release();
};

class Rva006E05B0 : public AptValue
{
public:
	void rva006E05B0();

	char m_pad00[0x5c - 4];
	int m_field5c;
};

void Rva006E05B0::rva006E05B0()
{
	int refCount = getRefCount();

	if (refCount <= 0)
	{
		g_bfmeAptAssertAtE17734("nRefCount > 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x277);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm int 3
	}

	if ((m_field5c & 0xc0000) == 0x40000 && refCount == 1)
		return;

	AptValue::Release();
}
