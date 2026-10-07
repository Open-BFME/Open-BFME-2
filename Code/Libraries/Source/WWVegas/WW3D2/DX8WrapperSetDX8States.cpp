// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z, retail 0x0006615F, 126 bytes.
// ?Set_DX8_Texture_Stage_State@DX8Wrapper@@SAXIKI@Z, retail 0x000661DD, 173 bytes.
// Dedicated TU (both bodies share the retail cookie, so they share this TU).
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
};

static unsigned RenderStates[256];
static unsigned TextureStageStates[16][32];
static bool snapshotActivated;
static void *d3dDevice;
static unsigned numberOfDX8Calls;
static unsigned renderStateChanges;
static unsigned textureStageStateChanges;

typedef HRESULT (__stdcall *SetRenderStateFn)(void *device, unsigned long state, unsigned value);
typedef HRESULT (__stdcall *SetTextureStageStateFn)(void *device, unsigned stage, unsigned long state, unsigned value);

// ?Set_DX8_Render_State@DX8Wrapper@@SAXKI@Z
inline void DX8Wrapper::Set_DX8_Render_State(unsigned long state, unsigned value)
{
	if (RenderStates[state] == value)
		return;

	if (snapshotActivated) {
		StringClass valueName(0, true);
		Get_DX8_Render_State_Value_Name(valueName, state, value);
	}

	RenderStates[state] = value;
	(*(SetRenderStateFn **)d3dDevice)[57](d3dDevice, state, value);
	numberOfDX8Calls++;
	renderStateChanges++;
}

// ?Set_DX8_Texture_Stage_State@DX8Wrapper@@SAXIKI@Z
inline void DX8Wrapper::Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value)
{
	if (stage >= 16) {
		(*(SetTextureStageStateFn **)d3dDevice)[67](d3dDevice, stage, state, value);
		numberOfDX8Calls++;
		return;
	}

	if (TextureStageStates[stage][state] == value)
		return;

	if (snapshotActivated) {
		StringClass valueName(0, true);
		Get_DX8_Texture_Stage_State_Value_Name(valueName, state, value);
	}

	TextureStageStates[stage][state] = value;
	(*(SetTextureStageStateFn **)d3dDevice)[67](d3dDevice, stage, state, value);
	numberOfDX8Calls++;
	textureStageStateChanges++;
}

#pragma inline_depth(0)
// ?bfmeEmitDX8WrapperSetDX8States@@YAXXZ present-unmatched
void bfmeEmitDX8WrapperSetDX8States()
{
	DX8Wrapper::Set_DX8_Render_State(0, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 0, 0);
}
#pragma inline_depth()
