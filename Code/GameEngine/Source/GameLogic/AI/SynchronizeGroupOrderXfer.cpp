// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?xfer@SynchronizeGroupOrder@@UAEXPAVXfer@@@Z @0x00546A34 68B evidence: vslot slot 3 offset 0xC of vtable 0x0086A314 class of ??1SynchronizeGroupOrder; base GroupOrder xfer rowed 0x00548AC2; version 1 1 via Xfer slot 0x28; set at +0x18 via rowed Rva002F1CDDXfer 0x002F1CDD; bool at +0x24 via Xfer slot 0x90.
#include <set>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
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
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};


typedef _STL::set<int> SetInt;
Xfer *Rva002F1CDDXfer(Xfer *xfer, SetInt *set);

#include "../../../Include/GameLogic/GroupOrder.h"
#include "../../../Include/GameLogic/Rva002EE9B7.h"

class SynchronizeGroupOrder : public GroupOrder
{
public:
	virtual ~SynchronizeGroupOrder();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
private:
	Rva002EE9B7 m_18;
	bool m_24;
};

void SynchronizeGroupOrder::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	GroupOrder::xfer(xfer);
	*xfer == version;
	Rva002F1CDDXfer(xfer, reinterpret_cast<SetInt *>(&m_18));
	*xfer == m_24;
}
