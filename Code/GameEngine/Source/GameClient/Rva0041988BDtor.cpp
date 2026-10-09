// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0041988B@@UAE@XZ @0x0041988B 59B dtor with member at +0xC plus base
// Evidence: stores vtable 0x007E7778 then calls rowed member dtor 0x0022DF1A at +0xC then rowed base 0x001B4E74; caller 0x0022E0CC; same 59B EH shape as Rva004189B2.
class AsciiStringMember
{
public:
	~AsciiStringMember();
};

// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva0022DDAB
{
public:
	~Rva0022DDAB();
};

class Rva0041988B : public SubsystemInterface
{
public:
	virtual ~Rva0041988B();
private:
	Rva0022DDAB m_00C;
};

Rva0041988B::~Rva0041988B() {}
