// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/firewall /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?openSpareSocket@FirewallHelperClass@@QAE_NG@Z
// retail 0x00595089, 132 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/FirewallHelper.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
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
extern FirewallHelperClass *TheFirewallHelper;

// ??0Rva005948F5@@QAE@XZ is rowed from Rva005948F5Ctor.cpp (0x005948F5): the
// 0x20-byte UDP default ctor this handler news at 0x00595089. Call it by the
// row name so the link resolves; the pin spelling ??0UDP@@QAE@XZ names the
// same address. Only the name moves (the pad keeps operator new's size).
class Rva005948F5
{
public:
	Rva005948F5();
private:
	char m_pad[0x20];
};

/***********************************************************************************************
 * FirewallHelperClass::FirewallHelperClass -- Constructor                                     *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/15/01 5:03PM ST : Created                                                               *
 *=============================================================================================*/
/* FirewallHelperClass::m_sourcePortPool: defined by its owning unit */

/***********************************************************************************************
 * FirewallHelperClass::Detect_Firewall -- See what our firewall is up to                      *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/15/01 6:47PM ST : Created                                                               *
 *=============================================================================================*/
// Retail 0x0066FCC0, 232 bytes. Identity: ZH detectFirewall and the
// FirewallNeedToRefresh key; BFME callers refresh the same firewall state.
// Both lookup and case-insensitive comparison allocate nothing and cannot
// throw. Keep that visible to avoid cleanup states for the temporary strings.
// BfmeSubENF is the existing typed ABI name for ILT 0x000405E8 -> 0x00075E00.
// The two state assignments share the value, as in the retail inlined helper.
static inline OptionPreferences::const_iterator firewallFind(const OptionPreferences& pref,const AsciiString& key) throw() { return pref.find(key); }
class BfmeSubENF { public: int bfmeCmpENF(const char*) throw(); };
static inline int firewallCompare(const AsciiString& value,const char* text) throw() { return ((BfmeSubENF*)&value)->bfmeCmpENF(text); }

/***********************************************************************************************
 * FHC::sendToManglerFromPort -- Send to the mangler from the specified port               *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Address of mangler server                                                         *
 *           Source port to send *from*                                                        *
 *                                                                                             *
 * OUTPUT:   True if sent OK                                                                   *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/15/01 12:47PM ST : Created                                                              *
 *=============================================================================================*/
// Already declared function-locally further down, where the mangler reply is checked;
// checked; sendToManglerFromPort needs it too, so it is hoisted here.
extern unsigned long CRC_Memory(const unsigned char *data, unsigned long length, unsigned long crc);

class FirewallHelperDetectionBeginUpdateShim
{
public:
	Bool thunk();
};

/*
 *  openSpareSocket - opens a socket for communication on a specified port.
 *  returns TRUE if successful, FALSE otherwise.
 */
Bool FirewallHelperClass::openSpareSocket(UnsignedShort port) {
	for (Int i = 0; i < MAX_SPARE_SOCKETS; ++i) {
		if (m_spareSockets[i].port == 0) {
			break;
		}
	}

	// don't have room for any more spare sockets.  Fail.
	if (i == MAX_SPARE_SOCKETS) {
		DEBUG_ASSERTCRASH(i < MAX_SPARE_SOCKETS, ("Ran out of spare sockets."));
		return FALSE;
	}

	m_spareSockets[i].udp = (UDP *)NEW Rva005948F5();
	if (m_spareSockets[i].udp == NULL) {
		DEBUG_LOG(("FirewallHelperClass::openSpareSocket - failed to create UDP object\n"));
		return FALSE;
	}

	if (m_spareSockets[i].udp->Bind((UnsignedInt)0, port) != 0) {
		DEBUG_CRASH(("FirewallHelperClass::openSpareSocket - Failed to init spare socket"));
		return FALSE;
	}

	m_spareSockets[i].port = port;
	DEBUG_LOG(("FirewallHelperClass::openSpareSocket - port %d is open for send\n", port));
	return TRUE;
}

