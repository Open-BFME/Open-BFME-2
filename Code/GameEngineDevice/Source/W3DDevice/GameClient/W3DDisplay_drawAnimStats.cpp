// cl: /DNDEBUG /MD /EHsc
// ?drawAnimStats@W3DDisplay@@QAEXXZ, retail 0x00043BF9, 240 bytes.
// W3DDisplay per-line color pass over the 25 debug strings at +0x1D0: each
// present line gets a severity color picked by its index (sparse switch with
// shared arms; other indices keep the running color, initially -1), then
// color(color, black), place(3, acc, 1, 1) and size(&w, &h), accumulating the
// width into acc from 3. Same DisplayString interface (setColors/draw/getSize
// at +0x28/+0x38/+0x3c) and same W3DDisplay home as the rowed sibling
// 0x0004387E (16 strings at +0x18c); the 25-table at +0x1D0 is proven by this
// body alone. Unblocks the 0x0004A3C4 dispatcher, whose arm1 tail-jumps here.
#include "../../../../GameEngine/Include/GameClient/DisplayString.h"
#include "../../../Include/W3DDevice/GameClient/W3DDisplayClass.h"

void W3DDisplay::drawAnimStats(void)
{
	int color = -1;
	int acc = 3;
	for (int i = 0; i < 0x19; ++i)
	{
		if (m_1D0[i] == 0)
			continue;
		switch (i)
		{
		case 4:
			color = 0xFFFF9696;
			break;
		case 5:
			color = 0xFF64FF64;
			break;
		case 6:
			color = 0xFFA0A0FF;
			break;
		case 8:
			color = 0xFFFFFF00;
			break;
		case 10:
			color = 0xE164FF64;
			break;
		case 11:
			color = 0xE1FFFF00;
			break;
		case 13:
			color = 0xE164FF64;
			break;
		case 14:
			color = 0xD7FFFF00;
			break;
		case 16:
			color = 0xE164FF64;
			break;
		case 17:
			color = 0xCDFFFF00;
			break;
		case 19:
			color = 0xE164FF64;
			break;
		case 20:
			color = 0xC3FFFF00;
			break;
		case 22:
			color = 0xE164FF64;
			break;
		case 23:
			color = 0xB9FFFF00;
			break;
		}
		m_1D0[i]->setColors(color, 0xFF000000);
		m_1D0[i]->draw(3, acc, 1, 1);
		int width;
		int height;
		m_1D0[i]->getSize(&width, &height);
		acc += height;
	}
}
