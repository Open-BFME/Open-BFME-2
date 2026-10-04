// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/firewall -Ireference/open-bfme-1/inputs/reference/shims/ini -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////


/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /RedAlert2/NAT.CPP                                          $*
 *                                                                                             *
 *                      $Author:: Steve_t                                                     $*
 *                                                                                             *
 *                     $Modtime:: 3/15/01 12:00PM                                             $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 *                                                                                             *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 *                                                                                             *
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/crc.h"
#include "Common/UserPreferences.h"
#include "GameNetwork/FirewallHelper.h"
#include "GameNetwork/NAT.h"
#include "GameNetwork/udp.h"
#include "GameNetwork/NetworkDefs.h"
#include "GameNetwork/GameSpy/GSConfig.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//
// ?behaviorDetectionUpdate@FirewallHelperClass@@QAE_NXZ
// retail 0x00595D2D, 104 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/FirewallHelper.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /Os it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.

Bool FirewallHelperClass::behaviorDetectionUpdate()
{
	if (m_currentState == DETECTIONSTATE_IDLE) {
		return FALSE;
	}

	if (m_currentState == DETECTIONSTATE_DONE) {
		return TRUE;
	}

	if (m_currentState == DETECTIONSTATE_BEGIN) {
		return detectionBeginUpdate();
	}

	if (m_currentState == DETECTIONSTATE_TEST1) {
		return detectionTest1Update();
	}

	if (m_currentState == DETECTIONSTATE_TEST2) {
		return detectionTest2Update();
	}

	if (m_currentState == DETECTIONSTATE_TEST3) {
		return detectionTest3Update();
	}

	if (m_currentState == DETECTIONSTATE_TEST3_WAITFORRESPONSES) {
		return detectionTest3WaitForResponsesUpdate();
	}

	if (m_currentState == DETECTIONSTATE_TEST4_1) {
		return detectionTest4Stage1Update();
	}

	if (m_currentState == DETECTIONSTATE_TEST4_2) {
		return detectionTest4Stage2Update();
	}

	if (m_currentState == DETECTIONSTATE_TEST5) {
		return detectionTest5Update();
	}

	return TRUE;
}

// The donor's detectionTest5Update is defined here because the only caller
// (/Os) inlines it to `mov [ecx+0x17C], 9; mov al,1; ret`, which is what
// retail encodes at 0x00595D8C.
// ?detectionTest5Update@FirewallHelperClass@@QAE_NXZ present-unmatched
Bool FirewallHelperClass::detectionTest5Update() {
	/*
	** We have done all the tests we *have* to. There's other info that it would be nice to know though.
	**
	** Test for the netgear bug behavior.
	*/
#if (0)
// moved to before test 1.  Moved because this flag could be specified for another firewall
// for testing purposes and never get this far because it has behavior that doesn't require
// all the tests to be performed.
// BGC 10/1/02
	DEBUG_LOG(("FirewallHelperClass::detectionTest5Update - Testing for Netgear bug\n"));

	/*
	** See if the user specified a netgear firewall - that will save us the trouble.
	*/
	if (TheGlobalData->m_firewallSendDelay) {
		UnsignedInt addbehavior = FIREWALL_TYPE_NETGEAR_BUG;
		addbehavior |= (UnsignedInt)m_behavior;
		m_behavior = (FirewallBehaviorType) addbehavior;
		DEBUG_LOG(("FirewallHelperClass::detectionTest5Update - Netgear bug specified by command line or SendDelay flag\n"));
	} else {
		DEBUG_LOG(("FirewallHelperClass::detectionTest5Update - Netgear bug not specified\n"));
	}
#endif // #if (0)

	DEBUG_LOG(("FirewallHelperClass::detectionTest5Update - All done, behavior is: "));

	if ((m_behavior & FIREWALL_TYPE_SIMPLE) != 0) {
		DEBUG_LOG((" FIREWALL_TYPE_SIMPLE "));
	}
	if ((m_behavior & FIREWALL_TYPE_DUMB_MANGLING) != 0) {
		DEBUG_LOG((" FIREWALL_TYPE_DUMB_MANGLING "));
	}
	if ((m_behavior & FIREWALL_TYPE_SMART_MANGLING) != 0) {
		DEBUG_LOG((" FIREWALL_TYPE_SMART_MANGLING "));
	}
	if ((m_behavior & FIREWALL_TYPE_NETGEAR_BUG) != 0) {
		DEBUG_LOG((" FIREWALL_TYPE_NETGEAR_BUG "));
	}
	if ((m_behavior & FIREWALL_TYPE_SIMPLE_PORT_ALLOCATION) != 0) {
		DEBUG_LOG((" FIREWALL_TYPE_SIMPLE_PORT_ALLOCATION "));
	}
	if ((m_behavior & FIREWALL_TYPE_RELATIVE_PORT_ALLOCATION) != 0) {
		DEBUG_LOG((" FIREWALL_TYPE_RELATIVE_PORT_ALLOCATION "));
	}
	if ((m_behavior & FIREWALL_TYPE_DESTINATION_PORT_DELTA) != 0) {
		DEBUG_LOG((" FIREWALL_TYPE_DESTINATION_PORT_DELTA "));
	}

	DEBUG_LOG(("\n"));

	m_currentState = DETECTIONSTATE_DONE;
	return TRUE;
}

