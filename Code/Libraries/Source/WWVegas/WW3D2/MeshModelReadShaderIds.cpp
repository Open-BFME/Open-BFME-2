// cl: /DNDEBUG /MD /GX-
//
// ?read_shader_ids@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x001889B0 (307 bytes).
// BFME1 MeshModelMaterialIds.cpp read_shader_ids port (single shaderid vs
// per-poly loop over PolyCount with Peek_Shader plus Set_Single_Shader /
// Set_Shader plus the SORT-flag block). BFME2 adaptations (all retail-measured
// from the 0x1889B0 body):
// - bool (AL) returns, not WW3DErrorType; signed int loop over PolyCount.
// - Has_Shader_Data inline: Shader[pass](+0x98) != NullShader (DIR32 global,
//   copied from retail, no pin) || ShaderArray[pass](+0xF8) != NULL.
// - Peek_Shader inlines as Shaders.Vector[shaderid] (Shaders DVC at +0xAC,
//   so Vector at +0xB0); the shaderid temp rides the dead context-arg slot.
// - Set_Single_Shader / Set_Shader resolve via pins (Shader-by-value shapes,
//   stolen manglings); the by-value shader overwrites a scratch push slot.
// - ShaderClass DWORD with inline DstBlend (bits&0xE0) / AlphaTest
//   (bits&0xC0000) tests (both zero-valued enum arms, test-only codegen);
//   SortLevel +0x1C, Flags +0x18 with SORT 0x10.
// Dedicated TU: marker-less meshmdlio.cpp cannot take rows (PostProcess
// precedent). 2 pins (Set_Single_Shader pre-existed at 0x15A7E0).

#ifndef NULL
#define NULL 0
#endif

typedef unsigned char uint8;
typedef unsigned long ulong;

class ShaderClass
{
public:
	ShaderClass() : m_bits(0) {}
	ShaderClass(const ShaderClass &other) : m_bits(other.m_bits) {}

	enum DstBlendType
	{
		DSTBLEND_ZERO = 0
	};

	enum AlphaTestType
	{
		ALPHATEST_DISABLE = 0
	};

	unsigned int Get_Dst_Blend_Func(void) const { return m_bits & 0xE0; }
	unsigned int Get_Alpha_Test(void) const { return m_bits & 0xC0000; }
	bool operator!=(const ShaderClass &other) const { return m_bits != other.m_bits; }

private:
	unsigned int m_bits;
};

extern ShaderClass NullShader;

class ChunkLoadClass
{
public:
	unsigned long Cur_Chunk_Length(void);
	unsigned long Read(void *dst, unsigned long size);
};

template <class T> class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
	virtual bool operator==(const DynamicVectorClass<T> &) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear(void);
	virtual int ID(T const *ptr);
	virtual int ID(T const &ptr);

	int Length(void) const { return VectorMax; }
	int Count(void) const { return ActiveCount; }
	T &operator[](int index) { return Vector[index]; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
	int ActiveCount;
	int GrowthStep;
};

class MeshMatDescClass
{
public:
	bool Has_Shader_Data(int pass) { return Shader[pass] != NullShader || ShaderArray[pass] != 0; }
	void Set_Single_Shader(ShaderClass shader, int pass);
	void Set_Shader(int index, ShaderClass shader, int pass);

private:
	char m_pad0[0x98];
	ShaderClass Shader[4];
	char m_pad1[0xF8 - 0xA8];
	void *ShaderArray[4];
	char m_pad2[0x118 - 0x108];
};

class MeshLoadContextClass
{
public:
	ShaderClass Peek_Shader(unsigned long index) { return Shaders[index]; }

private:
	char m_pad0[0x8C];
public:
	int CurPass;
private:
	char m_pad1[0xAC - 0x90];

public:
	DynamicVectorClass<ShaderClass> Shaders;

private:
	char m_pad2[0x124 - 0xC4];

public:
	MeshMatDescClass AlternateMatDesc;
};

class MeshModelClass
{
public:
	enum FlagsType
	{
		SORT = 0x10
	};
	void Set_Flag(FlagsType flag, bool onoff) { if (onoff) Flags |= flag; else Flags &= ~flag; }
	int Get_Polygon_Count(void) { return PolyCount; }

protected:
	virtual ~MeshModelClass();
	bool read_shader_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);

private:
	char m_pad0[0x18 - 4];
	int Flags;
	char SortLevel;
	char m_pad1[0x24 - 0x1D];
	int PolyCount;
	char m_pad2[0x8C - 0x28];

public:
	MeshMatDescClass *DefMatDesc;
};

// ?read_shader_ids@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_shader_ids(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	unsigned long shaderid;
	MeshMatDescClass *matdesc = DefMatDesc;

	if (DefMatDesc->Has_Shader_Data(context->CurPass)) {
		matdesc = &(context->AlternateMatDesc);
	}

	if (cload.Cur_Chunk_Length() == 1 * sizeof(unsigned long)) {
		cload.Read(&shaderid, sizeof(shaderid));
		ShaderClass shader = context->Peek_Shader(shaderid);
		matdesc->Set_Single_Shader(shader, context->CurPass);

		if ((context->CurPass == 0) &&
			(shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO) &&
			(shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE) &&
			(SortLevel == 0)) {
			Set_Flag(SORT, true);
		}
	} else {
		for (int i = 0; i < Get_Polygon_Count(); i++) {
			cload.Read(&shaderid, sizeof(shaderid));
			ShaderClass shader = context->Peek_Shader(shaderid);
			matdesc->Set_Shader(i, shader, context->CurPass);

			if ((context->CurPass == 0) &&
				(shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO) &&
				(shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE) &&
				(SortLevel == 0)) {
				Set_Flag(SORT, true);
			}
		}
	}

	return true;
}
