// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ?computeCameraBounds@Rva0009D55BProduct@@QAEXXZ retail 0x0009C18A (664 bytes; called
// only from the pinned 0x0009CD9B): takes the +0xD4 object's extent (slot 66)
// into +0x170 with TheLivingWorldManager's 2D bounds (+0x1C..+0x28) over its
// x/y, seeds +0x104 and +0xF8 from the low corner at ground level, drops the
// object by its height (identity transform, camera-object slot 21), sets the
// +0xDC distance to fit the bounds in a 25-degree half-angle (1.333 aspect),
// and from the corners 0x0009B7EA reports at zoom 0 and 1 derives the pan
// limits +0x124..+0x130 with the manager's +0x1C8/+0x1CC margins.
// The transform and vectors are the BFME 1 WWMath matrix3d.h/vector3.h inlines,
// as in the sibling units of 0x0009B510 and 0x0009B7EA.
#include <math.h>
#include "matrix3d.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// The rowed out-of-line copy constructor 0x0009AC04.
// class-gate: allow Region3D codegen view declaring the rowed out-of-line copy constructor 0x0009AC04 (the canonical header defines it inline); same 24-byte two-triple layout
struct Region3D
{
	Vector3 lo, hi;
	Region3D(const Region3D &other);
};

#define C18A_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define C18A_SLOTS16(p) C18A_SLOTS4(p##0) C18A_SLOTS4(p##1) C18A_SLOTS4(p##2) C18A_SLOTS4(p##3)

class Rva0009C18ARenderObj
{
public:
	C18A_SLOTS16(r0) C18A_SLOTS4(r1) virtual void r20();
	virtual void Set_Transform(const Matrix3D &m);	// slot 21
	C18A_SLOTS16(r2) C18A_SLOTS16(r3) C18A_SLOTS4(r4) C18A_SLOTS4(r5) C18A_SLOTS4(r6)
	virtual const Region3D *getExtent();	// slot 66
};
#undef C18A_SLOTS16
#undef C18A_SLOTS4

// TheLivingWorldManager's map block at +0x14.
struct Rva0009C18AMapView
{
	unsigned char m_pad00[0x08];
	float m_loX;	// +0x1C
	float m_loY;	// +0x20
	float m_hiX;	// +0x24
	float m_hiY;	// +0x28
	unsigned char m_pad18[0x1B4 - 0x18];
	float m_marginX;	// +0x1C8
	float m_marginY;	// +0x1CC
};
struct Rva0009C18AManagerView
{
	unsigned char m_pad00[0x14];
	Rva0009C18AMapView m_map;	// +0x14
};
class Rva0009C134Host { public: void rva0009B7EA(Coord3D *corners); };
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

// Layout view of the factory product (see Rva0009D55BProductCtor_Rva0009D55BProduct.cpp).
class Rva0009D55BProduct
{
public:
	void rva0009BAA4();
	void computeCameraBounds();

	char m_pad00[0xD4];
	Rva0009C18ARenderObj *m_D4;
	float m_D8;
	float m_DC;
	char m_padE0[0xF8 - 0xE0];
	Vector3 m_F8;
	Vector3 m_104;
	Vector3 m_110;
	float m_11C;
	float m_120;
	float m_124;
	float m_128;
	float m_12C;
	float m_130;
	float m_134;
	float m_138;
	float m_13C;
	Coord3D m_140[4];
	Region3D m_170;
};

// The tangent goes through math.h's float tan overload; the distance selection
// keeps X unless Y is greater, including unordered inputs.
void Rva0009D55BProduct::computeCameraBounds()
{
	m_170.Region3D::Region3D(*m_D4->getExtent());
	Rva0009C18AMapView &manager = ((Rva0009C18AManagerView *)TheLivingWorldManager)->m_map;
	m_170.hi.X = manager.m_hiX;
	m_170.hi.Y = manager.m_hiY;
	m_170.lo.X = manager.m_loX;
	m_170.lo.Y = manager.m_loY;
	m_104 = m_170.lo;
	m_104.Z = 0.0f;
	m_F8 = m_104;
	float distX = (m_170.hi.X - m_120) / tan(0.43633232f);
	float distY = ((m_170.hi.Y - m_120) * 1.333f) / tan(0.43633232f);
	Matrix3D tm(true);
	tm.Set_Translation(Vector3(0.0f, 0.0f, -(m_170.lo.Z - m_170.hi.Z)));
	m_170.lo.Z = m_170.hi.Z;
	m_D4->Set_Transform(tm);
	if (distY > distX)
		distX = distY;
	m_DC = distX;
	m_134 = 0.0f;
	rva0009BAA4();
	Coord3D corners[4];
	((Rva0009C134Host *)this)->rva0009B7EA(corners);
	float dx = m_F8.X - corners[0].x;
	m_124 = m_170.lo.X - m_170.hi.X * manager.m_marginX + m_120 + dx;
	m_12C = m_170.hi.X * manager.m_marginX + m_170.lo.X - (m_120 + dx);
	m_128 = m_170.lo.Y - manager.m_marginY * m_170.hi.Y + (m_F8.Y - corners[2].y) + m_120;
	m_130 = manager.m_marginY * m_170.hi.Y + m_170.lo.Y - (corners[0].y - m_F8.Y + m_120);
	m_134 = 1.0f;
	rva0009BAA4();
	((Rva0009C134Host *)this)->rva0009B7EA(m_140);
}
