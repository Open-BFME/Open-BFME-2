// cl: /MD
// Native 35100..35182 RET16, 35290..35314 RET16, 35320..353A3 RET16.
// Ghidra boundaries and CC padding agree. Reuse the independently matched
// 35080/35190/35210 counted-lock and SEH pattern at receiver+4E4/lock+18.
// The neutral engine344A0 spans759B and pops16; engine34B30 spans348B
// and pops20. Native wrapper loads prove each argument forwarding path.
// Original GeneralAllocator naming remains carried by sibling definitions.
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

// The multiple-allocation worker 0x00034B30 is rowed under its own view
// (Rva00034B30MallocMultiple.cpp), returning the chunk-pointer array.
class Rva00034B30
{
public:
    void **rva00034B30(unsigned int count, unsigned int sizesCount, const unsigned int *sizes, void **out, int flags);
};

#include "../../../Include/Common/GeneralAllocator.h"
namespace EA
{
namespace Allocator
{


void *GeneralAllocator::rva00035100(unsigned int size, unsigned int alignment, unsigned int offset, int flags)
{
    Rva00035080Lock lock(m_pLock);
    return rva000344A0(size, alignment, offset, flags);
}

void *GeneralAllocator::rva00035290(unsigned int count, unsigned int size, void **out, int flags)
{
    Rva00035080Lock lock(m_pLock);
    return ((Rva00034B30 *)this)->rva00034B30(count, 1, &size, out, flags);
}

void *GeneralAllocator::rva00035320(unsigned int count, const unsigned int *sizes, void **out, int flags)
{
    Rva00035080Lock lock(m_pLock);
    return ((Rva00034B30 *)this)->rva00034B30(count, count, sizes, out, flags);
}
}
}
