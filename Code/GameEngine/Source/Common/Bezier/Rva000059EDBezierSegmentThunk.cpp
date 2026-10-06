// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Bezier/Rva000059EDBezierSegmentThunk.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?forward@Rva000059EDBezierSegmentThunk@@QBEXMPAUCoord3D@@@Z 0x000A8B37 (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Retail 0x000059ED is a five-byte tail jump to BezierSegment's matched
// evaluateBezSegmentAtT body. This wrapper keeps the ILT's address-derived
// identity and emits the proven route without duplicating that body.

typedef float Real;

struct Coord3D;

class BezierSegment
{
public:
	void evaluateBezSegmentAtT(Real tValue, Coord3D *outResult) const;
};

class Rva000059EDBezierSegmentThunk
{
public:
	void forward(Real tValue, Coord3D *outResult) const;
};

void Rva000059EDBezierSegmentThunk::forward(Real tValue, Coord3D *outResult) const
{
	((const BezierSegment *)this)->evaluateBezSegmentAtT(tValue, outResult);
}
