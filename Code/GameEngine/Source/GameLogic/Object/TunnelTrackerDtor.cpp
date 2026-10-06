// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ??1TunnelTracker@@MAE@XZ retail 0x004F561D 103B
// Zero Hour TunnelTracker::~TunnelTracker shape: clear the tunnel-ID list at
// +8 (rowed folded _List_base<int>::clear 0x0023DAA5, EH state 3), then the
// lists at +0x14, +0x10 and +8 are destroyed through the rowed folded
// _List_base<int> dtor 0x004EC395; own vptrs C63234 (+0) and C63230 (+4, an
// interface base with no dtor); the inline Snapshot-style base dtor restores
// BBB554. Retail folds the element types to int; helper names are local.

#include <list>

template <> void _STL::_List_base<int, _STL::allocator<int> >::clear();
template <> _STL::_List_base<int, _STL::allocator<int> >::~_List_base();

class TunnelTrackerSnapshotBase
{
public:
	virtual ~TunnelTrackerSnapshotBase() {}
};

class TunnelTrackerInterfaceBase
{
public:
	virtual void onTunnel() = 0;
};

class TunnelTracker : public TunnelTrackerSnapshotBase, public TunnelTrackerInterfaceBase
{
protected:
	virtual ~TunnelTracker();

public:
	virtual void onTunnel();

private:
	_STL::list<int> m_tunnelIDs; // +0x08
	int m_containListSize; // +0x0C
	_STL::list<int> m_containList; // +0x10
	_STL::list<int> m_xferContainList; // +0x14
};

TunnelTracker::~TunnelTracker()
{
	m_tunnelIDs.clear();
}
