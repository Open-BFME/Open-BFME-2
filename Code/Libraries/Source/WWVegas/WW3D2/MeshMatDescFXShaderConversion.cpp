// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// Legacy W3D material -> FX shader conversion, retail 0x00199FFB..0x0019AEFC (3841 B, EH,
// cdecl static, returns bool in AL; its one caller, MeshModelClass::Register_For_Rendering
// 0x00173230, ignores the result). WorldBuilder 0x00A4FBA0 is the source-shape guide: its
// debug strings ("FXShader conversion: ...") and call order give every check, parameter
// record and message; the retail keeps the debug logging (bfmeRva000387C0 / debug
// callsite / theDebug stream, the matched-unit expansion of the BFME logging macro).
// The function and several callee names are address-derived placeholders (no named
// target symbol); member names follow WW3D's MeshMatDescClass / VertexMaterialClass /
// ShaderClass (bit layout as WW3D2 shader.h, verified by the retail masks).
// Source facts found against the retail body: the logging macro is a do/while(0)
// statement (cl hoists its enabled check out of both model/no-model arms); Get_Single
// _Texture returns a handle whose filter and name getters take the handle itself; the
// record finder is nothrow (its AsciiString argument has no unwind state); the
// _Vector_base ctor is the pinned folded copy at 0x00211E58, visible here so the
// empty allocator temporary sits in the dead parameter slot like retail.
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

#include "../../../../GameEngine/Source/Common/debug.h"
extern Debug *theDebug;

#define FXCONV_LOG(stream_expr) \
	do { \
	if (bfmeRva000387C0()) \
	{ \
		_bfme_debugRecordCallsite(1); \
		theDebug->SkipNext(); \
		Debug &dbg = theDebug->CrashBegin(0, 0, 0); \
		(dbg stream_expr).CrashDone(2); \
	} } while (0);

#include "../WWMath/Vector3Data.h"

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
	T *Referent;
};

#include "../WWLib/StringClassData.h"
inline StringClass::~StringClass() { Free_String(); }
inline StringClass::operator const char *() const { return m_Buffer; }


class TextureFilterClass
{
public:
	int Get_U_Addr_Mode() const { return m_U; }
	int Get_V_Addr_Mode() const { return m_V; }
	int Get_Mip_Mapping() const { return m_mip; }
	int m_pad00[2];
	int m_mip;
	int m_U;
	int m_V;
};

class ShroudFilter;
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/ShroudTexture.h"
class BFME2ParticleTextureHandle { public: StringClass Get_Texture_Name() const; };
class TextureClass
{
public:
	void Release_Ref();
	StringClass Get_Texture_Name() const { return ((const BFME2ParticleTextureHandle *)this)->Get_Texture_Name(); }
	TextureFilterClass *Get_Filter() { return (TextureFilterClass *)((ShroudTexture *)this)->getFilter(); }
};

class TextureMapperClass
{
public:
	virtual void s00();
	virtual void s01();
	virtual int Mapper_ID() const;			// +0x08
	virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual bool Add_FX_Parameters(_STL::vector<struct Rva0007BB16Record> &params);	// +0x20
};

class VertexMaterialClass
{
public:
	enum ColorSourceType { MATERIAL = 0 };
	ColorSourceType Get_Ambient_Color_Source();
	ColorSourceType Get_Diffuse_Color_Source();
	ColorSourceType Get_Emissive_Color_Source();
	void Get_Ambient(Vector3 *color) const;
	void Get_Diffuse(Vector3 *color) const;
	void Get_Specular(Vector3 *color) const;
	void Get_Emissive(Vector3 *color) const;
	float Get_Shininess() const;
	float Get_Opacity() const;
	TextureMapperClass *Peek_Mapper(int stage) const { return Mapper[stage]; }
	bool Get_Lighting() const { return UseLighting; }
	char m_pad00[0x20];
	TextureMapperClass *Mapper[2];		// +0x20
	char m_pad28[0x41];
	bool UseLighting;					// +0x69
};

#include "ShaderClass.h"

// <new> already supplies the placement allocation operators.
#define _OPERATOR_NEW_DEFINED_
#include "always.h"
// The game Debug declaration above replaces the reference debug singleton.
#define DEBUG_DEBUG_H
// The model header needs the complete list template as well as its bases.
#include "MeshModelClass.h"

#include "FXShaderSetup.h"

#include "../../../../GameEngine/Include/Common/Rva0010E482.h"
bool rva00199FA5(class Rva00199FA5Rec *model);

