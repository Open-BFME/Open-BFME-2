// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc

#include "../../Include/Common/GlobalData.h"

#include "../../Include/Common/SubsystemInterfaceList.h"

extern GlobalData *TheWritableGlobalData;
// The byte after TheSubsystemList (VA 0x00DFD944) that the subsystem loader
// reads to skip its cinematic exclusions (SubsystemInterface.cpp).
extern bool skipCinematicSubsystemExclusions;
// The byte stored at 0x009B6218 is the render-asset colouring flag that
// renderasset.cpp defines (the 8 bytes before it are WW3D's sorting clean_list).
extern bool g_Va00DB6218;

// ?Rva003B9E0FInit@@YAXXZ @0x003B9E0F 73B
// Target evidence: called by the following command-line helper; retail
// writes skipCinematicSubsystemExclusions and TheWritableGlobalData fields and sets the
// "Mods\\cinematics" string. Field identities beyond those globals are inferred.
void Rva003B9E0FInit()
{
	if (TheWritableGlobalData != 0)
	{
		skipCinematicSubsystemExclusions = true;
		TheWritableGlobalData->field0D45 = 1;
		TheWritableGlobalData->m_showTooltips = 0;
		TheWritableGlobalData->m_allowTreeFading = 0;
		g_Va00DB6218 = false;
		TheWritableGlobalData->m_modDir.set("Mods\\cinematics");
	}
}
