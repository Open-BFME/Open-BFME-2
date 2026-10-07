// ?rva004BFB1C@ActiveBody@@QAEXMPBUCoord3D@@@Z
// partial score=0.6 date=2026-10-07
// cl: /O1 /EHs /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <algorithm>
typedef float Real;
typedef int Int;
typedef bool Bool;
struct Coord3D { Real x, y, z; };
class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}
	Real X, Y, Z;
};
inline Vector3 operator-(const Vector3 &a) { return Vector3(-a.X, -a.Y, -a.Z); }
inline Real operator*(const Vector3 &a, const Vector3 &b) { return a.X * b.X + a.Y * b.Y + a.Z * b.Z; }
class Matrix3D
{
public:
	Vector3 Get_X_Vector() const { return Vector3(Row[0][0], Row[1][0], Row[2][0]); }
	Vector3 Get_Y_Vector() const { return Vector3(Row[0][1], Row[1][1], Row[2][1]); }
	Real Row[3][4];
};
class Object
{
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	void *m_vptr;
	void *m_template;
	Matrix3D m_transform;
};
class BodyModuleInterface
{
public:
	virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3(); virtual void i4(); virtual void i5();
	virtual Real getMaxHealth() const;
};
class Base0 { public: virtual void b0(); void *m_md; Object *m_object; void *m_v0c; };
class AB : public Base0, public BodyModuleInterface
{
public:
	void rva004BFB1C(Real amount, const Coord3D *pos);
	Object *getObject() const { return m_object; }
	unsigned char m_pad14[0xCC - 0x14];
	Real m_sideDamage[4];
};
void AB::rva004BFB1C(Real amount, const Coord3D *pos)
{
	const Matrix3D *mtx = getObject()->getTransformMatrix();
	Vector3 dir(mtx->Row[0][3] - pos->x, mtx->Row[1][3] - pos->y, mtx->Row[2][3] - pos->z);
	Real sides[4];
	sides[1] = mtx->Get_Y_Vector() * dir;
	sides[0] = -mtx->Get_X_Vector() * dir;
	sides[2] = -sides[0];
	sides[3] = -sides[1];

	_STL::vector<Int> order;
	for (Int i = 0; i < 4; ++i)
	{
		Bool inserted = false;
		for (_STL::vector<Int>::iterator it = order.begin(); it != order.end(); ++it)
		{
			if (sides[i] > sides[*it])
			{
				order.insert(it, i);
				inserted = true;
				break;
			}
		}
		if (!inserted)
			order.push_back(i);
	}

	Real maxPerSide = getMaxHealth() * 0.25f;
	maxPerSide *= 0.75f;
	Real remaining = amount;
	for (Int k = 0; remaining > 0.0f; ++k)
	{
		if (k >= 4)
			break;
		Int side = order[k];
		Real room = maxPerSide - m_sideDamage[side];
		Real take = _STL::min(remaining, room);
		if (take > 0.0f)
		{
			m_sideDamage[side] = m_sideDamage[side] + take;
			remaining -= take;
		}
	}
}
