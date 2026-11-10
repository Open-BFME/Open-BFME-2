// W3DTreeBuffer: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_W3DTREEBUFFER_H
#define CANONICAL_W3DTREEBUFFER_H

class AsciiString;
struct Coord3D;
class Matrix3D;
struct Rva000ECF79Coord;
struct Rva000ECF79Data;
class Vector3;

class W3DTreeBuffer
{
public:
	void addTree(unsigned int id, Rva000ECF79Coord location, float scale, const Matrix3D *transform, float randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD);
	void rva000EA24D();
	void rva000EA2C0(void *a0);
	char rva000EA327(void *key, Vector3 position, const Matrix3D *transform);
	bool rva000EA48D(void *a, const Coord3D *b, float c);
	bool rva000EA644(void *firstValue);
	bool rva000EA6A7(void *a);
	bool rva000ECF2A(unsigned int a, int b);
};

#endif // CANONICAL_W3DTREEBUFFER_H
