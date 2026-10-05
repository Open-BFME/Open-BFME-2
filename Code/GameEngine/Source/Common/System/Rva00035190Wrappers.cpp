// cl: /O2 /MD
//
// ?rva00035190@GeneralAllocator@Allocator@EA@@QAEPAXPAXIH@Z @0x00035190 125B Realloc-like
// ?rva00035210@GeneralAllocator@Allocator@EA@@QAEPAXIIH@Z @0x00035210 125B Calloc-like
// Homogeneous locked-delegation wrappers reusing the target-proven rowed
// Rva00035080Finish idiom (row 59692, 120B, primary fa09559c2d): SEH
// registration push -1 / push 0xB5CC48 / fs:[0] chain + push ecx/esi/edi +
// mov edi,ecx + mov esi,[edi+0x4E4] + test/spill + EnterCriticalSection
// (IAT 0xBBA200) + inc [esi+0x18], inner call with ecx=this pass-through,
// result held in edi across dec [esi+0x18] + LeaveCriticalSection
// (IAT 0xBBA204) + fs restore + ret 12. The two IAT calls are declared
// dllimport+throw() so cl omits the non-retail EH state reset, exactly as
// the 35080 TU. Lock layout is the proven subset: pointer at +0x4E4 with
// use count at +0x18 of the lock object; agrees with memory_pool.cpp
// GeneralAllocator at +0x4E4/+0x18. State slot +0x20 = 0x14+4*3, 3 pushes,
// ret 12 = 4*3 (family rule shared with 35080 2-arg +0x1C/ret8).
//
// TARGET (retail bytes, read off game.dat):
//   0x00035190 (125B): same prologue/handler/lock as 35080, then
//     3 loads [esp+0x24]/[esp+0x20]/[esp+0x1C] + push x3 + ecx=edi +
//     [esp+0x20]=0 + E8 BCF5FFFF -> 0x000347A0 + lock-release epilogue
//     (mov ecx,[esi+0x18]; dec ecx variant) + C2 0C 00; CC to 0x35210.
//   0x00035210 (125B): byte-identical except call disp E8 FCF7FFFF ->
//     0x00034A60 at +79 (diff is exactly 2 bytes +80/+81).
// Extents confirmed by ret + CC padding (35190 to 35210, 35210 to 35290).
// Callers (memory_pool.cpp rows 17191-17192): _Allocate clear path
// (size,1,0) -> 35210 vs normal (size,0) -> 35080; _Reallocate
// (block,size,0) -> 35190. Caller pushes prove 3-arg shape; ret12 proves
// 3 stack args; REL32 decodes prove targets independently:
//   35190 +79 E8 BCF5FFFF next 0x351E4 -> 0x347A0;
//   35210 +79 E8 FCF7FFFF next 0x35264 -> 0x34A60.
// Inner engines are UNROWED; only their ADDRESSES are used via
// address-derived GeneralAllocator pins (same names as writer-9 r4,
// identity unproven, never renamed to Malloc/Calloc/Realloc):
//   ?rva000347A0 (block,size,flags) thiscall ret12, 659B Ghidra (670B
//     ret+table per seat-42-r23, size not spent here);
//   ?rva00034A60 (count,size,flags) thiscall ret12, 163B Ghidra (172B
//     per seat-42-r23). No BFME1 donor (rg GeneralAllocator|PPMalloc
//     zero hits at 6583b3c1 per seat-42-r22); no 30520 rework; no header
//     edits; no STL; no fallbacks.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs) throw();
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs) throw();

class Rva00035080Lock
{
public:
	void *m_obj;
	Rva00035080Lock(void *obj) : m_obj(obj)
	{
		if (m_obj)
		{
			EnterCriticalSection(m_obj);
			++*(volatile int *)((char *)m_obj + 0x18);
		}
	}
	~Rva00035080Lock()
	{
		if (m_obj)
		{
			--*(volatile int *)((char *)m_obj + 0x18);
			LeaveCriticalSection(m_obj);
		}
	}
};

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	void *rva000347A0(void *block, unsigned int size, int flags);
	void *rva00034A60(unsigned int count, unsigned int size, int flags);
	void *rva00035190(void *block, unsigned int size, int flags);
	void *rva00035210(unsigned int count, unsigned int size, int flags);

private:
	char m_pad[0x4e4];
	void *m_pLock;
};

void *GeneralAllocator::rva00035190(void *block, unsigned int size, int flags)
{
	Rva00035080Lock lock(m_pLock);
	return rva000347A0(block, size, flags);
}

void *GeneralAllocator::rva00035210(unsigned int count, unsigned int size, int flags)
{
	Rva00035080Lock lock(m_pLock);
	return rva00034A60(count, size, flags);
}

}
}
