// cl: /O1 /DNDEBUG /MD /EHsc
// Rva002216A6_ParseDefaultMessageColor (retail 0x002216A6, 33 bytes). Parses
// a color through the rowed parseColorInt at 0x002F3FE into a stack temp
// (passed as both instance and store, userData 0), then stores the packed
// value at instance+0x24. Serves the DefaultMessageColor entry of the table
// at 0x7E6CE0 (siblings: DefaultOpenAudio, DefaultMessageFont,
// NotificationType). The callback name stays address-derived; the owning
// class is BFME2-new (no BFME1 donor).

class INI
{
public:
	static void parseColorInt(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002216A6_ParseDefaultMessageColor(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva002216A6_ParseDefaultMessageColor@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva002216A6_ParseDefaultMessageColor(INI *ini, void *instance, void *store, const void *userData)
{
	int color;
	INI::parseColorInt(ini, &color, &color, 0);
	((int *)instance)[9] = color;
}
