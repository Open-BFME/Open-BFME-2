// StandingWaterArea: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_STANDINGWATERAREA_H
#define CANONICAL_STANDINGWATERAREA_H

class StandingWaterArea
{
public:
	void LoadPCAFile();
	void loadFXShaderSetup();
	void rva00308A12(float fraction, int *r, int *g, int *b);
};

#endif // CANONICAL_STANDINGWATERAREA_H
