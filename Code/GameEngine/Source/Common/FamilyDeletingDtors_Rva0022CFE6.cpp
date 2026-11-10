// cl: /MD
// ??_GRva0022CFE6@@QAEPAXI@Z @0x0022D1C3 28B: scalar deleting dtor calls rowed ??1Rva0022CFE6 at 0x0022CFE6 plus rowed operator delete 0x0002FD60. Evidence: chain packet you-just-landed callee plus 28B push-esi call-test-je delete shape.
#include "../../Include/Common/Rva0022CFE6.h"
void famgenDelete(Rva0022CFE6 *p) { delete p; }
