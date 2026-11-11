// cl: /O1 /MD /EHsc /DNDEBUG
//
// ?update@W3DTerrainVisual@@UAEXXZ @0x00091D0D 37B: empty-base op, optional
// worker call, guarded tail dispatch. Invokes the pinned 1B ret stub
// 0x000B3FD0 on this (shared empty-base operation; implicit empty-base
// calls are elided by the compiler, so it is spelled explicitly), calls
// the pinned no-arg method 0x0010082F on +0x14 when non-null (this dies
// right after the load, so esi is popped before the call), then
// tail-jumps to the 16-byte dispatch at 0x0009A338 (rowed as the free
// Rva007B7600) as a member call on the shadow manager when it is set:
// retail loads ecx from g_shadowManager for the test and keeps it for the
// jump, which only a thiscall spelling reproduces. Honest address-derived
// names; boundary verified (push esi at 0x91D0D, jmp-or-ret at end).
//
// Identity: slot 10 (update) of the W3DTerrainVisual subsystem table (slot 1
// is the rowed W3DTerrainVisual::init 0x00091AEA, slot 9 W3DTerrainVisual::reset
// 0x00091CA7, slot 0 its deleting dtor over ~W3DTerrainVisual 0x0009203A), and
// the body is Zero Hour's W3DTerrainVisual::update: the base
// TerrainVisual::update (folded onto the shared empty ret 0x000B3FD0), then
// the water render object's per-frame update (0x0010082F) when present; BFME 2
// adds the shadow-manager dispatch.

#include "../../Include/Common/Rva000B3FD0.h"

class Rva0010082F
{
public:
	void rva0010082F();
};

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainVisualClass.h"

#include "../../Include/Common/Gen0003AC38.h"
class W3DShadowManager; extern W3DShadowManager *TheW3DShadowManager;

// ?update@W3DTerrainVisual@@UAEXXZ
void W3DTerrainVisual::update()
{
	// Retail passes the secondary SubsystemInterface receiver to the empty
	// base operation; the canonical class also accounts for that receiver's
	// four-byte displacement when it accesses m_waterRenderObject.
	((Rva000B3FD0 *)((char *)this + 4))->rva000B3FD0();
	if (m_waterRenderObject)
		((Rva0010082F *)m_waterRenderObject)->rva0010082F();
	if ((*(Gen0003AC38 * *)&TheW3DShadowManager))
		(*(Gen0003AC38 * *)&TheW3DShadowManager)->rva0009A338();
}


// The retail call in this body reads 0x0009A338, an address the ledger already
// carries as ?Rva007B7600@@YAXXZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?rva0009A338@Gen0003AC38@@QAEXXZ=?Rva007B7600@@YAXXZ")
