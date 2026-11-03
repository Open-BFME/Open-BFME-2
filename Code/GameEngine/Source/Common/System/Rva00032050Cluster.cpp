// BFME 2 PPMalloc GeneralAllocator heap-validation entry points near
// memory_pool.cpp. No `// cl:` line: like the near file memory_pool.cpp this
// unit compiles with the base flags (-O2 -GR- -EHsc-).
//
// ?rva000329E0@GeneralAllocator@Allocator@EA@@QAE_NH@Z, retail 0x000329E0, 54 B.
// ValidateHeap-like re-entrancy guard: the byte at +0x484 is a busy flag set
// while the real validator at 0x000321F0 runs, so a nested call reports
// success without recursing. Identity: the exported MemoryPool::_VerifyIntegrity
// at 0x00030680 calls this through the rowed wrapper, and the symbols.csv pin
// from those REL32 sites already names it. The flag byte, the 0x484 offset and
// the "valid == 0" return shape are read off the target body.

#include "../../../Include/Common/GeneralAllocator.h"
namespace EA
{
namespace Allocator
{


bool GeneralAllocator::rva000329E0(int level)
{
	int result = 0;
	if (m_484 == 0) {
		m_484 = 1;
		result = rva000321F0(level);
		m_484 = 0;
	}
	return result == 0;
}

}
}
