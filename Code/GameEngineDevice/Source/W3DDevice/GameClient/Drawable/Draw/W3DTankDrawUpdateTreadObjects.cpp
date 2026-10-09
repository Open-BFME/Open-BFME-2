// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [000CE16A,000CE3DE),628B, RET0. W3DTankDraw::updateTreadObjects,
// the Zero Hour W3DTankDraw.cpp body: release the old tread meshes, then
// collect up to four "*.TREADS*" mesh sub-objects of the render object whose
// vertex materials carry a linear-offset mapper, stop its automatic
// scrolling and hand the tread's material override to the mesh. Caller
// W3DTankDraw::doDrawModule 0x000CE3E3; layout as in that unit.

#include <string.h>

typedef float Real;
typedef int Int;
typedef bool Bool;

class Vector2
{
public:
	Vector2() {}
	Vector2(Real x, Real y) { X = x; Y = y; }
	Vector2 &operator=(const Vector2 &v) { X = v.X; Y = v.Y; return *this; }
	Real X;
	Real Y;
};

class TextureMapperClass
{
public:
	enum { MAPPER_ID_LINEAR_OFFSET = 1 };
	virtual void vf00();
	virtual void vf01();
	virtual int Mapper_ID(void) const;	// slot 2 (+0x08)
};

class LinearOffsetTextureMapperClass : public TextureMapperClass
{
public:
	void Set_UV_Offset_Delta(const Vector2 &per_second)
	{
		UVOffsetDeltaPerMS = per_second;
		UVOffsetDeltaPerMS.X *= -0.001f;
		UVOffsetDeltaPerMS.Y *= -0.001f;
	}

private:
	unsigned char m_pad04[0x1C - 0x04];
	Vector2 UVOffsetDeltaPerMS;
};

class VertexMaterialClass
{
public:
	TextureMapperClass *Peek_Mapper(void) { return Mapper; }

private:
	unsigned char m_pad00[0x20];
	TextureMapperClass *Mapper;
};

class MaterialInfoClass
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	int Vertex_Material_Count(void) const { return VertexMaterialCount; }
	VertexMaterialClass *Peek_Vertex_Material(int index) const;

private:
	int NumRefs;
	unsigned char m_pad08[0x18 - 0x08];
	int VertexMaterialCount;
};

struct Material_Override
{
	int Struct_ID;
	Vector2 customUVOffset;
};

class RenderObjClass
{
public:
	enum { CLASSID_MESH = 0 };
	virtual void Delete_This(void);	// slot 0
	virtual void vf01(); virtual void vf02();
	virtual int Class_ID(void) const;	// slot 3 (+0x0C)
	virtual void vf04(); virtual void vf05();
	virtual const char *Get_Name(void) const;	// slot 6 (+0x18)
	virtual void vf07(); virtual void vf08(); virtual void vf09(); virtual void vf10();
	virtual void vf11(); virtual void vf12(); virtual void vf13(); virtual void vf14();
	virtual void vf15(); virtual void vf16(); virtual void vf17(); virtual void vf18();
	virtual void vf19(); virtual void vf20(); virtual void vf21(); virtual void vf22();
	virtual void vf23(); virtual void vf24(); virtual void vf25(); virtual void vf26();
	virtual void vf27();
	virtual int Get_Num_Sub_Objects(void) const;	// slot 28 (+0x70)
	virtual void vf29();
	virtual RenderObjClass *Get_Sub_Object(int index) const;	// slot 30 (+0x78)
	virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34();
	virtual void vf35(); virtual void vf36(); virtual void vf37(); virtual void vf38();
	virtual void vf39(); virtual void vf40(); virtual void vf41(); virtual void vf42();
	virtual void vf43(); virtual void vf44(); virtual void vf45(); virtual void vf46();
	virtual void vf47(); virtual void vf48(); virtual void vf49(); virtual void vf50();
	virtual void vf51(); virtual void vf52(); virtual void vf53(); virtual void vf54();
	virtual void vf55(); virtual void vf56(); virtual void vf57(); virtual void vf58();
	virtual void vf59(); virtual void vf60(); virtual void vf61(); virtual void vf62();
	virtual void vf63(); virtual void vf64(); virtual void vf65(); virtual void vf66();
	virtual void vf67(); virtual void vf68(); virtual void vf69(); virtual void vf70();
	virtual void vf71(); virtual void vf72(); virtual void vf73(); virtual void vf74();
	virtual void vf75(); virtual void vf76(); virtual void vf77(); virtual void vf78();
	virtual void vf79(); virtual void vf80(); virtual void vf81(); virtual void vf82();
	virtual void vf83(); virtual void vf84();
	virtual MaterialInfoClass *Get_Material_Info(void);	// slot 85 (+0x154)
	virtual void Set_User_Data(void *value, Bool recursive = false);	// slot 86 (+0x158)

	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

private:
	int NumRefs;
};

