// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_firewallhelper /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/inputs/reference/shims/firewall /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// ?rva0059534A@Rva0059534A@@QAEXG@Z @0x0059534A 70B evidence: callees UDP dtor 0x00594918 operator delete 0x0002FD60 rowed; 12 callers; prev Disp8Word next Rva0025BFE3Derived

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/crc.h"
#include "Common/UserPreferences.h"
#include "GameNetwork/FirewallHelper.h"
#include "GameNetwork/NAT.h"
#include "GameNetwork/udp.h"
#include "GameNetwork/NetworkDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"

class Rva0059534A
{
private:
	struct Slot { UDP *ptr; unsigned short key; char m_padKey[2]; };
public:
	void rva0059534A(unsigned short port); // FirewallHelperClass::closeSpareSocket
	char m_pad00[0x14];
private:
	Slot m_slots[8]; // +0x14
};

void Rva0059534A::rva0059534A(unsigned short key)
{
    for (int i = 0; i < 8; ++i) {
        if (m_slots[i].key == key) {
            UDP *p = m_slots[i].ptr;
            if (p != 0) {
                delete p;
                m_slots[i].ptr = 0;
            }
            m_slots[i].key = 0;
            break;
        }
    }
}
