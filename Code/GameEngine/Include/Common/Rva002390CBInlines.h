// Retail's record destructor at RVA 0x004C9F38 releases the handle at +4.
// Include the bodies in units where retail inlines the member cleanup.
#pragma once

#include "Rva002390CB.h"
#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

inline Rva0036CA00Str::~Rva0036CA00Str()
{
    if (m_item)
        m_item->Release_Ref();
}

inline Rva002390CB::~Rva002390CB() {}
