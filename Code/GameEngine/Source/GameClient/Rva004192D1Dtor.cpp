// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva004192D1@@UAE@XZ @0x004192D1 59B dtor with member at +0xC plus base
// Evidence: stores vtable 0x007E7740 then calls rowed member dtor 0x0022DEE1 at +0xC then rowed base 0x001B4E74; caller 0x0022E079; same 59B EH shape as Rva004189B2.
class AsciiStringMember
{
public:
	~AsciiStringMember();
};

// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva0022DD62
{
public:
	~Rva0022DD62();
};

class Rva004192D1 : public SubsystemInterface
{
public:
	virtual ~Rva004192D1();
private:
	Rva0022DD62 m_00C;
};

Rva004192D1::~Rva004192D1() {}
