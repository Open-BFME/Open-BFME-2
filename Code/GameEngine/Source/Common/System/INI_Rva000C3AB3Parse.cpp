// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// stlport
// ?Rva000C3AB3Parse@INI@@SAXPAV1@PAX1PBX@Z @0x000C3AB3 187B (native
// C3AB3..C3B6E). INI field parser for a per-weapon-slot AsciiString list:
// the slot index comes from scanIndexList over TheWeaponSlotTypeNames
// (0x00DBC284, as in the matched parseTWS 0x004D7EF9), the value from
// getNextAsciiString lower-cased with "None" cleared; the STLport
// vector<AsciiString> at store grows to index+1 (rowed resize 0x000C32D9)
// before the slot is assigned, and a non-null instance receives the stored
// string through rowed 0x000C2AA4. Neighbours 0x000C3824 / 0x000C3B6E give
// the INI static-parser shape. Names address-derived.
#include <vector>
#include "ascii_string.h"

extern const char *TheWeaponSlotTypeNames[];

class Rva000C2AA4
{
public:
	void rva000C2AA4(const AsciiString &val);
};

// vector<AsciiString>::resize(n, x): retail's STLport passes x by value,
// unlike the vendored header's const& spelling, so the rowed body keeps its
// address-named view.
class Rva000C32D9
{
public:
	void rva000C32D9(unsigned int n, AsciiString x);
};

#include "../../../Include/Common/INI/INI.h"

void INI::Rva000C3AB3Parse(INI *ini, void *instance, void *store, const void *userData)
{
	unsigned int index = (unsigned int)ini->scanIndexList(ini->getNextToken(0), TheWeaponSlotTypeNames);
	AsciiString value = ini->getNextAsciiString();
	value.toLower();
	if (value.isNone())
		value.clear();
	_STL::vector<AsciiString> *vec = (_STL::vector<AsciiString> *)store;
	if (vec->size() < index + 1)
		((Rva000C32D9 *)vec)->rva000C32D9(index + 1, AsciiString(""));
	(*vec)[index] = value;
	if (instance != 0)
		((Rva000C2AA4 *)instance)->rva000C2AA4((*vec)[index]);
}
