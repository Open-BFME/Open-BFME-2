// cl: /MD
// Display's slot 35 inserts the argument through View's slot 151 (+0x25c).
// The existing ledger signature retains Display*; the target dispatch and
// canonical View layout identify the pointee used by this body.
#include "../../Include/GameClient/View.h"
#include "../../Include/GameClient/Display.h"

void Display::rva0025C134(Display *display)
{
    field1C = reinterpret_cast<View *>(display)->prependViewToList(field1C);
}
