// cl: /Ireference/shims/bfmerendobj /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Get_Inverse@Matrix4@@QBEXAAV1@@Z, retail 0x00715E90 (19 B).
// BFME2's D3DX9-backed 4x4 inverse, the sibling of the rowed
// ?Get_Inverse@Matrix3D@@QBEXAAV1@@Z 0x00713290: the out-parameter is pushed
// as pOut, its own stack slot is reused for the determinant temporary, and
// this is pushed as pM.  The retail call displacement resolves to the pinned
// _D3DXMatrixInverse@12 import thunk 0x0062AF38.  Caller 0x0014A880 pushes a
// stack matrix as the out argument and reads the inverted rows back, so the
// reference-parameter recipe is target evidence.  The class is the TU-scoped
// Matrix4 view this unit needs; the matrix layout is sixteen floats.
#include "D3dx8math.h"

class Matrix4
{
public:
	void Get_Inverse(Matrix4 & out) const;
private:
	float m[4][4];
};

void Matrix4::Get_Inverse(Matrix4 & out) const
{
	float det;
	D3DXMatrixInverse((D3DXMATRIX *)&out, &det, (D3DXMATRIX *)this);
}
