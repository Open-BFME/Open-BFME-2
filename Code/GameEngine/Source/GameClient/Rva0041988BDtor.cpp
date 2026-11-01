// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022A8F3Subsystem@@UAE@XZ @0x0041988B 59B dtor with member at +0xC plus base
// Evidence: stores vtable 0x007E7778 then calls rowed member dtor 0x0022DF1A at +0xC then rowed base 0x001B4E74; caller 0x0022E0CC; same 59B EH shape as Rva004189B2.
// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva0022DDAB
{
public:
	~Rva0022DDAB();
};

class Rva0022A8F3Subsystem : public SubsystemInterface
{
public:
	virtual ~Rva0022A8F3Subsystem();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
private:
	Rva0022DDAB m_00C;
};

Rva0022A8F3Subsystem::~Rva0022A8F3Subsystem() {}
