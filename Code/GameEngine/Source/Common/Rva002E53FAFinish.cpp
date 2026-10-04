// ?rva002E53FA@OptionPreferences@@QAEXH@Z
// stlport
//
// ?rva002E53FA@OptionPreferences@@QAEXH@Z, retail 0x002E53FA,
// 96 bytes. AudioLOD setter twin of rva002E537B: writes the AudioLOD name
// for val through base-map subscript 0x002031FB plus StringBase::set
// 0x000055F5; level name from rowed indexed getter 0x00202678; key
// "AudioLOD" at 0x804CB8; manager at 0x9FE144.

// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB

#include <map>
#include <stdlib.h>
#include <string.h>

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> AsciiPreferenceMap;

namespace _STL
{
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

// The rowed indexed getter at 0x00202678 is a __stdcall free function
// (?Rva00202678Get@@YGPBDH@Z), but the retail caller sets ecx to
// TheGameLODManager immediately before the call, i.e. it was compiled
// against a GameLODManager thiscall method at the same address. Model that
// call shape here and bind this spelling to the rowed address so the linker
// emits the same REL32 the retail caller uses.
class GameLODManager
{
public:
	const char *getAudioLODLevelName(Int i);
};

extern GameLODManager *TheGameLODManager;

extern "C" const char *__stdcall Rva00202678Get(int);

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	void rva002E53FA(Int val);
};

void OptionPreferences::rva002E53FA(Int val)
{
	AsciiString key("AudioLOD");
	const char *levelName = TheGameLODManager->getAudioLODLevelName(val);
	AsciiString &value = (*this)[key];
	value.set(levelName);
}
