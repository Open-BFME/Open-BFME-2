// W3DBridgeBuffer: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_W3DBRIDGEBUFFER_H
#define CANONICAL_W3DBRIDGEBUFFER_H

class W3DTerrainLogic;

class W3DBridgeBuffer
{
public:
	~W3DBridgeBuffer();
	void allocateBridgeBuffers();
	void clearAllBridges();
	void loadBridges(W3DTerrainLogic *pTerrainLogic, bool saveGame);
};

#endif // CANONICAL_W3DBRIDGEBUFFER_H
