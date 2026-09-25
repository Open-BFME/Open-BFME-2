// cl: /O1 /DNDEBUG /MD /EHsc /Oi-
// Retail omits the frame pointer here, so no /Oy- like its siblings.
//
// Environment preset name lookup (retail 0x00050F7D, 35B). Dedicated TU.
//
// Maps a reverb-environment index to its display name through a 26-entry
// {name, index} table (None, Padded Cell, Room, ... Drugged, Dizzy,
// Psychotic); anything outside 0..25 yields "<Unknown>". The table is
// BFME2-specific (the strings appear nowhere in the BFME1 tree). The sole
// retail caller at 0x005426E feeds the result into an AsciiString, so the
// value type below is a plain name pointer. Names are descriptive; no retail
// spellings are known.

struct EnvironmentNameEntry
{
	const char *name;
	int environmentType;
};

static const EnvironmentNameEntry s_environmentNames[] = {
	{ "None", 0 },
	{ "Padded Cell", 1 },
	{ "Room", 2 },
	{ "Bathroom", 3 },
	{ "Living Room", 4 },
	{ "Stone Room", 5 },
	{ "Auditorium", 6 },
	{ "Concert Hall", 7 },
	{ "Cave", 8 },
	{ "Arena", 9 },
	{ "Hangar", 10 },
	{ "Carpeted Hallway", 11 },
	{ "Hallway", 12 },
	{ "Stone Corridor", 13 },
	{ "Alley", 14 },
	{ "Forest", 15 },
	{ "City", 16 },
	{ "Mountains", 17 },
	{ "Quarry", 18 },
	{ "Plain", 19 },
	{ "Parking Lot", 20 },
	{ "Sewer Pipe", 21 },
	{ "Underwater", 22 },
	{ "Drugged", 23 },
	{ "Dizzy", 24 },
	{ "Psychotic", 25 },
};

// getEnvironmentName @0x50F7D
const char *getEnvironmentName(int environmentType)
{
	for (unsigned int i = 0; i < 26; ++i)
	{
		if (environmentType == s_environmentNames[i].environmentType)
			return s_environmentNames[i].name;
	}
	return "<Unknown>";
}
