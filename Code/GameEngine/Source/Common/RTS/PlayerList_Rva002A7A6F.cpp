// cl: /DNDEBUG /MD /EHsc
// platformsdk
//
// ?Rva002A7A6F@PlayerList@@QAEPAVPlayer@@H@Z,
// retail 0x002A7A6F, 49 bytes. Dedicated TU.
//
// Opaque row: this body is the crash-less twin of the findPlayerWithNameKey
// body at 0x002A7A41 (same TU flags, same codegen, only the field offset
// differs: +0x3AC instead of name key at +0x50, hence 3 bytes longer for the
// disp32 load). The retail count sits at +0x14 over an inline player pointer
// array at +0x18, exactly as in the sibling TU. Five image-wide callers all
// go through ThePlayerList (0x00DFEEE8) passing key-sized dwords.
//
// Retraction history: first landed as getPlayerFromMask, but the TRUE
// getPlayerFromMask was then found at 0x002A7B91 (zero-guard plus
// getNthPlayer loop with inlined 1-shift-plus-m-playerIndex-at-0x54, bound
// 0x14) and the TRUE getEachPlayerFromMask at 0x002A7BC9 (both banked as
// partials with stashes). The +0x3AC field identity is unproven, so the name
// claims only class, signature and address (RadiusDecal Rva00330E15
// precedent for opaque Rva+class+signature rows).

typedef int Int;

#include <windows.h>

#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/PlayerList.h"

// ?Rva002A7A6F@PlayerList@@QAEPAVPlayer@@H@Z
Player *PlayerList::Rva002A7A6F(Int key)
{
	for (Int i = 0; i < m_playerCount; i++)
	{
		if (m_players[i]->m_3AC == key)
		{
			return m_players[i];
		}
	}
	return NULL;
}
