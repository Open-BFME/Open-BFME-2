#ifndef BFME2_ARMY_MOVE_DISPATCH_VIEW_H
#define BFME2_ARMY_MOVE_DISPATCH_VIEW_H
#include "ArmyMoveCoordinateView.h"
class Rva00318C79Owner;
class Rva002B2702B0;
// Borrowed dispatch view: native 0x002B26D0 leaves this untouched; 0x002B4F6C uses
// the proven region-manager pointer at+B0. Original class name unproven.
class Rva002B26D0
{
public:
	void rva002B26D0(Rva00318C79Owner *owner, void *key, Rva002B2858Coord pair, void *extra);

private:
	unsigned char m_pad00[0xB0];
	Rva002B2702B0 *m_b0;
};
#endif
