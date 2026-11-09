// cl: /DNDEBUG /MD
// dxsdk
// platformsdk
// Open-BFME5 conversions.
//
// ?bfmeStepTDB@@YAXXZ, retail 0x0011DC20 (58B). Called once by the rowed
// W3DGlowOutlineMaterialPassClass::UnInstall_Materials. The bfme1 sweep maps that call to BFME1
// 0x904720 where bfmeApplyBQ and bfmeStepTDB are ICF twins, so this
// transcribes reference/open-bfme-1/Code/GameEngine/Source/Common/
// BfmeConv1753.cpp bfmeApplyBQ with BQ names swapped for TDB ones.
//
// The device call is IDirect3DDevice9::SetFVF (slot 89; slot 92, which
// GoTDB rows, is SetVertexShader). The /G7 P4 tuning is load-bearing: it
// emits the retail cmp-byte-imm and add-mem-imm forms where /O1-/O2/G6 use
// test and inc.
#include <d3d9.h>

struct BfmeStateTDB
{
	unsigned char m_bfmeHeadTDB[0x14];
	void **m_bfmeSourceTDB;
	char m_bfmeBusyTDB;
};

// The ledger's DX8Wrapper device (0x9EDA34, a protected static read through a
// derived view) and DX8 call counter (0x9EDA98). The device keeps its D3D8
// type name but is a Direct3D 9 device.
struct IDirect3DDevice8;
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
#include "../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"
extern unsigned number_of_DX8_calls;

// Retail reads the render state's first vertex buffer and its type (0x00DEE858, 0x00DEE844). This body once
// defined its own two globals there, which nothing set, so it always returned early (P82).
struct BfmeDeviceTDB : DX8Wrapper
{
	static IDirect3DDevice9 *get() { return reinterpret_cast<IDirect3DDevice9 *>(D3DDevice); }
	static BfmeStateTDB *state() { return reinterpret_cast<BfmeStateTDB *>(render_state.vertex_buffers[0]); }
	static unsigned mode() { return render_state.vertex_buffer_types[0]; }
};

// ?bfmeStepTDB@@YAXXZ
void bfmeStepTDB(void)
{
	if (BfmeDeviceTDB::state() == 0)
		return;

	if (BfmeDeviceTDB::mode() != 0 && BfmeDeviceTDB::mode() != 2)
		return;

	if (BfmeDeviceTDB::state()->m_bfmeBusyTDB)
		return;

	BfmeDeviceTDB::get()->SetFVF((DWORD)*BfmeDeviceTDB::state()->m_bfmeSourceTDB);

	++number_of_DX8_calls;
}
