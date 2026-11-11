// PathfinderPosGoalManager: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_PATHFINDERPOSGOALMANAGER_H
#define CANONICAL_PATHFINDERPOSGOALMANAGER_H

class Xfer;

class PathfinderPosGoalManager
{
public:
	void LoadPostProcess();
	void rva004DD658(Xfer *xfer);
	bool rva004DE2ED();
};

#endif // CANONICAL_PATHFINDERPOSGOALMANAGER_H
