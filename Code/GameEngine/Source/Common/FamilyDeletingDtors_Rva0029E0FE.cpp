// cl: /MD
// ??_GRva0029E00D@@QAEPAXI@Z, retail 0x0029E0FE 28B: scalar deleting dtor calls the rowed ??1 at 0x0029E00D plus rowed operator delete 0x0002FD60.
#include "../../Include/Common/Rva0029E00D.h"

void Rva0029E00D_Delete(Rva0029E00D *p) { delete p; }
