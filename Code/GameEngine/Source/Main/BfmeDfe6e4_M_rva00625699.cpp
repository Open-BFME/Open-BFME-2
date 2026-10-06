// cl: /DNDEBUG /MD /EHsc
// ?_M_rva00625699@BfmeDfe6e4@@QAEXXZ
// retail 0x00225699, 39 bytes. Guarded counter decrement under the class
// critical section, refreshing the timestamp first via the matched
// rva00225492 sibling. Volatile counter + /O1 + /G7 gives the retail
// cmp-mem + sub-mem (non-volatile loads hoist to mov/test/add-store;
// base+G7 keeps the hoist). Dedicated TU: the 28B increment sibling uses
// non-volatile + base+G7, so sharing would break one of them.

struct CRITICAL_SECTION
{
	unsigned char data[24];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section);

class BfmeDfe6e4
{
public:
	void _M_rva00625699();
	void rva00225492();

private:
	// Retail layout: guarded counter at +0x6C, critical section at +0x70.
	unsigned char m_unreconstructed_00[0x6C];
	volatile int m_refCount; // +0x6C
	CRITICAL_SECTION m_cs; // +0x70
};

// ?_M_rva00625699@BfmeDfe6e4@@QAEXXZ
void BfmeDfe6e4::_M_rva00625699()
{
	rva00225492();
	EnterCriticalSection(&m_cs);
	if (m_refCount > 0) {
		--m_refCount;
	}
	LeaveCriticalSection(&m_cs);
}
