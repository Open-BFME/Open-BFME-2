// ?rva00594F19@Rva00594F19@@QAEHHPAG0AAHAA_N@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/firewall /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// FirewallHelperClass's mangler-response reader and NAT detection state
// updates, ported from Zero Hour's GameEngine/Source/GameNetwork/
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

unsigned int __cdecl BFMEComputeCRC(const unsigned char *data, unsigned int len, unsigned int seed);

struct Rva00594DC0Msg;

class Rva00594DC0
{
public:
	void rva00594DC0(Rva00594DC0Msg *msg); // FirewallHelperClass::byteAdjust
};

class Rva0059534A
{
public:
	void rva0059534A(UnsignedShort port); // FirewallHelperClass::closeSpareSocket
};

class Rva0059517F
{
public:
	// FirewallHelperClass::sendToManglerFromPort(address, port, packetID, destPort, blitzme)
	Bool rva0059517F(unsigned long address, UnsignedShort port, UnsignedShort packetID, UnsignedShort destPort, Bool blitzme);
};

// FirewallHelperClass::getNATPortAllocationScheme with BFME 2's signature:
// relativeDelta became an Int with a third value (2: the mangled ports'
// own deltas grow by a constant step), which the vendored ZH header's
// Bool& declaration cannot name, so it lives on an address-named view.
class Rva00594F19
{
public:
	Int rva00594F19(Int numPorts, UnsignedShort *originalPorts, UnsignedShort *mangledPorts, Int &relativeDelta, Bool &looksGood);
};

static const UnsignedShort BFME_MANGLER_PORT = 4321;
// BFME 2's behavior enum has one more flag before it: retail ORs in 0x80.
static const UnsignedInt BFME_FIREWALL_TYPE_DESTINATION_PORT_DELTA = 128;

#define closeSpareSocket(port) (((Rva0059534A *)this)->rva0059534A(port))
#define sendToManglerFromPort(address, port, packetID, destPort) \
	(((Rva0059517F *)this)->rva0059517F((address), (port), (packetID), (destPort), FALSE))
#define byteAdjust(data) (((Rva00594DC0 *)this)->rva00594DC0((Rva00594DC0Msg *)(data)))

/* static */ Int FirewallHelperClass::m_sourcePortPool = 4096;

UnsignedShort FirewallHelperClass::getNextTemporarySourcePort(Int skip)
{
	UnsignedShort return_port = (UnsignedShort) m_sourcePortPool;

	/*
	** Try max 256 ports until we find one we can bind to a socket.
	*/
	Int tries = 256;
	if (skip == 0) {
		skip = 1;
	}

	while (tries--) {

		m_sourcePortPool += skip;
		return_port = (UnsignedShort) m_sourcePortPool;

		if (m_sourcePortPool > 65535) {
			// BFME 2 wraps to 8088 (target evidence), Zero Hour to 2048.
			m_sourcePortPool = 8088;
		}

		/*
		** Bind a socket to the port to see if it's free.
		*/
		Bool result = openSpareSocket(return_port);

		if (result) {
			closeSpareSocket(return_port);
			return(return_port);
		}
	}

	return(return_port);

}

Int Rva00594F19::rva00594F19(Int numPorts, UnsignedShort *originalPorts, UnsignedShort *mangledPorts, Int &relativeDelta, Bool &looksGood)
{
	Int diff1 = mangledPorts[1] - mangledPorts[0];
	Int diff2 = mangledPorts[2] - mangledPorts[1];
	Int diff3 = mangledPorts[3] - mangledPorts[2];

	if (diff1 == diff2 && diff2 == diff3) {
		relativeDelta = 0;
		looksGood = TRUE;
		return(diff1);
	}

	if (diff1 == diff2) {
		relativeDelta = 0;
		looksGood = FALSE;
		return(diff1);
	}

	if (diff2 == diff3) {
		relativeDelta = 0;
		looksGood = FALSE;
		return(diff2);
	}

	/*
	** See if the mangled ports keep a constant offset from the source ports.
	*/
	Int deltas[NUM_TEST_PORTS];
	for (Int i=0 ; i<numPorts ; i++) {
		deltas[i] = mangledPorts[i] - originalPorts[i];
	}

	diff1 = deltas[1] - deltas[0];
	diff2 = deltas[2] - deltas[1];
	diff3 = deltas[3] - deltas[2];

	if (diff1 == diff2 && diff2 == diff3) {
		relativeDelta = 1;
		looksGood = TRUE;
		return(diff1);
	}

	if (diff1 == diff2 || diff1 == diff3) {
		relativeDelta = 1;
		looksGood = FALSE;
		return(diff1);
	}

	if (diff2 == diff3) {
		relativeDelta = 1;
		looksGood = FALSE;
		return(diff2);
	}

	/*
	** BFME 2: the mangled ports' deltas themselves grow by a constant step.
	*/
	diff1 = mangledPorts[1] - mangledPorts[0];
	diff2 = mangledPorts[2] - mangledPorts[1];
	diff3 = mangledPorts[3] - mangledPorts[2];
	if (diff2 - diff1 == diff3 - diff2) {
		relativeDelta = 2;
		looksGood = TRUE;
		return(diff1);
	}

	looksGood = FALSE;
	relativeDelta = 0;
	return(0);
}

