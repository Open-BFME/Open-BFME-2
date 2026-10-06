// cl: /Ireference/shims/bfme2_ascii /MD
// ??1Rva000899E5@@QAE@XZ, retail 0x000899E5, 60 bytes.
// Non-virtual dtor releasing two AsciiStrings at +0xAC/+0xB0 with EH states.
// Evidence: __EH_prolog, and/or [ebp-4] states, rowed releaseBuffer twice in reverse order,
// frameless otherwise, bare ret. Owner unknown so honest Rva name.
#include "ascii_string.h"

class Rva000899E5
{
public:
	~Rva000899E5();

private:
	unsigned char m_pad[0xAC];
	AsciiString m_ac;
	AsciiString m_b0;
};

Rva000899E5::~Rva000899E5()
{
}
