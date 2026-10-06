// cl: /DNDEBUG /MD
//
// MaterialInfoClass::Reset_Texture_Mappers (retail 0x00184010, 69 bytes) and
// MaterialInfoClass::Has_Time_Variant_Texture_Mappers (retail 0x00184060,
// 84 bytes). BFME1 matinfo.h/vertmaterial.h port.
//
// Retail evidence:
// - Both walk this+0x0C (DynamicVector<VertexMaterial*> array) with count at
//   this+0x18 (ActiveCount: VectorClass is Vector+VectorMax+pad = 12 bytes,
//   so ActiveCount lands at +0x18 when the vector sits at +0x0C).
// - Each element's Mapper[8] sits at +0x20 (BFME1 VertexMaterialClass_Init
//   thunk comment: Name=0x1C, Mapper[8]=0x20).
// - Inner virtuals are TextureMapper slots 0x18 (Reset, void) and 0x10
//   (Is_Time_Variant, bool): the Scale vtable at 0xBD55D4 carries Clone at
//   slot 3 (landed row 0x183F10), return-false at slot 4 (Is_Time_Variant
//   base), Scale Apply at slot 5, empty at slot 6 (Reset base), return-false
//   at slot 7 (Needs_Normals base).
// - Callers pass the object in ecx with no stack args (thiscall void / bool).
// BFME1 shape (matinfo.h Reset_Texture_Mappers + Has_Time_Variant calling the
// header-inline Reset_Mappers / Are_Mappers_Time_Variant, which loop 8
// mappers) inlines to exactly these double loops under /O2+/G7.

class W3DMPO
{
};

class RefCountClass
{
public:
	virtual void Delete_This()
	{
		delete this;
	}

protected:
	int m_refCount;
};

class TextureMapperClass : public W3DMPO, public RefCountClass
{
public:
	virtual ~TextureMapperClass()
	{
	}

	virtual int Mapper_ID()
	{
		return 0;
	}

	virtual TextureMapperClass *Clone() = 0;
	virtual bool Is_Time_Variant()
	{
		return false;
	}

	virtual void Apply(int uvArrayIndex) = 0;
	virtual void Reset()
	{
	}

	virtual bool Needs_Normals()
	{
		return false;
	}

	virtual void Calculate_Texture_Matrix() = 0;

protected:
	unsigned int m_stage;
};

class VertexMaterialClass
{
public:
	virtual ~VertexMaterialClass()
	{
	}

	void Reset_Mappers()
	{
		for (int stage = 0; stage < 8; stage++) {
			if (Mapper[stage]) {
				Mapper[stage]->Reset();
			}
		}
	}

	bool Are_Mappers_Time_Variant() const
	{
		for (int stage = 0; stage < 8; stage++) {
			if (Mapper[stage] && (Mapper[stage]->Is_Time_Variant())) {
				return true;
			}
		}
		return false;
	}

private:
	unsigned char m_pad[0x20 - 4];
	TextureMapperClass *Mapper[8];
};

template <class T>
class VectorClass
{
public:
	virtual ~VectorClass()
	{
	}

	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template <class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	int ActiveCount;
	int GrowthStep;

	int Count() const
	{
		return ActiveCount;
	}
};

class MaterialInfoClass
{
public:
	virtual ~MaterialInfoClass()
	{
	}

	void Reset_Texture_Mappers();
	bool Has_Time_Variant_Texture_Mappers();

private:
	unsigned char m_pad[0x08 - 4];
	DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
};

void MaterialInfoClass::Reset_Texture_Mappers()
{
	int vmatCount = VertexMaterials.Count();
	for (int materialIndex = 0; materialIndex < vmatCount; materialIndex++) {
		VertexMaterials.Vector[materialIndex]->Reset_Mappers();
	}
}

bool MaterialInfoClass::Has_Time_Variant_Texture_Mappers()
{
	int vmatCount = VertexMaterials.Count();
	for (int materialIndex = 0; materialIndex < vmatCount; materialIndex++) {
		if (VertexMaterials.Vector[materialIndex]->Are_Mappers_Time_Variant()) {
			return true;
		}
	}
	return false;
}
