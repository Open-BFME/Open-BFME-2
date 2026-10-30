// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
// ?addTreeType@W3DTreeBuffer@@QAEHABVAsciiString@@0PBXH00@Z, retail 0x000EC75D (617 bytes,
// ret 0x18), called from addTree 0x000ECF79 and the template lookup 0x000ECDF5. Donor:
// Open-BFME-1 W3DTreeBufferAddTreeType.cpp (BFME1 0x00735E10). BFME2 layout read from
// retail: the type-changed flag is +0x44556, 64 types of 0x5C at +0x44558 (count +0x45C58).
//
typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;

class MeshClass;
class RenderObjClass;

#include "W3DTreeRecord.h"
#include "W3DTreeTypeRecord.h"
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"
#include "aabox.h"

#include "ascii_string.h"

class Rva00735E10TreeType
{
public:
	MeshClass *m_mesh;
	Vector3 m_offset;
	SphereClass m_bounds;
	const void *m_data;
	unsigned char m_gap0024[0x44 - 0x24];
	UnsignedByte m_doShadow;
	UnsignedByte m_pad0045[3];
	AsciiString m_textureName;
	AsciiString m_modelName;
	AsciiString m_nameC;
	AsciiString m_nameD;
	Int m_field0058;
};

struct Rva00735E10VertexBuffer
{
	unsigned char m_head[0x0c];
	Vector3 *m_array;
};

struct Rva00735E10Model
{
	unsigned char m_head[0x28];
	Int m_vertexCount;
	unsigned char m_gap002c[4];
	Rva00735E10VertexBuffer *m_vertexBuffer;

	Int Get_Vertex_Count(void) const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array(void) const { return m_vertexBuffer->m_array; }
};

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

class MeshClass : public RenderObjClass
{
public:
	Rva00735E10Model *Peek_Model(void) const { return m_model; }
	unsigned char m_meshGap[0xC4 - 8]; // +0x08
	Rva00735E10Model *m_model; // +0xC4
};

extern RenderObjClass *Create_Render_Obj(const char *name);


class TextureClass;

template <class T> class RefCountPtr;
template <> class RefCountPtr<TextureClass>
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
	TextureClass *Ptr;
};

class Rva000E6AC0Base
{
public:
	Rva000E6AC0Base() {}
	virtual ~Rva000E6AC0Base() {}
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

class Rva0052413E
{
public:
	Rva0052413E() throw();
	~Rva0052413E();
private:
	unsigned char m_storage[12];
};

struct TTree;

class W3DTreeBuffer : public Rva000E6AC0
{
	friend class Rva000EC9C6;
protected:
	void updateTexture();
	void updateTopplingTree(TTree *tree);
public:
	W3DTreeBuffer();
public:
	void rva000EA24D();
private:
	Rva000EDA94Record m_records[1200];
private:
	int m_count;
private:
	unsigned char m_44544;
private:
	unsigned char m_44545; // +0x44545
private:
	unsigned char m_44546;
private:
	unsigned char m_44547;
private:
	Rva0052413E m_objects;
private:
	unsigned char m_44554;
private:
	unsigned char m_44555;
private:
	unsigned char m_44556;
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
};

// ?addTreeType@W3DTreeBuffer@@QAEHABVAsciiString@@0PBXH00@Z
Int W3DTreeBuffer::addTreeType(const AsciiString &modelName,
	const AsciiString &nameC, const void *data, Int shadowKind,
	const AsciiString &textureName, const AsciiString &nameD)
{
    Rva00735E10TreeType *m_treeTypes = reinterpret_cast<Rva00735E10TreeType *>(m_types);
	if (m_typeCount >= 64) {
		return 0;
	}
	m_44556 = 1;

	m_treeTypes[m_typeCount].m_mesh = 0;

	RenderObjClass *robj = Create_Render_Obj(modelName.str());

	if (robj == 0) {
		return 0;
	}
	AABoxClass box;

	robj->Get_Obj_Space_Bounding_Box(box);
	Vector3 offset(0, 0, 0);
	if (robj->Class_ID() == 0x19) {
		RenderObjClass *hlod = robj;
		robj = hlod->Get_Sub_Object(0);
		const Matrix3D xfm = robj->Get_Bone_Transform(0);
		xfm.Get_Translation(&offset);
		hlod->Release_Ref();
	}

	if (robj->Class_ID() == 0)
		m_treeTypes[m_typeCount].m_mesh = robj->renderObjSlot14();

	MeshClass *mesh = m_treeTypes[m_typeCount].m_mesh;
	if (mesh == 0) {
		robj->Release_Ref();
		return 0;
	}

	Int numVertex = mesh->Peek_Model()->Get_Vertex_Count();
	Vector3 *pVert = mesh->Peek_Model()->Get_Vertex_Array();

	mesh->Validate_Transform();
	SphereClass bounds(pVert, numVertex);
	SphereClass &destBounds = m_treeTypes[m_typeCount].m_bounds;
	bounds.Center += offset;
	destBounds = bounds;
	m_treeTypes[m_typeCount].m_data = data;
	m_treeTypes[m_typeCount].m_offset = offset;
	m_treeTypes[m_typeCount].m_doShadow = (shadowKind == 1);
	m_treeTypes[m_typeCount].m_textureName.setCopyInline(textureName);
	reinterpret_cast<StringBase<char> *>(&m_treeTypes[m_typeCount].m_textureName)->concat(".tga");
	m_treeTypes[m_typeCount].m_modelName.setCopyInline(modelName);
	m_treeTypes[m_typeCount].m_nameC.setCopyInline(nameC);
	m_treeTypes[m_typeCount].m_nameD.setCopyInline(nameD);
	// Retail initializes this per-type sentinel after the string fields.
	m_treeTypes[m_typeCount].m_field0058 = -2;
	m_typeCount++;
	return m_typeCount - 1;
}
