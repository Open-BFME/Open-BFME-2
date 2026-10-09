// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva0035986C@@QAE@H_NH0@Z, retail 0x0035986C, 57 bytes.
// Ctor storing vtable 0x008153D8 at [this] with bool-to-0/0x7FFFF43 convert:
// mov eax,ecx; mov ecx,[esp+4]; mov [eax+4],ecx; mov cl,[esp+8]; neg cl;
// mov [eax],vtable; sbb ecx,ecx; and [eax+0x10],0; and [eax+0x14],0;
// and ecx,0x7FFFF43; mov [eax+8],ecx; mov ecx,[esp+0xC]; mov [eax+0xC],ecx;
// mov cl,[esp+0x10]; mov [eax+0x18],cl; ret 0x10. Caller at 0x00359AB8 pushes
// 0/[ebp+0x18]/[ebp+0x14]/esi with this lea [ebp-0x30]. Identity stays honest
// Rva ctor (sibling of 0x003598D3 vtable 0x008153DC).
#include "../GameLogic/System/TerrainResourceVisitorView.h"
Rva0035986C::Rva0035986C(int a1, bool a2, int a3, bool a4)
{
	m_04 = a1;
	m_08 = a2 ? 0x7FFFF43 : 0;
	m_0C = a3;
	m_10 = 0;
	m_14 = 0;
	m_18 = a4;
}
