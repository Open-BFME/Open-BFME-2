// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?setLeaveFrame@BFMENetInformPlayerLeaveFrameCommandMsg@@QAEXI@Z,
// retail 0x004D59FF (17B). Ported from Open-BFME-1
// Code/GameEngine/Source/GameNetwork/NetCommandMsg_ctors.cpp
// (BFME1 0x006741A0). Trimmed to the placed leave-frame setter;
// the 58 sibling ctors/accessors are declared-only here.

typedef int Int;
typedef unsigned int UnsignedInt;

enum NetCommandType
{
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8
};

#include "../../Include/GameNetwork/BFMENetInformPlayerLeaveFrameCommandMsg.h"

// ?setLeaveFrame@BFMENetInformPlayerLeaveFrameCommandMsg@@QAEXI@Z
void BFMENetInformPlayerLeaveFrameCommandMsg::setLeaveFrame(UnsignedInt frame)
{
	m_commandType = NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME;
	m_leaveFrame = frame;
}

// The type-8 and type-9 packet readers both pass the dword at this+0x20 here.
// ?setLeavingPlayerID@BFMENetInformPlayerLeaveFrameCommandMsg@@QAEXH@Z
void BFMENetInformPlayerLeaveFrameCommandMsg::setLeavingPlayerID(Int playerID)
{
	m_leavingPlayerID = playerID;
}
