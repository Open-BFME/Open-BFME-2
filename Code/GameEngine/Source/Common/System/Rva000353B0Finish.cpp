// ?rva000353B0@GeneralAllocator@Allocator@EA@@QAEPAXPAXH_N0I@Z @0x000353B0 57B.
// PPMalloc GeneralAllocator report open (ReportBegin-like), under the name
// memory_pool.cpp's _Exit and _DumpFragmentation call. A non-null context
// must carry the "PANS" block signature and is returned as-is, else NULL; a
// null context takes a snapshot through the allocator at 0x00034D10 and
// stamps +0x0D on success. Retail forwards the bool flag as the whole
// argument dword, so the callee is declared with the bool it takes. Names are
// address-derived; the default /O2 shape has no frame, so there is no // cl:
// line.
#include "../../../Include/Common/GeneralAllocator.h"
namespace EA
{
namespace Allocator
{
}
}

void *EA::Allocator::GeneralAllocator::rva000353B0(void *context, int blockTypes, bool copy, void *storage, unsigned int storageSize)
{
	void *result;
	if (context != 0)
	{
		result = context;
		if (*(int *)context != 0x534e4150)
			result = 0;
	}
	else
	{
		result = rva00034D10(blockTypes, copy, storage, storageSize);
		if (result)
			*((char *)result + 0xd) = 1;
	}
	return result;
}