#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

enum TreadType { TREAD_LEFT = 0, TREAD_RIGHT = 1, TREAD_MIDDLE = 2 };

struct TreadObjectInfo
{
	RenderObjClass *m_robj;
	TreadType m_type;
	Material_Override m_materialSettings;
};

struct W3DTankDrawModuleData
{
	unsigned char m_pad000[0x190];
	Real m_treadAnimationRate;
};

class W3DModelDraw
{
public:
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03();
	virtual void vf04(); virtual void vf05(); virtual void vf06(); virtual void vf07();
	virtual void vf08(); virtual void vf09(); virtual void vf10(); virtual void vf11();
	virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15();
	virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
	virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27();
	virtual void vf28(); virtual void vf29(); virtual void vf30(); virtual void vf31();
	virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
	virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39();
	virtual void vf40(); virtual void vf41(); virtual void vf42(); virtual void vf43();
	virtual void vf44(); virtual void vf45(); virtual void vf46(); virtual void vf47();
	virtual void vf48();
	virtual RenderObjClass *getRenderObject(void);	// slot 49 (+0xC4)
	const W3DTankDrawModuleData *getW3DTankDrawModuleData() const { return m_moduleData; }

protected:
	const W3DTankDrawModuleData *m_moduleData;
	unsigned char m_pad008[0x2E8 - 0x08];
};

class W3DTankDraw : public W3DModelDraw
{
protected:
	enum { MAX_TREADS_PER_TANK = 4 };
	void updateTreadObjects(void);

	unsigned char m_pad2E8[0x300 - 0x2E8];
	RenderObjClass *m_prevRenderObj;
	TreadObjectInfo m_treads[MAX_TREADS_PER_TANK];
	Int m_treadCount;
};

// ?updateTreadObjects@W3DTankDraw@@IAEXXZ
void W3DTankDraw::updateTreadObjects(void)
{
	RenderObjClass *robj = getRenderObject();

	for (Int i = 0; i < m_treadCount; i++)
		REF_PTR_RELEASE(m_treads[i].m_robj);
	m_treadCount = 0;

	if (getW3DTankDrawModuleData() && getW3DTankDrawModuleData()->m_treadAnimationRate && robj)
	{
		for (Int i = 0; i < robj->Get_Num_Sub_Objects() && m_treadCount < MAX_TREADS_PER_TANK; i++)
		{
			RenderObjClass *subObj = robj->Get_Sub_Object(i);
			const char *meshName;
			if (subObj && subObj->Class_ID() == RenderObjClass::CLASSID_MESH && subObj->Get_Name()
				&& ((meshName = strchr(subObj->Get_Name(), '.')) != 0 && *(meshName++))
				&& _strnicmp(meshName, "TREADS", 6) == 0)
			{
				MaterialInfoClass *mat = subObj->Get_Material_Info();
				if (mat)
				{
					for (Int j = 0; j < mat->Vertex_Material_Count(); j++)
					{
						VertexMaterialClass *vmaterial = mat->Peek_Vertex_Material(j);
						LinearOffsetTextureMapperClass *mapper = (LinearOffsetTextureMapperClass *)vmaterial->Peek_Mapper();
						if (mapper && mapper->Mapper_ID() == TextureMapperClass::MAPPER_ID_LINEAR_OFFSET)
						{
							mapper->Set_UV_Offset_Delta(Vector2(0, 0));
							subObj->Add_Ref();
							m_treads[m_treadCount].m_robj = subObj;
							m_treads[m_treadCount].m_type = TREAD_MIDDLE;
							subObj->Set_User_Data(&m_treads[m_treadCount].m_materialSettings);
							m_treads[m_treadCount].m_materialSettings.customUVOffset = Vector2(0, 0);
							switch (meshName[6])
							{
								case 'L':
								case 'l':
									m_treads[m_treadCount].m_type = TREAD_LEFT;
									break;
								case 'R':
								case 'r':
									m_treads[m_treadCount].m_type = TREAD_RIGHT;
									break;
							}
							m_treadCount++;
						}
					}
					REF_PTR_RELEASE(mat);
				}
			}
			REF_PTR_RELEASE(subObj);
		}
	}

	m_prevRenderObj = robj;
}
