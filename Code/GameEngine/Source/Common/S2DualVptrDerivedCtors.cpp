// cl: /O1 /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
// AudioManager's constructor (retail 0x0005107D, 32 bytes): the base
// constructor and the three vptr stores that follow it:
//
//     push esi / mov esi,ecx / call <REL32>
//     mov dword ptr [esi+0xC],<SNAPSHOT-VFTABLE>
//     mov dword ptr [esi],<OWN-VFTABLE-FOR-FIRST>
//     mov dword ptr [esi+0xC],<OWN-VFTABLE-FOR-SECOND>
//     mov eax,esi / pop esi / ret
//
// The called constructor is retail 0x001B4E63, the rowed SubsystemInterface
// constructor, and the slot at +0xC is the Snapshot base. The canonical header gives this unit
// AudioManager's whole table, not the 14 slots its private view compiled.
#include "../../Include/Common/GameAudio.h"

// @??0AudioManager@@QAE@XZ 0x0005107D
AudioManager::AudioManager()
{
}
