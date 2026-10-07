// BFME1 donor1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/Common/ScreenFilter_preRenderSetTargetNoPass.cpp.
// Native vtable pointer atRVA0x7CF278 targets0xF83A9; preceding RET ends
// at0xF83A9 and the closed81-byte body ends RET8 at0xF83F7.
// Writes false through argument1; binds surface this+0x1C through the rowed
// DX8Wrapper::Set_Render_Target0x11E250, then rowed seven-argument Clear
// 0x11D330 with color-only zero RGB/alpha and depth1, and returns true.
// Receiver's original class/method name and unused argument2's meaning remain
// unproven; its two stack slots follow the donor ABI, preserving nativeRET8.
// cl: -O1 -arch:SSE -G7 -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Include
#include "vector3.h"

struct IDirect3DSurface8;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer);
	// BFME2 rowed seven-argument Clear at0x11D330; class-Vector3 ABI.
	static void Clear(bool clear_color, bool clear_z, bool clear_stencil,
		const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};

class Rva000F83A9FilterView
{
public:
	bool rva000F83A9(bool &skipRender, int &scenePassMode);

private:
	char pad[0x1C];
	IDirect3DSurface8 *m_surface;
};

// ?rva000F83A9@Rva000F83A9FilterView@@QAE_NAA_NAAH@Z
bool Rva000F83A9FilterView::rva000F83A9(bool &skipRender, int &scenePassMode)
{
	skipRender = false;
	DX8Wrapper::Set_Render_Target(m_surface, true);
	Vector3 color;
	color.X = 0.0f;
	color.Y = 0.0f;
	color.Z = 0.0f;
	DX8Wrapper::Clear(true, false, false, color, 0.0f, 1.0f, 0);
	return true;
}
