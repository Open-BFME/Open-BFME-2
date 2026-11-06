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

class Rva0036E346;
class Xfer;
struct Coord3D;
struct GroupOrderCommand;
enum NameKeyType;
class GroupOrder
{
public:
    GroupOrder();
    GroupOrder(const GroupOrder &other);
    GroupOrder(Rva0036E346 *holder);
    virtual ~GroupOrder();
    virtual void loadPostProcess() {}
    virtual const char *getClassName() = 0;
    virtual void xfer(Xfer *xfer);
    virtual void rva00546A78(int val) = 0;
    virtual bool rva005468AB(int unused) = 0;
    virtual unsigned int rva00546AC0(int val) = 0;
    virtual void slot07Set(int unused) {}
    virtual Coord3D *getDestination(int position) = 0;
    virtual bool isNearDestination(const Coord3D *position) { return false; }
    virtual int slot10() { return -1; }
    virtual bool slot11Command(int *outType, GroupOrderCommand *command) = 0;
    virtual NameKeyType getClassKey() = 0;
    virtual GroupOrder *rva005469FD() = 0;
    int *m_04;
    int *m_08;
    void *m_0C;
    void *m_10;
    void *m_14;
};
#include "../../../Include/GameLogic/Rva002EE9B7.h"

class SynchronizeGroupOrder : public GroupOrder
{
public:
    SynchronizeGroupOrder();
    SynchronizeGroupOrder(const SynchronizeGroupOrder &other);
    SynchronizeGroupOrder(Rva0036E346 *holder);
    virtual ~SynchronizeGroupOrder();
    virtual const char *getClassName();
    virtual void xfer(Xfer *xfer);
    virtual void rva00546A78(int val);
    virtual bool rva005468AB(int unused);
    virtual unsigned int rva00546AC0(int val);
    virtual Coord3D *getDestination(int position) { return reinterpret_cast<Coord3D *>(position); }
    virtual bool slot11Command(int *outType, GroupOrderCommand *command) { return false; }
    virtual NameKeyType getClassKey();
    virtual SynchronizeGroupOrder *rva005469FD();
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
