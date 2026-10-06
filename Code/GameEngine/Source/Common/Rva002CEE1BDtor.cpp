// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva002CEE1B@@UAE@XZ, RVA 0x002CEE1B, 72 bytes.
// Dtor via vtable 0x00802244 plus ehvec array at +0x0C plus rowed base
// GameEngineDeletingBase dtor 0x001B4E74. Evidence: EH_prolog plus vtable
// store plus ??_M 0x00629110 with 0x80 0x1C plus base dtor plus caller
// deleting dtor 0x002CEEE6. Flags /O1 /MD /EHsc for EH frame.
#include "ascii_string.h"

struct Elem002CEE1B
{
	AsciiString m_str;
	char m_pad[24];
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

class Rva002CEE1B : public GameEngineDeletingBase
{
public:
	virtual ~Rva002CEE1B();

private:
	char m_pad04[0x0C - 4];
	Elem002CEE1B m_arr0C[128];
};

Rva002CEE1B::~Rva002CEE1B()
{
}
