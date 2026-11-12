// cl: /MD
// ??_GBfmeStringRecord0021A940@@QAEPAXI@Z at 0x0021AAC5 (28B). Scalar deleting dtor calls rowed ??1 at 0x0021A90F plus rowed operator delete 0x0002FD60. Evidence: chain lane all callees rowed.
#include "../../Include/Common/BfmeStringRecord0021A940.h"

void BfmeStringRecord0021A940_Delete(BfmeStringRecord0021A940 *p) { delete p; }
