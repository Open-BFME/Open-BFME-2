// cl: /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
//
// Bodies ported from Open-BFME-1's
// Libraries/Source/WWVegas/WW3D2/DX8Wrapper_Set_Pixel_Shader_Constant.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: DX8Wrapper::Set_Pixel_Shader_Constant 0x00075399 (86B).
// Callee addresses are read off retail's call sites (reverse/symbols.csv).
// Only the placed bodies are carried; the donor's other definitions are
// omitted.
//
// Open-BFME5 near-twin conversion.
// Twin: ?Set_Vertex_Shader_Constant@DX8Wrapper@@SAXHPBXH@Z @ 0x0071BEB0
//       (game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp, matched via
//       object-symbol on the same inline body dx8wrapper.h defines).
//
// This is DX8Wrapper::Set_Pixel_Shader_Constant, the sibling inline in the
// same header (dx8wrapper.h:756). Retail calls the device at +0x1B4 (index
// 109), which neither D3D8 header lands on: the device keeps dx8wrapper.h's
// D3D8 type name but is a Direct3D 9 device, and index 109 is
// IDirect3DDevice9::SetPixelShaderConstantF from the vendored SDK. The extern
// globals below name-mangle identically to DX8Wrapper's real static members
// regardless of which header declared them.
#include <string.h>
#include <d3d9.h>

struct IDirect3DDevice8;

#include "../WWMath/Vector4Data.h"

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	static void Set_Pixel_Shader_Constant(int reg, const void *data, int count);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

protected:	// as dx8wrapper.h: the statics mangle as protected members
	static IDirect3DDevice8 *D3DDevice;
	static Vector4 Pixel_Shader_Constants[8];
};

// ?Set_Pixel_Shader_Constant@DX8Wrapper@@SAXHPBXH@Z
// A dx8wrapper.h inline (WWINLINE): the shader-manager units emit the same select-any copy.
inline void DX8Wrapper::Set_Pixel_Shader_Constant(int reg, const void *data, int count)
{
	int memsize = sizeof(Vector4) * count;

	// may be incorrect if shaders are created and destroyed dynamically
	if (memcmp(data, &Pixel_Shader_Constants[reg], memsize) == 0)
		return;

	memcpy(&Pixel_Shader_Constants[reg], data, memsize);
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetPixelShaderConstantF(reg,
		(const float *)data, count);
	number_of_DX8_calls++;
}

// Header inline that other units emit as select-any copies, which a plain
// definition here collided with. The anchor keeps this unit's copy for its
// row; it is not retail data.
void (*_bfmeInlineAnchor_DX8Wrapper_Set_Pixel_Shader_Constant)(int, const void *, int) = &DX8Wrapper::Set_Pixel_Shader_Constant;
