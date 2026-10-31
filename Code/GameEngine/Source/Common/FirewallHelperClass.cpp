// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_firewallhelper /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/inputs/reference/shims/firewall /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// FirewallHelperClass's virtual destructor and the scalar deleting destructor
// that fills the only slot of its one-slot vftable 0x00C70A2C (VA; installed
// at +0 by the constructor 0x00594CDD). ZH FirewallHelper.h declares
// virtual ~FirewallHelperClass() as the class's only virtual, and ZH
// FirewallHelper.cpp defines it as { reset(); }.
//
// ??1FirewallHelperClass@@UAE@XZ @0x00595390 10B: restores the vtable and
// tail-jumps to reset (rowed at 0x0059515C under its address name). Retail
// keeps this out-of-line copy although no code calls it.
// ??_GFirewallHelperClass@@UAEPAXI@Z @0x00595D0B 34B: the compiler-generated
// scalar deleting destructor with the destructor expanded inline (vtable
// store, reset), then operator delete (0x0002FD60) when bit 0 of the flags
// is set; returns this (ret 4). Only the vftable reaches it.
//
// Evidence for reset: 0x0059515C calls 0x0059510D (closeAllSpareSockets in
// the ZH order), zeroes the state at +0x17C and clears the eight message
// lengths (stride 0x1E from +0x9E), which is ZH reset() on this layout.

// The unit holding the out-of-line destructor: Rva00594CDDPermuted.cpp's inline
// copy of it, which that unit's own ??_G needs, stands aside here.
#define FIREWALLHELPER_DESTRUCTOR_OUT_OF_LINE
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

FirewallHelperClass::~FirewallHelperClass(void)
{
	// FirewallHelperClass::reset(), rowed under its address name.
	((Rva0059515C *)this)->rva0059515C();
}
