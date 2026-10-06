// cl: /DNDEBUG /MD /EHsc
//
// ?Add_Textures_Material_And_Shader@Textures_Material_And_Shader_Booking_Struct@@QAE_NPAVBfmeHandleCX@@PAVVertexMaterialClass@@VShaderClass@@@Z, RVA 0x00143AD0, 292B.
// Booking of unique texture/material/shader combos for Generate_Texture_Categories.
// Evidence: BFME1 donor dx8renderer.cpp Textures_Material_And_Shader_Booking_Struct
// with MAX 64 and 4 arrays at +0x0/+0x100/+0x200/+0x300 count +0x400; caller
// 0x00146DEE passes stack booking struct and tests al for insert; material
// compare via inlined Get_CRC cache (+0x64/+0x68 calling rowed Compute_CRC
// 0x0013CA20) replacing donor Equal_Material; textures via BfmeHandleCX word
// inc at +4 plus rowed TextureBaseClass::Release_Ref 0x0061ED10.

#include <stddef.h>

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

class BfmeHandleCX
{
public:
	TextureClass *p;

	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p != NULL)
			++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(other.p) + 4);
		if (p != NULL)
			p->Release_Ref();
		p = other.p;
		return *this;
	}

	bool operator==(const BfmeHandleCX &other) const
	{
		return p == other.p;
	}
};

class VertexMaterialClass
{
	char m_pad[0x64];
	mutable unsigned long m_crc;
	mutable bool m_dirtyFlag;

public:
	unsigned long Get_CRC() const
	{
		if (m_dirtyFlag)
		{
			m_crc = Compute_CRC();
			m_dirtyFlag = false;
		}
		return m_crc;
	}

private:
	unsigned long Compute_CRC() const;
};

class ShaderClass
{
	unsigned m_bits;

public:
	unsigned Get_Bits() const { return m_bits; }
};

inline static bool Equal_Material(const VertexMaterialClass *mat1, const VertexMaterialClass *mat2)
{
	unsigned long crc0 = mat1 ? mat1->Get_CRC() : 0;
	unsigned long crc1 = mat2 ? mat2->Get_CRC() : 0;
	return crc0 == crc1;
}

struct Textures_Material_And_Shader_Booking_Struct
{
	enum { MAX_ADDED_TYPE_COUNT = 64 };
	enum { MAX_TEX_STAGES = 2 };

	BfmeHandleCX added_textures[MAX_TEX_STAGES][MAX_ADDED_TYPE_COUNT];
	VertexMaterialClass *added_materials[MAX_ADDED_TYPE_COUNT];
	unsigned added_shader_bits[MAX_ADDED_TYPE_COUNT];
	unsigned added_type_count;

	bool Add_Textures_Material_And_Shader(BfmeHandleCX *texs, VertexMaterialClass *mat, ShaderClass shd);
};

bool Textures_Material_And_Shader_Booking_Struct::Add_Textures_Material_And_Shader(
	BfmeHandleCX *texs,
	VertexMaterialClass *mat,
	ShaderClass shd)
{
	unsigned index;
	for (index = 0; index < added_type_count; ++index)
	{
		bool all_textures_same = true;
		for (unsigned stage = 0; stage < MAX_TEX_STAGES; ++stage)
			all_textures_same = all_textures_same && (texs[stage] == added_textures[stage][index]);
		if (all_textures_same &&
			Equal_Material(mat, added_materials[index]) &&
			shd.Get_Bits() == added_shader_bits[index])
			return false;
	}

	for (unsigned stage = 0; stage < MAX_TEX_STAGES; ++stage)
		added_textures[stage][added_type_count] = texs[stage];
	added_materials[added_type_count] = mat;
	added_shader_bits[added_type_count] = shd.Get_Bits();
	++added_type_count;
	return true;
}
