// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS
// ?xfer@ChangeStanceGroupOrder@@UAEXPAVXfer@@@Z @0x00546B91 54B evidence: slot 3 of 0x0086A36C ChangeStanceGroupOrder; base GroupOrder xfer rowed 0x00548AC2 then xferVersion 1-1 then XferStancesEnum rowed 0x0045ED66 for this+0x18; member int at +0x18 (the stance).
// Proven method keeps real name xfer.
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef unsigned int UnsignedInt;


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
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};


extern void __cdecl XferStancesEnum(Xfer *xfer, int *value);

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva0036E346;
class Xfer;
enum ObjectID;

// The direct base GroupOrder (ctor 0x005488C5, called only by the six group
// orders) is 0x18 bytes: vptr 0xC6A520, vector-built member at +4 via
// 0x211E58, zeros at +0x10/+0x14. Do NOT declare an explicit vptr member on
// the base: the hidden vptr sits at +0 and a declared one shifts every slot.
// Its table is Snapshot's: loadPostProcess in slot 1, the class-name getter
// in slot 2 and xfer (0x00548AC2) in slot 3 (GroupOrderDerivedDtors.cpp).
class GroupOrder : public Snapshot
{
public:
	GroupOrder();
	GroupOrder(Rva0036E346 *holder);
	GroupOrder(const GroupOrder &other);
	virtual ~GroupOrder();

	virtual void xfer(Xfer *xfer);

protected:
	unsigned char m_pad04[0x14];
};

// Table 0x0086A36C: slot 3 xfer 0x00546B91, slot 4 rva00546BED 0x00546BED.
class ChangeStanceGroupOrder : public GroupOrder
{
public:
	ChangeStanceGroupOrder();
	ChangeStanceGroupOrder(Rva0036E346 *holder, int stance);
	ChangeStanceGroupOrder(const ChangeStanceGroupOrder &other);
	virtual ~ChangeStanceGroupOrder();

	virtual void xfer(Xfer *xfer);
	virtual void rva00546BED(ObjectID id);

private:
	int m_stance;		// +0x18
};

void ChangeStanceGroupOrder::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	GroupOrder::xfer(xfer);
	*xfer == version;
	XferStancesEnum(xfer, &m_stance);
}
