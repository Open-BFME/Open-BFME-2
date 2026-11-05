// cl: /MD
// Display's slot 35 prepends the argument view to the +0x1C list through
// View's slot 151 (+0x25c) and stores the new head.
#include "../../Include/GameClient/View.h"
#include "../../Include/GameClient/Display.h"

void Display::rva0025C134(View *view)
{
    field1C = view->prependViewToList(field1C);
}
