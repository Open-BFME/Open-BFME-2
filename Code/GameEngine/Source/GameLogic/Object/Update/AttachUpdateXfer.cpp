// cl: /DNDEBUG /MD
//
// AttachUpdate::xfer, retail 0x004918AC (102 bytes): slot 3 of the class's
// primary vtable 0x00C4DB20. Version 3 over the UpdateModule base: the
// attached Object's ID (+0x20); before version 2 a dropped bool; from version
// 3 the +0x24 handle through TheEva's 0x001DEC48 (pinned by address; it runs
// its own versioned xfer). The version block is the BFME2 two-byte form the
// rowed Rva0054840AXfer.cpp uses.
typedef unsigned char UnsignedByte;
typedef bool Bool;
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
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

class Xfer::Version
{
public:
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};
enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *objectID);
#include "../../../../Include/GameClient/Eva.h"
extern Eva *TheEva;
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
class AttachUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	ObjectID m_attachedID;		// +0x20
	int m_evaHandle;		// +0x24
};
void AttachUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 3;
	xfer->operator==(version);
	UpdateModule::xfer(xfer);
	XferObjectID(xfer, &m_attachedID);
	if (version.m_currentVersion < 2)
	{
		Bool dropped = false;
		xfer->operator==(dropped);
	}
	if (version.m_currentVersion >= 3)
		TheEva->xferEvaEventID(xfer, &m_evaHandle);
}
