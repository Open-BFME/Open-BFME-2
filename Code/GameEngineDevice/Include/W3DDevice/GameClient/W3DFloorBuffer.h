// W3DFloorBuffer: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_W3DFLOORBUFFER_H
#define CANONICAL_W3DFLOORBUFFER_H

class AsciiString;
class Gen_uw_000e5033;

class W3DFloorBuffer
{
public:
	Gen_uw_000e5033 *addFloor(int a0, AsciiString *a1, AsciiString *a2, bool a3, bool a4);
	void allocateFloorBuffers();
	void rva000E473F();
	void rva000E598B();
};

#endif // CANONICAL_W3DFLOORBUFFER_H
