// cl: /DNDEBUG /MD
// W3DDisplay.cpp's debug-display placeholder callbacks. Zero Hour has
// StatDebugDisplay(DebugDisplayInterface *, void *, FILE *) as a bare
// DEBUG_CRASH; BFME 2 writes the separator and the placeholder message to the
// file instead (IAT fprintf/fflush) and adds three siblings. Each function's
// name is the one its own message string spells.
//
// ?StatDebugDisplay@@YAXPAVDebugDisplayInterface@@PAXPAU_iobuf@@@Z       @0x00043D0F 45B
// ?SkirmishAIDebugDisplay@@YAXPAVDebugDisplayInterface@@PAXPAU_iobuf@@@Z @0x00043D3C 45B
// ?AnimDebugDisplay@@YAXPAVDebugDisplayInterface@@PAXPAU_iobuf@@@Z       @0x00043D69 45B
// ?NetworkDebugDisplay@@YAXPAVDebugDisplayInterface@@PAXPAU_iobuf@@@Z    @0x00043D96 45B

#include <stdio.h>

class DebugDisplayInterface;

void StatDebugDisplay(DebugDisplayInterface *, void *, FILE *fp)
{
	if (fp)
	{
		fprintf(fp, "----------------------------------------------------------------\n");
		fprintf(fp, "StatDebugDisplay should never be called directly, but is just a placeholder for drawDebugStats()");
		fflush(fp);
	}
}

void SkirmishAIDebugDisplay(DebugDisplayInterface *, void *, FILE *fp)
{
	if (fp)
	{
		fprintf(fp, "----------------------------------------------------------------\n");
		fprintf(fp, "SkirmishAIDebugDisplay should never be called directly, but is just a placeholder for drawSkirmishAIStats()");
		fflush(fp);
	}
}

void AnimDebugDisplay(DebugDisplayInterface *, void *, FILE *fp)
{
	if (fp)
	{
		fprintf(fp, "----------------------------------------------------------------\n");
		fprintf(fp, "AnimDebugDisplay(...) should never be called directly, but is just a placeholder for drawDebugStats()");
		fflush(fp);
	}
}

void NetworkDebugDisplay(DebugDisplayInterface *, void *, FILE *fp)
{
	if (fp)
	{
		fprintf(fp, "----------------------------------------------------------------\n");
		fprintf(fp, "NetworkDebugDisplay(...) should never be called directly, but is just a placeholder for drawDebugStats()");
		fflush(fp);
	}
}
