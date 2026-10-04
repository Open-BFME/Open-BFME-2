// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ??1Rva005D4913@@QAE@XZ @0x005D4913 54B: non-virtual dtor destroying AsciiString at +8 and Rva0052413E at +0xC. Evidence: EH prolog with two member-dtor calls in retail order plus deleting-dtor caller 0x005D49DD plus holder caller 0x005D4BE7.
#include "ascii_string.h"

class Rva0052413E
{
public:
	~Rva0052413E();
};

class Rva005D4913
{
public:
	~Rva005D4913();
private:
	char m_pad00[8];
	AsciiString m_08;
	Rva0052413E m_0C;
};
Rva005D4913::~Rva005D4913()
{
}
