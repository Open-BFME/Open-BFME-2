// cl: /DNDEBUG /MD
//
// ?SetParentCell@PathfindCell (retail 0x0052DAC4, 14 bytes): nested one-field
// setter that copies *source into the info buffer's +8 dword. Shape mirrors
// Rva003F69C0Object::set in the neighbouring TU, which sets two fields;
// this body sets only the first. Evidence: 8 callers pass a pointer from
// [ebp+8] with ecx=esi (e.g. 0x002F4603 pushes [ebp+8] after loading the
// inner word at +0x12); /O1 reproduces retail's ecx reuse where /O2 uses edx.

#include "../../Include/Common/MixFileInfoBuffer.h"
#include "../../Include/GameLogic/PathfindCell.h"

void PathfindCell::SetParentCell(int *source)
{
	((MixFileInfoBuffer *)m_info)->field08 = *source;
}
