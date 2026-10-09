// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ??1AwardSystemManager@@UAE@XZ @ 0x0040BFAA (74B). Dtor with vtable 0x008392E0 calling two vector dtors then base.
// Evidence: retail stores vtable 0x00C392E0 then calls rowed 0x0040B59F at +0x18 and 0x0040BEBA at +0x0C then rowed SubsystemInterface 0x001B4E74; caller 0x0040C0AB deleting dtor.
// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

struct Rva0040B59F
{
	~Rva0040B59F();
	char m_data[12];
};

struct Rva0040BEBA
{
	~Rva0040BEBA();
	char m_data[12];
};

class AwardSystemManager : public SubsystemInterface
{
public:
	virtual ~AwardSystemManager();
private:
	Rva0040BEBA m_0C;
	Rva0040B59F m_18;
};

AwardSystemManager::~AwardSystemManager()
{
}
