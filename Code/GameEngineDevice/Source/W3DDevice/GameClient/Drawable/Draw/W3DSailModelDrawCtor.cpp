// cl: /DNDEBUG /MD /EHsc
//
// ??0W3DSailModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000D078F,
// 60 bytes. Draw-side ctor completing the W3DSailModelDraw file-unit (name
// getter rowed at 0xD0810 returning the W3DSailModelDraw literal; pool key
// rowed at 0xD07CB; ModuleData factory rowed at 0x64FD3; behavior instance
// factory rowed at 0x64F98 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the W3DScriptedModelDraw base
// 0xC0DD8 with a float zero and a flag zero around the derived vtable slots
// stored explicitly via pointer casts (W3DTreeDraw precedent: no virtuals are
// declared anywhere so no vtable is emitted here; the immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the existing
// W3DScriptedModelDraw pin). Row supersedes the ctor pin.
//
// W3DSailModelDraw::rva000D08C3, retail 0x000D08C3..0x000D0B34 (625 bytes,
// ret 4): the class's override of the empty one-argument hook in the last
// W3DScriptedModelDraw slot (vtable entry 0x007CDD64; the other scripted
// draws hold an empty stub there). It turns the transform about Z toward a
// fixed wind direction: a function-local (0.5 0.5 0) normalized through the
// rowed Coord3D::Normalize 0x00005A70 on every call. The X and Y columns'
// dots with it give the angle (acos, then the rowed normalizeAngle
// 0x00238954), capped by MaxRotationDegrees (+0x188 of the module data) and
// mirrored when the Y dot is negative; once a last angle is held (+0x2E8,
// valid flag +0x2EC) the change per call is limited to AboutDamping (+0x190).
// The result is stored and applied through WWMath's inline Rotate_Z.
// WorldBuilder twin 0x0095E7A0 (unnamed) builds each column as a named
// MathCoord3D.h coordinate and takes the dot through that header's member
// (asserts at lines 580 and 581): named columns give retail's register
// numbering and the early Row[1][1] load, where temporaries do not. fabsf
// rather than the fabs(float) overload puts the argument pop before the
// fxch and keeps retail's reload of the last angle in the damping branch.
#include <math.h>
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;

Real normalizeAngle(Real angle);

struct SailCoord3D : Coord3D
{
	SailCoord3D(Real a, Real b, Real c) { x = a; y = b; z = c; }
	~SailCoord3D() {}
	Real dot(const Coord3D &c3dIn) const { return x * c3dIn.x + y * c3dIn.y + z * c3dIn.z; }
};

#include "../../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"


#include "../../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
// WWMath matrix3d.h's inline Rotate_Z, which the canonical header leaves to units.
static __forceinline void matrixRotateZ(Matrix3D &m, float theta)
{
	float tmp1, tmp2;
	float c, s;

	c = cosf(theta);
	s = sinf(theta);

	tmp1 = m.Row[0][0]; tmp2 = m.Row[0][1];
	m.Row[0][0] = (float)( c*tmp1 + s*tmp2);
	m.Row[0][1] = (float)(-s*tmp1 + c*tmp2);

	tmp1 = m.Row[1][0]; tmp2 = m.Row[1][1];
	m.Row[1][0] = (float)( c*tmp1 + s*tmp2);
	m.Row[1][1] = (float)(-s*tmp1 + c*tmp2);

	tmp1 = m.Row[2][0]; tmp2 = m.Row[2][1];
	m.Row[2][0] = (float)( c*tmp1 + s*tmp2);
	m.Row[2][1] = (float)(-s*tmp1 + c*tmp2);
}

extern "C" const unsigned char __identifier("??_7Rva000CA119@@6BRva000CA119_B2@@@")[];
extern "C" const unsigned char __identifier("??_7W3DTankDraw@@6BDrawInterfaceA@@@")[];

extern "C" const unsigned char __identifier("??_7W3DSailModelDraw@@6B@")[];

class Thing;
class ModuleData;

class W3DScriptedModelDraw
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);

protected:
	unsigned char m_pad00[0x04];
	const ModuleData *m_moduleData; // +0x04
	unsigned char m_pad08[0x2E8 - 0x08];
};

class W3DSailModelDrawModuleData
{
public:
	unsigned char m_pad00[0x188];
	Real m_maxRotation; // +0x188 MaxRotationDegrees
	Real m_blowingThreshold; // +0x18C BlowingThresholdDegrees
	Real m_aboutDamping; // +0x190 AboutDamping
};

class W3DSailModelDraw : public W3DScriptedModelDraw
{
public:
	W3DSailModelDraw(Thing *thing, const ModuleData *moduleData);
	void rva000D08C3(Matrix3D *mat);

private:
	Real m_lastAngle; // +0x2E8
	bool m_hasLastAngle; // +0x2EC
};

// ??0W3DSailModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0xD078F
W3DSailModelDraw::W3DSailModelDraw(Thing *thing, const ModuleData *moduleData) :
	W3DScriptedModelDraw(thing, moduleData)
{
	*(unsigned int *)this = (unsigned int)__identifier("??_7W3DSailModelDraw@@6B@");
	*(unsigned int *)((char *)this + 0x0C) = ((unsigned int)__identifier("??_7W3DTankDraw@@6BDrawInterfaceA@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7Rva000CA119@@6BRva000CA119_B2@@@"));
	m_lastAngle = 0.0f;
	m_hasLastAngle = false;
}

void W3DSailModelDraw::rva000D08C3(Matrix3D *mat)
{
	static SailCoord3D axis(0.5f, 0.5f, 0.0f);
	axis.Normalize();
	SailCoord3D xcol(mat->Row[0][0], mat->Row[1][0], mat->Row[2][0]);
	Real cosAngle = axis.dot(xcol);
	SailCoord3D ycol(mat->Row[0][1], mat->Row[1][1], mat->Row[2][1]);
	Real sinAngle = axis.dot(ycol);
	const W3DSailModelDrawModuleData *data = (const W3DSailModelDrawModuleData *)m_moduleData;
	if (-1.0f > cosAngle)
		cosAngle = -1.0f;
	else if (cosAngle > 1.0f)
		cosAngle = 1.0f;
	Real angle = normalizeAngle((Real)acos(cosAngle));
	if (angle > data->m_maxRotation)
		angle = data->m_maxRotation;
	if (sinAngle < 0.0f)
		angle = normalizeAngle(-angle);
	if (m_hasLastAngle)
	{
		if (fabsf(angle - m_lastAngle) > data->m_aboutDamping)
		{
			if (angle < m_lastAngle)
				angle = m_lastAngle - data->m_aboutDamping;
			else
				angle = data->m_aboutDamping + m_lastAngle;
		}
	}
	m_lastAngle = angle;
	matrixRotateZ(*mat, m_lastAngle);
	m_hasLastAngle = true;
}
