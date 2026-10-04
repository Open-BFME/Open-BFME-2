// cl: /O1 /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/connectionmanager /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameNetwork/ConnectionManager.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ConnectionManager::sendFrameDataToPlayer 0x004D04A4 (37B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
#define Matrix4x4 Matrix4  // BFME renamed it
#define _BFME_RETAIL_TREE_INSERT_LAYOUT

#include "PreRTS.h"

#include "GameLogic/GameLogic.h"
#include "GameNetwork/NetCommandMsg.h"
#include "GameNetwork/ConnectionManager.h"



// BFME's version bears no resemblance to the reference's, which loops
// sendSingleFrameToPlayer over a frame range. Here it only raises the per-player
// watermark at this+0x12060, and the actual resend is driven separately by
// 0x00664B40. DisconnectManager::processDisconnectFrame is its caller.
// Retail forms the address of BOTH operands and loads through the selected one
// (lea eax,[ecx+eax*4+0x12060] ... lea ecx,[esp+8] ... mov edx,[ecx]; mov [eax],edx).
// BaseType.h's `max` macro cannot produce that under MSVC 7.1: it treats the
// ternary as an rvalue -- binding a reference to it is rejected outright -- so
// whatever BFME calls here is the STL-shaped template that returns const T&.
// Spelled locally because pulling in <algorithm> collides with GameMemory.h's
// placement new. Argument order is fixed by the equal case: retail takes the
// second operand when the two are equal.
template <class T> inline const T &maxRef(const T &a, const T &b) { return a > b ? a : b; }

void ConnectionManager::sendFrameDataToPlayer(UnsignedInt playerID, UnsignedInt startingFrame) {
	if (playerID >= MAX_SLOTS) {
		return;
	}

	m_playerLatestFrame[playerID] = maxRef(m_playerLatestFrame[playerID], startingFrame);
}
