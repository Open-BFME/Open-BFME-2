// cl: /GS
// 0x007E8E90: Rva007E8810Message::addInt64. Formats %I64d then stores the
// field through Rva007ECE60; a negative result writes -100 at +0x24.

#include <stdio.h>

#include "../../Include/Common/ScalarTypes/Source/FeslInt64.h"

int Rva007ECE60(char *record, int size, const char *name, const char *value);

#include "../../Include/GameNetwork/Rva007E8810Message.h"

void Rva007E8810Message::addInt64(const char *key, FeslInt64 value)
{
	char buf[0x20];
	sprintf(buf, "%I64d", value);
	if (Rva007ECE60(m_10, m_14, key, buf) < 0)
		m_24 = -100;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeSet2VJF@BfmeMsgVJF@@QAEXPBDPAX1@Z=?addInt64@Rva007E8810Message@@QAEXPBD_J@Z")
