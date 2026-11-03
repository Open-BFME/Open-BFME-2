// cl: /O1 /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
#include "../../../../Include/GameLogic/Module/BodyModule.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	ActiveBody( Thing *thing, const ModuleData *moduleData );
	virtual ~ActiveBody();

protected:
	virtual void xfer( Xfer *xfer );
};

class PorcupineFormationBodyModule : public ActiveBody
{
public:
	PorcupineFormationBodyModule( Thing *thing, const ModuleData *moduleData );
	virtual ~PorcupineFormationBodyModule();

protected:
	virtual void xfer( Xfer *xfer );
};

PorcupineFormationBodyModule::PorcupineFormationBodyModule(
	Thing *thing, const ModuleData *moduleData )
	: ActiveBody( thing, moduleData )
{
}

PorcupineFormationBodyModule::~PorcupineFormationBodyModule()
{
}

// Slot 3 of the vftable 0x00C5C3C8 that constructor 0x004C1FE6 stores at +0.
// /OPT:ICF folded the identical Version1-then-ActiveBody::xfer bodies of
// HighlanderBody, ImmortalBody, RespawnBody, OathbreakerBody and this class;
// the kept copy sits in this class's run, between 0x004C2095 and 0x004C20D5.
void PorcupineFormationBodyModule::xfer( Xfer *xfer )
{
	xfer->Version1();
	ActiveBody::xfer( xfer );
}
