// cl: /MD /EHsc
// ZH ConnectionManager::getFrameCommandList, donor BFME1 6583b3c1.
// Target 0x004D0027..0x004D00BB keeps the eight-slot list merge, but uses
// frame managers at +0x12104, resetFrame(frame, true), and a Network call
// at vtable +0x60 before the loop. The slot's semantic name is unproven.
// Existing recovered list and FrameDataManager bodies establish all callees.

#include "../../Include/GameNetwork/NetCommandListClass.h"

#include "../../Include/GameNetwork/FrameDataManagerClass.h"

#include "../../Include/GameNetwork/NetworkInterfaceClass.h"
extern NetworkInterface *TheNetwork;

// ZH NetworkUtil.cpp defines (MAX_FRAMES_AHEAD/2)+1. Target VA 0x00DD2DBC
// contains 65; this body reads it as a runtime global rather than a constant.
int FRAMES_TO_KEEP = 65;

#include "../../Include/GameNetwork/ConnectionManager.h"

NetCommandList *ConnectionManager::getFrameCommandList(unsigned int frame)
{
	NetCommandList *result = new NetCommandList;
	result->reset();
	TheNetwork->slot24();
	for (int i = 0; i < 8; ++i) {
		if (m_frameData[i]) {
			result->appendList(m_frameData[i]->getFrameCommandList(frame));
			if (frame > FRAMES_TO_KEEP)
				m_frameData[i]->resetFrame(frame - FRAMES_TO_KEEP, true);
		}
	}
	return result;
}
