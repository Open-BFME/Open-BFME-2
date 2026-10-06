// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva00415AE0@@QAE@XZ retail 0x00415AE0 53B
// Destroys the rowed Rva0041580E member at +8 (dtor 0x004159AA) under EH
// state 0, then the AsciiString at +0 through releaseBuffer 0x00036410.
// Caller: rowed ??_GRva00415AE0 0x00415C68. Names address-derived.

#include "ascii_string.h"

struct Rva0041580E
{
	~Rva0041580E();
	void *m_head00;
	int m_flag04;
};

class Rva00415AE0
{
public:
	~Rva00415AE0();

private:
	AsciiString m_name; // +0x00
	int m_04;
	Rva0041580E m_list; // +0x08
};

Rva00415AE0::~Rva00415AE0()
{
}
