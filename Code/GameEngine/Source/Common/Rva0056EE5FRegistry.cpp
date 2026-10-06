// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva0056EE5F@Rva0056EE5F@@QAEEXZ retail 0x0056EE5F 121B
// Evidence: GetStringFromRegistry 0x00234E0B with Registered and empty via 0x00037BA0; compareNoCase true via 0x00037980; releaseBuffer 0x00036410; callers 0x00571C81 0x00571C93; precedent RegistryAsciiPath
typedef unsigned char Bool8;
class AsciiString;
#include "ascii_string.h"
bool __cdecl GetStringFromRegistry(AsciiString path, AsciiString key, AsciiString &val);
struct Rva0056EE5F
{
	Bool8 rva0056EE5F();
};
Bool8 Rva0056EE5F::rva0056EE5F()
{
	AsciiString val;
	GetStringFromRegistry("", "Registered", val);
	return (Bool8)(((const StringBase<char> &)val).compareNoCase("true") == 0);
}
