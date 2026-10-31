// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
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
#include "rendobj.h"
#include "ascii_string.h"
#include "Coord3D.h"
#include "Coord2D.h"
#include "../../../../Libraries/Include/Lib/Region2D.h"

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

struct Rva000ECDF5TreeDrawData;

class ModuleData
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual const Rva000ECDF5TreeDrawData *getAsW3DTreeDrawModuleData() const;
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
struct Rva00735E10Model;
class MeshClass : public RenderObjClass
{
public:
	Rva00735E10Model *Peek_Model(void) const { return m_model; }
	Rva00735E10Model *m_model; // +0xC4
};
extern RenderObjClass *Create_Render_Obj(const char *name);

// addTree's position, taken by value and converted from the caller's Coord3D.
struct Rva000ECF79Coord
{
	Rva000ECF79Coord(const Coord3D &c) : x(c.x), y(c.y), z(c.z) {}
	float x, y, z;
};
struct Rva000ECF79Data;

// The 0xE8-byte tree record (Zero Hour TTree plus BFME fields); default ctor 0x000EB27F.
#include "W3DTreeRecord.h"

// The memberwise record copy at 0x000EADA7, rowed as a copy constructor.
struct FourDwords
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
};

struct ThreeDwords
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

class Rva000EADA7
{
public:
	Rva000EADA7(const Rva000EADA7 &that);
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	unsigned char m_44;
	unsigned char m_pad45[3];
	Region2D m_region;
	int m_58;
	int m_5c;
	int m_60;
	int m_64;
	int m_68;
	int m_6c;
	int m_70;
	ThreeDwords m_74;
	int m_80;
	int m_84;
	unsigned char m_88;
	unsigned char m_pad89[3];
	int m_8c;
	int m_90;
	int m_94;
	int m_98;
	int m_9c;
	struct FourDwords
	{
		unsigned int a;
		unsigned int b;
		unsigned int c;
		unsigned int d;
	};
	FourDwords m_a0;
	FourDwords m_b0;
	int m_c0;
	unsigned char m_c4;
	unsigned char m_padc5[3];
	int m_c8;
	int m_cc;
	int m_d0;
	int m_d4;
	int m_d8;
	int m_dc;
	int m_e0;
	int m_e4;
};

struct W3DTreeType {
	MeshClass *m_mesh;
	Vector3 m_offset;
	SphereClass m_bounds;
	const struct Rva000ECF79Data *m_data;
	Coord2D m_coord24;
	Coord2D m_coord2C;
	Coord2D m_coord34;
	Coord2D m_coord3C;
	bool m_doShadow;
	AsciiString m_textureName;
	AsciiString m_modelName;
	AsciiString m_nameC;
	AsciiString m_templateName;
	int m_field58;
};

#include "W3DTreeRecord.h"
#include "W3DTreeTypeRecord.h"

class Rva000E6AC0Base
{
public:
	Rva000E6AC0Base() {}
	virtual ~Rva000E6AC0Base() {}
};

class Rva0052413E
{
public:
	Rva0052413E() throw();
	~Rva0052413E();
private:
	unsigned char m_storage[12];
};

class TextureClass;

template <class T> class RefCountPtr;

template <> class RefCountPtr<TextureClass>
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
	TextureClass *Ptr;
};

class Rva000E6AC0 : public Rva000E6AC0Base
{
public:
	Rva000E6AC0();
	void rva000E65B1();
	virtual ~Rva000E6AC0();
private:
	unsigned char m_storage[0x38 - 4]; // +0x04
protected:
	RefCountPtr<TextureClass> texture38, texture3c; // +0x38
	char list40[0x28], list68[0x28]; // +0x40
private:
	unsigned char m_pad90[0x5BC - 0x90];
protected:
	float m_sinkScale; // +0x5BC
};

struct TTree;

class Xfer;
struct Rva000EAFA4Coord3;
struct Rva000EAFA4Coord2;
struct Rva000ECF79Coord;
struct Rva000ECF79Data;

class W3DTreeBuffer : public Rva000E6AC0
{
	friend class Rva000EC9C6;
protected:
	void updateTexture();
	void updateTopplingTree(TTree *tree);
	virtual void xfer(Xfer *xfer);
public:
	W3DTreeBuffer();
public:
	void rva000EA24D();
private:
	Rva000EDA94Record m_records[1200];
private:
	int m_count;
private:
	unsigned char m_anythingChanged;
private:
	unsigned char m_44545; // +0x44545
private:
	unsigned char m_changed;
private:
	unsigned char m_44547;
private:
	Rva0052413E m_objects;
private:
	unsigned char m_initialized;
private:
	unsigned char m_44555;
private:
	unsigned char m_needUpdate;
private:
	unsigned char m_44557;
private:
	Rva000EC67F m_types[64]; // +0x44558
private:
	int m_typeCount;
private:
	int m_45c5c; // +0x45C5C
private:
	int m_45c60;
private:
	unsigned char m_45c64;
public:
	bool rva000EA48D(void *key, const Coord3D *direction, float height);
	bool rva000EA644(void *key);
	void rva000EA2C0(void *key);
	bool rva000EA6A7(void *key);
	void rva000EB2EF(int index);
	void rva000EB0E6(int index);
	bool rva000ECF2A(unsigned key, int mode);
	void startMorph(int index, int mode);
	int addTreeType(const AsciiString &modelName, const AsciiString &nameC, const void *data, int shadowKind,
		const AsciiString &textureName, const AsciiString &templateName);
	int rva000ECDF5(const AsciiString &templateName, int shadowKind, const AsciiString &textureName);
	char rva000EA327(void *key, Vector3 position, const Matrix3D *transform);
	bool rva000EAFA4(int index, Rva000EAFA4Coord3 *position, float *radius, Rva000EAFA4Coord2 *primary,
		Rva000EAFA4Coord2 *secondary);
	void addTree(unsigned int id, Rva000ECF79Coord location, float scale, const Matrix3D *transform,
		float randomScaleAmount, const Rva000ECF79Data *data, int shadowKind, const AsciiString &textureName,
		const AsciiString &templateName);
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
	Int numTrees = m_count;
	*xfer == numTrees;

