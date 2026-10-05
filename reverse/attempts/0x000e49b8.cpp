// ?rva000E49B8@Rva000E48BC@@QAE_NH@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /MD /arch:SSE
//
// ?rva000E48BC@Rva000E48BC@@QAE_NPAVRva000E488F@@@Z, retail 0x000E48BC, 252 bytes.
// Updates world pos at +0 from offset at +0x10 via Drawable at +0x2C matrix
// then checks container predicate and returns changed.
// Evidence: retail push ebp plus mov ebp esp plus sub esp 0x0c frame; mov
// esi ecx plus mov ecx [esi+0x2C] plus test plus mov bl [esi+0x80] plus je;
// push edi plus lea edi [esi+0x10] plus call getTransformMatrix at 0x0027628E
// plus cmp esi edi plus jne plus movss mulss addss rows plus pop edi; mov
// ecx [ebp+8] plus push esi plus call 0x000E488F plus neg sbb inc plus xor
// ecx ecx plus cmp bl al plus mov [esi+0x80] al plus setne cl plus mov al cl;
// Matrix3D Transform_Vector alias check plus Z Y X row order proven by
// retail movss sequence; container Rva000E488F rowed; Drawable
// getTransformMatrix pinned; callers at 0x000E5819; unblocks 0x000E57FF.
// Layout begin +0 plus +0x10 plus +0x2C plus +0x80 proven by retail loads;
// element and owner unproven so honest Rva names only.
#define WWINLINE __forceinline

class Vector3
{
public:
	float X;
	float Y;
	float Z;
	WWINLINE float &operator[](int i) { return (&X)[i]; }
	WWINLINE const float &operator[](int i) const { return (&X)[i]; }
	WWINLINE Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
	WWINLINE float &operator[](int i) { return (&X)[i]; }
	WWINLINE const float &operator[](int i) const { return (&X)[i]; }
};

#pragma optimize("ty", on)
class Matrix3D
{
public:
	Vector4 Row[3];
	WWINLINE Vector4 &operator[](int i) { return Row[i]; }
	WWINLINE const Vector4 &operator[](int i) const { return Row[i]; }
	static WWINLINE void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in) {
			tmp = in;
			v = &tmp;
		} else {
			v = (Vector3 *)&in;
		}
		out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
		out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
		out->Z = (A[2][0] * v->X + A[2][1] * v->Y + A[2][2] * v->Z + A[2][3]);
	}
};
#pragma optimize("", on)

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
};

class Rva000E488F
{
public:
	bool rva000E488F(void *arg);
};

class Rva000E48BC
{
public:
	bool rva000E48BC(Rva000E488F *container);
	bool rva000E49B8(int player);
	Vector3 m_pos;
	float m_extent;
	Vector3 m_offset;
	char m_pad1C[0x2C - 0x1C];
	Drawable *m_drawable;
	char m_pad30[0x80 - 0x30];
	bool m_flag;
};

bool Rva000E48BC::rva000E48BC(Rva000E488F *container)
{
	bool old = m_flag;
	if (m_drawable) {
		Vector3 *out = &m_pos;
		const Vector3 *in = &m_offset;
		const Matrix3D *mtx = m_drawable->getTransformMatrix();
		Matrix3D::Transform_Vector(*mtx, *in, out);
	}
	bool cur = !container->rva000E488F(this);
	m_flag = cur;
	return old != cur;
}

enum CellShroudStatus
{
	CellShroudStatusShrouded = 0,
	CellShroudStatusClear = 1
};
struct Coord3D
{
	float X;
	float Y;
	float Z;
};
class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int player, const Coord3D *pos) const;
};
extern PartitionManager *TheShroudManager;

// ?rva000E49B8@Rva000E48BC@@QAE_NH@Z present-unmatched
bool Rva000E48BC::rva000E49B8(int player)
{
	Drawable *d = m_drawable;
	if (d && ((*(int *)((char *)d + 0x264) >> 12) & 1))
		return true;
	if (!TheShroudManager)
		return false;
	if (d) {
		Vector3 *out = &m_pos;
		const Vector3 *in = &m_offset;
		const Matrix3D *mtx = d->getTransformMatrix();
		Matrix3D::Transform_Vector(*mtx, *in, out);
	}
	Coord3D c;
	c.X = m_pos.X;
	c.Y = m_pos.Y;
	c.Z = m_pos.Z;
	if (!TheShroudManager->getShroudStatusForPlayer(player, &c))
		return true;
	c.X = m_pos.X + m_extent;
	c.Y = m_pos.Y;
	c.Z = m_pos.Z;
	if (!TheShroudManager->getShroudStatusForPlayer(player, &c))
		return true;
	c.X = m_pos.X - m_extent;
	c.Y = m_pos.Y;
	c.Z = m_pos.Z;
	if (!TheShroudManager->getShroudStatusForPlayer(player, &c))
		return true;
	c.X = m_pos.X;
	float yPlus = m_pos.Y;
	c.Y = yPlus + m_extent;
	c.Z = m_pos.Z;
	if (!TheShroudManager->getShroudStatusForPlayer(player, &c))
		return true;
	c.X = m_pos.X;
	c.Y = m_pos.Y - m_extent;
	c.Z = m_pos.Z;
	if (!TheShroudManager->getShroudStatusForPlayer(player, &c))
		return true;
	return false;
}