#include "../WWLib/Rva0007BB16Record.h"
struct BfmeAssignRecord36
{
	BfmeAssignRecord36(const char *name, int type);
	void *name;
	int type;
	void *texture;
	float vector[4];
	int integer;
	bool boolean;
};
#include "Rva00151288.h"
class Rva00199FCC { public: void *rva00199FCC(const AsciiString &name) throw(); };
namespace
{
// The parameter record: rowed ctor/dtor carry different ledger view names over
// one 36-byte storage.
struct FXParameter
{
	__forceinline FXParameter(const char *name, int type) : storage(name, type) {}
	__forceinline ~FXParameter() { ((Rva0007BB16Record *)&storage)->~Rva0007BB16Record(); }
	Rva0007BB16Record &record() { return *(Rva0007BB16Record *)&storage; }
	BfmeAssignRecord36 storage;
};
}
namespace _STL
{
	template <> inline __declspec(noinline) _Vector_base<Rva0007BB16Record, allocator<Rva0007BB16Record> >::_Vector_base(const allocator<Rva0007BB16Record> &a)
		: _M_start(0), _M_finish(0), _M_end_of_storage(a, (Rva0007BB16Record *)0) {}
	template <> void vector<Rva0007BB16Record>::push_back(const Rva0007BB16Record &);
	template <> void vector<Rva0007BB16Record>::reserve(size_t);
	template <> vector<Rva0007BB16Record>::~vector();
}
RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char *shader,
	const char *technique, const _STL::vector<Rva0007BB16Record> *parameters, int lod);

class MeshMatDescClass
{
public:
	int Get_Pass_Count() const { return PassCount; }
	bool Has_Material_Data(int pass);
	bool Has_Shader_Data(int pass);
	bool Has_Texture_Data(int pass, int stage) const { return TextureArray[stage] != 0 || Texture[pass][stage] != 0; }
	VertexMaterialClass *Peek_Material(int pass) const { return Material[pass]; }
	ShaderClass Get_Shader(int pass) const { return Shader[pass]; }
	RefCountPtr<TextureClass> Get_Single_Texture(int pass, int stage) const;
	void Set_Single_Rva0015A800(void *setup, int pass);
	void Store_Pass0_State(bool fxShader);
	int PassCount;						// +0x00
	char m_pad04[0x94];
	ShaderClass Shader[4];				// +0x98
	VertexMaterialClass *Material[4];	// +0xA8
	char m_padb8[0x10];
	TextureClass *Texture[1][2];		// +0xC8
	char m_padd0[0x18];
	void *MaterialArray[4];				// +0xE8
	void *ShaderArray[4];				// +0xF8
	void *TextureArray[2];
};

class Rva00199FFB
{
public:
	static bool rva00199FFB(MeshMatDescClass *matDesc, MeshModelClass *model);
};

