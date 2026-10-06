// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// ??1Rva005F6051@@QAE@XZ @0x005F6051 69B
// Destructor destroying members in reverse declaration order: vector-like
// member at +0x18 through rowed 0x005242D7, vector-like member at +0xC through
// rowed 0x0052413E, AsciiString at +8 through releaseBuffer 0x00036410.
// Evidence: member offsets from the lea sequence; states 1/0/-1 and
// __EH_prolog from three unwindable members under /EHsc; name pinned as the
// pointee dtor called by 0x005F64DB; rowed member dtors reused by exact name.
#include "ascii_string.h"

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva005F6051
{
public:
	~Rva005F6051();
private:
	int m_00;
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	Rva005242D7 m_18;
};

Rva005F6051::~Rva005F6051()
{
}
