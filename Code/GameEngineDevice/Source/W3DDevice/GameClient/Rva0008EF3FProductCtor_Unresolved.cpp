// cl: /DNDEBUG /MD /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ow
// Split from Rva0008EF3FProductCtor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// ??0Rva0008EF3FProduct@@QAE@XZ retail 0x0008EF3F 66B.
//
// The 0xAC0-byte product of game client vtable 0x00BC4738 factory 0x0004C492
// (W3DGameClientFactories.cpp). Target facts: it calls the rowed
// ??0InGameUI@@QAE@XZ 0x002A61A9, stores its own vptrs 0x00BC7A88/+0x0C
// 0x00BC7A78/+0x10 0x00BC7A64 over InGameUI's three bases, clears two
// 25-pointer arrays at +0x9F0/+0xA54 in one loop and then +0xAB8/+0xABC; the
// object ends at 0xAC0, the factory's allocation size.
//
// Donor inference (Zero Hour W3DInGameUI.cpp, not asserted as the target
// name): this is W3DInGameUI::W3DInGameUI -- MAX_MOVE_HINTS is 25 and the
// fields are m_moveHintRenderObj/m_moveHintAnim then the building placement
// anchor and arrow. The class keeps the ledger's address-derived name.

#include "Common/Snapshot.h"

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class View;
class Drawable;
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class RenderObjClass;
class HAnimClass;

// The five-slot interface at +0x10 (InGameUICtor.cpp).
#include "../../../../GameEngine/Include/GameClient/InGameUI.h"


class Rva0008EF3FProduct : public InGameUI
{
public:
	Rva0008EF3FProduct();
	virtual ~Rva0008EF3FProduct();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void drawSelectionRegion(void);
	virtual void drawMoveHints(View *view);
	virtual void drawPlaceAngle(View *view);

private:
	enum { MAX_MOVE_HINTS = 25 };

	RenderObjClass *m_moveHintRenderObj[MAX_MOVE_HINTS];	// +0x9F0
	HAnimClass *m_moveHintAnim[MAX_MOVE_HINTS];		// +0xA54
	class RenderObjClass *m_buildingPlacementAnchor;	// +0xAB8
	class RenderObjClass *m_buildingPlacementArrow;		// +0xABC
};

Rva0008EF3FProduct::Rva0008EF3FProduct()
{
	int i;

	for (i = 0; i < MAX_MOVE_HINTS; i++)
	{
		m_moveHintRenderObj[i] = 0;
		m_moveHintAnim[i] = 0;
	}

	m_buildingPlacementAnchor = 0;
	m_buildingPlacementArrow = 0;
}
