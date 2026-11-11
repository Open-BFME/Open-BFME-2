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


class NetworkInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void netPad22();
	virtual void netPad23();
	virtual void netPad24();
	virtual void netPad25();
	virtual void netPad26();
	virtual void netPad27();
	virtual void sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID);
	virtual int sendFileAnnounce(AsciiString path, UnsignedByte playerMask);
	virtual int getFileTransferProgress(int playerID, AsciiString path);
	virtual bool areAllQueuesEmpty();
	virtual void beginFileTransfer();
	virtual void endFileTransfer();
};

#include "../../Include/GameClient/GameText.h"

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
		TheNetwork->beginFileTransfer();

	if (mask)
	{
		screen->rva005832D0(filename);
		DWORD startTime = timeGetTime();
		screen->rva00583202(600);
		((Rva005830AE *)screen)->rva005830AE(0);

		int fileCommandID = 0;
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
					int slotTransferPercent = TheNetwork->getFileTransferProgress(i, filename);
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
		TheNetwork->endFileTransfer();

	return true;
}
