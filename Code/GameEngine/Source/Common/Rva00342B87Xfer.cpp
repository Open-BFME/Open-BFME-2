// cl: /MD
// ?xfer@Rva00342B87@@MAEXPAVXfer@@@Z @0x00340C2D 50B: slot 3 xfer of vtable 0x008128D0 (Rva00342B87) also serving 0x0086A250 (Rva0036804F derived with no extra members inherits it). Version1 then base AIInternalMoveToState xfer via pin 0x0033FF76 then int at +0x4C via slot 0x7C plus Coord at +0x20 via slot 0x60. Evidence: callees rowed and pinned layout from Rva00342B87Ctor int 0x4C plus AI goal at 0x20 vtable slot 3.
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

#include "../../Include/Common/BfmeXfer.h"

#include "../../../Libraries/Include/Lib/Coord3DBase.h"

class StateMachine;

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;
};

class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer(Xfer *xfer);
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3DBase m_goalPosition;
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3DBase))];
	bool m_adjustsDestination;
};

class Rva00342B87 : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_4C;
};

void Rva00342B87::xfer(Xfer *xfer)
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	*xfer == m_4C;
	*xfer == m_goalPosition;
}