UnsignedShort FirewallHelperClass::getManglerResponse(UnsignedShort packetID, Int time)
{
	ManglerMessage *msg = NULL;

	sockaddr_in addr;

	for (Int i = 0; i < MAX_SPARE_SOCKETS; ++i) {
		UDP *udp = m_spareSockets[i].udp;
		if (udp != NULL) {
			ManglerMessage *message = findEmptyMessage();
			if (message == NULL) {
				break;
			}
			Int retval = udp->Read((unsigned char *)message, sizeof(ManglerData), &addr);
			if (retval > 0) {
				UnsignedInt crc = BFMEComputeCRC((const unsigned char *)(&(message->data.magic)), sizeof(ManglerData) - sizeof(unsigned int), 0);
				if (crc != htonl(message->data.CRC)) {
					continue;
				}
				byteAdjust(&(message->data));
				message->length = retval;
				if (message->data.PacketID == packetID) {
					msg = message;
					message->length = 0;
				}
				if (htons(message->data.PacketID) == packetID) { // retail imports htons here (same swap)
					msg = message;
					message->length = 0;
				}
			}
		}
	}

	// See if we have already received it and saved it.
	if (msg == NULL) {
		for (i = 0; i < MAX_SPARE_SOCKETS; ++i) {
			if ((m_messages[i].length != 0) && (m_messages[i].data.PacketID == packetID)) {
				msg = &(m_messages[i]);
				msg->length = 0;
			}
		}
	}

	if (msg == NULL) {
		return 0;
	}

	UnsignedShort mangled_port = msg->data.MyMangledPortNumber;
	return mangled_port;
}

Bool FirewallHelperClass::detectionTest1Update() {

	m_mangledPorts[0] = getManglerResponse(m_packetID);

	/*
	** See if we got no response or a non-mangled response.
	*/
	if (m_mangledPorts[0] == 0 || m_mangledPorts[0] == m_sparePorts[0]) {
		if (m_mangledPorts[0] == m_sparePorts[0]) {
			m_sourcePortAllocationDelta = 0;
		}
		if ((m_mangledPorts[0] == 0) && ((timeGetTime() - m_timeoutStart) < m_timeoutLength)) {
			// we are still waiting for a response and haven't timed out yet.
			return FALSE;
		}
		if ((m_mangledPorts[0] == 0) && ((timeGetTime() - m_timeoutStart) >= m_timeoutLength)) {
			// we are still waiting for a response and we timed out.
		}
		// either we have received a non-mangled response or we timed out waiting for a response.
		closeSpareSocket(m_sparePorts[0]);

		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}

	/*
	** Send to the mangler from this port until we get a response.
	*/
	m_timeoutStart = timeGetTime();
	m_timeoutLength = 6000;
	m_mangledPorts[1] = 0;
	sendToManglerFromPort(m_manglers[1], m_sparePorts[0], m_packetID+1, BFME_MANGLER_PORT);

	m_currentState = DETECTIONSTATE_TEST2;
	return FALSE;
}

Bool FirewallHelperClass::detectionTest2Update() {

	m_mangledPorts[1] = getManglerResponse(m_packetID+1);

	if (m_mangledPorts[1] == 0) {
		if ((timeGetTime() - m_timeoutStart) <= m_timeoutLength) {
			return FALSE;
		}
		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}

	/*
	** We are done with this socket/port
	*/
	closeSpareSocket(m_sparePorts[0]);

	/*
	** See if we got no response or a non-mangled response.
	*/
	if (m_mangledPorts[1] == m_sparePorts[0]) {
		UnsignedInt addBehavior = (UnsignedInt)FIREWALL_TYPE_SIMPLE;
		addBehavior |= (UnsignedInt)m_behavior;
		m_behavior = (FirewallBehaviorType)addBehavior;
		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}

	// BFME 2 (target evidence): a mangling firewall is no longer simple.
	m_behavior = (FirewallBehaviorType)((UnsignedInt)m_behavior & ~(UnsignedInt)FIREWALL_TYPE_SIMPLE);

	if (m_mangledPorts[0] == m_mangledPorts[1]) {
		UnsignedInt addBehavior = (UnsignedInt)FIREWALL_TYPE_DUMB_MANGLING;
		addBehavior |= (UnsignedInt)m_behavior;
		m_behavior = (FirewallBehaviorType)addBehavior;
	} else {
		UnsignedInt addBehavior = (UnsignedInt)FIREWALL_TYPE_SMART_MANGLING;
		addBehavior |= (UnsignedInt)m_behavior;
		m_behavior = (FirewallBehaviorType)addBehavior;
	}

	m_currentTry = 0;
	m_packetID = m_packetID + 10;

	m_currentState = DETECTIONSTATE_TEST3;
	return FALSE;
}

