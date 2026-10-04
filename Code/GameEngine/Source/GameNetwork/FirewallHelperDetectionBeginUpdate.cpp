// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/firewall /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// FirewallHelperClass::getManglerName and detectionBeginUpdate, ported from Zero Hour's GameEngine/Source/GameNetwork/
// FirewallHelper.cpp (GeneralsMD tree vendored under reference/open-bfme-1/
// inputs/reference; the Open-BFME-1 reconstruction carries the same bodies).
// The ZH class layout is BFME 2's (target evidence: ctor 0x00594CDD news
// 0x190 bytes; m_behavior +0x04, delta +0x0C, spare sockets +0x14, manglers
// +0x54, spare ports +0x68, mangled ports +0x78, packet id +0x88, messages
// +0x8A, state +0x17C, timeout start/length +0x180/+0x184).
// Target evidence for the BFME 2 differences: sendToManglerFromPort (rowed
// 0x0059517F) takes the destination port before blitzme (4321 =
// MANGLER_PORT, 4322 for the "different destination port" sends);
// closeSpareSocket is the rowed 0x0059534A, byteAdjust the rowed 0x00594DC0
// and CRC_Memory the rowed BFMEComputeCRC; all reached through the
// address-named views the other units use.
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

// Its own unit, as in the Open-BFME-1 reconstruction: retail inlines the
// mangler-address memset (four DWORD stores) while the other detection
// updates call memset, so memset is an intrinsic here only. The empty
// string, strlen, strcpy, memcmp and memcpy stay calls, as in retail.

class Rva0059517F
{
public:
	// FirewallHelperClass::sendToManglerFromPort(address, port, packetID, destPort, blitzme)
	Bool rva0059517F(unsigned long address, UnsignedShort port, UnsignedShort packetID, UnsignedShort destPort, Bool blitzme);
};

// BFME 2's GameSpyConfigInterface keeps getManglerLocation in vslot 11
// (call [eax+0x2C]); the vendored ZH interface has it at slot 12.
class BfmeGameSpyConfigView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual Bool getManglerLocation(Int index, AsciiString& host, UnsignedShort& port) = 0;
};

// BFME 2's GlobalData firewall fields (target evidence: +0xA50 / +0xA54
// read through TheWritableGlobalData); the ZH header's offsets differ.
struct BfmeGlobalDataFirewall
{
	char m_pad000[0xA50];
	Bool m_firewallSendDelay;		// +0xA50
	char m_padA51[3];
	UnsignedInt m_firewallPortOverride;	// +0xA54
};
#define BfmeFirewallGlobals ((const BfmeGlobalDataFirewall *)TheWritableGlobalData)

static const UnsignedShort BFME_MANGLER_PORT = 4321;

#define sendToManglerFromPort(address, port, packetID, destPort) \
	(((Rva0059517F *)this)->rva0059517F((address), (port), (packetID), (destPort), FALSE))

/* static */ void FirewallHelperClass::getManglerName(Int manglerIndex, Char *nameBuf)
{
	AsciiString host;
	UnsignedShort port;
	((BfmeGameSpyConfigView *)TheGameSpyConfig)->getManglerLocation(manglerIndex, host, port);
	strcpy(nameBuf, host.str());
}

#pragma intrinsic(memset)
Bool FirewallHelperClass::detectionBeginUpdate() {
	m_packetID = 0x7f00;

	/*
	** Find the mangler servers.
	*/
	UnsignedByte mangler_addresses[4][4];
	memset(mangler_addresses, 0, sizeof mangler_addresses);

	/*
	** If there is a port override then we don't need to detect anything.
	*/
	if (BfmeFirewallGlobals->m_firewallPortOverride != 0) {
		m_behavior = FIREWALL_TYPE_SIMPLE;
		if (BfmeFirewallGlobals->m_firewallSendDelay) {
			UnsignedInt addbehavior = FIREWALL_TYPE_NETGEAR_BUG;
			addbehavior |= (UnsignedInt)m_behavior;
			m_behavior = (FirewallBehaviorType) addbehavior;
		}
		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}

	m_timeoutStart = timeGetTime();
	m_timeoutLength = 5000;

	int namenum = 0;

	do {
		AsciiString host;
		UnsignedShort port;
		((BfmeGameSpyConfigView *)TheGameSpyConfig)->getManglerLocation(namenum, host, port);
		const char *mangler_name_ptr = host.str();
		namenum++;

		if (strlen(mangler_name_ptr) == 0) {
			break;
		}

		/*
		** Resolve the mangler address.
		*/
		char temp_name[256];
		strcpy(temp_name, mangler_name_ptr);
		struct hostent *host_info = gethostbyname(temp_name);

		if (!host_info) {
			break;
		}

		/*
		** Skip addresses we already have.
		*/
		Bool found = FALSE;
		for (Int i=0 ; i<m_numManglers; i++) {
			if (memcmp(mangler_addresses[i], &host_info->h_addr_list[0][0], 4) == 0) {
				found = TRUE;
				break;
			}
		}

		if (!found) {
			Int m = m_numManglers++;
			memcpy(&mangler_addresses[m][0], &host_info->h_addr_list[0][0], 4);
			htonl((UnsignedInt)mangler_addresses[m]);
		}

	} while ((m_numManglers < MAX_NUM_MANGLERS) && ((timeGetTime() - m_timeoutStart) < m_timeoutLength));

	if (m_numManglers < 3) {
		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}

	for (Int i=0 ; i<m_numManglers ; i++) {
		UnsignedInt temp = 0;
		temp = mangler_addresses[i][3];
		temp += mangler_addresses[i][2] << 8;
		temp += mangler_addresses[i][1] << 16;
		temp += mangler_addresses[i][0] << 24;
		m_manglers[i] = temp;
	}

	if (BfmeFirewallGlobals->m_firewallSendDelay) {
		UnsignedInt addbehavior = FIREWALL_TYPE_NETGEAR_BUG;
		addbehavior |= (UnsignedInt)m_behavior;
		m_behavior = (FirewallBehaviorType) addbehavior;
	}

	m_sparePorts[0] = getNextTemporarySourcePort(0);
	if (!openSpareSocket(m_sparePorts[0])) {
		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}

	/*
	** Send to the mangler from this port until we get a response.
	*/
	m_timeoutStart = timeGetTime();
	m_timeoutLength = 6000;

	sendToManglerFromPort(m_manglers[0], m_sparePorts[0], m_packetID, BFME_MANGLER_PORT);
	m_currentState = DETECTIONSTATE_TEST1;
	return FALSE;
}
