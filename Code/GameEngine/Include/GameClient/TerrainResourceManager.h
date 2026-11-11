// TerrainResourceManager: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_TERRAINRESOURCEMANAGER_H
#define CANONICAL_TERRAINRESOURCEMANAGER_H

class Cb00359D42;

class TerrainResourceManager
{
public:
	void enumerateRegisteredClaimants(int v, Cb00359D42 *cb);
	float rva00359A0C(float x, float y, float radius, bool flag, int playerIndex);
	void rva0035A61F(unsigned int *diffuse, int x, int y, int playerIndex);
};

#endif // CANONICAL_TERRAINRESOURCEMANAGER_H
