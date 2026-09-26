// cl: /O1 /DNDEBUG /MD /GX-
// Rva00563EA8_ParseEventFX (retail 0x00563EA8, 23 bytes).
// EventFX entry of the table at 0x86CAC0: forwards to the rowed
// parseAsciiString at 0x002F11E with userData forced to 0 (EventTime's
// sibling entry at +0x14 uses parseGameClientRandomVariable).

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00563EA8_ParseEventFX(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva00563EA8_ParseEventFX@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva00563EA8_ParseEventFX(INI *ini, void *instance, void *store, const void *userData)
{
	parseAsciiString(ini, instance, store, 0);
}
