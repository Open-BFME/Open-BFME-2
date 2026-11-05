// cl: /EHs-c- /Ireference/shims/bfme2_ascii

// Rva00290EFE::getGhostObject, retail 0x00290EFE (189 bytes).
// BFME2 ghost-object predicate for the subobject at Object+0x64: when global
// ghost objects are enabled and the host thing is KINDOF bit-2 flagged it
// scans the thing draw-module vector for a W3DDefaultDraw entry through a
// make-ghost flag cleared plus break on a hit (the donor form; the toolchain
// folds it to direct miss jumps but keeps the late edi save that the flag
// selects). A cleared flag means no ghost (null). On a kept flag it asks the
// for a ghost of the host Object and returns it skipped past its vptr.
// Donor is the BFME1 Rva001CA550::getGhostObject backport (same scan plus the
// same manager tail); BFME2 repairs are the missing override dance plus the
// moved ThingTemplate kindOf (+0x108) and draw-module vector (+0x2F0) plus
// the moved global flag (+0xC69). The getNthName bounds-checked copy-out and
// the 4-byte-string temp teardown resolve through this TU own spellings at
// 0x001F12DF and 0x00036410; strcmp rides the existing _strcmp pin.

#include "ascii_string.h"

struct ModuleNugget
{
	char m_bytes[20];
};

#include "../../../Include/Common/ModuleInfoClass.h"

#include "../../../Include/Common/ThingTemplate.h"

class Object;

#include "../../../Include/GameLogic/GhostObjectManager.h"

extern GhostObjectManager *TheGhostObjectManager;
// TheGhostObjectManager: matched references place it at VA 0xdff188 (zero-filled .bss).
GhostObjectManager * TheGhostObjectManager;

#include "../../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

#include <string.h>

class Rva00290EFE
{
public:
	void *getGhostObject();
};

// ?getGhostObject@Rva00290EFE@@QAEPAXXZ @0x00290EFE
void *Rva00290EFE::getGhostObject()
{
	if (TheWritableGlobalData->field0C69 == 0)
		return 0;
	ThingTemplate *thing = *(ThingTemplate **)((char *)this - 0x60);
	if ((*(const unsigned char *)thing->m_kindof & 4) != 0) {
		ModuleInfo *drawMod = (ModuleInfo *)thing->m_drawModuleInfo;
		int makeGhostObject = 1;
		// LINK: drawMod->getCount() inlined here but the live call emits a
		// loser COMDAT (first-copy-wins, no retail address). Manual inline of
		// the identical body keeps the bytes and drops the emission.
		for (int i = 0; i < (((char *)drawMod->m_end - (char *)drawMod->m_begin) / 20); i++) {
			if (strcmp(drawMod->getNthName(i).str(), "W3DDefaultDraw") == 0) {
				makeGhostObject = 0;
				break;
			}
		}
		if (makeGhostObject != 0) {
			void *ghost = TheGhostObjectManager->addGhostObject((Object *)((char *)this - 0x64));
			return ghost != 0 ? (char *)ghost + 4 : 0;
		}
	}
	return 0;
}
