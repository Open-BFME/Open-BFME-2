// cl: /O1 /DNDEBUG /MD
// ??0Rva005CBA04@@QAE@VBfmeFixedStorage002CF0F0@@@Z retail 0x005CBA04 28B
// Base ctor storing vtable 0x00C74DB8 (RVA 0x00874DB8) then copy-constructs
// the 4B member at +4 from the by-value FixedStorage param via rowed copy
// 0x002CF0F0 (lea eax,[esp+8]; push eax; lea ecx,[esi+4]). Evidence: same
// vtable stored by 7B trivial dtor at 0x005CB9F3 and by deleting dtor at
// 0x005CBA20 (test [esp+4],1; mov [esi],vtable; je; push esi; call delete
// 0x0002FD60); vtable slot0 is 0x005CBA20 slot1-3 false 0x005CB9FF slot4-7
// true 0x005CB9FA slot8 bittest 0x005CBA3D; derived ctors at 0x00574815
// (vtable 0x00C6E3E8) 0x005756B6 (0x00C6E620) 0x0057709A (0x00C6E8A8)
// 0x005E5A38 (0x00C77D90) each build a 4B temp (globals 0x00E0661C/0x00E0660C
// or via 0x005E5A24->0x005E5963 bits 0,0,3) pass it by value here then store
// outer arg at +8 and overwrite vtable; strings "button" and
// "ToggleSelectionDetailsButton" follow the vtable but prove no donor class
// so the honest Rva address name is used. Flags copied from neighbour
// BitFlags11DisabilityCtors.cpp; same as FixedStorageCopyBFME2.cpp.
#include "../../Include/Common/BfmeFixedStorage002CF0F0.h"

#include "../../Include/Common/Rva005CBA04.h"

Rva005CBA04::Rva005CBA04(BfmeFixedStorage002CF0F0 storage)
	: m_storage(storage)
{
}

// ??1Rva005CBA04@@UAE@XZ present-unmatched
Rva005CBA04::~Rva005CBA04()
{
}
