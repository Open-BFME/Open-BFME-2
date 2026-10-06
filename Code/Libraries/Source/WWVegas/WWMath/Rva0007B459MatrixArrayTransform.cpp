// cl: /Ireference/shims/bfmerendobj /MD /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME1 donor6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/Libraries/Source/WWVegas/WWMath/matrix3d.h: mulVector3Array(Vector3*,int).
// Lead: clean coltest.cpp compiled under BFME2 O1/G7/SSE/MD.
// Target168B at7B459 begins after verified147B Translate7B3C6 and ends
// on RET8 before rowed192B Transform_Vector7B501. No Ghidra entry, direct
// E8/E9 callers or absolute references were found: reachability is unknown.
// It reads a count, visits in-place12B vectors and applies
// three16B rows including translation. No calls or relocations. Original
// target class/method names are unproven; shared math classes are views.
// Copyright2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the donor.
// Keep the donor expression parentheses: MSVC7.1 SSE register allocation
// differs without them, despite identical source-level arithmetic.
// Store the three temporaries directly to avoid emitting an unused
// Vector3::Set COMDAT copy under this unit's O1/SSE flags.
#include "matrix3d.h"
class Rva0007B459MatrixArrayTransform : public Matrix3D
{
public:
 void transform_inplace(Vector3 *inout, int count) const;
};
void Rva0007B459MatrixArrayTransform::transform_inplace(Vector3 *inout, int count) const
{
 while (count--)
 {
  float x = (Row[0].X * inout->X + Row[0].Y * inout->Y + Row[0].Z * inout->Z + Row[0].W);
  float y = (Row[1].X * inout->X + Row[1].Y * inout->Y + Row[1].Z * inout->Z + Row[1].W);
  float z = (Row[2].X * inout->X + Row[2].Y * inout->Y + Row[2].Z * inout->Z + Row[2].W);
  inout->X = x;
  inout->Y = y;
  inout->Z = z;
  ++inout;
 }
}