bool Rva00199FFB::rva00199FFB(MeshMatDescClass *matDesc, MeshModelClass *model)
{
	if (matDesc->Get_Pass_Count() != 1)
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Cannot convert multi pass material")
		else
			FXCONV_LOG(<< "FXShader conversion: Cannot convert multi pass material")
		return false;
	}
	if ((unsigned char)((Rva0010E482 *)matDesc)->rva0010E482(0))
		return true;
	if (!matDesc->Has_Material_Data(0) || !matDesc->Has_Shader_Data(0))
		return false;

	Bool hasTextureArray = false;
	for (Int stage = 0; stage < 2; stage++)
		hasTextureArray = hasTextureArray || matDesc->Texture[0][stage] != 0;
	if (matDesc->MaterialArray[0] || matDesc->ShaderArray[0] || hasTextureArray)
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Cannot convert multiple materials on one mesh")
		else
			FXCONV_LOG(<< "FXShader conversion: Cannot convert multiple materials on one mesh")
		return false;
	}

	_STL::vector<Rva0007BB16Record> params;
	params.reserve(20);
	VertexMaterialClass *material = matDesc->Peek_Material(0);
	ShaderClass shader = matDesc->Get_Shader(0);
	Bool useMaterialColors = material->Get_Lighting() && shader.Get_Primary_Gradient() != 0;

	{
		FXParameter param("ColorAmbient", 4);
		if (useMaterialColors)
		{
			if (material->Get_Ambient_Color_Source() == VertexMaterialClass::MATERIAL)
				material->Get_Ambient((Vector3 *)param.storage.vector);
			else
				param.storage.vector[0] = 1.0f, param.storage.vector[1] = 1.0f, param.storage.vector[2] = 1.0f;
		}
		params.push_back(param.record());
	}
	{
		FXParameter param("ColorDiffuse", 4);
		if (useMaterialColors)
		{
			if (material->Get_Diffuse_Color_Source() == VertexMaterialClass::MATERIAL)
				material->Get_Diffuse((Vector3 *)param.storage.vector);
			else
				param.storage.vector[0] = 1.0f, param.storage.vector[1] = 1.0f, param.storage.vector[2] = 1.0f;
		}
		params.push_back(param.record());
	}
	{
		FXParameter param("ColorSpecular", 4);
		if (useMaterialColors)
			material->Get_Specular((Vector3 *)param.storage.vector);
		params.push_back(param.record());
	}
	{
		FXParameter param("Shininess", 2);
		param.storage.vector[0] = material->Get_Shininess();
		params.push_back(param.record());
	}
	{
		FXParameter param("ColorEmissive", 4);
		if (useMaterialColors && material->Get_Emissive_Color_Source() == VertexMaterialClass::MATERIAL)
			material->Get_Emissive((Vector3 *)param.storage.vector);
		else
			param.storage.vector[0] = 1.0f, param.storage.vector[1] = 1.0f, param.storage.vector[2] = 1.0f;
		params.push_back(param.record());
	}
	{
		FXParameter param("Opacity", 2);
		if (shader.Get_Primary_Gradient() != 0 && material->Get_Ambient_Color_Source() == VertexMaterialClass::MATERIAL
			&& material->Get_Diffuse_Color_Source() == VertexMaterialClass::MATERIAL
			&& material->Get_Emissive_Color_Source() == VertexMaterialClass::MATERIAL)
			param.storage.vector[0] = material->Get_Opacity();
		else
			param.storage.vector[0] = 1.0f;
		params.push_back(param.record());
	}

	for (Int mapperStage = 0; mapperStage < 2; mapperStage++)
	{
		TextureMapperClass *mapper = material->Peek_Mapper(mapperStage);
		if (mapper && !mapper->Add_FX_Parameters(params))
		{
			if (model)
				FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Cannot convert texture mapper in stage " << mapperStage << "(MapperID " << mapper->Mapper_ID() << ")")
			else
				FXCONV_LOG(<< "FXShader conversion: Cannot convert texture mapper in stage " << mapperStage << "(MapperID " << mapper->Mapper_ID() << ")")
			return false;
		}
	}

	Int numTextures = 0;
	if (matDesc->Get_Single_Texture(0, 0).Referent != 0)
	{
		numTextures = 1;
		if (matDesc->Get_Single_Texture(0, 1).Referent != 0)
			numTextures = 2;
	}
	else if (matDesc->Get_Single_Texture(0, 1).Referent != 0)
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Texture stage 1 used without stage 0")
		else
			FXCONV_LOG(<< "FXShader conversion: Texture stage 1 used without stage 0")
		return false;
	}

	if (shader.Get_Depth_Compare() != 3 && shader.Get_Depth_Compare() != 1)
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Depth comparison function is not less-equal (Uses " << shader.Get_Depth_Compare() << ")")
		else
			FXCONV_LOG(<< "FXShader conversion: Depth comparison function is not less-equal (Uses " << shader.Get_Depth_Compare() << ")")
		return false;
	}
	{
		FXParameter param("DepthWriteEnable", 7);
		param.storage.boolean = shader.Get_Depth_Mask() == 1;
		params.push_back(param.record());
	}
	if (shader.Get_Color_Mask() != 1)
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Color write is not enabled (Uses " << shader.Get_Color_Mask() << ")")
		else
			FXCONV_LOG(<< "FXShader conversion: Color write is not enabled (Uses " << shader.Get_Color_Mask() << ")")
		return false;
	}
	if (shader.Get_Primary_Gradient() != 0 && shader.Get_Primary_Gradient() != 1)
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Primary gradient is not 'Modulate' or 'Disable' (Uses " << shader.Get_Primary_Gradient() << ")")
		else
			FXCONV_LOG(<< "FXShader conversion: Primary gradient is not 'Modulate' or 'Disable' (Uses " << shader.Get_Primary_Gradient() << ")")
		return false;
	}
	if (shader.Get_Secondary_Gradient() != 0)
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Secondary gradient is not 'Disable' (Uses " << shader.Get_Secondary_Gradient() << ")")
		else
			FXCONV_LOG(<< "FXShader conversion: Secondary gradient is not 'Disable' (Uses " << shader.Get_Secondary_Gradient() << ")")
		return false;
	}

	Int detailColor = shader.Get_Post_Detail_Color_Func();
	Int secondaryBlendMode = -1;
	if (detailColor == 0)
	{
		if (numTextures > 1)
			numTextures = 1;
	}
	else if (detailColor == 2)
		secondaryBlendMode = 0;
	else if (detailColor == 11)
		secondaryBlendMode = 1;
	else if (detailColor == 8)
		secondaryBlendMode = 2;
	else if (detailColor == 12)
		secondaryBlendMode = 3;
	else if (detailColor == 13)
	{
		secondaryBlendMode = 3;
		FXParameter param("HouseColorEnable", 7);
		param.storage.boolean = true;
		params.push_back(param.record());
	}
	else
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Unsupported DetailColor mode. Supported: 'Disable', 'Scale', 'Scale2X', 'DetailBlend', 'ModAlphaAddColor' or 'HouseColor' (Uses " << detailColor << ")")
		else
			FXCONV_LOG(<< "FXShader conversion: Unsupported DetailColor mode. Supported: 'Disable', 'Scale', 'Scale2X', 'DetailBlend', 'ModAlphaAddColor' or 'HouseColor' (Uses " << detailColor << ")")
		return false;
	}
	if (secondaryBlendMode != -1)
	{
		FXParameter param("SecondaryTextureBlendMode", 6);
		param.storage.integer = secondaryBlendMode;
		params.push_back(param.record());
	}

	if (shader.Get_Post_Detail_Alpha_Func() != 0)
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: DetailAlpha is not 'Disable' (Uses " << shader.Get_Post_Detail_Alpha_Func() << ")")
		else
			FXCONV_LOG(<< "FXShader conversion: DetailAlpha is not 'Disable' (Uses " << shader.Get_Post_Detail_Alpha_Func() << ")")
		return false;
	}
	{
		FXParameter param("AlphaTestEnable", 7);
		param.storage.boolean = shader.Get_Alpha_Test() != 0;
		params.push_back(param.record());
	}
	{
		FXParameter param("CullingEnable", 7);
		param.storage.boolean = !(model && (model->Flags & MeshGeometryClass::TWO_SIDED));
		params.push_back(param.record());
	}

	Int srcBlend = shader.Get_Src_Blend_Func();
	Int dstBlend = shader.Get_Dst_Blend_Func();
	Int blendMode = -1;
	if (srcBlend == 1 && dstBlend == 0)
		blendMode = 0;
	else if (srcBlend == 2 && dstBlend == 5)
		blendMode = 1;
	else if (srcBlend == 1 && dstBlend == 1)
		blendMode = 2;
	else
	{
		if (model)
			FXCONV_LOG(<< "Mesh \"" << model->Get_Name() << "\" FXShader conversion: Unsupported SrcBlend/DestBlend combination. Supported: One/Zero, SrcAlpha/InvSrcAlpha, One/One (Uses " << srcBlend << "/" << dstBlend << ")")
		else
			FXCONV_LOG(<< "FXShader conversion: Unsupported SrcBlend/DestBlend combination. Supported: One/Zero, SrcAlpha/InvSrcAlpha, One/One (Uses " << srcBlend << "/" << dstBlend << ")")
		return false;
	}
	if (blendMode != -1)
	{
		FXParameter param("BlendMode", 6);
		param.storage.integer = blendMode;
		params.push_back(param.record());
	}

	if (shader.Get_Texturing() == 0)
		numTextures = 0;
	{
		FXParameter param("NumTextures", 6);
		param.storage.integer = numTextures;
		params.push_back(param.record());
	}

	for (Int i = 0; i < numTextures; i++)
	{
		RefCountPtr<TextureClass> texture = matDesc->Get_Single_Texture(0, i);
		{
			AsciiString name;
			name.format("Texture_%d", i);
			FXParameter param(name.str(), 1);
			((Rva00151288 *)&param.record())->rva00151288(((const BFME2ParticleTextureHandle *)&texture)->Get_Texture_Name());
			params.push_back(param.record());
		}
		{
			AsciiString name;
			name.format("Sampler_ClampU_ClampV_NoMip_%d", i);
			FXParameter param(name.str(), 4);
			param.storage.vector[0] = (float)(((TextureFilterClass *)((ShroudTexture *)&texture)->getFilter())->Get_U_Addr_Mode() == 1);
			param.storage.vector[1] = (float)(((TextureFilterClass *)((ShroudTexture *)&texture)->getFilter())->Get_V_Addr_Mode() == 1);
			param.storage.vector[2] = (float)(((TextureFilterClass *)((ShroudTexture *)&texture)->getFilter())->Get_Mip_Mapping() == 0);
			params.push_back(param.record());
		}
	}
	if (numTextures == 1)
	{
		Rva0007BB16Record *sampler = (Rva0007BB16Record *)((Rva00199FCC *)&params)->rva00199FCC(AsciiString("Sampler_ClampU_ClampV_NoMip_0"));
		if (sampler)
		{
			Rva0007BB16Record copy(*sampler);
			copy.SetName("Sampler_ClampU_ClampV_NoMip_1");
			params.push_back(copy);
		}
	}

	RefCountPtr<FXShaderSetup> setup = Rva00152C47_CreateFXShaderSetup("DefaultW3D.fx", "Default", &params, 4);
	if (!setup.Referent)
		return false;
	matDesc->Set_Single_Rva0015A800(setup.Referent, 0);
	matDesc->Store_Pass0_State(true);
	return true;
}
