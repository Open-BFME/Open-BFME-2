// cl: /DNDEBUG /O1 /G7 /arch:SSE /EHsc /MD /Oi- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
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

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>

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

// Inverse lookup (retail 0x0005505F, 65B, a Ghidra-unlisted gap body): the
// table index of a case-insensitively matching name, -1 when none matches.
// Retail accepts the misspelling "Hanger" for Hangar (10) first. The name
// arrives by reference and only the rowed StringBase<char>::compareNoCase
// (const char *) 0x00037980 is called on it; the descriptive name is ours.
template <class T> class StringBase
{
public:
	int compareNoCase(const T *str) const;
};
class AsciiString;

int getEnvironmentTypeFromName(const AsciiString &name)
{
	const StringBase<char> &text = reinterpret_cast<const StringBase<char> &>(name);
	if (text.compareNoCase("Hanger") == 0)
		return 10;
	for (unsigned int i = 0; i < 26; ++i)
	{
		if (text.compareNoCase(s_environmentNames[i].name) == 0)
			return s_environmentNames[i].environmentType;
	}
	return -1;
}

#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"

// MilesAudioManager view: only the +0x9D4 mutex is touched here.
class MilesAudioManager
{
public:
	virtual const _STL::vector<const char *> &rva00058314(void);
	void internalSetReverbRoomType(int type);
	virtual void rva0005522C(const AsciiString &name);
private:
	char at04[0x9D4 - 0x04];
	void *m_mutex;
	char at9D8[0xBE4 - 0x9D8];
	int m_atBE4;
};

// Native 00058314..000583BA, vftable slot 92 (+0x170, entry 0x007C5720).
// Under the mutex, a function-static list of the selectable environment
// names (every table entry but None) is built once and returned.
const _STL::vector<const char *> &MilesAudioManager::rva00058314(void)
{
	MilesMutexGuard guard(&m_mutex, 0);
	static _STL::vector<const char *> s_names;
	if (s_names.empty())
	{
		s_names.reserve(25);
		for (unsigned int i = 0; i < 26; ++i)
		{
			if (s_environmentNames[i].environmentType)
				s_names.push_back(s_environmentNames[i].name);
		}
	}
	return s_names;
}

// ?rva0005522C@MilesAudioManager@@QAEXABVAsciiString@@@Z @0x0005522C 153B.
// Reverb-room setter: Hanger special-cased to 10, else a case-insensitive
// table lookup (same shape as the rowed getEnvironmentTypeFromName above),
// -1 falling back to vtable slot 91 (+0x16C), otherwise storing the type at
// +0xBE4 and calling the rowed internalSetReverbRoomType 0x000512C4.
// Slot 91 is reached through an explicit vtable fetch so this TU emits no
// new vtable entries.
static inline int milesEnvironmentType(const AsciiString &name)
{
	const StringBase<char> &text = reinterpret_cast<const StringBase<char> &>(name);
	unsigned i = 0;
	if (text.compareNoCase("Hanger") == 0)
		return 10;
	for (; i < 26; ++i)
		if (text.compareNoCase(s_environmentNames[i].name) == 0)
			return s_environmentNames[i].environmentType;
	return -1;
}

void MilesAudioManager::rva0005522C(const AsciiString &name)
{
	MilesMutexGuard guard(&m_mutex, 0);
	int type = milesEnvironmentType(name);
	if (type == -1) {
		typedef void (__fastcall *Slot91Fn)(MilesAudioManager *);
		((Slot91Fn)(*(void ***)this)[91])(this);
	}
	else
		internalSetReverbRoomType(m_atBE4 = type);
}