Bool FirewallHelperClass::detectionTest3Update() {
	/*
	** Try this whole thing a max of 3 times.
	*/
	if (m_currentTry < 3) {
		memset(m_sparePorts, 0, sizeof(m_sparePorts));
		memset(m_mangledPorts, 0, sizeof(m_mangledPorts));

		/*
		** Open a socket for each source port.
		*/
		for (Int i=0 ; i<NUM_TEST_PORTS ; i++) {
			m_sparePorts[i] = getNextTemporarySourcePort(i);
			if (!openSpareSocket(m_sparePorts[i])) {

				/*
				** Close any spare ports we allocated already before we bail.
				*/
				for (Int j=0 ; j<i ; j++) {
					if (m_sparePorts[j]) {
						closeSpareSocket(m_sparePorts[j]);
					}
				}
				m_currentState = DETECTIONSTATE_DONE;
				return TRUE;
			}
		}

		m_timeoutStart = timeGetTime();
		m_timeoutLength = 12000;

		for (i=0 ; i<NUM_TEST_PORTS ; i++) {
			if (m_mangledPorts[i] == 0) {
				sendToManglerFromPort(m_manglers[0], m_sparePorts[i], m_packetID+i, BFME_MANGLER_PORT);
			}
		}

		m_numResponses = 0;

		m_currentState = DETECTIONSTATE_TEST3_WAITFORRESPONSES;
		return FALSE;
	}

	m_currentState = DETECTIONSTATE_DONE;
	return TRUE;
}

Bool FirewallHelperClass::detectionTest3WaitForResponsesUpdate() {
	for (Int i = 0; i < NUM_TEST_PORTS; ++i) {
		if (m_mangledPorts[i] == 0) {
			m_mangledPorts[i] = getManglerResponse(m_packetID + i);
			if (m_mangledPorts[i] != 0) {
				++m_numResponses;
			}
		}
	}

	if (m_numResponses < NUM_TEST_PORTS) {
		if ((timeGetTime() - m_timeoutStart) > m_timeoutLength) {
			/*
			** Close down those sockets - we are finished with them.
			*/
			for (Int j=0 ; j<i ; j++) {
				if (m_spareSockets[j].port != 0) {
					closeSpareSocket(m_spareSockets[j].port);
				}
			}
			m_currentState = DETECTIONSTATE_DONE;
			return TRUE;
		}
		return FALSE;
	}

	/*
	** Close down those sockets - we are finished with them.
	*/
	for (Int j=0 ; j<i ; j++) {
		if (m_spareSockets[j].port != 0) {
			closeSpareSocket(m_spareSockets[j].port);
		}
	}

	/*
	** We need at least 4 responses to be sure of the port allocation scheme.
	*/
	if (m_numResponses < 4) {
		if (m_lastSourcePortAllocationDelta != 0 && (int)m_lastBehavior > (int)FIREWALL_TYPE_SIMPLE) {
			/*
			** If the delta we got last time we played looks good then use that.
			*/
			m_sourcePortAllocationDelta = m_lastSourcePortAllocationDelta;
		}
		m_currentState = DETECTIONSTATE_DONE;
		return TRUE;
	}


	Int relative_delta = 0;
	Bool looks_good;
	Int delta = ((Rva00594F19 *)this)->rva00594F19(m_numResponses, m_sparePorts, m_mangledPorts, relative_delta, looks_good);

	if (delta) {

		/*
		** Hey, we got it!
		*/
		UnsignedInt addbehavior = 0;
		if (relative_delta == 1) {
			addbehavior = (UnsignedInt)FIREWALL_TYPE_RELATIVE_PORT_ALLOCATION;
		} else if (relative_delta == 2) {
			// BFME 2's third scheme: no longer simple, and both of its new
			// high behavior flags (0x40 | 0x80) are set.
			m_behavior = (FirewallBehaviorType)((UnsignedInt)m_behavior & ~(UnsignedInt)FIREWALL_TYPE_SIMPLE);
			addbehavior = 0xC0;
		} else {
			addbehavior = (UnsignedInt)FIREWALL_TYPE_SIMPLE_PORT_ALLOCATION;
		}
		addbehavior |= (UnsignedInt)m_behavior;
		m_behavior = (FirewallBehaviorType) addbehavior;

		m_sourcePortAllocationDelta = delta;
	} else {
		if (m_lastSourcePortAllocationDelta != 0 && (Int)m_lastBehavior > (Int)FIREWALL_TYPE_SIMPLE) {
			/*
			** If the delta we got last time we played looks good then use that.
			*/
			m_sourcePortAllocationDelta = m_lastSourcePortAllocationDelta;
		}
		++m_currentTry;
		m_currentState = DETECTIONSTATE_TEST3;
		return FALSE;
	}

	/*
	** Fourth test.
	**
	** Test to see if the NAT mangles differently per destination port at the same IP.
	*/
	if ((m_behavior & FIREWALL_TYPE_SMART_MANGLING) != 0) {

		if ((m_behavior & FIREWALL_TYPE_SIMPLE_PORT_ALLOCATION) != 0) {

			/*
			** We need 2 source ports for this.
			*/
			m_sparePorts[0] = getNextTemporarySourcePort(0);
			if (!openSpareSocket(m_sparePorts[0])) {
				m_currentState = DETECTIONSTATE_DONE;
				return TRUE;
			}

			m_sparePorts[1] = getNextTemporarySourcePort(0);
			if (!openSpareSocket(m_sparePorts[1])) {
				closeSpareSocket(m_sparePorts[0]);
				m_currentState = DETECTIONSTATE_DONE;
				return TRUE;
			}

			/*
			** Get a reference port.
			*/
			m_timeoutStart = timeGetTime();
			m_timeoutLength = 4000;
			m_mangledPorts[0] = 0;
			m_packetID += 10;

			/*
			** Wait for a response.
			*/
			sendToManglerFromPort(m_manglers[0], m_sparePorts[0], m_packetID, BFME_MANGLER_PORT);

			m_currentState = DETECTIONSTATE_TEST4_1;
			return FALSE;
		} else {
			/*
			** NAT32 uses different mangled source ports for different destination ports.
			*/
			UnsignedInt addbehavior = 0;
			addbehavior = BFME_FIREWALL_TYPE_DESTINATION_PORT_DELTA;
			addbehavior |= (UnsignedInt)m_behavior;
			m_behavior = (FirewallBehaviorType) addbehavior;
		}
	}

	m_currentState = DETECTIONSTATE_TEST5;
	return FALSE;
}

