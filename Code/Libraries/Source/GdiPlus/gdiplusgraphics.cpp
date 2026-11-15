// cl: /GX-
// platformsdk
// Microsoft Platform SDK GDI+ 1.0 GdiPlusGraphics.h inlines. Graphics carries
// no vtable, so its two members sit at +0 and +4 and the constructor writes
// lastResult before nativeGraphics - the order the retail body has.

#include <windows.h>
#include <gdiplus.h>
#include "../../../GameEngine/Include/GameClient/ImageClass.h"

namespace Gdiplus
{

// ?bfmeAnchorGdiplusGraphics absent-from-retail
Status bfmeAnchorGdiplusGraphics(Image *image, INT x, INT y)
{
    Graphics *g = new Graphics(image);
    return g->DrawImage(image, x, y);
}

}
