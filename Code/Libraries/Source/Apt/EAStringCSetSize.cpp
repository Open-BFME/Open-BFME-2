// cl: /O2 /MD
// Target: ?SetSize@EAStringC@@QAEXH@Z at 0x006D3BC0 (82B true size; ghidra
// 71B truncates mid-store, retail runs to last ret at +0x4F with int3 pad to
// +0x52).
// EA Apt string bounds-checked size install: asserts
// "uSize <= GetInternalMaxSize()" at EAString.inl:92 via the shared Apt
// assert/import/flag triple (pins pre-exist per the SetSize symbol note),
// then installs the low word. Layout from retail: this+0 is the rep pointer,
// rep+2 is the size word, rep+4 is the capacity word. Assert/call/flag
// pattern mirrors AptDisplayList.cpp and AptActionInterpreterBitwise.cpp.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

struct EAStringRep
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
};

class EAStringC
{
public:
	unsigned int GetInternalMaxSize() const { return m_rep->m_maxSize; }
	void SetSize(int uSize);
	void setCapacityWord_Rva006D2E00(unsigned int value);

private:
	EAStringRep *m_rep;
};

// ?SetSize@EAStringC@@QAEXH@Z
void EAStringC::SetSize(int uSize)
{
	if (!(uSize <= GetInternalMaxSize())) {
		g_bfmeAptAssertAtE17734("uSize <= GetInternalMaxSize()", ".\\string\\EAString.inl", 0x5C);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__asm int 3
		}
	}
	m_rep->m_size = (unsigned short)uSize;
}

// Clean BF1 9cbfb551fe Rva0089CompactHelpers.cpp setField04 supplies a
// structural lead, not the original name. Target 6D2E00..6D2E0E has complete
// INT3 boundaries and stores the argument low word at rep+4. The adjacent
// verified GetInternalMaxSize and SetSize establish this real capacity field;
// the original setter name and argument type remain unknown.
void EAStringC::setCapacityWord_Rva006D2E00(unsigned int value)
{
    m_rep->m_maxSize = (unsigned short)value;
}
