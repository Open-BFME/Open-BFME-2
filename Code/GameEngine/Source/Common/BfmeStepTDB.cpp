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

extern BfmeStateTDB *g_bfmeStateTDB;
// g_bfmeStateTDB: matched references place it at VA 0xdee858 (zero-filled .bss).
BfmeStateTDB * g_bfmeStateTDB;
extern int g_bfmeModeTDB;
// g_bfmeModeTDB: matched references place it at VA 0xdee844 (zero-filled .bss).
int g_bfmeModeTDB;
// The ledger's DX8Wrapper device (0x9EDA34, a protected static read through a
// derived view) and DX8 call counter (0x9EDA98). The device keeps its D3D8
// type name but is a Direct3D 9 device.
struct IDirect3DDevice8;
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
extern unsigned number_of_DX8_calls;

struct BfmeDeviceTDB : DX8Wrapper
{
	static IDirect3DDevice9 *get() { return reinterpret_cast<IDirect3DDevice9 *>(D3DDevice); }
};

// ?bfmeStepTDB@@YAXXZ
void bfmeStepTDB(void)
{
	if (g_bfmeStateTDB == 0)
		return;

	if (g_bfmeModeTDB != 0 && g_bfmeModeTDB != 2)
		return;

	if (g_bfmeStateTDB->m_bfmeBusyTDB)
		return;

	BfmeDeviceTDB::get()->SetFVF((DWORD)*g_bfmeStateTDB->m_bfmeSourceTDB);

	++number_of_DX8_calls;
}
