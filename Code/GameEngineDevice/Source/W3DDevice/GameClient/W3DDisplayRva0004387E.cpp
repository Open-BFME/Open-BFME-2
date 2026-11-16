// cl: /DNDEBUG /MD /EHsc
// ?rva0004387E@W3DDisplay@@QAEXXZ, retail 0x0004387E, 77 bytes.
// W3DDisplay debug-string row draw: 16 strings at +0x18c, each color(-1, black),
// place(3, y, 1, 1), size(&w, &h), y += h from y=3.
// Evidence: BFME1 donor W3DDisplayDrawStrings006e8790.cpp (same 3 virtuals at
// +0x28/+0x38/+0x3c, same constants, 15 at +0x18c); retail loops 0x10;
// neighbours in same GameClient dir; caller 0x0004A3C4 jumps here.
#include "../../../../GameEngine/Include/GameClient/DisplayString.h"
#include "../../../Include/W3DDevice/GameClient/W3DDisplayClass.h"

void W3DDisplay::rva0004387E(void)
{
	int x = 3;
	DisplayString **p = m_18C;
	int n = 16;
	do
	{
		int height;
		int width;
		(*p)->setColors(-1, 0xff000000);
		(*p)->draw(3, x, 1, 1);
		(*p)->getSize(&width, &height);
		x += height;
		++p;
		--n;
	} while (n);
}
