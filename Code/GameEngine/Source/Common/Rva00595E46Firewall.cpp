// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_firewallhelper /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/inputs/reference/shims/firewall /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// ?Rva00595E46Save@@YAXXZ @0x00595E46 314B evidence: FirewallBehavior 0x7EB734 plus FirewallPortAllocationDelta 0x7EB700 strings via OptionPreferences map plus TheWritableGlobalData firewallBehavior+0xA4C and delta+0xA58 via g_a063b0 plus UserPreferences write; callers 0x00518324 0x00519CCC 0x005700D4
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

// Declaration-only: the rowed map<AsciiString,AsciiString>::operator[] is bound,
// this TU emits no per-flag copy of it or of the tree internals it pulls in.
namespace _STL {
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>, allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &);
}

// BFME 2's GlobalData firewall fields (target evidence: +0xA4C to +0xA58 read
// and written through TheWritableGlobalData); the ZH header's offsets differ.
struct BfmeGlobalDataFirewall
{
	char m_pad000[0xA4C];
	Int m_firewallBehavior;			// +0xA4C
	Bool m_firewallSendDelay;		// +0xA50
	char m_padA51[3];
	UnsignedInt m_firewallPortOverride;	// +0xA54
	Short m_firewallPortAllocationDelta;	// +0xA58
	char m_padA5A[0x2];
};

struct Rva00A063B0Obj
{
	void *m_vtbl;
	Int m_04;
	char m_pad08[4];
	Short m_0C;
	char m_pad0E[0x17C - 0x0E];
	Int m_17C;
};

extern struct Rva00A063B0Obj *g_a063b0;

void Rva00595E46Save(void)
{
	OptionPreferences prefs;
	Rva00A063B0Obj *info = g_a063b0;
	char num[16];
	num[0] = 0;
	info->m_17C = 0;
	((BfmeGlobalDataFirewall *)TheWritableGlobalData)->m_firewallBehavior = info->m_04;
	_itoa(((BfmeGlobalDataFirewall *)TheWritableGlobalData)->m_firewallBehavior, num, 10);
	AsciiString numstr;
	numstr = num;
	{
		AsciiString key("FirewallBehavior");
		AsciiString &slot = prefs[key];
		slot = numstr;
	}
	((BfmeGlobalDataFirewall *)TheWritableGlobalData)->m_firewallPortAllocationDelta = g_a063b0->m_0C;
	num[0] = 0;
	_itoa(((BfmeGlobalDataFirewall *)TheWritableGlobalData)->m_firewallPortAllocationDelta, num, 10);
	numstr = num;
	{
		AsciiString key("FirewallPortAllocationDelta");
		AsciiString &slot = prefs[key];
		slot = numstr;
	}
	prefs.write();
}

// Native OptionPreferences table C04CE8 slot0 -> deleting body2E42D2
// -> complete destructor2E4272. Keep this binding separate from the local view.
#pragma comment(linker, "/alternatename:??1OptionPreferences@@UAE@XZ=??1Rva002E4272@@UAE@XZ")
