// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug
//
// ?rva0027BED0@BfmeDrawableDrawTransform@@QAEXPAVMatrix3D@@@Z, retail
// 0x0027BED0..0x0027C157 (647 bytes), thiscall RET 4, called from
// Drawable::draw.
//
// Target evidence: copies *getTransformMatrix() (0x0027628E) into the
// caller's matrix, skips the multiply when the byte at +0x43F is set,
// otherwise post-multiplies by the matrix returned from 0x00271423, then
// passes the matrix to 0x0027BB65 (thiscall RET 4).
// Donor structure (Zero Hour Drawable::draw): transformMtx =
// *getTransformMatrix(); if (!isInstanceIdentity())
// transformMtx.postMul(*getInstanceMatrix()); applyPhysicsXform(&transformMtx).
// BFME factored those three statements into this helper. The +0x43F flag
// name and the applyPhysicsXform name of 0x0027BB65 are carried from the
// donor; 0x00271423 keeps its ledger address name.
// The flag must be read through an inline getter: a direct member test
// compiles the same instructions but swaps three mulss operand loads in
// the inlined WWMath postMul.

#define inline static inline
#include <math.h>
#undef inline
#include "../../../../reference/shims/bfme_colmathaabox/wwmath.h"
#include "../../../../reference/shims/bfme_matrix3d_sse_link/vector3.h"
#include "../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
#include "../../../../reference/shims/bfme_matrix3d_sse_link/matrix3d.h"

#include "../../Include/GameClient/Drawable.h"

class Rva00271423
{
public:
	Matrix3D *rva00271423();
};

class BfmeDrawableDrawTransform
{
public:
	void rva0027BED0(Matrix3D *transformMtx);
	bool isInstanceIdentity() const { return m_instanceIsIdentity; }

	char m_pad000[0x43F];
	bool m_instanceIsIdentity;	// +0x43F
};

void BfmeDrawableDrawTransform::rva0027BED0(Matrix3D *transformMtx)
{
	*transformMtx = *((Drawable *)this)->getTransformMatrix();
	if (!isInstanceIdentity())
		transformMtx->postMul(*((Rva00271423 *)this)->rva00271423());
	((Drawable *)this)->applyPhysicsXform(transformMtx);
}
