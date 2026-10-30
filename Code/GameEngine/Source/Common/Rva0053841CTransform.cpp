// cl: /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /O1 /G7 /arch:SSE /ICode/Libraries/Include /DNDEBUG /MD
// stlport
// QuadStrip2D::rva0053841C (retail 0x0053841C, 239 bytes); its WorldBuilder twin 0x00BACBF0 lies in the QuadStrip2D.cpp run.
// Layout as in Rva005388C2Assign.cpp: four-float edges at +0x00, Region2D at +0x0C, float at +0x1C, refresh flag at +0x20.
#include <new>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include "Lib/Region2D.h"
#include <vector>

struct BfmeFloat4Record00469C61
{
public:
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
	float w; // +0x0C
};

class QuadStrip2D
{
public:
	void rva0053841C(const Matrix3D &mtx);
private:
	_STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> > m_vec;
	Region2D m_region;
	float m_1c;
	unsigned char m_20;
};

// Transforms both points of every edge as Vector3(x, y, 0) in place, then sets the refresh flag.
void QuadStrip2D::rva0053841C(const Matrix3D &mtx)
{
	_STL::vector<BfmeFloat4Record00469C61>::iterator end = ((_STL::vector<BfmeFloat4Record00469C61> *)&m_vec)->end();
	for (_STL::vector<BfmeFloat4Record00469C61>::iterator it = ((_STL::vector<BfmeFloat4Record00469C61> *)&m_vec)->begin(); it != end; ++it) {
		Vector3 v(it->x, it->y, 0.0f);
		Matrix3D::Transform_Vector(mtx, v, &v);
		it->x = v.X;
		it->y = v.Y;
		v = Vector3(it->z, it->w, 0.0f);
		Matrix3D::Transform_Vector(mtx, v, &v);
		it->z = v.X;
		it->w = v.Y;
	}
	m_20 = 1;
}
