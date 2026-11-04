// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?Install_Materials@MaterialPassClass@@UBEXXZ, retail 0x0013EFA0..0x0013F0A5 (261 B), the
// MaterialPassClass vtable entry at 0x007D3314. Zero Hour matpass.cpp Install_Materials (WB
// 0x009E1F30, vtable evidence): DX8Wrapper::Set_Material and Set_Shader inline on
// render_state (0x00DEE5D8, changed bits 0x4000/0x8000; Set_Shader keeps its snapshot
// StringClass), then one BFME2Set_Texture per stage up to the caps' max textures per pass,
// each stage handle formed by the rowed 0x0013EF40. Layout per MaterialPassClassDestructor.cpp.
#include "VertexMaterialClass.h"


#include "ShaderClass.h"

class DX8Caps
{
public:
	int Get_Max_Textures_Per_Pass() const { return MaxTexturesPerPass; }
private:
	unsigned char m_pad000[0x2B0];
	int MaxTexturesPerPass;
};

#include "RenderStateStruct.h"

struct BFME2TextureResource { unsigned Vtable; unsigned short Refs; void Release_Ref(); };
struct BFME2TextureRef
{
	BFME2TextureResource *Ptr;
	~BFME2TextureRef() { if (Ptr) Ptr->Release_Ref(); }
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);

class Rva0013EF40Category
{
public:
	BFME2TextureRef Get_Texture(int stage);
private:
	unsigned Prefix[2]; // +0x00
	BFME2TextureResource * Textures[2]; // +0x08
};

class DX8Wrapper
{
public:
	static __forceinline void Set_Material(VertexMaterialClass *material)
	{
		if (material)
			material->Add_Ref();
		if (render_state.material)
			render_state.material->Release_Ref();
		render_state.material = material;
		render_state_changed |= 0x4000;
	}
	static __declspec(dllimport) __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty && shader.ShaderBits == render_state.shader.ShaderBits)
			return;
		render_state.shader.ShaderBits = shader.ShaderBits;
		render_state_changed |= 0x8000;
		StringClass str;
	}
	static DX8Caps *Get_Current_Caps() { return CurrentCaps; }
protected:
	static unsigned int render_state_changed;
	static RenderStateStruct render_state;
	static DX8Caps *CurrentCaps;
};

#include "MaterialPassClass.h"

void MaterialPassClass::Install_Materials(void) const
{
	DX8Wrapper::Set_Material(Peek_Material());
	DX8Wrapper::Set_Shader(Peek_Shader());
	for (int i = 0; i < DX8Wrapper::Get_Current_Caps()->Get_Max_Textures_Per_Pass(); i++)
		BFME2Set_Texture(i, ((Rva0013EF40Category *)this)->Get_Texture(i));
}
