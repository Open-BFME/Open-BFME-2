// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ??0Rva00541021@@QAE@ABU0@@Z @0x00541021 29B: copy ctor of 28-byte element (int at +0 plus Region3D at +4). Evidence: calls rowed Region3D copy 0x0009AC04; callers are vector helpers 0x0054105B 0x0054107F 0x0054112D 0x00541D10; element stride 0x1C proven by idiv in callers.
#include "../../../Include/Lib/Region3D.h"
#include "../../../../GameEngine/Include/Common/Rva00541021.h"
Rva00541021::Rva00541021(const Rva00541021 &other)
    : m_field0(other.m_field0), m_region(other.m_region)
{
}

// Retail's assignment folds onto the copy ctor (0x00541D80 in vector::insert
// calls 0x00541021 with ecx=position, arg=&x_copy; 0x0054112D's copy_backward
// loop does the same): an int copy, then the Region3D copy, then return this.
Rva00541021 &Rva00541021::operator=(const Rva00541021 &other)
{
    m_field0 = other.m_field0;
    m_region.Region3D::Region3D(other.m_region);
    return *this;
}
