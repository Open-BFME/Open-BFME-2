// cl: /O1 /EHsc /MD /arch:SSE
// CaveSystem.cpp -- CaveSystem members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. Zero Hour's getTunnelTrackerForCaveIndex
// (GameLogic/System/CaveSystem.cpp) without its lazy creation: the tracker
// vector sits at +0x10.

typedef int Int;
typedef unsigned int UnsignedInt;

class TunnelTracker;

// STLport vector<TunnelTracker *> view.
class TunnelTrackerVector
{
public:
	UnsignedInt size() const { return m_finish - m_start; }
	TunnelTracker *operator[](UnsignedInt i) const { return m_start[i]; }

private:
	TunnelTracker **m_start;
	TunnelTracker **m_finish;
	TunnelTracker **m_endOfStorage;
};

class CaveSystem
{
public:
	TunnelTracker *getTunnelTrackerForCaveIndex(UnsignedInt index);

private:
	unsigned char m_pad00[0x10];
	TunnelTrackerVector m_tunnelTrackerVector;	// +0x10
};

// CaveSystem::getTunnelTrackerForCaveIndex, retail 0x004275B6.
TunnelTracker *CaveSystem::getTunnelTrackerForCaveIndex(UnsignedInt index)
{
	TunnelTracker *retVal = 0;
	if (index < m_tunnelTrackerVector.size())
		retVal = m_tunnelTrackerVector[index];
	return retVal;
}
