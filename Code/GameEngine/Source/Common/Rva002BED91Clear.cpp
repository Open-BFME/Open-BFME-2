// cl: /MD
//
// ?clear@Rva002BED91@@QAEXXZ, RVA 0x002BED91, 19 bytes.
// Opaque single-holder clear: releases the TargetRef00217D4C referent at +0
// via rowed fastcall ?ReleaseTreeHintRef00217D4C@@YIXPAUTargetRef00217D4C@@@Z
// (0x0007DEEF) then nulls it. Same 19B shape as ?clear@Rva000A8C9B@@QAEXXZ.
// Evidence: setter at 0x003F8396 calls this to release old [edi] before
// storing new pointer and AddRef at +4; loop at 0x00528309 calls this on
// [esi+4] element member; tail-jmp target of 0x003F7F30 (lea +0x1c; jmp).

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

#include "../../Include/Common/Rva002BED91.h"

void Rva002BED91::clear()
{
    if (m_00)
    {
        ReleaseTreeHintRef00217D4C(m_00);
        m_00 = 0;
    }
}

void Rva002BED91::set(TargetRef00217D4C *p)
{
    if (p != m_00)
    {
        clear();
        m_00 = p;
        if (p)
            ++p->references;
    }
}
