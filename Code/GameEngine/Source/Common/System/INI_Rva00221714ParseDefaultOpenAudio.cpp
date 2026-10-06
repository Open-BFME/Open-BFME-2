// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Rva00221714_ParseDefaultOpenAudio (retail 0x00221714, 75 bytes). Parses a
// string through the rowed parseAsciiString at 0x002F11E into a stack temp
// (passed as both instance and store, userData 0), assigns it through the
// pinned AsciiString copy assignment at 0x000366F0 to instance+0x10, then
// tears the temp down through the pinned teardown at 0x00036410. Serves the
// DefaultOpenAudio entry of the table at 0x7E6CE0 (siblings:
// DefaultMessageFont, DefaultMessageColor, NotificationType). The callback
// name stays address-derived; the owning class is BFME2-new (no BFME1 donor).

#include "ascii_string.h"

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00221714_ParseDefaultOpenAudio(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva00221714_ParseDefaultOpenAudio@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva00221714_ParseDefaultOpenAudio(INI *ini, void *instance, void *store, const void *userData)
{
	AsciiString text;
	INI::parseAsciiString(ini, &text, &text, 0);
	AsciiString &slot = *(AsciiString *)((char *)instance + 0x10);
	slot = text;
}
