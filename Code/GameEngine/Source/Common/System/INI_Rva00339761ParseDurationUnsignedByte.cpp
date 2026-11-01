// cl: /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?Rva00339761_ParseDurationUnsignedByte@INI@@SAXPAV1@PAX1PBX@Z, retail
// 0x00339761 (119B), in the INI.cpp parse run. The parseDurationUnsignedInt
// conversion (scale 0x00DBA4EC, double ceil import, __ftol2) into a byte
// store, throwing INIException "Duration %u must be less than %d frames"
// (argument count 3: the milliseconds and 255) when the frame count exceeds
// 255. Serves HandOffModeDuration (0x00C362D0). Name address-derived.

#include <math.h>

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/INI/FieldParse.h"

// Retail value at 0x00DBA4EC owned by INI_parseDurationUnsignedShort.cpp.
extern float g_parseDurationMsecScale;

// ?Rva00339761_ParseDurationUnsignedByte@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva00339761_ParseDurationUnsignedByte(INI *ini, void *, void *store, const void *)
{
	unsigned int val = ini->scanUnsignedInt(ini->getNextToken(0));
	unsigned int frames = (unsigned int)ceil((double)(g_parseDurationMsecScale * (float)val));
	if (frames > 255)
		throw INIException(3, "Duration %u must be less than %d frames", val, 255);
	*(unsigned char *)store = (unsigned char)frames;
}
