// Rva0009C134Host: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0009C134HOST_H
#define CANONICAL_RVA0009C134HOST_H

struct Coord3D;
class Matrix3D;

class Rva0009C134Host
{
public:
	void buildCameraTransform(Matrix3D &tm, float distance, float pitch);
	void rva0009AACF(int b, float a);
	void rva0009B7EA(Coord3D *corners);
	void rva0009BAA4();
	void rva0009C134();
	void setupSunRays();
};

#endif // CANONICAL_RVA0009C134HOST_H
