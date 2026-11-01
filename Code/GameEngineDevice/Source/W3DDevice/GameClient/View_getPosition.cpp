// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
// stlport

// View::getPosition is an inline in GameClient/View.h (public virtual):
//     virtual void getPosition(Coord3D *pos) { *pos=m_pos; }
// The BFME1 donor W3DView.cpp only emits it through the included header. Retail
// 0x0008BB27 copies the 12-byte Coord3D at this+0xC to *pos, which fixes m_pos;
// the header body is emitted out-of-line here, donor's other bodies omitted.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../GameEngine/Include/GameClient/View.h"

// Select-any like the GameClient/View.cpp copy (this retail body comes first in
// link order, so it is the copy the link keeps); the anchor keeps the body emitted.
inline void View::getPosition( Coord3D *pos )
{
	*pos = m_pos;
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitViewGetPosition@@YAXPAVView@@PAUCoord3D@@@Z absent-from-retail
void bfmeEmitViewGetPosition(View *view, Coord3D *pos)
{
	view->View::getPosition(pos);
}
