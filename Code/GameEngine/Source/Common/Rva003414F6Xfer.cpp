// cl: /MD
// ?xfer@Rva0033F4DF@@MAEXPAVXfer@@@Z @0x003414F6 97B: Rva0033F4DF xfer slot 3.
// IsLightCRC early-out via slot 0x10 then Version1 via rowed 0x000053EE then bool has=(m_20!=0) via slot 0x90 then lazy create via m_machine slot 0x24 then Snapshot via slot 0x30.
// Precedent Rva0033F33D Snapshot via slot 0x30 plus bool via slot 0x90 shape.
// Vtable 0x008112C0 slot 3.
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
class StateMachine;
class SnapshotCreator
{
public:
	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
	virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
	virtual void c08();
	virtual Snapshot *createSnapshot();
};
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	SnapshotCreator *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};
class Rva0033F4DF : public State
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Snapshot *m_20;
};
void Rva0033F4DF::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	bool has = (m_20 != 0);
	*xfer == has;
	if (has) {
		if (m_20 == 0)
			m_20 = m_machine->createSnapshot();
		if (has)
			*xfer == *m_20;
	}
}
