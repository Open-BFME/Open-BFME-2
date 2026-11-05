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

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

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

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

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
	// LINK: same-body helpers under TU-unique names (identical inlined bytes);
	// this TU's getters lose to the first-in-order copies, so rebind the calls.
	Real bfme_bib_major() const { return m_majorRadius; }
	Real bfme_bib_minor() const { return m_minorRadius; }

private:
	char m_pad04[0x24 - 0x04];
	Real m_majorRadius;					// +0x24
	Real m_minorRadius;					// +0x28
	char m_pad2C[0x5C - 0x2C];
};

#include "../../../../GameEngine/Include/Common/ThingTemplate.h"

static Real bibExitWidth(const ThingTemplate *thingTemplate)
{ return thingTemplate->m_factoryExitWidth; }

static Real bibExtraWidth(const ThingTemplate *thingTemplate)
{ return thingTemplate->m_factoryExtraBibWidth; }

static const GeometryInfo &templateGeometryInfo(const ThingTemplate *thingTemplate)
{ return *reinterpret_cast<const GeometryInfo *>(thingTemplate->m_geometryInfo); }


// Existing matched accessor at 0x0055A88B reads the drawable ID at +0x100.
class Rva0055A88BDwordField
{
public:
    int get() const;
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
};

// BFME 2 Object: template +0x04, inline transform +0x08, ID +0x74 and its
// own geometry info +0xA8 (retail 0x00092DD8 reads them directly).
class Object
{
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	ObjectID getID() const { return m_id; }
	const ThingTemplate *getTemplate() const { return m_template; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }

private:
	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
	Matrix3D m_transform;				// +0x08
	char m_pad38[0x74 - 0x38];
	ObjectID m_id;						// +0x74
	char m_pad78[0xA8 - 0x78];
	GeometryInfo m_geometryInfo;		// +0xA8
};

// The terrain render object's bib forwarders (rowed 0x0006840A, 0x000683FF).
class Rva0006840A
{
public:
	void rva0006840A(Vector3 corners[4], DrawableID id, bool highlight);
};
class Rva000683FF
{
public:
	void rva000683FF(Vector3 corners[4], ObjectID id, bool highlight);
};

#include "../../../Include/W3DDevice/GameClient/W3DTerrainVisualClass.h"

void W3DTerrainVisual::addFactionBibDrawable(Drawable *factionBuilding, Bool highlight, Real extra)
{
	if (m_logicHeightMap)
	{
		const Matrix3D *mtx = factionBuilding->getTransformMatrix();
		Vector3 corners[4];
		Coord3DSet pos;
		pos.set(0, 0, 0);
		Real exitWidth = bibExitWidth(factionBuilding->getTemplate());
		Real extraWidth = bibExtraWidth(factionBuilding->getTemplate()) + extra;
		const GeometryInfo info = templateGeometryInfo(factionBuilding->getTemplate());
		Real sizeX = info.bfme_bib_major();
		Real sizeY = info.bfme_bib_minor();
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
		((Rva0006840A *)m_terrainRenderObject)->rva0006840A(corners, (DrawableID)((const Rva0055A88BDwordField *)factionBuilding)->get(), highlight);
	}
}

// ?addFactionBib@W3DTerrainVisual@@UAEXPAVObject@@_NM@Z retail
// 0x00092DD8..0x000930A5 (717 bytes) thiscall RET 0xC, the vtable slot two
// before addFactionBibDrawable (0x007C80C8). Zero Hour's Object overload of
// the same bib: the object's own geometry info, inline transform and ID,
// and the render object's ObjectID forwarder 0x000683FF.
void W3DTerrainVisual::addFactionBib(Object *factionBuilding, Bool highlight, Real extra)
{
	if (m_logicHeightMap)
	{
		const Matrix3D *mtx = factionBuilding->getTransformMatrix();
		Vector3 corners[4];
		Coord3DSet pos;
		pos.set(0, 0, 0);
		Real exitWidth = bibExitWidth(factionBuilding->getTemplate());
		Real extraWidth = bibExtraWidth(factionBuilding->getTemplate()) + extra;
		const GeometryInfo info = factionBuilding->getGeometryInfo();
		Real sizeX = info.bfme_bib_major();
		Real sizeY = info.bfme_bib_minor();
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
		((Rva000683FF *)m_terrainRenderObject)->rva000683FF(corners, factionBuilding->getID(), highlight);
	}
}
