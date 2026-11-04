// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The far end of the request-frame-data round trip:
//   resendFrameRangeToPlayer,        retail 0x004D0381, 291 bytes
//   processRequestFrameDataCommand,  retail 0x004D0984, 134 bytes
//
// Reference: Open-BFME-1 native_connection_timing.cpp, the two functions of
// the same names (0x006659B0 clamps the requested window to the frames still
// kept and hands it to the resender; the resender sends every stored command of
// each frame to the requesting slot alone, then a frame-info command carrying
// the local expected count). Names are carried from that donor.
// Target evidence: the dispatcher 0x004D2F04 calls 0x004D0984 for command type
// 9, which calls 0x004D0381 with the sender's slot and the clamped range.
// BFME 2 differences read from these bodies: the last frame is clamped to the
// current logic frame rather than the one before it, and the slack is the
// GlobalData dword at +0xC18. The request's first and last frames (+0x1C and
// +0x20) are read through the folded getters 0x0030F2C7 and 0x0030D377; the
// frame-info command is the 0x28-byte type built by 0x004CEEC3 (frame +0x1C,
// command count +0x24).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

enum
{
	MAX_SLOTS = 8
};

#include "../Common/GameLogicObjectLookupView.h"

#include "../../Include/Common/GlobalData.h"

extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData
extern Int FRAMES_TO_KEEP;

#include "../../Include/GameNetwork/NetCommandMsg.h"

inline void NetCommandMsg::setID(unsigned short id)
{
	m_id = id;
}

class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_msg; }
	NetCommandRef *getNext() { return m_next; }

private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
};

#include "../../Include/GameNetwork/NetCommandListClass.h"

class NetFrameCommandMsg : public NetCommandMsg
{
public:
	NetFrameCommandMsg();
	void setFrame(UnsignedInt frame) { m_frame = frame; }
	void setCommandCount(UnsignedInt count) { m_commandCount = count; }

private:
	UnsignedInt m_frame;
	UnsignedInt m_playerFrame;
	UnsignedInt m_commandCount;
};

// The folded dword getters at +0x1C and +0x20.
class NetWrapperCommandMsg
{
public:
	UnsignedByte *getData();
	UnsignedInt getDataLength();
};

class BFMENetRequestFrameDataCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getFirstFrame() { return (UnsignedInt)((NetWrapperCommandMsg *)this)->getData(); }
	UnsignedInt getLastFrame() { return ((NetWrapperCommandMsg *)this)->getDataLength(); }
};

#include "../../Include/GameNetwork/FrameDataManagerClass.h"

Bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

template <class T> const T &frameMaximum(const T &lhs, const T &rhs)
{
	return rhs > lhs ? rhs : lhs;
}

template <class T> const T &frameMinimum(const T &lhs, const T &rhs)
{
	return rhs < lhs ? rhs : lhs;
}

#include "../../Include/GameNetwork/ConnectionManager.h"

class BFMEConnectionManager
{
public:
	void resendFrameRangeToPlayer(Int playerID, UnsignedInt startFrame, UnsignedInt endFrame);
	void processRequestFrameDataCommand(void *command);

private:
	char m_pad00000[0x12028];
	Int m_localSlot;
	char m_pad1202C[0x12104 - 0x1202c];
	FrameDataManager *m_frameData[MAX_SLOTS];
};

void BFMEConnectionManager::resendFrameRangeToPlayer(Int playerID, UnsignedInt startFrame, UnsignedInt endFrame)
{
	UnsignedInt lastFrame = frameMinimum(endFrame, TheGameLogic->getFrame());
	if (startFrame + FRAMES_TO_KEEP < lastFrame)
		startFrame = lastFrame > (UnsignedInt)FRAMES_TO_KEEP ? lastFrame - FRAMES_TO_KEEP : 0;
	for (UnsignedInt frame = startFrame; frame <= lastFrame; ++frame)
	{
		UnsignedByte relay = (UnsignedByte)1 << playerID;
		FrameDataManager **manager = m_frameData;
		Int slotsRemaining = MAX_SLOTS;
		do
		{
			if (*manager != 0)
			{
				NetCommandList *list = (*manager)->getFrameCommandList(frame);
				if (list != 0)
				{
					for (NetCommandRef *ref = list->getFirstMessage(); ref != 0; ref = ref->getNext())
						((ConnectionManager *)this)->sendLocalCommandDirect(ref->getCommand(), relay);
				}
			}
			++manager;
		} while (--slotsRemaining != 0);
		NetFrameCommandMsg *msg = new NetFrameCommandMsg;
		msg->setFrame(frame);
		if (DoesCommandRequireACommandID(msg->getNetCommandType()))
			msg->setID(GenerateNextCommandID());
		msg->setPlayerID(m_localSlot);
		msg->setCommandCount(m_frameData[m_localSlot]->getFrameCommandCount(frame));
		((ConnectionManager *)this)->sendLocalCommandDirect(msg, relay);
		msg->detach();
	}
}

void BFMEConnectionManager::processRequestFrameDataCommand(void *command)
{
	BFMENetRequestFrameDataCommandMsg *msg = static_cast<BFMENetRequestFrameDataCommandMsg *>(command);
	if (msg == 0)
		return;
	UnsignedInt startFrame = msg->getFirstFrame();
	UnsignedInt endFrame = msg->getLastFrame();
	if (endFrame < startFrame)
		return;
	UnsignedInt slack = TheGlobalData->m_networkRunAheadSlack;
	UnsignedInt currentFrame = TheGameLogic->getFrame();
	if (endFrame + slack < currentFrame)
		return;
	UnsignedInt lastFrame = frameMinimum(endFrame, TheGameLogic->getFrame());
	UnsignedInt earliest;
	if (currentFrame >= slack)
		earliest = currentFrame - slack;
	else
		earliest = 0;
	UnsignedInt firstFrame = frameMaximum(startFrame, earliest);
	if (firstFrame <= lastFrame)
		resendFrameRangeToPlayer(msg->getPlayerID(), firstFrame, lastFrame);
}
