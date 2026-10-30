// cl: /EHs-
// ?rva004FBF8E@RegionAwardDispute@@QAEXXZ, retail 0x004FBF8E, 111 bytes.
// Evaluation step run by the RegionAwardDispute constructor: asks the
// LivingWorldLogic +0xB0 host (0x0020F27E) for the disputed region's (+0x04)
// beacon position; when it has one, takes the host's next beacon id (+0x2C
// pre-increment) into +0x18, creates the beacon through TheLivingWorldManager,
// then reports whether GetResolvableBy matches LivingWorldLogic 0x002B2B66
// to 0x004FBDB0.

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../Common/RegionCenterPointDispatchView.h"

// The host's beacon-id counter at +0x2C.
struct RegionAwardDisputeBeaconCounter
{
	char m_pad00[0x2C];
	int m_nextBeaconId2C;	// +0x2C
};

class Rva002B2B66
{
public:
	int rva002B2B66();	// 0x002B2B66
};

class LivingWorldLogic
{
public:
	char m_pad00[0xB0];
	Rva0020F27EHost *m_hostB0;	// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

class LivingWorldManager
{
public:
	void CreateBeaconObject(int id, const Coord2D *pos, int kind);	// 0x00213171
};
extern LivingWorldManager *TheLivingWorldManager;

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	vector(const vector &other);
	~vector();
	void push_back(const T &value);	// the folded push_back 0x004DFCB0
	unsigned int size() const { return m_finish - m_start; }
	const T &operator[](unsigned int i) const { return m_start[i]; }
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}
struct RegionAwardDisputeFlags
{
	RegionAwardDisputeFlags() {}
	RegionAwardDisputeFlags(int bits) : m_bits(bits) {}
	void set(int mask) { m_bits |= mask; }
	int m_bits;
};

class RegionAwardDispute : public Snapshot
{
public:
	virtual ~RegionAwardDispute();
	RegionAwardDispute(int region, const _STL::vector<unsigned int> &players, int flags);
	void rva004FBF8E();
	int GetResolvableBy();			// 0x004FBED6
	void rva004FC0ED(const _STL::vector<int> &players);
	void rva004FBDB0(bool local);		// rowed 0x004FBDB0
protected:
	// Retail vftable 0x00BFE280 slots 1..3: 0x004FBFFD, 0x002B6476, 0x004FBDF7.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
private:
	int m_region;				// +0x04
	_STL::vector<unsigned int> m_players;	// +0x08
	RegionAwardDisputeFlags m_flags;	// +0x14
	int m_winner;				// +0x18
	bool m_resolved;			// +0x1C
};

void RegionAwardDispute::rva004FBF8E()
{
	Coord2D pos;
	Rva0020F27EHost *host = TheLivingWorldLogic->m_hostB0;
	if (host->rva0020F27E(m_region, (int)&pos)) {
		RegionAwardDisputeBeaconCounter *next =
			reinterpret_cast<RegionAwardDisputeBeaconCounter *>(TheLivingWorldLogic->m_hostB0);
		++next->m_nextBeaconId2C;
		int id = next->m_nextBeaconId2C;
		m_winner = id;
		TheLivingWorldManager->CreateBeaconObject(id, &pos, 1);
		int resolvableBy = GetResolvableBy();
		rva004FBDB0(reinterpret_cast<Rva002B2B66 *>(TheLivingWorldLogic)->rva002B2B66() == resolvableBy);
	}
}

// Retail 0x004FBFFD (5 bytes, right after the evaluation): vftable 0x00BFE280
// slot 1, a tail jump into the evaluation above.
void RegionAwardDispute::loadPostProcess()
{
	rva004FBF8E();
}
