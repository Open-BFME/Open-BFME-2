// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ??1Rva0029E2A9@@QAE@XZ @0x0029E2A9 53B
// Record dtor with AsciiStrings at +0/+4 via rowed releaseBuffer 0x00036410
// (+4 first with EH state 0 then +0). Same shape as BfmeStringRecord000B94D2.
#include "ascii_string.h"

struct Rva0029E2A9
{
	AsciiString m_00;
	AsciiString m_04;
	~Rva0029E2A9();
};

Rva0029E2A9::~Rva0029E2A9()
{
}
