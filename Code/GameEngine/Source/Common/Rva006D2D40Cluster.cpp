// cl: /MD /DNDEBUG
//
// ?CleanPool@AptValueGC_PoolManager@@QAEXXZ @ 0x006D2D40, 71 bytes.
//
// The pool manager is the same class AptGCRva006E6F80.cpp walks from a global
// (`g_pChainBlockAllocatorF4`, VA 0x00E176F4): thiscall, chain block at +4, and
// GetFirstAptValue/GetNextAptValue at 0x006D2CB0/0x006D2B70 (both pinned, both
// row-free) return the linked AptValue records in +4's chain.
//
// The body counts every live value the chain walk visits and asserts the count
// against the manager's own expected count at +0x14. The assert triple is the
// project-wide Apt one: __cdecl (expression, file, line) through the pointer
// at VA 0x00E17734, with the break-on-assert flag at 0x00DDC01C deciding whether
// the trailing __debugbreak runs.
//
// Retail's loop keeps the count in edi and re-reads this in ecx each iteration,
// which is what `for (value = GetFirstAptValue(); value; value = GetNext(value))
// ++count;` emits: the increment sits inside the body before the next call, and
// the loop-carried value is pushed (GetNextAptValue takes it by const pointer)
// and reloaded into ecx as the implicit this.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptValue
{
public:
	int m_value;
};

class AptValueGC_PoolManager
{
public:
	AptValue *GetFirstAptValue();
	AptValue *GetNextAptValue(const AptValue *value);
	void CleanPool();

private:
	char m_pad00[4];
	void *mChainBlock;
	char m_pad08[12];
	int mnItemsAllocated;
};

// ?CleanPool@AptValueGC_PoolManager@@QAEXXZ
void AptValueGC_PoolManager::CleanPool()
{
	int nItemsFound = 0;
	for (AptValue *value = GetFirstAptValue(); value; value = GetNextAptValue(value))
	{
		++nItemsFound;
	}
	if (nItemsFound != mnItemsAllocated)
	{
		g_bfmeAptAssertAtE17734("nItemsFound == mnItemsAllocated",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueGCAllocator.cpp", 0x173);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
		{
			__debugbreak();
		}
	}
}