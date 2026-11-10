// cl: /Ireference/shims/bfmerendobj /O2 /G7 /MD /arch:SSE /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME1 donor 4367fc698990427e26cc1c399989d074d8ee9bbe:
// game/Libraries/Source/WWVegas/WWMath/Matrix3D_Transform_Vector.cpp,
// retail RVA 0x009244F0 (199B). BFME2 SSE settings reproduce 302B at
// 0x00168AD0, with int3 on both sides and a terminal ret 20.
// Target evidence: two 12B-stride input arrays, one 12B-stride output,
// three matrix rows 16B apart and six products summed per output coordinate.
// Row fourth components are unused. No calls or relocations occur in the body.
// Structural view: reuse the shared Matrix3D/Vector3 layout rather than the
// donor's private class copies. This adapter adds no data or virtual methods;
// the original target class and method names remain unproven.

// Same first-array anchor as Matrix3DUnmatchedSSE.cpp: keep the emitted
// compiler vector constructor iterator at retail's 34B /O1 shape.
// This static driver is unemitted and has no retail claim.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
// ?bfmePairTransformVciAnchor absent-from-retail
static void bfmePairTransformVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

#include "matrix3d.h"
class Rva00168AD0MatrixPairTransform : public Matrix3D
{
public:
 void transform_pair_vectors(const Vector3 *in0, const Matrix3D &matrix, const Vector3 *in1, Vector3 *out, int count) const;
};
void Rva00168AD0MatrixPairTransform::transform_pair_vectors(const Vector3 *in0, const Matrix3D &matrix,
	const Vector3 *in1, Vector3 *out, int count) const
{
	while (count--)
	{
		out->X = Row[0].X * in0->X + Row[0].Y * in0->Y + Row[0].Z * in0->Z
			+ matrix[0].X * in1->X + matrix[0].Y * in1->Y + matrix[0].Z * in1->Z;
		out->Y = Row[1].X * in0->X + Row[1].Y * in0->Y + Row[1].Z * in0->Z
			+ matrix[1].X * in1->X + matrix[1].Y * in1->Y + matrix[1].Z * in1->Z;
		out->Z = Row[2].X * in0->X + Row[2].Y * in0->Y + Row[2].Z * in0->Z
			+ matrix[2].X * in1->X + matrix[2].Y * in1->Y + matrix[2].Z * in1->Z;
		++in0;
		++in1;
		++out;
	}
}
