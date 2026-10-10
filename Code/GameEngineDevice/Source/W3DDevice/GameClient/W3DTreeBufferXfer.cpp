// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ?xfer@W3DTreeBuffer@@MAEXPAVXfer@@@Z retail 0x000ED47D (1559 bytes). Slot 3 of the
// W3DTreeBuffer vtable 0x007CEEA4 (base vtable 0x007CEAB4 slot 3 is the rowed base xfer
// 0x000E63DC called first). Donor: Open-BFME-1 W3DTreeBufferXfer.cpp (BFME1 0x007371D0)
// which is Zero Hour's tree loop preceded by BFME's type table. BFME2 differences read
// from retail: version 4 and no camera/small-buffer tail. Callees: addTree 0x000ECF79
// plus the tree record ctor 0x000EB27F and memberwise copy 0x000EADA7 plus the rowed
// Coord3D/Matrix3D/DrawableID/W3DToppleState xfer helpers. Layout follows the addTree unit.
typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include <string.h>
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"
#include "ascii_string.h"
#include "Coord3D.h"
#include "Coord2D.h"

class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer {
public:
	class Version;
	Xfer();
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;
	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};
class Xfer::Version {
public:
	Version(unsigned char current, unsigned char minimum) : m_current(current), m_minimum(minimum) {}
	unsigned char m_current;
	unsigned char m_minimum;
};

// Rowed helpers: base xfer, three-float and matrix transfers, drawable id, topple state.
class Rva000E63DCObj;
void __stdcall Rva000E63DCDo(Rva000E63DCObj *obj);
void Rva0030612AXfer(Xfer *xfer, float *vals);
void Rva003062FEXfer(Xfer *xfer, float *vals);
void XferDrawableID(Xfer *xfer, int *value);
class Rva000EA1DBTarget;
void __cdecl Rva000EA1DBTopple(Rva000EA1DBTarget *obj, int val);

class ModuleData {
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	// Returns the tree type's draw data; the original name is unknown.
	virtual const struct Rva000ECF79Data *slot16() const;
};

class ModuleInfo {
public:
	const ModuleData *getNthData(Int i) const;
};

class ThingTemplate {
public:
	const ModuleInfo &getModuleInfo2F0(void) const { return m_moduleInfo2F0; }
private:
	unsigned char m_pad000[0x2f0];
	ModuleInfo m_moduleInfo2F0;
};

