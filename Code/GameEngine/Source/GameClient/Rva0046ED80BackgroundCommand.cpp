// cl: -DNDEBUG -DWIN32 -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient

// Retail 0x0046ED80, 108 bytes. The callback maps the three background
// commands used by the scripted UI to WindowManager operations.

#include <string.h>

#include "../../Include/Common/Rva00222A8BTarget.h"

// Retail global 0x012F19E8. EA's own name for this pointer; see
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp for the definition.
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

// ?Rva0046ED80@@YAXPBD@Z
void Rva0046ED80(const char *command)
{
	if (!command)
		return;

	int (__cdecl *compare)(const char *, const char *) = _strcmpi;
	if (compare(command, "fadein") == 0)
	{
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva002233A6(1);
		return;
	}

	if (compare(command, "fadeout") == 0)
	{
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva00222F55(false);
		return;
	}

	if (compare(command, "off") == 0)
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva00222F55(true);
}
