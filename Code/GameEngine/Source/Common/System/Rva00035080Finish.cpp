// cl: /MD
//
// ?rva00035080@GeneralAllocator@Allocator@EA@@QAEPAXIH@Z @0x00035080 120B.
// Malloc-like lock-guard wrapper: counted guard over the lock at +0x4E4
// (use count at +0x18 of the lock) via IAT EnterCriticalSection 0xBBA200 /
// LeaveCriticalSection 0xBBA204, SEH stub 0xB5CC48 shared with the rowed
// sibling 0x00034C90 in Rva00034C90Finish.cpp, then forwards (size, flags)
// to the 1466B malloc body at 0x00033ED0 and returns its result.
//
// TARGET (retail bytes, read off game.dat): push -1; push 0xB5CC48;
// fs:[0] chain; push ecx/esi/edi; edi=ecx; esi=[edi+0x4E4]; test esi;
// [esp+8]=esi; je skip; Enter(esi); ++[esi+0x18]; ecx=[esp+0x20];
// edx=[esp+0x1C]; push ecx; push edx; ecx=edi; [esp+0x1C]=0 (EH state);
// call 0x00033ED0; test esi; edi=eax; je skip; --[esi+0x18]; Leave(esi);
// ecx=[esp+0xC]; eax=edi; pop edi/esi; fs restore; add esp,0x10; ret 8.
// Ghidra FUN_00435080 120B; extent confirmed by CC padding to 0x35100.
// Callers: default-heap wrapper 0x0002FFC0 (size,0) and MemoryPool::_Allocate
// 0x00030520 (size,0) vs calloc path (size,1,0) to 0x00035210.
// Body 0x00033ED0: sub esp,0x10; flags&8 mmap path via 0x00032DF0 else
// size+11 round to 0x10, bin walk at this+0x00..0x30. Its class label is
// pin-carried (existing pin ?rva00033ED0@Rva006C1F60@@QAEPAXIH@Z, identity
// unproven); the call below reuses that pin and adds none. Target evidence
// proves the wrapper ABI, call chain and lock offsets +0x4E4/+0x18. The
// GeneralAllocator class spelling is carried by existing pins and siblings;
// its original retail type identity remains uncertain. No new pins or headers.
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

class Rva006C1F60
{
public:
	void *rva00033ED0(unsigned int size, int flags);
};

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	void *rva00035080(unsigned int size, int flags);

private:
	char m_pad[0x4e4];
	void *m_pLock;
};

void *GeneralAllocator::rva00035080(unsigned int size, int flags)
{
	Rva00035080Lock lock(m_pLock);
	return ((::Rva006C1F60 *)this)->rva00033ED0(size, flags);
}

}
}
