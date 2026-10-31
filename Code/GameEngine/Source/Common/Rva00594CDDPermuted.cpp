// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_firewallhelper /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/inputs/reference/shims/firewall /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ??0FirewallHelperClass@@QAE@XZ, retail 0x00594cdd, 154 bytes. Banked partial (score 0.92) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Evidence: vtable 0x00870A2C at [this]; layout matches ZH FirewallHelper.h (spareSockets 8x8 at +0x14, manglers 4 at +0x54, sparePorts/mangledPorts at +0x68/+0x78, packetID +0x88, messages 8x30 at +0x8A length at +0x14, state/timeouts at +0x17C..+0x18C); timeGetTime IAT + div/div static m_sourcePortPool; caller 0x00595143.
// stlport
// The dtor (row 0x00595390, Rva00595D0BFirewall.cpp) is reset() 0x0059515C; retail's
// ??1FirewallHelperClass@@UAE@XZ present-unmatched
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/crc.h"
#include "Common/UserPreferences.h"
#include "GameNetwork/FirewallHelper.h"
#include "GameNetwork/NAT.h"
#include "GameNetwork/udp.h"
#include "GameNetwork/NetworkDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"

struct Rva0059510DEntry
{
	UDP *ptr;
	unsigned short flag;
	char _pad[2];
};

class Rva0059510D
{
public:
	void rva0059510D();
private:
	char m_lead[0x14];
	Rva0059510DEntry m_entries[8];
};

class Rva0059515C : public Rva0059510D
{
public:
	void rva0059515C();
private:
	char m_pad54[0x36];
	ManglerMessage m_messages[8];
	FirewallDetectionState m_currentState;
};

// The dtor (row 0x00595390, FirewallHelperClass.cpp) is reset() 0x0059515C; retail's
// vtable ??_G (0x00595D0B) inlines it, so this view must see the same body.
#ifndef FIREWALLHELPER_DESTRUCTOR_OUT_OF_LINE
inline FirewallHelperClass::~FirewallHelperClass(void)
{
	((Rva0059515C *)this)->rva0059515C();
}
#endif

FirewallHelperClass::FirewallHelperClass(void) throw()
{
	m_currentTry = 0;
	m_numManglers = 0;
	m_numResponses = 0;
	m_packetID = 0;
	m_timeoutLength = 0;
	m_timeoutStart = 0;
	m_behavior = FIREWALL_TYPE_UNKNOWN;
	m_lastBehavior = FIREWALL_TYPE_UNKNOWN;
	m_sourcePortAllocationDelta = 0;
	m_lastSourcePortAllocationDelta = 0;
	for (int i = 0; i < 8; i++)
	{
		m_spareSockets[i].port = 0;
		m_mangledPorts[i] = 0;
		m_spareSockets[i].udp = 0;
		m_messages[i].length = 0;
		m_sparePorts[i] = 0;
	}
	for (int i = 0; 4 > i; ++i)
		m_manglers[i] = 0;
	m_currentState = DETECTIONSTATE_IDLE;
	m_sourcePortPool = timeGetTime() / 1000 % 1000 + 0x1000;
}
