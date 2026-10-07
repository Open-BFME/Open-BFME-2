// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002122FD@@YGHABVAsciiString@@@Z @0x002122FD 30B
// Target evidence: forwards the input AsciiString through NameKeyGenerator at
// 0x0009FA65, loads the global LivingWorldManager pointer, and tail-returns the
// raw result of 0x002122D4. The helper body remains blocked and is only pinned
// as the directly observed call target; manager operation and key meaning remain unknown.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Rva002122D4
{
public:
	int rva002122D4(int rawKey);
};

int __stdcall rva002122FD(const AsciiString &name)
{
	int rawKey = TheNameKeyGenerator->nameToKey(name);
	return ((Rva002122D4 *)TheLivingWorldManager)->rva002122D4(rawKey);
}
