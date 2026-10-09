// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002122FD@Rva00DFE1C8Host@@QAEHABVAsciiString@@@Z @0x002122FD 30B
// Native constructor caller 003FA9FB supplies the manager in ECX. The
// forwarding body ignores it, but that does not establish a free-function ABI.
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

class Rva00DFE1C8Host { public: int rva002122FD(const AsciiString &); };

int Rva00DFE1C8Host::rva002122FD(const AsciiString &name)
{
	int rawKey = TheNameKeyGenerator->nameToKey(name);
	return ((Rva002122D4 *)TheLivingWorldManager)->rva002122D4(rawKey);
}