// TheThingFactory->findTemplate, rowed under its address name.
class ThingFactory {
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
class ThingFactory;
extern ThingFactory *TheThingFactory;

class MeshClass;
class RenderObjClass {
public:
	virtual void Delete_This(void) = 0;
	virtual void renderObjSlot04(void) = 0;
	virtual void renderObjSlot08(void) = 0;
	virtual Int Class_ID(void) const = 0;
	virtual void renderObjSlot10(void) = 0;
	// Retail slot +0x14 returns the mesh view; its original name is unknown.
	virtual MeshClass *renderObjSlot14(void) const = 0;

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	Int m_refCount;
};
class MeshClass : public RenderObjClass {
};
extern RenderObjClass *Create_Render_Obj(const char *name);

// addTree's position, taken by value and converted from the caller's Coord3D.
struct Rva000ECF79Coord {
	Rva000ECF79Coord(const Coord3D &c) : x(c.x), y(c.y), z(c.z) {}
	Real x, y, z;
};
struct Rva000ECF79Data;

// The 0xE8-byte tree record (Zero Hour TTree plus BFME fields); default ctor 0x000EB27F.
class Rva000EB08C {
public:
	Rva000EB08C();
	Vector3 location;
	Real scale;
	Matrix3D transform;
	Int treeType;
	unsigned char m_pad44[0x58 - 0x44];
	UnsignedInt drawableID;
	unsigned char m_pad5c[0x6c - 0x5c];
	Real m_angularVelocity;
	Real m_angularAcceleration;
	Coord3D m_toppleDirection;
	Int m_toppleState;
	Real m_angularAccumulation;
	unsigned char m_pad88[4];
	UnsignedInt m_options;
	Matrix3D m_mtx;
	UnsignedInt m_sinkFramesLeft;
	Bool m_flagC4;
	unsigned char m_padC5[0xe0 - 0xc5];
	Int m_fieldE0;
	Int m_fieldE4;
};

// The memberwise record copy at 0x000EADA7, rowed as a copy constructor.
class Rva000EADA7 {
public:
	Rva000EADA7(const Rva000EADA7 &that);
};

struct W3DTreeType {
	MeshClass *m_mesh;
	Vector3 m_offset;
	SphereClass m_bounds;
	const Rva000ECF79Data *m_data;
	Coord2D m_coord24;
	Coord2D m_coord2C;
	Coord2D m_coord34;
	Coord2D m_coord3C;
	Bool m_doShadow;
	AsciiString m_textureName;
	AsciiString m_modelName;
	AsciiString m_nameC;
	AsciiString m_templateName;
	Int m_field58;
};

class W3DTreeBuffer {
public:
	void rva000ECF79(unsigned int id, Rva000ECF79Coord location, float scale, const Matrix3D *transform,
		float randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
		const AsciiString &templateName);
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned char m_pad004[0x5c0 - 4];
	Rva000EB08C m_trees[1200];
	Int m_numTrees;
	unsigned char m_pad44544[0x44558 - 0x44544];
	W3DTreeType m_treeTypes[64];
	Int m_numTreeTypes;
};

// ?xfer@W3DTreeBuffer@@MAEXPAVXfer@@@Z
void W3DTreeBuffer::xfer(Xfer *xfer)
{
	Rva000E63DCDo((Rva000E63DCObj *)xfer);
	if (xfer->IsLightCRC())
		return;

	// Retail stores {1, 4} and tests the second byte (the version read back on load).
	Xfer::Version version(1, 4);
	*xfer == version;

	Int i;
	Int numTrees = m_numTrees;
	*xfer == numTrees;

	if (version.m_minimum >= 2) {
		*xfer == m_numTreeTypes;
		for (i = 0; i < m_numTreeTypes; i++) {
			Rva0030612AXfer(xfer, &m_treeTypes[i].m_offset.X);
			Rva0030612AXfer(xfer, &m_treeTypes[i].m_bounds.Center.X);
			*xfer == m_treeTypes[i].m_bounds.Radius;
			*xfer == m_treeTypes[i].m_coord24;
			*xfer == m_treeTypes[i].m_coord2C;
			*xfer == m_treeTypes[i].m_coord34;
			*xfer == m_treeTypes[i].m_coord3C;
			*xfer == m_treeTypes[i].m_doShadow;
			*xfer == m_treeTypes[i].m_textureName;
			*xfer == m_treeTypes[i].m_modelName;
			*xfer == m_treeTypes[i].m_nameC;
			*xfer == m_treeTypes[i].m_field58;
			*xfer == m_treeTypes[i].m_templateName;
			if (xfer->IsLoading()) {
				// Rebuild the type's draw data and mesh from the loaded names.
				const ThingTemplate *tmpl = TheThingFactory->findTemplate(m_treeTypes[i].m_templateName);
				if (tmpl) {
					// A named reference keeps retail's receiver-before-argument order.
					const ModuleInfo &moduleInfo = tmpl->getModuleInfo2F0();
					const ModuleData *moduleData = moduleInfo.getNthData(0);
					if (moduleData)
						m_treeTypes[i].m_data = moduleData->slot16();
				}
				if (m_treeTypes[i].m_mesh) {
					m_treeTypes[i].m_mesh->Release_Ref();
					m_treeTypes[i].m_mesh = 0;
				}
				RenderObjClass *robj = Create_Render_Obj(m_treeTypes[i].m_modelName.str());
				if (robj) {
					if (robj->Class_ID() == 0)
						m_treeTypes[i].m_mesh = robj->renderObjSlot14();
					else
						robj->Release_Ref();
				}
			}
		}
	}

	if (xfer->IsLoading())
		m_numTrees = 0;

	for (i = 0; i < numTrees; i++) {
		Rva000EB08C tree;
		memset(&tree, 0, sizeof(tree));
		AsciiString modelName;
		AsciiString modelTexture;
		Int treeType = -2;
		if (xfer->IsStoring()) {
			((Rva000EADA7 *)&tree)->Rva000EADA7::Rva000EADA7(*(const Rva000EADA7 *)&m_trees[i]);
			treeType = m_trees[i].treeType;
			if (treeType != -2) {
				modelName = m_treeTypes[treeType].m_modelName;
				modelTexture = m_treeTypes[treeType].m_nameC;
			}
		}
		*xfer == modelName;
		*xfer == modelTexture;
		if (xfer->IsLoading()) {
			Int j;
			for (j = 0; j < m_numTreeTypes; j++) {
				if (m_treeTypes[j].m_modelName.compareNoCase(modelName) == 0 &&
						m_treeTypes[j].m_nameC.compareNoCase(modelTexture) == 0) {
					treeType = j;
					break;
				}
			}
		}

		*xfer == tree.location.X;
		*xfer == tree.location.Y;
		*xfer == tree.location.Z;
		*xfer == tree.scale;
		Rva003062FEXfer(xfer, (float *)&tree.transform);
		XferDrawableID(xfer, (int *)&tree.drawableID);

		*xfer == tree.m_angularVelocity;
		*xfer == tree.m_angularAcceleration;
		*xfer == *(Coord3DBase *)&tree.m_toppleDirection;
		Rva000EA1DBTopple((Rva000EA1DBTarget *)xfer, (int)&tree.m_toppleState);
		*xfer == tree.m_angularAccumulation;
		*xfer == tree.m_options;
		Rva003062FEXfer(xfer, version.m_minimum >= 3 ? (float *)&tree.m_mtx : (float *)&tree.transform);
		*xfer == tree.m_sinkFramesLeft;
		*xfer == tree.m_flagC4;
		*xfer == tree.m_fieldE0;
		*xfer == tree.m_fieldE4;

		Bool doShadow = false;
		AsciiString textureName;
		if (!xfer->IsLoading() && treeType >= 0 && treeType < m_numTreeTypes) {
			doShadow = m_treeTypes[treeType].m_doShadow;
			textureName = m_treeTypes[treeType].m_textureName;
		}
		*xfer == doShadow;
		*xfer == textureName;

		if (xfer->IsLoading() && treeType >= 0 && treeType < m_numTreeTypes) {
			Coord3D pos;
			pos.x = tree.location.X;
			pos.y = tree.location.Y;
			pos.z = tree.location.Z;
			rva000ECF79(tree.drawableID, pos, tree.scale, &tree.transform, 0, m_treeTypes[treeType].m_data,
				doShadow ? 1 : 0, textureName, m_treeTypes[treeType].m_templateName);
			if (m_numTrees) {
				Rva000EB08C *curTree = &m_trees[m_numTrees - 1];
				curTree->m_angularAcceleration = tree.m_angularAcceleration;
				curTree->m_angularVelocity = tree.m_angularVelocity;
				curTree->m_toppleDirection = tree.m_toppleDirection;
				curTree->m_toppleState = tree.m_toppleState;
				curTree->m_options = tree.m_options;
				curTree->m_mtx = tree.m_mtx;
				curTree->m_sinkFramesLeft = tree.m_sinkFramesLeft;
				curTree->m_flagC4 = tree.m_flagC4;
				curTree->m_fieldE0 = tree.m_fieldE0;
				curTree->m_fieldE4 = tree.m_fieldE4;
			}
		}
	}
}
