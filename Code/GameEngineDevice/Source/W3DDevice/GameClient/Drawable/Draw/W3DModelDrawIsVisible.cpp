// cl: /MD /DNDEBUG C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// W3DModelDraw::isVisible, retail 0x000B37F0 (28 bytes), ported from Zero
// Hour's GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// W3DModelDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// Identity: slot 37 of the W3DModelDraw-family vtable 0x00BCBFC0 (slot-2 name
// getter returns "W3DSupplyDraw"), two after the rowed
// setFullyObscuredByShroud as in Zero Hour's DrawModule (BFME 2 inserts one
// slot between them), followed by the large reactToTransformChange and the
// empty reactToGeometryChange; the body is Zero Hour's
// "m_renderObject && m_renderObject->Is_Really_Visible()".
// BFME 2 differences (target evidence): m_renderObject sits at +0x50, and
// the visibility test is RenderObjClass vtable slot 96 (+0x180), a virtual
// call where Zero Hour inlines a bit test; the slot's name is carried over
// from Zero Hour as an inference. Retail is size-optimised (/O1: xor/inc for
// true), which the /O2 W3DModelDraw.cpp port does not reproduce, so the body
// lives here.

typedef bool Bool;

#include "../../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

class W3DModelDraw
{
public:
	virtual Bool isVisible() const;
private:
	unsigned char m_pad04[0x50 - 0x04];
	RenderObjClass *m_renderObject; // +0x50
};

//-------------------------------------------------------------------------------------------------
Bool W3DModelDraw::isVisible() const
{
	return (m_renderObject && m_renderObject->Is_Really_Visible());
}
