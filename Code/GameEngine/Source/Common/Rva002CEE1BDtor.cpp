// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva002CEE1B@@UAE@XZ, RVA 0x002CEE1B, 72 bytes.
// Dtor via vtable 0x00802244 plus ehvec array at +0x0C plus rowed base
// SubsystemInterface dtor 0x001B4E74. Evidence: EH_prolog plus vtable
// store plus ??_M 0x00629110 with 0x80 0x1C plus base dtor plus caller
// deleting dtor 0x002CEEE6. Flags /O1 /MD /EHsc for EH frame.
#include "ascii_string.h"

// The array's element (0x1C bytes). Retail's ??_M at 0x00629110 is given
// 0x000B3FD0, a bare ret, as the element destructor: an element owns nothing
// it releases. RayEffectSystem::addRayEffect (0x002CED84) fills the slots.
// An AsciiString at +0 here had the image release each slot's first word
// at teardown (P102).
struct Elem002CEE1B
{
	~Elem002CEE1B() {}

	void *m_word00;
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
