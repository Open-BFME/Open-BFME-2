// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseUpgradeTemplate@INI@@SAXPAV1@PAX1PBX@Z, retail 0x00339679, 90 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseUpgradeTemplate (Common/INI/INI.cpp): when
// TheUpgradeCenter (0x00DFEB60) exists, store the upgrade it finds by name.

class UpgradeTemplate;

#include "ascii_string.h"


#include "../../../Include/Common/Upgrade.h"

extern UpgradeCenter *TheUpgradeCenter;

#include "../../../Include/Common/INI/INI.h"

// ?parseUpgradeTemplate@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseUpgradeTemplate(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	if (TheUpgradeCenter)
	{
		const UpgradeTemplate *uu = TheUpgradeCenter->findUpgrade(AsciiString(token));
		*(const UpgradeTemplate **)store = uu;
	}
}
