// ?Rva0010F011Get@@YAPAXXZ
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc
#include "../../Code/GameEngine/Include/Common/Rva00041004Lock.h"

void *Rva0010F011Get()
{
    static Rva00041004 obj(1);
    return &obj;
}
