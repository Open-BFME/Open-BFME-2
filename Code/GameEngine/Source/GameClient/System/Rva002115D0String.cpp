// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /EHsc /MD
// ?rva002115D0@Rva002115D0@@QAE?AVAsciiString@@I@Z @0x002115D0 28B
// The body constructs an AsciiString in the hidden return buffer at [ebp+8]
// through the rowed StringBase<char> constructor at 0x00037BA0. Its source
// pointer is the empty literal at VA 0x00BBAC1C (RVA 0x007BAC1C). The receiver
// and one unused 32-bit argument have no further support, so the address-based
// name and raw argument spelling retain that uncertainty.
#include "ascii_string.h"

extern const char g_Rva0107301CEmptyString[];

class Rva002115D0
{
public:
	AsciiString rva002115D0(unsigned int rawArgument);
};

AsciiString Rva002115D0::rva002115D0(unsigned int)
{
	return AsciiString(g_Rva0107301CEmptyString);
}
