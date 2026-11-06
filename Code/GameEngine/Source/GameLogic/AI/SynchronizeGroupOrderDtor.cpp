// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ??1SynchronizeGroupOrder@@UAE@XZ, retail 0x005468E1, 59 bytes.
// SynchronizeGroupOrder destructor: reinstalls vtable 0x0086A314, destroys the +0x18
// 12-byte member through the rowed ??1Rva002EE9B7 (state 0), then calls the rowed
// base ??1GroupOrder at 0x00548948 (state -1). Layout from the
// rowed ctor 0x00546982 in SynchronizeGroupOrder.cpp (GroupOrder base
// 0x18, member at +0x18, bool at +0x24). Member is the opaque rowed tree/pool
// type so the call mangles to the row name and links; vtable immediate is
// DIR32.

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
// ??1SynchronizeGroupOrder@@UAE@XZ @0x005468E1
SynchronizeGroupOrder::~SynchronizeGroupOrder()
{
}
