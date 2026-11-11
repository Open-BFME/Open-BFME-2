// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ICF twin of the 1-byte ret at 0x000B3FD0 (rowed as ??1Region2D@@QAE@XZ,
// region.cpp, among some fifty empty bodies retail folds there): the empty
// member Rva005CD2D0ResetGroundPlacement.cpp calls on its owner.
#include "../../Include/Common/Rva000B3FD0Nop.h"

void Rva000B3FD0Nop::noop()
{
}
