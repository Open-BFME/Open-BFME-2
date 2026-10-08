// cl: /MD
//
// ?rva00100362@?$SimpleDynVecClass@VVector3@@@@QBEXABVPlaneClass@@AAV1@@Z, retail 0x00100362, 518 bytes.
// Clip polygon against plane into dest. Donor logic VisPolyClass::Clip in
// reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/visrasterizer.cpp
// adapted to raw SimpleDynVecClass<Vector3> (this/dest are the Verts vectors).
// Evidence: this+4/this+12 are Vector/ActiveCount; arg8 is Plane (N at +0/+4/+8
// D at +0xc); arg12 dest cleared then Add calls; callers at 0x00100731 etc pass
// frustum planes at +0x30..+0x80 ping-ponging two temps; callees rowed
// Compute_Intersection 0x00069168 Add 0x001002C5 single-arg 0x00100354.
// The loop names the current vertex as a reference before testing it: passed
// straight to In_Front, MSVC 7.1 loads point.X rather than N.X for the last
// product, against retail.

class Vector3
{
public:
	float X;
	float Y;
	float Z;
	static void Lerp(const Vector3 &a, const Vector3 &b, float alpha, Vector3 *out)
	{
		out->X = a.X + (b.X - a.X) * alpha;
		out->Y = a.Y + (b.Y - a.Y) * alpha;
		out->Z = a.Z + (b.Z - a.Z) * alpha;
	}
};

class PlaneClass
{
public:
	bool Compute_Intersection(const Vector3 &p0, const Vector3 &p1, float *set_t) const;
	bool In_Front(const Vector3 &point) const
	{
		float dist = N.Z * point.Z;
		dist += N.Y * point.Y;
		dist += N.X * point.X;
		return dist > D;
	}
	Vector3 N;
	float D;
};

// Target view only: the six frustum planes start at +0x30 and are 16 bytes
// apart in the object passed to rva001006f8 at 0x001006F8.
struct Rva001006F8FrustumView
{
	char pad00[0x30];
	PlaneClass planes[6];
};

template <class Type>
class SimpleDynVecClass
{
public:
	SimpleDynVecClass(int size);
	virtual __declspec(nothrow) ~SimpleDynVecClass();
	bool Add(const Type &object, int new_size_hint);
	bool rva00100354(const Type &object);
	void rva00100362(const class PlaneClass &plane, SimpleDynVecClass<Vector3> &dest) const;
	void rva00100568();
	void rva001006f8(const Rva001006F8FrustumView &frustum, SimpleDynVecClass<Type> &dest) const;
	void Delete_All(bool allow_shrink = true) { ActiveCount = 0; }
	int Count() const { return ActiveCount; }
	const Type &operator[](int i) const { return Vector[i]; }
	Type *Vector;
	int VectorMax;
	int ActiveCount;
};

void SimpleDynVecClass<Vector3>::rva00100362(const PlaneClass &plane, SimpleDynVecClass<Vector3> &dest) const
{
	dest.Delete_All(false);
	int vcount = Count();
	int iprev = vcount - 1;
	bool prev_point_in_front;
	bool cur_point_in_front;
	float alpha;
	Vector3 int_point;
	int i = 0;
	if (vcount <= 2)
		return;
	prev_point_in_front = !plane.In_Front((*this)[iprev]);
	for (int j = 0; j < vcount; j++) {
		const Vector3 &cur = (*this)[i];
		cur_point_in_front = !plane.In_Front(cur);
		if (prev_point_in_front) {
			if (cur_point_in_front) {
				dest.rva00100354((*this)[i]);
			} else {
				plane.Compute_Intersection((*this)[iprev], (*this)[i], &alpha);
				Vector3::Lerp((*this)[iprev], (*this)[i], alpha, &int_point);
				dest.Add(int_point, 0);
			}
		} else {
			if (cur_point_in_front) {
				plane.Compute_Intersection((*this)[iprev], (*this)[i], &alpha);
				Vector3::Lerp((*this)[iprev], (*this)[i], alpha, &int_point);
				dest.Add(int_point, 0);
				dest.rva00100354((*this)[i]);
			}
		}
		prev_point_in_front = cur_point_in_front;
		iprev = i;
		i++;
		if (i >= vcount)
			i = 0;
	}
}

// Target evidence: this is an address-derived thiscall body (0x001006F8,
// 184 bytes). It applies the six contiguous frustum planes to this vector,
// ping-ponging two temporary SimpleDynVecClass<Vector3> objects, then calls
// the separately pinned vector post-pass at 0x00100568. The sequence mirrors
// the six-plane VisPolyClass clipping in the BFME1 visrasterizer.cpp donor;
// that donor guides the operation, while the target calls and plane offsets
// establish this body's structure. The actual class and public method name
// remain unresolved.
void SimpleDynVecClass<Vector3>::rva001006f8(const Rva001006F8FrustumView &frustum,
		SimpleDynVecClass<Vector3> &dest) const
{
	register int zero = 0;
	SimpleDynVecClass<Vector3> first(zero);
	SimpleDynVecClass<Vector3> second(zero);
	rva00100362(frustum.planes[0], second);
	second.rva00100362(frustum.planes[1], first);
	first.rva00100362(frustum.planes[2], second);
	second.rva00100362(frustum.planes[3], first);
	first.rva00100362(frustum.planes[4], second);
	second.rva00100362(frustum.planes[5], dest);
	dest.rva00100568();
}

template void SimpleDynVecClass<Vector3>::rva001006f8(
		const Rva001006F8FrustumView &, SimpleDynVecClass<Vector3> &) const;
