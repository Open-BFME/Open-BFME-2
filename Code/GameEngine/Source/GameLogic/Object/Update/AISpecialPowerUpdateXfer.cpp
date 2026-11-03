// cl: /DNDEBUG /MD
//
// ?xfer@AISpecialPowerUpdate@@MAEXPAVXfer@@@Z, retail 0x004B3352, 153 bytes.
// Slot 3 of ??_7AISpecialPowerUpdate 0x00C56E1C (slot-2 name getter returns
// "AISpecialPowerUpdate"; the rowed dtor 0x004B2E79 installs it).
// Version(1,3), the rowed UpdateModule::xfer 0x0044DF9F, from version 3 a
// bool at +0x21; on load with that bool set (or from an older save) the
// pinned no-argument member 0x004B303F; a bool at +0x20; then, when the
// object at +0x24 exists, its slot-1 transfer, gated before version 2 on
// the rowed TheSkirmishAIManager record lookup for the controlling player. Member
// names not recovered.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

class Player;

#include "../object.h"

struct Rva002A8AB1Record;

#include "../../../../Include/GameLogic/Rva002A8F24.h"

extern Rva002A8F24 *TheSkirmishAIManager;

class Rva004B3352State
{
public:
	virtual void s00();
	virtual void xfer(Xfer *xfer);
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class AISpecialPowerUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	void postInitAISpecialPower();

	bool m_20;
	bool m_21;
	Rva004B3352State *m_24;
};

// ?xfer@AISpecialPowerUpdate@@MAEXPAVXfer@@@Z @0x004B3352
void AISpecialPowerUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;

	UpdateModule::xfer(xfer);

	if (version.m_minimum >= 3)
		*xfer == m_21;

	if (xfer->IsLoading() && (m_21 || version.m_minimum < 3))
		postInitAISpecialPower();

	*xfer == m_20;

	if (m_24)
	{
		if (version.m_minimum >= 2 || TheSkirmishAIManager->rva002A8AB1(getObject()->getControllingPlayer()))
			m_24->xfer(xfer);
	}
}
