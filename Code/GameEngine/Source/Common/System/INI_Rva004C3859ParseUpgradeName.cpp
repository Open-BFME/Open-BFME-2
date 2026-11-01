// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Rva004C3859_ParseUpgradeName (retail 0x004C3859, 63 bytes). Reads one
// AsciiString through the rowed getNextAsciiString at 0x002EA4F by value
// (hidden-pointer construction into a stack temp, no zero-init store),
// pushes it through the pinned vector<AsciiString>::push_back at 0x002DBE6
// onto the store, then tears the temp down through the pinned teardown at
// 0x00036410. Serves the UpgradeName entry of the table at 0x85CDC0
// (sibling UpgradeOCL). The callback name stays address-derived; the owning
// struct is BFME2-new (no BFME1 donor).

#include "ascii_string.h"

namespace _STL
{
template <class T> class allocator
{
};

template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

#include "../../../Include/Common/INI/INI.h"

// ?Rva004C3859_ParseUpgradeName@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004C3859_ParseUpgradeName(INI *ini, void *instance, void *store, const void *userData)
{
	AsciiString name = ini->getNextAsciiString();
	((_STL::vector<AsciiString> *)store)->push_back(name);
}

// A second real callback, retail 0x004C7E09..0x004C7E48. Its field-parse
// entry at RVA 0x0085E23C independently names UpgradeName, selects this
// callback at +4 and writes the destination at instance+0x7C. Native reads
// the INI and destination stack arguments and uses the same string/vector
// providers as the callback above. Original C++ declaration scope is unknown.
// These are separate bodies with separate exception graphs: an object-symbol
// alias to the first body cannot supply this callback's own cleanup handler.
void Rva004C7E09_ParseUpgradeName(INI *ini, void *instance, void *store, const void *userData)
{
	AsciiString name = ini->getNextAsciiString();
	((_STL::vector<AsciiString> *)store)->push_back(name);
}
