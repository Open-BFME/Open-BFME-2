// cl: /DNDEBUG /MD /EHsc /O1
// stlport
//
// ??1BaikonurLaunchPower@@UAE@XZ, retail 0x004CAFDD, 48 bytes.
// ModuleData dtor: tears down the BfmeObject544 vector at +0x08 through the
// rowed 0x4CAE89 body, then restores the Snapshot base vtable 0x00BBB554.
// Empty derived body with EH state 0 (EH prolog, no base call since Snapshot
// dtor is inline). Shape follows the landed CivilianSpawnCollideModuleDataDtor
// (TU-local Snapshot with inline BBB554-restoring dtor, novtable derived to
// suppress own store, empty body) plus the RampageBehaviorModuleDataDtor vector
// precedent. Layout from the rowed ctor 0x004CAEE6 (vtable 0x85F098 at +0,
// vector at +0x08, size 0x14 via factory 0x00252C13 pushing 0x14). Caller is
// the slot-0 ??_G at 0x004CAFC1 (vtable 0x85F098). Donor: BFME1
// BaikonurLaunchPower.cpp virtual dtor.
#include <vector>

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

struct BfmeObject544
{
	~BfmeObject544();
};

class __declspec(novtable) BaikonurLaunchPower : public Snapshot
{
public:
	virtual ~BaikonurLaunchPower();

private:
	int m_unused04; // +0x04
	_STL::vector<BfmeObject544> m_vec08; // +0x08
};

BaikonurLaunchPower::~BaikonurLaunchPower()
{
}
