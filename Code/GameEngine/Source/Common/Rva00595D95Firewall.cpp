// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_firewallhelper /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/inputs/reference/shims/firewall /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// ?rva00595D95@Rva00595D95@@QAE_NXZ @0x00595D95 177B evidence: FirewallNeedToRefresh TRUE strings plus TheWritableGlobalData firewallBehavior+0xA4C via OptionPreferences find; callers 0x005182DE 0x00519C83 0x00572506; nonthrowing compare preserves the temporary cleanup state
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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

// Retail compares the temporary TRUE value without another EH state.
template <> int StringBase<char>::compareNoCase(const char *) const throw();

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

class Rva00595D95
{
public:
	bool rva00595D95();
private:
	char m_pad00[4];
	int m_04;
	char m_pad08[0x174];
	int m_17C;
};

bool Rva00595D95::rva00595D95()
{
	OptionPreferences prefs;
	OptionPreferences::const_iterator it = prefs.find("FirewallNeedToRefresh");
	if (it != prefs.end()) {
		AsciiString val = it->second;
		if (val.compareNoCase("TRUE") == 0)
			((BfmeGlobalDataFirewall *)TheWritableGlobalData)->m_firewallBehavior = false;
	}
	if (((BfmeGlobalDataFirewall *)TheWritableGlobalData)->m_firewallBehavior == 0) {
		m_04 = 1;
		m_17C = 1;
		return false;
	}
	return true;
}
