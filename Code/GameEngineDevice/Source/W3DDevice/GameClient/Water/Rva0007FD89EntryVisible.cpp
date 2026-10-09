// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva0007FB85@Rva0007FD89Entry@@QAE_NPAX@Z, retail 0x0007FB85..0x0007FC38
// (179 bytes, EH, RET 4): the per-entry test the rowed
// WaterRenderObjClass::IsReflectionVisible (0x0007FD89) runs with the camera.
// It refreshes the camera's frustum (rowed CameraClass::Update_Frustum),
// copies the entry's points (the 12-byte vector at +0x14) into a polygon
// (rowed SimpleDynVecClass<Vector3> constructor and single-argument add),
// clips it against the camera's frustum at +0x100 into a second polygon
// (rowed clip 0x001006F8) and answers whether at least three vertices
// survive. Both polygons are torn down by the rowed destructor.

#include <vector>

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

struct Rva001006F8FrustumView;

template <class Type>
class SimpleDynVecClass
{
public:
	SimpleDynVecClass(int size);
	virtual __declspec(nothrow) ~SimpleDynVecClass();
	bool rva00100354(const Type &object);
	void rva001006f8(const Rva001006F8FrustumView &frustum, SimpleDynVecClass<Vector3> &dest) const;
	int Count() const { return ActiveCount; }
protected:
	Type *Vector;
	int VectorMax;
	int ActiveCount;
};

class CameraClass
{
public:
	const Rva001006F8FrustumView &Get_Frustum() const { Update_Frustum(); return *(const Rva001006F8FrustumView *)((const char *)this + 0x100); }
protected:
	void Update_Frustum() const;
};

class Rva0007FD89Entry
{
public:
	bool rva0007FB85(void *camera);
private:
	unsigned char m_pad00[0x14];
	_STL::vector<Vector3> m_points;			// +0x14
};

bool Rva0007FD89Entry::rva0007FB85(void *camera)
{
	const Rva001006F8FrustumView &frustum = ((CameraClass *)camera)->Get_Frustum();
	SimpleDynVecClass<Vector3> polygon(0);
	for (int i = 0; i < (int)m_points.size(); i++)
		polygon.rva00100354(m_points[i]);
	SimpleDynVecClass<Vector3> clipped(0);
	polygon.rva001006f8(frustum, clipped);
	if (clipped.Count() >= 3)
		return true;
	return false;
}
