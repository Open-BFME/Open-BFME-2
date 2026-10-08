// ?drawHiliteBar@@YAXPBVImage@@00HHHH@Z
// partial score=0.996 date=2026-10-07
// ?drawHiliteBar@@YAXPBVImage@@00HHHH@Z
// partial score=0.9222 date=2026-10-05
// ?drawHiliteBar@@YAXPBVImage@@00HHHH@Z
// partial score=0.95 date=2026-10-01
// ?drawHiliteBar@@YAXPBVImage@@00HHHH@Z
// partial score=0.95 date=2026-10-01
// cl: /Ireference/shims/bfme2gwm /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /G7 /arch:SSE
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
// ?drawHiliteBar@@YAXPBVImage@@00HHHH@Z @0x000A273F 254B donor=ZH W3DListBox.cpp drawHiliteBar without smallCenter; caller=drawListBoxText 0x000A283D; vtable=GameWindowManager+0x108 Display+0xa8+0xb0
#include <stdlib.h>

#include "../../../../../../../reference/shims/w3ddisplaystring/GameClient/DisplayString.h"

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "W3DDevice/GameClient/W3DGadget.h"

// BFME2 Display vtable: retail calls setClipRegion at +0xa8 (slot 42) and
// enableClipping at +0xb0 (slot 44) with isClippingEnabled between (donor ZH
// has them at +0x68/+0x6c/+0x70). Pad to retail-measured offsets; only the
// members this body touches are modelled.
class Display
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03(); virtual void pad04(); virtual void pad05();
	virtual void pad06(); virtual void pad07(); virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15(); virtual void pad16(); virtual void pad17();
	virtual void pad18(); virtual void pad19(); virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27(); virtual void pad28(); virtual void pad29();
	virtual void pad30(); virtual void pad31(); virtual void pad32(); virtual void pad33(); virtual void pad34(); virtual void pad35();
	virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39(); virtual void pad40(); virtual void pad41();
	virtual void setClipRegion(IRegion2D *region);
	virtual Bool isClippingEnabled();
	virtual void enableClipping(Bool onoff);
};
extern Display *TheDisplay;

// drawHiliteBar without smallCenter: retail 0x000A273F is 254B vs donor 319B, missing second loop
static void drawHiliteBar(const Image *left, const Image *right,
	const Image *center,
	Int startX, Int startY,
	Int endX, Int endY)
{
	ICoord2D barWindowSize;
	Int xOffset = 0, yOffset = 0;
	ICoord2D start, end;
	Int i;
	IRegion2D clipRegion;

	barWindowSize.x = endX - startX;
	barWindowSize.y = endY - startY;

	if (barWindowSize.x < left->getImageWidth() + right->getImageWidth())
		barWindowSize.x = left->getImageWidth() + right->getImageWidth();

	ICoord2D leftSize, rightSize;
	leftSize.x = left->getImageWidth();
	leftSize.y = left->getImageHeight();
	rightSize.x = right->getImageWidth();
	rightSize.y = right->getImageHeight();

	ICoord2D leftEnd, rightStart;
	leftEnd.x = startX + leftSize.x + xOffset;
	leftEnd.y = startY + barWindowSize.y + yOffset;
	rightStart.x = startX + barWindowSize.x - rightSize.x + xOffset;
	rightStart.y = startY + yOffset;

	Int centerWidth, pieces;

	centerWidth = rightStart.x - leftEnd.x;

	pieces = centerWidth / center->getImageWidth();

	start.x = leftEnd.x;
	start.y = startY + yOffset;
	end.y = start.y + barWindowSize.y;
	for (i = 0; i < pieces; i++)
	{
		end.x = start.x + center->getImageWidth();
		TheWindowManager->winDrawImage(center,
			start.x, start.y,
			end.x, end.y);
		start.x += center->getImageWidth();
	}

	clipRegion.lo.x = leftEnd.x;
	clipRegion.lo.y = startY + yOffset;
	clipRegion.hi.x = leftEnd.x + centerWidth;
	clipRegion.hi.y = start.y + barWindowSize.y;
	TheDisplay->setClipRegion(&clipRegion);
	TheDisplay->enableClipping(FALSE);
	start.x = startX + xOffset;
	start.y = startY + yOffset;
	end = leftEnd;
	TheWindowManager->winDrawImage(left, start.x, start.y, end.x, end.y);

	start = rightStart;
	end.x = start.x + rightSize.x;
	end.y = start.y + barWindowSize.y;
	TheWindowManager->winDrawImage(right, start.x, start.y, end.x, end.y);
}
// force emission of the static above (custom register calling convention)
void ForceEmitHiliteBar(const Image *l, const Image *r, const Image *c, Int a, Int b, Int d, Int e)
{
	drawHiliteBar(l, r, c, a, b, d, e);
}
