// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// dxsdk
// platformsdk
//
// ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z, retail 0x0006615F, 126 bytes.
// ?Set_DX8_Texture_Stage_State@DX8Wrapper@@SAXIKI@Z, retail 0x000661DD, 173 bytes.
// Dedicated TU (both bodies share the retail cookie, so they share this TU).
// Data bindings follow the established address index and native providers;
// the outlined body must share state with DX8Wrapper and WW3D.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h,
// DX8Wrapper::Set_DX8_Render_State / Set_DX8_Texture_Stage_State): cached
// state setters that skip redundant device calls, record a snapshot name
// while the snapshot is active, then apply through the D3D device and bump
// the call counters. The retail bodies follow the reference header inline
// shape: the BFME2 deltas are the outlined bodies with SEH for the snapshot
// string temp, sixteen texture stages, and the deferred snapshot-name
// resolvers (0x121A10 / 0x120B90 pins).

#include <d3d9.h>

typedef int Int;
// The device keeps its D3D8 type name but is a Direct3D 9 device
// (SetRenderState slot 57, SetTextureStageState slot 67).
struct IDirect3DDevice8;

#include "../WWLib/StringClassData.h"
inline StringClass::~StringClass() { Free_String(); }

#include "DX8WrapperClass.h"

#include "WW3DClass.h"
extern unsigned number_of_DX8_calls;

// ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z
inline void DX8Wrapper::Set_DX8_Render_State(unsigned long state, unsigned value)
{
	if (RenderStates[state] == value)
		return;

	if (WW3D::SnapshotActivated) {
		StringClass valueName(0, true);
		Get_DX8_Render_State_Value_Name(valueName, state, value);
	}

	RenderStates[state] = value;
	reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetRenderState((D3DRENDERSTATETYPE)state, value);
	number_of_DX8_calls++;
	render_state_changes++;
}

// ?Set_DX8_Texture_Stage_State@DX8Wrapper@@SAXIKI@Z
inline void DX8Wrapper::Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value)
{
	if (stage >= 16) {
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTextureStageState(stage, (D3DTEXTURESTAGESTATETYPE)state, value);
		number_of_DX8_calls++;
		return;
	}

	if (TextureStageStates[stage][state] == value)
		return;

	if (WW3D::SnapshotActivated) {
		StringClass valueName(0, true);
		Get_DX8_Texture_Stage_State_Value_Name(valueName, state, value);
	}

	TextureStageStates[stage][state] = value;
	reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetTextureStageState(stage, (D3DTEXTURESTAGESTATETYPE)state, value);
	number_of_DX8_calls++;
	texture_stage_state_changes++;
}

#pragma inline_depth(0)
// ?bfmeEmitDX8WrapperSetDX8States@@YAXXZ present-unmatched
void bfmeEmitDX8WrapperSetDX8States()
{
	DX8Wrapper::Set_DX8_Render_State(0, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 0, 0);
}
#pragma inline_depth()
