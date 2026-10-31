// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/framedata -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork

// FrameData::getAckCommandCount, 0x006703D0, 47 bytes.
//
// Walks m_commandList and counts entries whose NetCommandMsg satisfies
// CommandRequiresAck. The ILT thunk at 0x0004207D is the only call site inside
// the loop; it lands on the predicate at 0x00682DB0. FrameDataManager's body at
// 0x006708C0 indexes the ring and forwards here.

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"
#include "GameNetwork/FrameData.h"
#include "GameNetwork/NetworkUtil.h"

// FrameData: m_frameCommandCount +0x00, m_commandCount +0x04, m_commandList +0x08.
// m_lastFailedCC is at +0x0c and m_lastFailedFrameCC is at +0x10.

// ?getAckCommandCount@FrameData@@QAEIXZ
UnsignedInt FrameData::getAckCommandCount()
{
	NetCommandList *list = m_commandList;
	if (list == 0)
		return 0;

	UnsignedInt count = 0;
	// The list head is at +0x04; the header only declares getFirstMessage().
	NetCommandRef *ref = *(NetCommandRef **)((char *)list + 4);
	while (ref != 0)
	{
		// getCommand() reads m_msg at this+0x00.
		unsigned char requiresAck = (unsigned char)CommandRequiresAck(ref->getCommand());
		if (requiresAck)
			++count;
		ref = ref->getNext(); // m_next at this+0x04
	}

	return count;
}
