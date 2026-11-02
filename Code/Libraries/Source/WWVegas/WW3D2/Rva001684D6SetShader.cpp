// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Native 00167EC4..00167ED1 RET4: store the incoming dword at +0xE8 of the
// 0x108-byte streak render object Rva001684D6 (renderer settings start at
// +0xE4, Rva001684D6Ctor.cpp). The only caller, the W3DStreakDraw
// constructor 0x000D02A7, builds a ShaderClass copy (ZH shader.h: one
// ShaderBits dword, user copy constructor, no destructor) in the argument
// slot from ShaderClass::_PresetAdditiveShader or _PresetAlphaShader, so the
// parameter is a ShaderClass passed by value (ZH StreakLineClass /
// SegLineRendererClass Set_Shader shape). Owner class stays address-named.

#include "ShaderClass.h"

class Rva001684D6
{
public:
	void Set_Shader(ShaderClass shader);

private:
	char m_before[0xE8];
	ShaderClass m_shader;
};

void Rva001684D6::Set_Shader(ShaderClass shader)
{
	m_shader = shader;
}
