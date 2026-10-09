// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva002CEE1B@@UAE@XZ, RVA 0x002CEE1B, 72 bytes.
// Dtor via vtable 0x00802244 plus ehvec array at +0x0C plus rowed base
// SubsystemInterface dtor 0x001B4E74. Evidence: EH_prolog plus vtable
// store plus ??_M 0x00629110 with 0x80 0x1C plus base dtor plus caller
// deleting dtor 0x002CEEE6. Flags /O1 /MD /EHsc for EH frame.
#include "ascii_string.h"

struct Elem002CEE1B
{
	AsciiString m_str;
	char m_pad[24];
};

// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva002CEE1B : public SubsystemInterface
{
public:
	virtual ~Rva002CEE1B();

private:
	Elem002CEE1B m_arr0C[128];
};

Rva002CEE1B::~Rva002CEE1B()
{
}
