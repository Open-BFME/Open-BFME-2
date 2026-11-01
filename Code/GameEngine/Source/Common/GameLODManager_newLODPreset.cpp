// ?newLODPreset@GameLODManager@@QAEPAULODPresetInfo@@W4StaticGameLODLevel@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_gamelod /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/gamelod /Ireference/open-bfme-1/reference/shims/ini_noinline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc
// stlport
#include "PreRTS.h"
#include "Common/GameLOD.h"
//
// ?newLODPreset@GameLODManager@@QAEPAULODPresetInfo@@W4StaticGameLODLevel@@@Z, retail 0x0020202B, 45 bytes.
// GameLODManager::newLODPreset (WorldBuilder GameLOD.cpp:394; ZH signature,
// called from INI::parseLODPreset 0x00202E23). Fixed-slot pool allocator. The sibling constructor Rva00201EACLODManager
// (Code/GameEngine/Source/Common/Rva00201DC4LODDefaults.cpp) proves the array
// composition this addresses: presets[5][32] of 32-byte stride at +0x208
// (5*32*32 = 0x1000, running 0x208..0x1208) and the pool of five 32-entry
// counters at +0x17AC. The retail body is
//   mov eax,[esp+4]; lea edx,[ecx+eax*4+0x17ac]; push esi; mov esi,[edx];
//   cmp esi,0x20; jge ret0; inc esi; shl eax,5; add eax,esi; shl eax,5;
//   mov [edx],esi; lea eax,[eax+ecx+0x208]
// so the returned slot is pool[index*32 + count+1] and the counter is
// post-incremented: the incremented value is the one stored AND the one added,
// hence `++m_counts[index]` written inline in the return expression. Hoisting
// that increment into a local makes MSVC keep a second live copy (the extra
// `push edi` / `lea edi,[esi+1]`) and swap the lea/push order, which is the
// whole diff against retail.
// Neighbours: prev 0x0020200D RetailBenchProfileAllocator, next 0x002025AC.
// Unlock lane: landing this makes 0x00202E23 ready.


LODPresetInfo *GameLODManager::newLODPreset(StaticGameLODLevel index)
{
	if (m_numLevelPresets[index] < 32)
		return &m_lodPresets[index][(++m_numLevelPresets[index]) - 1];
	return 0;
}