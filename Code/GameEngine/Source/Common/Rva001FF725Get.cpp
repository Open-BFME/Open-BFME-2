// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?Rva001FF725Get@@YG?AW4ScienceType@@ABVAsciiString@@@Z @0x001FF725 30B
// Unlock lane: if AsciiString empty return SCIENCE_INVALID (-1) else tail-jmp
// to NameKeyGenerator::nameToKey via TheNameKeyGenerator. Callers include
// 0x003062B6 0x003BC6E6 grantScience path. Via rowed isEmpty 0x00001E2F.
#include "ascii_string.h"
enum ScienceType { SCIENCE_INVALID = -1 };
enum NameKeyType { NAMEKEY_INVALID = -1 };
class NameKeyGenerator {
public:
	NameKeyType nameToKey(const AsciiString &str);
};
extern NameKeyGenerator *TheNameKeyGenerator;

ScienceType __stdcall Rva001FF725Get(const AsciiString &str)
{
	if (str.isEmpty())
		return SCIENCE_INVALID;
	return (ScienceType)TheNameKeyGenerator->nameToKey(str);
}
