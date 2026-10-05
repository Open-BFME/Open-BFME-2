// cl: /DNDEBUG /MD /EHsc
// ??0CriticalSectionLock@@QAE@PAUBfmeCriticalSection@@@Z @0x0061FC40, 22 bytes.
// BFME1 Bfme sweep exact placement; verbatim source import. The unmatched
// Glo00EF3330::h00489410 draft that lived here called the unpinned
// ?j_00043c57@@YAXXZ, which nothing defines, so the file could not link;
// the draft is removed (no row ever claimed it) and only the matched lock
// helper remains.

struct BfmeCriticalSection
{
	unsigned char m_unmodelled_000[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(BfmeCriticalSection *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(BfmeCriticalSection *cs);

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(BfmeCriticalSection *section) : m_section(section)
	{
		EnterCriticalSection(m_section);
	}

	~CriticalSectionLock()
	{
		LeaveCriticalSection(m_section);
	}

private:
 	BfmeCriticalSection *m_section;
};

// This anchor only makes this unit emit its rowed ??0 copy for the ledger;
// it is not retail code. The in-class ctor is a COMDAT that MSVC drops when
// nothing references it, so the matched row needs a caller in this TU.
#pragma inline_depth(0)
// ?bfmeEmitCriticalSectionLockCtor@@YAXPAUBfmeCriticalSection@@@Z present-unmatched
void bfmeEmitCriticalSectionLockCtor(BfmeCriticalSection *section)
{
 	CriticalSectionLock lock(section);
}
#pragma inline_depth()