Bool FirewallHelperClass::detectionTest4Stage1Update() {
	m_mangledPorts[0] = getManglerResponse(m_packetID);

	if (m_mangledPorts[0] == 0) {
		if ((timeGetTime() - m_timeoutStart) > m_timeoutLength) {
			closeSpareSocket(m_sparePorts[0]);
			closeSpareSocket(m_sparePorts[1]);
			m_currentState = DETECTIONSTATE_DONE;
			return TRUE;
		}
		return FALSE;
	}

	/*
	** Send out to a different port at that IP.
	** We won't get a response for this.
	*/
	UnsignedInt addr = m_manglers[0];
	UnsignedShort port1 = BFME_MANGLER_PORT + 1;
	sendToManglerFromPort(addr, m_sparePorts[0], m_packetID, port1);
	sendToManglerFromPort(addr, m_sparePorts[0], m_packetID, port1);
	sendToManglerFromPort(addr, m_sparePorts[0], m_packetID, port1);

	m_packetID++;
	m_timeoutStart = timeGetTime();
	m_timeoutLength = 4000;

	sendToManglerFromPort(m_manglers[0], m_sparePorts[1], m_packetID, BFME_MANGLER_PORT);

	m_currentState = DETECTIONSTATE_TEST4_2;
	return FALSE;
}

Bool FirewallHelperClass::detectionTest4Stage2Update() {
	m_mangledPorts[1] = getManglerResponse(m_packetID);

	if (m_mangledPorts[1] == 0) {
		if ((timeGetTime() - m_timeoutStart) > m_timeoutLength) {
			closeSpareSocket(m_sparePorts[0]);
			closeSpareSocket(m_sparePorts[1]);
			m_currentState = DETECTIONSTATE_DONE;
			return TRUE;
		}
		return FALSE;
	}

	if (m_mangledPorts[1] != m_mangledPorts[0] + m_sourcePortAllocationDelta) {
		UnsignedInt addbehavior = 0;
		addbehavior = BFME_FIREWALL_TYPE_DESTINATION_PORT_DELTA;
		addbehavior |= (UnsignedInt)m_behavior;
		m_behavior = (FirewallBehaviorType) addbehavior;
	}

	// BFME 2 has no fifth test: the detection is done here.
	m_currentState = DETECTIONSTATE_DONE;
	return TRUE;
}
