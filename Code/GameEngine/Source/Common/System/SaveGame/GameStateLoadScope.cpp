// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native load dispatcher 2DD91A constructs this empty scope at [ebp-1C]
// through 47A6A9 and destroys it through B3FD0, both normally and in its
// FuncInfo state 3 cleanup. GameLogicInit.cpp already declares the same
// ABI view for the new-game pass. Its original class identity is unknown.
// These are the real empty constructor/destructor definitions; their full
// bodies and relocations equal the existing region/coordinate ICF owners.
// Keep them separate from the callers: exposing their empty definitions
// there removes a cleanup state that the native callers retain.
#include "../../../../Include/Common/Rva00248558Scope.h"

Rva00248558Scope::Rva00248558Scope()
{
}

Rva00248558Scope::~Rva00248558Scope()
{
}
