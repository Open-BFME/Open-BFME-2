// QuadStrip2D: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_QUADSTRIP2D_H
#define CANONICAL_QUADSTRIP2D_H

struct BfmeE8;
class DataChunkInput;
class Matrix3D;

class QuadStrip2D
{
public:
	void parse(DataChunkInput &file, int flag);
	void rva005382F4(const BfmeE8 &offset);
	void rva0053841C(const Matrix3D &mtx);
	QuadStrip2D &rva005388F7(const QuadStrip2D &other);
	void rva0053892C(unsigned int count);
};

#endif // CANONICAL_QUADSTRIP2D_H
