// cl: /D_CRTIMP= /D_STLP_USE_STATIC_LIB /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Include
//
// Record builders of the Rva000748F6 command pool (the class behind the
// Rva0007517F virtual interface): each fetches the pooled record through the
// rowed Rva00074AFFGet, stamps its kind at +0, stores the two flag fields at
// +0x34/+0x38 and fills the 48-byte transform at +4 (twelve dword moves for a
// copied Matrix3D). Facts from the retail bytes: kind 0 builds the
// from->to segment matrix through Matrix3D::Set(x, y, z, pos) with zero y/z
// axes; kinds 1-4 copy the caller's transform and scale its three axes in
// Matrix3D::Scale order (row 0..2 of column x, then y, then z): kind 1 by a
// float[3], kind 2 and 4 uniformly, kind 3 by (radius, radius, height).
// The Matrix3D/Vector3 members and the Set/Scale axis order are BFME 1's WWMath
// (donor); the scale loops are written out through a local __forceinline
// helper because the header's own Matrix3D::Scale inlines with a commuted
// multiply that retail does not have.
#include "matrix3d.h"

class Rva000748F6
{
public:
	int m_kind;
	Matrix3D m_transform; // +4
	int m_34;
	unsigned char m_38;
};

Rva000748F6 *__stdcall Rva00074AFFGet(int dummy);

static __forceinline void scaleAxes(Matrix3D &matrix3D, float scaleX, float scaleY, float scaleZ)
{
	matrix3D[0][0] *= scaleX; matrix3D[1][0] *= scaleX; matrix3D[2][0] *= scaleX;
	matrix3D[0][1] *= scaleY; matrix3D[1][1] *= scaleY; matrix3D[2][1] *= scaleY;
	matrix3D[0][2] *= scaleZ; matrix3D[1][2] *= scaleZ; matrix3D[2][2] *= scaleZ;
}

Rva000748F6 *__stdcall Rva00074B3BGet(const Vector3 *from, const Vector3 *to, int arg34, unsigned char arg38, int dummy)
{
	Rva000748F6 *record = Rva00074AFFGet(dummy);
	record->m_kind = 0;
	record->m_34 = arg34;
	record->m_38 = arg38;
	Vector3 dir = *to - *from;
	record->m_transform.Set(dir, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), *from);
	return record;
}

Rva000748F6 *__stdcall Rva00074C3FGet(const Matrix3D *transform, const float *axisScale, int arg34, unsigned char arg38, int dummy)
{
	Rva000748F6 *record = Rva00074AFFGet(dummy);
	record->m_kind = 1;
	record->m_34 = arg34;
	record->m_38 = arg38;
	record->m_transform = *transform;
	scaleAxes(record->m_transform, axisScale[0], axisScale[1], axisScale[2]);
	return record;
}

Rva000748F6 *__stdcall Rva00074DB4Get(const Matrix3D *transform, float scale, int arg34, unsigned char arg38, int dummy)
{
	Rva000748F6 *record = Rva00074AFFGet(dummy);
	record->m_kind = 2;
	record->m_34 = arg34;
	record->m_38 = arg38;
	record->m_transform = *transform;
	Matrix3D &matrix3D = record->m_transform;
	matrix3D[0][0] *= scale; matrix3D[1][0] *= scale; matrix3D[2][0] *= scale;
	matrix3D[0][1] *= scale; matrix3D[1][1] *= scale; matrix3D[2][1] *= scale;
	matrix3D[0][2] *= scale; matrix3D[1][2] *= scale; matrix3D[2][2] *= scale;
	return record;
}

Rva000748F6 *__stdcall Rva00074F25Get(const Matrix3D *transform, float radius, float height, int arg34, unsigned char arg38, int dummy)
{
	Rva000748F6 *record = Rva00074AFFGet(dummy);
	record->m_kind = 3;
	record->m_34 = arg34;
	record->m_38 = arg38;
	record->m_transform = *transform;
	float scaleRadius = radius;
	float h = height;
	scaleAxes(record->m_transform, scaleRadius, scaleRadius, h);
	return record;
}

Rva000748F6 *__stdcall Rva00075091Get(const Matrix3D *transform, float scale, int arg34, unsigned char arg38, int dummy)
{
	Rva000748F6 *record = Rva00074AFFGet(dummy);
	record->m_kind = 4;
	record->m_34 = arg34;
	record->m_38 = arg38;
	record->m_transform = *transform;
	Matrix3D &matrix3D = record->m_transform;
	matrix3D[0][0] *= scale; matrix3D[1][0] *= scale; matrix3D[2][0] *= scale;
	matrix3D[0][1] *= scale; matrix3D[1][1] *= scale; matrix3D[2][1] *= scale;
	matrix3D[0][2] *= scale; matrix3D[1][2] *= scale; matrix3D[2][2] *= scale;
	return record;
}
