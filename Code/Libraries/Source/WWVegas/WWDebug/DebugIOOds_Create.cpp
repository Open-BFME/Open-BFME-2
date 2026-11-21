// cl: /DNDEBUG /MD /EHa

#include <new>

extern void *DebugAllocMemory(unsigned size);

#include "../../debug/bfme_debug_io_interface.h"

bool DebugIOInterface::HasInput()
{
    return false;
}

// The base deleting destructor is frameless. The derived retail bodies retain EBP.
#pragma optimize("y", off)
#include "../../debug/bfme_debug_io_ods.h"

// ?Create@DebugIOOds@@SAPAVDebugIOInterface@@XZ
DebugIOInterface *DebugIOOds::Create(void)
{
    return new (DebugAllocMemory(sizeof(DebugIOOds))) DebugIOOds();
}
