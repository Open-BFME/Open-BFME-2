// ?doFileTransfer@@YA_NVAsciiString@@H@Z
// cl: /Oi /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// platformsdk
// Ported from Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d,
// game/GameEngine/Source/GameNetwork/FileTransfer_doFileTransfer.cpp.
// Native 0x0044C5C7..0x0044C872 and WB 0x01448920 establish the complete
// map-transfer loop, by-value filename lifetime, progress labels, and timers.
// BFME2 adds eight GameInfo slots, six network slots, and five text slots.
// Popup setters retain the member ABI demonstrated by their WB bodies.
// /Oi restores the native eight-DWORD zero-fill and consequent IAT scheduling.
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

template <typename T>
const T &minimum(const T &first, const T &second)
{
	return first < second ? first : second;
}

#include "ascii_string.h"
#include "unicode_string.h"
#include <windows.h>
#include <string.h>
#include "../../Include/GameNetwork/GameInfo.h"


#include "../../Include/GameClient/GameText.h"
#include "../../Include/GameNetwork/NetworkInterfaceClass.h"

class Rva005830AE {public:void rva005830AE(int);};

#include "../../Include/Common/AptFileTransferPopup.h"

extern NetworkInterface *TheNetwork;
extern GameInfo *TheGameInfo;
extern GameTextInterface *TheGameText;
extern int g_Va00E06398;

bool doFileTransfer(AsciiString filename, int mask)
{
	AptFileTransferPopup *screen = (AptFileTransferPopup *)g_Va00E06398;
	bool fileTransferDone = false;
	int fileTransferPercent = 0;

	if (TheNetwork)
		TheNetwork->slot32();

	if (mask)
	{
		screen->rva005832D0(filename);
		DWORD startTime = timeGetTime();
		screen->rva00583202(600);
		((Rva005830AE *)screen)->rva005830AE(0);

		UnsignedShort fileCommandID = 0;
		bool sentFile = false;
		if (TheGameInfo->amIHost())
		{
			Sleep(500);
			fileCommandID = TheNetwork->sendFileAnnounce(filename, mask);
		}
		else
		{
			sentFile = true;
		}

		int lastPlayerProgress[8];
		memset(lastPlayerProgress, 0, sizeof(lastPlayerProgress));
		int lastProgressTime = timeGetTime();
		int nextSendSlot = 1;

		while (!fileTransferDone)
		{
			if (!sentFile)
			{
				int playerMask = (1 << nextSendSlot) & mask;
				if (playerMask)
					TheNetwork->sendFile(filename, playerMask, fileCommandID);
				++nextSendSlot;
				if (nextSendSlot == 8)
					sentFile = true;
			}

			fileTransferDone = true;
			fileTransferPercent = 100;
			for (int i = 1; i < 8; ++i)
			{
				if (TheGameInfo->getConstSlot(i)->isHuman() &&
					!TheGameInfo->getConstSlot(i)->hasMap())
				{
					int slotTransferPercent = TheNetwork->slot30(i, filename);
					fileTransferPercent = minimum(fileTransferPercent, slotTransferPercent);

					if (slotTransferPercent != lastPlayerProgress[i])
					{
						if (slotTransferPercent == 0)
							screen->ProcessProgress(i, slotTransferPercent,
								TheGameText->fetch("MapTransfer:Preparing"));
						else if (slotTransferPercent < 100)
							screen->ProcessProgress(i, slotTransferPercent,
								TheGameText->fetch("MapTransfer:Recieving"));
						else
							screen->ProcessProgress(i, slotTransferPercent,
								TheGameText->fetch("MapTransfer:Done"));
						lastPlayerProgress[i] = slotTransferPercent;
						lastProgressTime = timeGetTime();
					}
				}
			}

			if (fileTransferPercent < 100)
			{
				fileTransferDone = false;
				if (fileTransferPercent == 0)
					screen->ProcessProgress(0, fileTransferPercent,
						TheGameText->fetch("MapTransfer:Preparing"));
				else
					screen->ProcessProgress(0, fileTransferPercent,
						TheGameText->fetch("MapTransfer:Sending"));
			}
			else
			{
				screen->ProcessProgress(0, fileTransferPercent,
					TheGameText->fetch("MapTransfer:Done"));
			}

			int now = timeGetTime();
			if (fileTransferPercent)
			{
				if (now > lastProgressTime + 30000)
					break;
			}
			else if (now > lastProgressTime + 120000)
			{
				break;
			}
			if (now > startTime + 600000)
				break;

			screen->rva00583202((startTime + 600000 - now) / 1000);
			((Rva005830AE *)screen)->rva005830AE(fileTransferPercent);
		}

		if (!fileTransferDone)
			return false;
	}

	if (TheNetwork)
		TheNetwork->slot33();

	return true;
}
