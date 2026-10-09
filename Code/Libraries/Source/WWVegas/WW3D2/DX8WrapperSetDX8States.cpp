// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
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

typedef int Int;
typedef long HRESULT;
struct IDirect3DDevice8;

#define NULL 0

class StringClass
{
public:
	StringClass(int value, bool flag);
	~StringClass() { Free_String(); }
private:
	void Free_String();
};

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned value);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, unsigned long state, unsigned value);
protected:
	static unsigned RenderStates[256];
	static unsigned TextureStageStates[16][32];
	static IDirect3DDevice8 *D3DDevice;
	static unsigned render_state_changes;
	static unsigned texture_stage_state_changes;
};

class WW3D
{
	friend class DX8Wrapper;
	static bool SnapshotActivated;
};
extern unsigned number_of_DX8_calls;

typedef HRESULT (__stdcall *SetRenderStateFn)(void *device, unsigned long state, unsigned value);
typedef HRESULT (__stdcall *SetTextureStageStateFn)(void *device, unsigned stage, unsigned long state, unsigned value);

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
	(*(SetRenderStateFn **)D3DDevice)[57](D3DDevice, state, value);
	number_of_DX8_calls++;
	render_state_changes++;
}

// ?Set_DX8_Texture_Stage_State@DX8Wrapper@@SAXIKI@Z
inline void DX8Wrapper::Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value)
{
	if (stage >= 16) {
		(*(SetTextureStageStateFn **)D3DDevice)[67](D3DDevice, stage, state, value);
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
	(*(SetTextureStageStateFn **)D3DDevice)[67](D3DDevice, stage, state, value);
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