	if (version.m_minimum >= 2) {
		*xfer == m_typeCount;
		for (i = 0; i < m_typeCount; i++) {
			Rva0030612AXfer(xfer, &((W3DTreeType *)m_types)[i].m_offset.X);
			Rva0030612AXfer(xfer, &((W3DTreeType *)m_types)[i].m_bounds.Center.X);
			*xfer == ((W3DTreeType *)m_types)[i].m_bounds.Radius;
			*xfer == ((W3DTreeType *)m_types)[i].m_coord24;
			*xfer == ((W3DTreeType *)m_types)[i].m_coord2C;
			*xfer == ((W3DTreeType *)m_types)[i].m_coord34;
			*xfer == ((W3DTreeType *)m_types)[i].m_coord3C;
			*xfer == ((W3DTreeType *)m_types)[i].m_doShadow;
			*xfer == ((W3DTreeType *)m_types)[i].m_textureName;
			*xfer == ((W3DTreeType *)m_types)[i].m_modelName;
			*xfer == ((W3DTreeType *)m_types)[i].m_nameC;
			*xfer == ((W3DTreeType *)m_types)[i].m_field58;
			*xfer == ((W3DTreeType *)m_types)[i].m_templateName;
			if (xfer->IsLoading()) {
				// Rebuild the type's draw data and mesh from the loaded names.
				const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(((W3DTreeType *)m_types)[i].m_templateName);
				if (thingTemplate) {
					// A named reference keeps retail's receiver-before-argument order.
					const ModuleInfo &moduleInfo = thingTemplate->getModuleInfo2F0();
					const ModuleData *moduleData = moduleInfo.getNthData(0);
					if (moduleData)
						((W3DTreeType *)m_types)[i].m_data = (const Rva000ECF79Data *)moduleData->getAsW3DTreeDrawModuleData();
				}
				if (((W3DTreeType *)m_types)[i].m_mesh) {
					((W3DTreeType *)m_types)[i].m_mesh->Release_Ref();
					((W3DTreeType *)m_types)[i].m_mesh = 0;
				}
				RenderObjClass *robj = Create_Render_Obj(((W3DTreeType *)m_types)[i].m_modelName.str());
				if (robj) {
					// Retail slot +0x14 returns the mesh view; its original name is unknown.
					if (robj->Class_ID() == 0)
						((W3DTreeType *)m_types)[i].m_mesh = (MeshClass *)robj->_bfme_ro_v3();
					else
						robj->Release_Ref();
				}
			}
		}
	}

	if (xfer->IsLoading())
		m_count = 0;

	for (i = 0; i < numTrees; i++) {
		Rva000EDA94Record tree;
		memset(&tree, 0, sizeof(tree));
		AsciiString modelName;
		AsciiString modelTexture;
		Int treeType = -2;
		if (xfer->IsStoring()) {
			((Rva000EADA7 *)&tree)->Rva000EADA7::Rva000EADA7(*(const Rva000EADA7 *)&m_records[i]);
			treeType = m_records[i].treeType;
			if (treeType != -2) {
				modelName = ((W3DTreeType *)m_types)[treeType].m_modelName;
				modelTexture = ((W3DTreeType *)m_types)[treeType].m_nameC;
			}
		}
		*xfer == modelName;
		*xfer == modelTexture;
		if (xfer->IsLoading()) {
			Int j;
			for (j = 0; j < m_typeCount; j++) {
				// Retail folds AsciiString::compareNoCase to the rowed
				// StringBase<char> body at 0x6A00 (symbols.csv pin): no
				// wrapper exists in the image, so our TU must not emit its
				// 5B-jmp copy (link census L+S). Spelling the StringBase
				// call directly is what the inlined wrapper already emits;
				// AsciiString is its one-pointer layout twin, so the
				// twin casts are no-ops.
				if (((const StringBase<char> &)((W3DTreeType *)m_types)[j].m_modelName).compareNoCase(*(const StringBase<char> *)&modelName) == 0 &&
						((const StringBase<char> &)((W3DTreeType *)m_types)[j].m_nameC).compareNoCase(*(const StringBase<char> *)&modelTexture) == 0) {
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
		if (!xfer->IsLoading() && treeType >= 0 && treeType < m_typeCount) {
			doShadow = ((W3DTreeType *)m_types)[treeType].m_doShadow;
			textureName = ((W3DTreeType *)m_types)[treeType].m_textureName;
		}
		*xfer == doShadow;
		*xfer == textureName;

		if (xfer->IsLoading() && treeType >= 0 && treeType < m_typeCount) {
			Coord3D pos;
			pos.x = tree.location.X;
			pos.y = tree.location.Y;
			pos.z = tree.location.Z;
			addTree(tree.drawableID, pos, tree.scale, &tree.transform, 0, ((W3DTreeType *)m_types)[treeType].m_data,
				doShadow ? 1 : 0, textureName, ((W3DTreeType *)m_types)[treeType].m_templateName);
			if (m_count) {
				Rva000EDA94Record *curTree = &m_records[m_count - 1];
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
