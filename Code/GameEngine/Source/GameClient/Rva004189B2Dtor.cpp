// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022A968Subsystem@@UAE@XZ @0x004189B2 59B dtor with member at +0xC plus base
// Evidence: stores vtable 0x007E7708 then calls rowed member dtor 0x0022DEA8 at +0xC then rowed base 0x001B4E74; caller 0x0022E026; abuts next 0x004189ED; prev Rva0041811DGet flags.
// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva0022DD19
{
public:
	~Rva0022DD19();
};

class Rva0022A968Subsystem : public SubsystemInterface
{
public:
	virtual ~Rva0022A968Subsystem();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
private:
	Rva0022DD19 m_00C;
};

Rva0022A968Subsystem::~Rva0022A968Subsystem() {}
