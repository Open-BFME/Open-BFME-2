// cl: /DNDEBUG /MD /GX-
//
// ?read_shaders@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x0018AC90 (160 bytes).
// BFME1 meshmdlio.cpp read_shaders port (W3dShaderStruct loop over
// MatInfo.ShaderCount with bulk Read, Convert_Shader, Add_Shader). BFME2
// adaptations (all retail-measured from the 0x18AC90 body):
// - bool (AL) returns, not WW3DErrorType.
// - ShaderCount at context+0x80; Shaders DynamicVectorClass<ShaderClass> at
//   context+0xAC (Vector+4/VectorMax+8/IsValid+0xC/IsAllocated+0xD/
//   ActiveCount+0x10/GrowthStep+0x14, matching vector.h ordering).
// - TU-local ShaderClass DWORD defaulting to 0x10441B (retail stashes the
//   default to the Convert dst slot; the shared headers default to 0x8441B).
// - Add_Shader inlines as DynamicVectorClass::Add (ActiveCount-vs-Length
//   guard, IsAllocated/!VectorMax/GrowthStep grow checks, virtual Resize at
//   slot 2 with (total, NULL), then ActiveCount++ store); no out-of-line call.
// - Callee-clean thiscalls (Read, Resize) emit no caller cleanup; the static
//   Convert_Shader is cdecl (caller add-esp-8). The Convert dst reuses the
//   dead context-arg slot.
// Dedicated TU: marker-less meshmdlio.cpp cannot take rows (PostProcess
// precedent). No new pins (Read + Convert_Shader resolve via matched rows).

#ifndef NULL
#define NULL 0
#endif

typedef unsigned char uint8;
typedef unsigned long ulong;

struct W3dShaderStruct
{
	W3dShaderStruct(void) {}

	uint8 DepthCompare;
	uint8 DepthMask;
	uint8 ColorMask;
	uint8 DestBlend;
	uint8 FogFunc;
	uint8 PriGradient;
	uint8 SecGradient;
	uint8 SrcBlend;
	uint8 Texturing;
	uint8 DetailColorFunc;
	uint8 DetailAlphaFunc;
	uint8 ShaderPreset;
	uint8 AlphaTest;
	uint8 PostDetailColorFunc;
	uint8 PostDetailAlphaFunc;
	uint8 pad[1];
};

class ShaderClass
{
public:
	ShaderClass() : m_bits(0x10441B) {}

private:
	unsigned int m_bits;
};

class W3dUtilityClass
{
public:
	static void Convert_Shader(const W3dShaderStruct &shader, ShaderClass *set);
};

class ChunkLoadClass
{
public:
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

	bool Add(T const &object)
	{
		if (ActiveCount >= Length()) {
			if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
				if (!Resize(Length() + GrowthStep)) {
					return false;
				}
			} else {
				return false;
			}
		}
		(*this)[ActiveCount++] = object;
		return true;
	}

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
	int ActiveCount;
	int GrowthStep;
};

class MeshLoadContextClass
{
public:
	int __forceinline Add_Shader(ShaderClass shader)
	{
		int index = Shaders.Count();
		Shaders.Add(shader);
		return index;
	}

private:
	char m_pad0[0x80];
public:
	int ShaderCount;
private:
	char m_pad1[0x8C - 0x84];
	int CurPass;
	int CurTexStage;
	char m_pad2[0xAC - 0x94];

public:
	DynamicVectorClass<ShaderClass> Shaders;
};

class MeshModelClass
{
protected:
	virtual ~MeshModelClass();
	bool read_shaders(ChunkLoadClass &cload, MeshLoadContextClass *context);
};

// ?read_shaders@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_shaders(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	W3dShaderStruct shader;
	for (unsigned int i = 0; i < context->ShaderCount; i++) {
		if (cload.Read(&shader, sizeof(shader)) != sizeof(shader)) {
			return false;
		}
		ShaderClass newshader;
		W3dUtilityClass::Convert_Shader(shader, &newshader);

		int index = context->Add_Shader(newshader);
		(void)index;
	}
	return true;
}
