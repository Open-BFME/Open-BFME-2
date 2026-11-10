// cl: /O2 /G7 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Native final RET4 occupies all three bytes at 7166C4..7166C7.
// BFME1 a7c38d3b2597121f178ab5190b3062478823257d, WWMath/matrix4.h:
// Gauss-Jordan elimination with partial pivoting and vector4.h arithmetic.
// BFME2 715EB0..7166C7 uses an explicit output pointer. It writes the result
// directly there and does not return an aggregate pointer in EAX. The caller
// at 7133F0 supplies the same output storage. This ABI difference also lets
// MSVC reproduce retail's pivot-search and elimination unrolling naturally.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
// The Vector4 view is the SSE link view (ctor/Set/scalar product stay inline
// without emitting copies that compete with retail's owners); the row below
// keeps this unit's /O2 flags. WWMath's Fabs is inlined everywhere here, so
// its /O2 copy is renamed out of the link (retail's owner is size-optimised).
#define Fabs Fabs_BFME_LINK_LOCAL
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"

#include "Matrix4Data.h"

void Matrix4::Inverse(Matrix4 *out) const
{
    // Keep the elimination workspace local: its copy/access helpers are not
    // additional definitions of Matrix4 public members elsewhere in the tree.
    struct Matrix4InverseWork
    {
    public:
        __forceinline Matrix4InverseWork(const Matrix4 &matrix4)
        {
            Row[0] = matrix4.Row[0]; Row[1] = matrix4.Row[1];
            Row[2] = matrix4.Row[2]; Row[3] = matrix4.Row[3];
        }
        __forceinline explicit Matrix4InverseWork(bool identity)
        {
            if (identity) {
                Row[0].Set(1, 0, 0, 0); Row[1].Set(0, 1, 0, 0);
                Row[2].Set(0, 0, 1, 0); Row[3].Set(0, 0, 0, 1);
            }
        }
        __forceinline Vector4 &operator[](int i) { return Row[i]; }
        __forceinline const Vector4 &operator[](int i) const { return Row[i]; }
        Vector4 Row[4];
    };
    
    Matrix4 &b = *out;
    Matrix4InverseWork a(*this);
    b.Row[0].Set(1, 0, 0, 0); b.Row[1].Set(0, 1, 0, 0);
    b.Row[2].Set(0, 0, 1, 0); b.Row[3].Set(0, 0, 0, 1);
    int i, j, i1;

    for (j = 0; j < 4; ++j) {
        i1 = j;
        for (i = j + 1; i < 4; ++i) {
            if (WWMath::Fabs(a[i][j]) > WWMath::Fabs(a[i1][j]))
                i1 = i;
        }

        Swap(a.Row[i1], a.Row[j]);
        Swap(b.Row[i1], b.Row[j]);
        b.Row[j] /= a.Row[j][j];
        a.Row[j] /= a.Row[j][j];

        for (i = 0; i < 4; ++i) {
            if (i != j) {
                b.Row[i] -= a[i][j] * b.Row[j];
                a.Row[i] -= a[i][j] * a.Row[j];
            }
        }
    }
}
