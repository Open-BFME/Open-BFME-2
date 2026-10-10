// cl: /O1 /G7 /MD /EHsc
// Lazily constructed process-wide lock object (Rva00041004 with argument 1) returned by pointer;
// the function-local static supplies the guard byte and the registered atexit teardown.
#include "../../Include/Common/Rva00041004Lock.h"

void *Rva0010F011Get()
{
    static Rva00041004 obj(1);
    return &obj;
}
