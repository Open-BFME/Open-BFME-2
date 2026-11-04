// cl: /O1 /DNDEBUG /MD /EHsc
//
// MixFileInfoBuffer ?bfmeUnlink (retail 0x002E6BE2, 33 bytes): detaches a
// buffer through its backlink (+0x38) and next (+0x34) fields, zeroing both.
// Split from MixFileInfoBuffer_releaseInto.cpp, which must keep the helpers
// declared-only (same-TU definitions let the compiler trust ecx across the
// call; retail homes this in esi). The sibling ?bfmeLinkInto definition and
// its row live in MixFileInfoBuffer.cpp. Donor:
// Open-BFME-1 Code/GameEngine/Source/Common/MixFileInfoBuffer_releaseInto.cpp
// with the link fields shifted +8.

#include "../../Include/Common/MixFileInfoBuffer.h"

extern int TheMixFileInfoCount;

// ?bfmeUnlink@MixFileInfoBuffer@@AAEXXZ @0x2E6BE2
void MixFileInfoBuffer::bfmeUnlink(void) throw()
{
	if (field38)
	{
		*field38 = field34;

		if (field34)
			field34->field38 = field38;

		field38 = 0;
		field34 = 0;
	}
}

// MixFileInfoBuffer::bfmeLinkInto: defined in MixFileInfoBuffer.cpp (its row's unit).
