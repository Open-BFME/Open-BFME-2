// ?rva000D08C3@Rva000D08C3@@QAEXPAVMatrix3D@@@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// NEAR (helper draft, not under Code/): 617 of 625 bytes; same frame,
// calls, branches and Rotate_Z tail. Remaining: (1) the two axis dot
// products use different xmm registers/load order (retail keeps axis.z in
// xmm4 and loads Row[1][1] early); (2) the turn-limit else branch reloads
// (+0x190 then +0x2E8) where cl reuses xmm0 = m_lastAngle (8 bytes). Needs
// the class-gate Coord3D allow (Normalize/dtor) as written.
// ?rva000D08C3@Rva000D08C3@@QAEXPAVMatrix3D@@@Z retail 0x000D08C3..0x000D0B34 (625 bytes, ret 4).
// A draw-module vtable slot (entry at 0x007CDD64) that limits how far a
// transform may turn about Z. It measures the matrix's X column against the
// fixed normalized (0.5 0.5 0) axis (function-local static, normalized
// through the rowed Coord3D::Normalize 0x00005A70 on every call): the
// clamped dot gives the angle (acos then the rowed normalizeAngle
// 0x00238954), capped by the module data's +0x188 and mirrored when the Y
// column's dot is negative; after the first call the change from the last
// angle (+0x2E8; +0x2EC marks it valid) is limited to the module data's
// +0x190 per call. The result is stored and applied as WWMath's inline
// Matrix3D::Rotate_Z (cos/sin imports). WorldBuilder twin 0x0095E7A0 is
// unnamed; owner and member names are not recovered.
// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's Normalize (rowed 0x00005A70) nor the user-declared empty destructor that makes the static axis register an atexit stub (retail 0x007B6DA9 ret); same three floats

extern "C" double __cdecl acos(double);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);

typedef float Real;

struct Coord3D
{
	Coord3D(Real ax, Real ay, Real az) : x(ax), y(ay), z(az) {}
	~Coord3D() {}
	Real Normalize();
	Real dot(const Coord3D &o) const { return x * o.x + y * o.y + z * o.z; }

	Real x, y, z;
};

Real normalizeAngle(Real angle);

class Matrix3D
{
public:
	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float c, s;

		c = (float)cos(theta);
		s = (float)sin(theta);

		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)(c * tmp1 + s * tmp2);
		Row[0][1] = (float)(-s * tmp1 + c * tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)(c * tmp1 + s * tmp2);
		Row[1][1] = (float)(-s * tmp1 + c * tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)(c * tmp1 + s * tmp2);
		Row[2][1] = (float)(-s * tmp1 + c * tmp2);
	}

	float Row[3][4];
};

struct Rva000D08C3Data
{
	char m_pad[0x188];
	Real m_maxAngle; // +0x188
	Real m_pad18C;
	Real m_maxTurn; // +0x190
};

class Rva000D08C3
{
public:
	void rva000D08C3(Matrix3D *mat);

private:
	void *m_vtable;
	const Rva000D08C3Data *m_data; // +0x04
	char m_pad08[0x2E8 - 0x08];
	Real m_lastAngle; // +0x2E8
	bool m_hasLastAngle; // +0x2EC
};

void Rva000D08C3::rva000D08C3(Matrix3D *mat)
{
	static Coord3D axis(0.5f, 0.5f, 0.0f);
	axis.Normalize();
	Real cosAngle = axis.dot(Coord3D(mat->Row[0][0], mat->Row[1][0], mat->Row[2][0]));
	Real sinAngle = axis.dot(Coord3D(mat->Row[0][1], mat->Row[1][1], mat->Row[2][1]));
	const Rva000D08C3Data *data = m_data;
	if (cosAngle < -1.0f)
		cosAngle = -1.0f;
	else if (cosAngle > 1.0f)
		cosAngle = 1.0f;
	Real angle = normalizeAngle((Real)acos(cosAngle));
	if (angle > data->m_maxAngle)
		angle = data->m_maxAngle;
	if (sinAngle < 0.0f)
		angle = normalizeAngle(-angle);
	if (m_hasLastAngle)
	{
		if (fabs(angle - m_lastAngle) > data->m_maxTurn)
		{
			if (angle < m_lastAngle)
				angle = m_lastAngle - data->m_maxTurn;
			else
				angle = data->m_maxTurn + m_lastAngle;
		}
	}
	m_lastAngle = angle;
	mat->Rotate_Z(m_lastAngle);
	m_hasLastAngle = true;
}
