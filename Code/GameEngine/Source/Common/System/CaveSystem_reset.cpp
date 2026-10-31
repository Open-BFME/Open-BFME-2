// cl: /O1 /arch:SSE /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?reset@CaveSystem@@QAEXXZ @0x0042767F 55B.
// Frees every owned element of the malloc-config pointer vector at +0x10 of the
// CaveSystem object (the vector its dtor at 0x00427611 releases), then erases the
// whole range. The virtual first slot runs with flags 0, followed by the
// scalar operator delete 0x0002FD60 on the returned pointer.
typedef int Int;
typedef unsigned int UnsignedInt;

class TunnelTracker;
#include <vector>

// Pointer-vector begin/end/clear are expanded inline here; their out-of-line copies
// would differ from retail's. Declared imported and force-inlined, they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
TunnelTracker **vector<TunnelTracker *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
TunnelTracker **vector<TunnelTracker *>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
void vector<void *>::clear() { erase(begin(), end()); }
}

class TunnelTracker
{
public:
	TunnelTracker();
	virtual ~TunnelTracker();
	char pad[0x28 - 4];
};

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class CaveSystem : public SubsystemInterface, public Snapshot
{
public:
	CaveSystem();
	virtual ~CaveSystem();
	void reset();
	TunnelTracker *getTunnelTrackerForCaveIndex(UnsignedInt index);
	void registerNewCave(Int theIndex);
	void unregisterCave(Int theIndex);
	virtual void crc(Xfer *xfer) {}
	virtual void DoXfer(Xfer *xfer);
	virtual void LoadPostProcess() {}

private:
	_STL::vector<TunnelTracker *> m_tunnelTrackerVector;
};

void CaveSystem::reset()
{
	for (_STL::vector<TunnelTracker *>::iterator it = m_tunnelTrackerVector.begin(); it != m_tunnelTrackerVector.end(); ++it)
	{
		if (*it)
		{
			::delete *it;
		}
	}
	reinterpret_cast<_STL::vector<void *> *>(&m_tunnelTrackerVector)->clear();
}
