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

#include "../../../../GameEngine/Include/Common/BfmeXfer.h"
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
Xfer *Rva003062FEXfer(Xfer *xfer, float *vals);
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

class AsciiString;
class ThingTemplate
{
public:
	const ModuleInfo &getModuleInfo2F0(void) const { return m_drawModuleInfo; }
	char m_pad00[0x64];
	AsciiString m_name; // +0x64
	char m_pad68[0x288];
	ModuleInfo m_drawModuleInfo; // +0x2F0
	char m_pad2F1[0x3];
};

// TheThingFactory->findTemplate, rowed under its address name.
class ThingFactory {
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
class ThingFactory;
extern ThingFactory *TheThingFactory;

class MeshClass;
class Matrix3D;
class AABoxClass;
class RenderObjClass
{
public:
	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}
	virtual void Delete_This(void) = 0;
	virtual void renderObjSlot04(void) = 0;
	virtual void renderObjSlot08(void) = 0;
	virtual Int Class_ID(void) const = 0;
	virtual void renderObjSlot10(void) = 0;
	// Retail slot +0x14 returns the mesh view; its original name is unknown.
	virtual MeshClass *renderObjSlot14(void) const = 0;
	virtual void renderObjSlot18(void) = 0;
	virtual void renderObjSlot1C(void) = 0;
	virtual void renderObjSlot20(void) = 0;
	virtual void renderObjSlot24(void) = 0;
	virtual void renderObjSlot28(void) = 0;
	virtual void renderObjSlot2C(void) = 0;
	virtual void renderObjSlot30(void) = 0;
	virtual void renderObjSlot34(void) = 0;
	virtual void renderObjSlot38(void) = 0;
	virtual void renderObjSlot3C(void) = 0;
	virtual void renderObjSlot40(void) = 0;
	virtual void renderObjSlot44(void) = 0;
	virtual void renderObjSlot48(void) = 0;
	virtual void renderObjSlot4C(void) = 0;
	virtual void Validate_Transform(void) const = 0;
	virtual void renderObjSlot54(void) = 0;
	virtual void renderObjSlot58(void) = 0;
	virtual void renderObjSlot5C(void) = 0;
	virtual void renderObjSlot60(void) = 0;
	virtual void renderObjSlot64(void) = 0;
	virtual void renderObjSlot68(void) = 0;
	virtual void renderObjSlot6C(void) = 0;
	virtual void renderObjSlot70(void) = 0;
	virtual void renderObjSlot74(void) = 0;
	virtual RenderObjClass *Get_Sub_Object(Int index) const = 0;
	virtual void renderObjSlot78(void) = 0;
	virtual void renderObjSlot7C(void) = 0;
	virtual void renderObjSlot80(void) = 0;
	virtual void renderObjSlot84(void) = 0;
	virtual void renderObjSlot88(void) = 0;
	virtual void renderObjSlot8C(void) = 0;
	virtual void renderObjSlot90(void) = 0;
	virtual void renderObjSlot94(void) = 0;
	virtual void renderObjSlot98(void) = 0;
	virtual void renderObjSlot9C(void) = 0;
	virtual void renderObjSlotA0(void) = 0;
	virtual void renderObjSlotA4(void) = 0;
	virtual void renderObjSlotA8(void) = 0;
	virtual void renderObjSlotAC(void) = 0;
	virtual void renderObjSlotB0(void) = 0;
	virtual void renderObjSlotB4(void) = 0;
	virtual void renderObjSlotB8(void) = 0;
	virtual void renderObjSlotBC(void) = 0;
	virtual void renderObjSlotC0(void) = 0;
	virtual void renderObjSlotC4(void) = 0;
	virtual Matrix3D Get_Bone_Transform(Int index) = 0;
	virtual void renderObjSlotCC(void) = 0;
	virtual void renderObjSlotD0(void) = 0;
	virtual void renderObjSlotD4(void) = 0;
	virtual void renderObjSlotD8(void) = 0;
	virtual void renderObjSlotDC(void) = 0;
	virtual void renderObjSlotE0(void) = 0;
	virtual void renderObjSlotE4(void) = 0;
	virtual void renderObjSlotE8(void) = 0;
	virtual void renderObjSlotEC(void) = 0;
	virtual void renderObjSlotF0(void) = 0;
	virtual void renderObjSlotF4(void) = 0;
	virtual void renderObjSlotF8(void) = 0;
	virtual void renderObjSlotFC(void) = 0;
	virtual void renderObjSlot100(void) = 0;
	virtual void renderObjSlot104(void) = 0;
	virtual void renderObjSlot108(void) = 0;
	virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const = 0;
	Int m_refCount; // +0x04
};
struct Rva00735E10Model;
class MeshClass : public RenderObjClass
{
public:
	Rva00735E10Model *Peek_Model(void) const { return m_model; }
	unsigned char m_meshGap[0xC4 - 8]; // +0x08
	Rva00735E10Model *m_model; // +0xC4
};
extern RenderObjClass *Create_Render_Obj(const char *name);

// addTree's position, taken by value and converted from the caller's Coord3D.
struct Rva000ECF79Coord {
	Rva000ECF79Coord(const Coord3D &c) : x(c.x), y(c.y), z(c.z) {}
	Real x, y, z;
};
struct Rva000ECF79Data;

// The 0xE8-byte tree record (Zero Hour TTree plus BFME fields); default ctor 0x000EB27F.
#include "W3DTreeRecord.h"

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
	void addTree(unsigned int id, Rva000ECF79Coord location, float scale, const Matrix3D *transform,
		float randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
		const AsciiString &templateName);
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned char m_pad004[0x5c0 - 4];
	Rva000EDA94Record m_trees[1200];
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
				const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(m_treeTypes[i].m_templateName);
				if (thingTemplate) {
					// A named reference keeps retail's receiver-before-argument order.
					const ModuleInfo &moduleInfo = thingTemplate->getModuleInfo2F0();
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
		Rva000EDA94Record tree;
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
				// Retail folds AsciiString::compareNoCase to the rowed
				// StringBase<char> body at 0x6A00 (symbols.csv pin): no
				// wrapper exists in the image, so our TU must not emit its
				// 5B-jmp copy (link census L+S). Spelling the StringBase
				// call directly is what the inlined wrapper already emits;
				// AsciiString is its one-pointer layout twin, so the
				// twin casts are no-ops.
				if (((const StringBase<char> &)m_treeTypes[j].m_modelName).compareNoCase(*(const StringBase<char> *)&modelName) == 0 &&
						((const StringBase<char> &)m_treeTypes[j].m_nameC).compareNoCase(*(const StringBase<char> *)&modelTexture) == 0) {
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
			addTree(tree.drawableID, pos, tree.scale, &tree.transform, 0, m_treeTypes[treeType].m_data,
				doShadow ? 1 : 0, textureName, m_treeTypes[treeType].m_templateName);
			if (m_numTrees) {
				Rva000EDA94Record *curTree = &m_trees[m_numTrees - 1];
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
