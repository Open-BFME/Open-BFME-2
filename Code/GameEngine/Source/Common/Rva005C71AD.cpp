// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva005C71AD@Rva005C71ADView@@QAEPAXPAXM00000000@Z retail 0x005C71AD..
// 0x005C743B (654B) thiscall ret 0x28.
//
// Coord3D key interpolator: the Coord3D sibling of the scalar
// CameraAnimationFrameData::doInterpolate 0x005C70DB and the quaternion
// interpolator 0x005C7098 (same int key at +0: 1 LINE 2 CATM else STEP).
// The first stack word is the result pointer (eax returns it); then t and
// four (point time) pairs. LINE blends the second and third points; CATM
// builds the outer control points from the time deltas (as 0x005C70DB does
// per component) and evaluates each component through the Catmull-Rom row
// ?Rva00503D8EEvaluate@@YAMMMMMM@Z (calls 0x005C735C 0x005C7386
// 0x005C73AE z then y then x); STEP copies the second point.
// Callers 0x00540E6C and 0x00540EBD (channel evaluator 0x0053FE64).
// WorldBuilder twin 0xEDB0C0 is CameraAnimationFrameData::doInterpolate
// (CameraAnimationFrameData.cpp asserts 88..357) returning a Vector3 by value;
// the pinned spelling models that return slot as the first pointer and types
// the times and points as void pointers.

float __cdecl Rva00503D8EEvaluate(float p0, float p1, float p2, float p3, float t);

// TU-local vector arithmetic over the Coord3D keys in the shape of WWMath's
// Vector3 inline operators (WorldBuilder's twin asserts in vector3.h:
// operator- 356 operator* 291 operator/ 314 operator+ 333); division
// multiplies by the reciprocal. operator- indexes through operator[] (with
// member access there cl schedules the second control point's products
// differently from retail).
class Rva005C71ADVec
{
public:
	Rva005C71ADVec() {}
	Rva005C71ADVec(const Rva005C71ADVec &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Rva005C71ADVec(float x, float y, float z) { X = x; Y = y; Z = z; }
	Rva005C71ADVec &operator=(const Rva005C71ADVec &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	float X, Y, Z;
};

inline Rva005C71ADVec operator+(const Rva005C71ADVec &a, const Rva005C71ADVec &b)
{
	return Rva005C71ADVec(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

inline Rva005C71ADVec operator-(const Rva005C71ADVec &a, const Rva005C71ADVec &b)
{
	return Rva005C71ADVec(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

inline Rva005C71ADVec operator*(const Rva005C71ADVec &a, float k)
{
	return Rva005C71ADVec(a.X * k, a.Y * k, a.Z * k);
}

inline Rva005C71ADVec operator*(float k, const Rva005C71ADVec &a)
{
	return Rva005C71ADVec(a.X * k, a.Y * k, a.Z * k);
}

inline Rva005C71ADVec operator/(const Rva005C71ADVec &a, float k)
{
	float ook = 1.0f / k;
	return Rva005C71ADVec(a.X * ook, a.Y * ook, a.Z * ook);
}

class Rva005C71ADView
{
public:
	void *rva005C71AD(void *result, float t, void *pa, void *ta, void *pc, void *tc, void *pf, void *tf, void *pd, void *td);
	int m_key;
};

void *Rva005C71ADView::rva005C71AD(void *result, float t, void *pa, void *ta, void *pc, void *tc, void *pf, void *tf, void *pd, void *td)
{
	Rva005C71ADVec *out = (Rva005C71ADVec *)result;
	const Rva005C71ADVec &a = *(const Rva005C71ADVec *)pa;
	const Rva005C71ADVec &c = *(const Rva005C71ADVec *)pc;
	const Rva005C71ADVec &f = *(const Rva005C71ADVec *)pf;
	const Rva005C71ADVec &d = *(const Rva005C71ADVec *)pd;
	switch (m_key) {
	case 1:
		*out = (1.0f - t) * c + t * f;
		break;
	case 2: {
		float d0 = (float)((int)tc - (int)ta);
		float d1 = (float)((int)tf - (int)tc);
		float d2 = (float)((int)td - (int)tf);
		Rva005C71ADVec v0;
		if (d0 > 0.0f)
			v0 = (a - c) * d1 / d0 + c;
		else
			v0 = a;
		Rva005C71ADVec v1;
		if (d2 > 0.0f)
			v1 = (d - f) * d1 / d2 + f;
		else
			v1 = d;
		*out = Rva005C71ADVec(Rva00503D8EEvaluate(v0.X, c.X, f.X, v1.X, t),
			Rva00503D8EEvaluate(v0.Y, c.Y, f.Y, v1.Y, t),
			Rva00503D8EEvaluate(v0.Z, c.Z, f.Z, v1.Z, t));
		break;
	}
	default:
		*out = c;
		break;
	}
	return out;
}
