// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?addFactionBibDrawable@W3DTerrainVisual@@UAEXPAVDrawable@@_NM@Z
// retail 0x00092A95..0x00092DD8 (835 bytes) thiscall RET 0xC.
//
// Zero Hour W3DTerrainVisual::addFactionBibDrawable (GeneralsMD
// W3DTerrainVisual.cpp), via Open-BFME-1's
// W3DTerrainVisualAddFactionBibDrawable.cpp (BFME 1 layout witnesses and the
// same Transform_Vector Z-row order). BFME 2 target facts: W3DTerrainVisual
// vtable slot (absolute reference 0x007C80D0); height map guard +0x1C and
// terrain render object +0x14; drawable template at +4 with factory exit
// width +0x4D4 extra bib width +0x4D8 and geometry info +0xA0 copied through
// rowed GeometryInfo copy ctor 0x000929E8 (major/minor radius +0x24/+0x28; no
// geometry-type test in BFME 2) and destroyed through rowed ~GeometryInfo
// 0x00050B2A; pinned Drawable::getTransformMatrix 0x0027628E and getID
// 0x0055A88B; the corners go to the render object's rowed bib forwarder
// 0x0006840A (addBibDrawable through its +0x385C W3DBibBuffer). The name and
// argument meanings are carried from Zero Hour and BFME 1.
#include "Coord3D.h"

typedef bool Bool;
typedef float Real;

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0,
	FORCE_DRAWABLEID_TO_LONG_SIZE = 0x7ffffff
};

// Zero Hour's Coord3D::set, absent from the canonical header.
struct Coord3DSet : public Coord3D
{
	void set(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }
};

class Vector3
{
public:
	Vector3() {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Real X;
	Real Y;
	Real Z;
};

class Vector4
{
public:
	Real &operator[](int i) { return (&X)[i]; }
	const Real &operator[](int i) const { return (&X)[i]; }
	Real X;
	Real Y;
	Real Z;
	Real W;
};

class Matrix3D
{
public:
	const Vector4 &operator[](int row) const { return Row[row]; }

	static __forceinline void Transform_Vector(const Matrix3D &matrix, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = (Vector3 *)&in;
		}
		out->X = (matrix[0][0] * v->X + matrix[0][1] * v->Y + matrix[0][2] * v->Z + matrix[0][3]);
		out->Y = (matrix[1][0] * v->X + matrix[1][1] * v->Y + matrix[1][2] * v->Z + matrix[1][3]);
		out->Z = (matrix[2][1] * v->Y + matrix[2][0] * v->X + matrix[2][2] * v->Z + matrix[2][3]);
	}

	Vector4 Row[3];
};

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &other);
	virtual ~GeometryInfo();
	Real getMajorRadius() const { return m_majorRadius; }
	Real getMinorRadius() const { return m_minorRadius; }

private:
	char m_pad04[0x24 - 0x04];
	Real m_majorRadius;					// +0x24
	Real m_minorRadius;					// +0x28
	char m_pad2C[0x5C - 0x2C];
};

class ThingTemplate
{
public:
	Real getFactoryExitWidth() const { return m_factoryExitWidth; }
	Real getFactoryExtraBibWidth() const { return m_factoryExtraBibWidth; }
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }

private:
	char m_pad000[0xA0];
	GeometryInfo m_geometryInfo;		// +0xA0
	char m_padFC[0x4D4 - 0xFC];
	Real m_factoryExitWidth;			// +0x4D4
	Real m_factoryExtraBibWidth;		// +0x4D8
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	DrawableID getID() const;
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
};

// The terrain render object's bib forwarder (rowed 0x0006840A).
class Rva0006840A
{
public:
	void rva0006840A(Vector3 corners[4], DrawableID id, bool highlight);
};

class W3DTerrainVisual
{
public:
	virtual void addFactionBibDrawable(Drawable *factionBuilding, Bool highlight, Real extra);

private:
	char m_pad04[0x14 - 0x04];
	Rva0006840A *m_terrainRenderObject;	// +0x14
	void *m_waterRenderObject;			// +0x18
	void *m_logicHeightMap;				// +0x1C
};

void W3DTerrainVisual::addFactionBibDrawable(Drawable *factionBuilding, Bool highlight, Real extra)
{
	if (m_logicHeightMap)
	{
		const Matrix3D *mtx = factionBuilding->getTransformMatrix();
		Vector3 corners[4];
		Coord3DSet pos;
		pos.set(0, 0, 0);
		Real exitWidth = factionBuilding->getTemplate()->getFactoryExitWidth();
		Real extraWidth = factionBuilding->getTemplate()->getFactoryExtraBibWidth() + extra;
		const GeometryInfo info = factionBuilding->getTemplate()->getTemplateGeometryInfo();
		Real sizeX = info.getMajorRadius();
		Real sizeY = info.getMinorRadius();
		corners[0].Set(pos.x, pos.y, pos.z);
		corners[0].X -= sizeX + extraWidth;
		corners[0].Y -= sizeY + extraWidth;
		corners[1].Set(pos.x, pos.y, pos.z);
		corners[1].X += sizeX + exitWidth + extraWidth;
		corners[1].Y -= sizeY + extraWidth;
		corners[2].Set(pos.x, pos.y, pos.z);
		corners[2].X += sizeX + exitWidth + extraWidth;
		corners[2].Y += sizeY + extraWidth;
		corners[3].Set(pos.x, pos.y, pos.z);
		corners[3].X -= sizeX + extraWidth;
		corners[3].Y += sizeY + extraWidth;
		mtx->Transform_Vector(*mtx, corners[0], &corners[0]);
		mtx->Transform_Vector(*mtx, corners[1], &corners[1]);
		mtx->Transform_Vector(*mtx, corners[2], &corners[2]);
		mtx->Transform_Vector(*mtx, corners[3], &corners[3]);
		m_terrainRenderObject->rva0006840A(corners, factionBuilding->getID(), highlight);
	}
}
