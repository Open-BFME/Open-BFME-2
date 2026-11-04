// cl: /DNDEBUG /MD /EHsc
// ?rva00411523@Rva00411523@@SAXXZ, retail 0x00411523 (44B).
// Eva-table walk over global at 0x00E02FE4 via pinned first 0x00427195 and
// rowed next 0x00411084, clearing byte at node+0x2C. Same first/next shape
// as ?messageToName@Eva in EvaMessageName.cpp; owner unproven so
// honest-address class; static, as the walk never reads ecx and its sole
// caller 0x0022244D calls it with no this setup.

#include "../../Include/GameClient/Rva000411084.h"

#include "../../Include/GameLogic/Rva000427195.h"


// VA 0x00E02FE4: the component-window table AptComponentWindowLookup.cpp owns.
extern unsigned int AptComponentWindowDataTableStorage[5];

struct Rva00411523Node
{
	char m_pad[0x2C];
	unsigned char m_flag2C;
};

class Rva00411523
{
public:
	static void rva00411523();
};

void Rva00411523::rva00411523()
{
	Rva000411084 iter;
	reinterpret_cast<Rva000427195 *>(AptComponentWindowDataTableStorage)->first(&iter);
	while (iter.m_current != 0) {
		((Rva00411523Node *)iter.m_current)->m_flag2C = 0;
		iter.next();
	}
}
