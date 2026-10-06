// cl: /DNDEBUG /MD
// ?Compute_Ram_Size@MeshMatDescClass@@QAEHXZ @ 0x0015CAE0 (427B).
// BFME1 donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/MeshMatDescClass_ComputeRamSize.cpp
// (base 0xF4, 8 UV + 2 color + per-pass material/texture/material-array/shader-array).
// BFME2 adaptations from retail 0x15CAE0 body: base 0x118, UV at +0x10 (x8), color at +0x50 (x4),
// material singles at +0xA8 (VertexMaterial 0x13D250), texture pairs at +0xC8 (x4 only),
// material arrays at +0xE8 (x4 + VertexMaterial loop), shader arrays at +0xF8 (x4 only),
// tail FXShader arrays at +0x108 (x4 + Rva00151FA8 loop). Layout 0x118 proven by MeshMatDescReset.
// Callers: MeshModelClass::Compute_Ram_Size at 0x001880F5 and 0x00188106.

class RefCounted
{
public:
	virtual void Release_Virtual() = 0;
	void Add_Ref() { ++m_refs; }
	void Release_Ref() { if (--m_refs == 0) Release_Virtual(); }

private:
	int m_refs;
};

class VertexMaterialClass : public RefCounted
{
public:
	int rva0013D250() const;
};

class Rva00151FA8 : public RefCounted
{
public:
	int rva00151FA8() const;
};

template <class T>
class BfmeBuffer
{
public:
	T **Get_Array() { return m_array; }
	int Get_Count() { return m_count; }
	T *Get_Element(int index)
	{
		if (Get_Array()[index] != 0) {
			Get_Array()[index]->Add_Ref();
		}
		return Get_Array()[index];
	}

private:
	char m_prefix[8];
	T **m_array;
	char m_gap[4];
	int m_count;
};

class MeshMatDescClass
{
public:
	int Compute_Ram_Size();

private:
	char m_pad00[0x10];
	BfmeBuffer<unsigned> *m_uv[8];
	int m_uvSource[4][2];
	BfmeBuffer<unsigned> *m_color[2];
	char m_pad58[0xA8 - 0x58];
	VertexMaterialClass *m_material[4];
	void *m_opaquePass[4];
	BfmeBuffer<unsigned> *m_textureArray[4][2];
	BfmeBuffer<VertexMaterialClass> *m_materialArray[4];
	BfmeBuffer<unsigned> *m_shaderArray[4];
	BfmeBuffer<Rva00151FA8> *m_tail[4];
};

typedef char MeshMatDescComputeRamSizeCheck[sizeof(MeshMatDescClass) == 0x118 ? 1 : -1];

int MeshMatDescClass::Compute_Ram_Size()
{
	int size = 0x118;

	if (m_uv[0] != 0) {
		size += m_uv[0]->Get_Count() * 8;
	}
	if (m_uv[1] != 0) {
		size += m_uv[1]->Get_Count() * 8;
	}
	if (m_uv[2] != 0) {
		size += m_uv[2]->Get_Count() * 8;
	}
	if (m_uv[3] != 0) {
		size += m_uv[3]->Get_Count() * 8;
	}
	if (m_uv[4] != 0) {
		size += m_uv[4]->Get_Count() * 8;
	}
	if (m_uv[5] != 0) {
		size += m_uv[5]->Get_Count() * 8;
	}
	if (m_uv[6] != 0) {
		size += m_uv[6]->Get_Count() * 8;
	}
	if (m_uv[7] != 0) {
		size += m_uv[7]->Get_Count() * 8;
	}
	if (m_color[0] != 0) {
		size += m_color[0]->Get_Count() * 4;
	}
	if (m_color[1] != 0) {
		size += m_color[1]->Get_Count() * 4;
	}

	for (int pass = 0; pass < 4; ++pass) {
		if (m_material[pass] != 0) {
			size += m_material[pass]->rva0013D250();
		}
		if (m_textureArray[pass][0] != 0) {
			size += m_textureArray[pass][0]->Get_Count() * 4;
		}
		if (m_textureArray[pass][1] != 0) {
			size += m_textureArray[pass][1]->Get_Count() * 4;
		}
		if (m_materialArray[pass] != 0) {
			size += m_materialArray[pass]->Get_Count() * 4;
			for (int index = 0; index < m_materialArray[pass]->Get_Count(); ++index) {
				VertexMaterialClass *material = m_materialArray[pass]->Get_Element(index);
				if (material != 0) {
					size += material->rva0013D250();
					material->Release_Ref();
				}
			}
		}
		if (m_shaderArray[pass] != 0) {
			size += m_shaderArray[pass]->Get_Count() * 4;
		}
		if (m_tail[pass] != 0) {
			size += m_tail[pass]->Get_Count() * 4;
			for (int index = 0; index < m_tail[pass]->Get_Count(); ++index) {
				Rva00151FA8 *shader = m_tail[pass]->Get_Element(index);
				if (shader != 0) {
					size += shader->rva00151FA8();
					shader->Release_Ref();
				}
			}
		}
	}

	return size;
}
