// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// platformsdk
// W3DDisplay::gatherNetworkStats, retail 0x00049271..0x00049B3A (2249 bytes).
// The WorldBuilder twin (W3DDisplay.cpp, assert line 2407) names it and gives
// the statement order; everything else is read from retail: seventeen network
// debug display strings at +0x234, the native debug font of the language data
// (+0xC8 name, +0xCC size, +0xD0 bold) through the pointer-taking BFME2
// FontLibrary::getFont, and the NetworkInterface slots the lines read.
#include <windows.h>
#include "unicode_string.h"
#include "ascii_string.h"
#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class GameFont;

#include "../../../../GameEngine/Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;

// The native debug display font description of the language data.
#include "../../../../GameEngine/Include/Common/GlobalLanguageClass.h"
extern GlobalLanguage *TheGlobalLanguageData;

#include "../../../../GameEngine/Include/GameClient/DisplayString.h"

#include "../../../../GameEngine/Include/GameClient/DisplayStringManager.h"
extern DisplayStringManager *TheDisplayStringManager;

// NetworkInterface slot uses in this unit (private-view names; original names unproved):
//   slot43 = isPacketRouter
//   slot44 = getPacketRouterSlot
//   slot47 = getPlayerName
//   slot53 = getIncomingBytesPerSecond
//   slot54 = getIncomingPacketsPerSecond
//   slot55 = getOutgoingBytesPerSecond
//   slot56 = getOutgoingPacketsPerSecond
//   slot59 = getFramesBehindPacketRouter
//   slot60 = getRunAheadCeilingHits
//   slot61 = getSequentialBuffer
//   slot62 = getSlotFrame
#include "../../../../GameEngine/Include/GameNetwork/NetworkInterfaceClass.h"
extern NetworkInterface *TheNetwork;

#include "../../../../GameEngine/Include/Common/GameEngine.h"
extern GameEngine *TheGameEngine;

// The writable global data as this body reads it.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class Rva00237E1F
{
public:
	int rva00237E1F();	// packed version number
};
struct BfmeNetworkStatsGlobalData
{
	char m_unreconstructed_000[0x28];
	Int m_framesPerSecondLimit;	// +0x28
	char m_unreconstructed_02c[0xB04 - 0x2C];
	Int m_iniCRC;			// +0xB04
	Rva00237E1F m_version;		// +0xB08
	char m_unreconstructed_b0c[0xB38 - 0xB08 - sizeof(Rva00237E1F)];
	Int m_cmdCRC;			// +0xB38
};

struct PlayerLeaveStatus
{
	int m_status;
	int m_quitFrame;
	int m_defeatFrame;
	int m_victoryFrame;
	bool m_notPresent;
	unsigned char m_unknown11[3];
	int m_isHuman;
	AsciiString m_playerName;
};

extern GameLogic *TheGameLogic;

// Frame pacing statistics (GameEngine's zero-filled data). Their original
// identifiers are unknown; the names follow the line they print.
extern int SkippedClientFrames;			// VA 0x00DFE6F0
UnsignedInt EngineSleepTimeTotal = 0;		// VA 0x00DFE6F8
Int BfmeLastSleptMS = 0;			// VA 0x00DFE6FC
Int BfmeLastFrameDeltaMS = 0;		// VA 0x00DFE700
UnsignedInt EngineInitialFrameTime = 0;		// VA 0x00DFE708
Bool EngineLimitFrameRate = 0;		// VA 0x00DFE70C
extern float g_Va00DBA2F8;			// VA 0x00DBA2F8, GameEngine.cpp's logic time scale
Real BfmeAverageFPSRatio = 0;		// VA 0x00DE1B2C
Int BfmeLastRunAheadCeilingHits = 0;		// VA 0x00DE1C9C
extern unsigned int BfmeNetworkRunAheadChangeFrame;		// VA 0x00DE1B30, frame of the last run-ahead change

enum { NETWORK_DEBUG_LINES = 17 };

class W3DDisplay
{
public:
	virtual void gatherNetworkStats();
private:
	char m_unreconstructed_004[0x234 - 4];
	DisplayString *m_networkDebugString[NETWORK_DEBUG_LINES];	// +0x234
};

void W3DDisplay::gatherNetworkStats()
{
	UnicodeString unibuffer;
	UnicodeString unibuffer2;

	if (!m_networkDebugString[0])
	{
		GameFont *font;
		GlobalLanguage *language = TheGlobalLanguageData;
		const AsciiString *fontName;
		if (language && (fontName = &language->m_nativeDebugDisplay.name, !((const StringBase<char> *)fontName)->isEmpty()))
		{
			font = TheFontLibrary->getFont(fontName, (Real)language->m_nativeDebugDisplay.size, language->m_nativeDebugDisplay.bold);
		}
		else
		{
			AsciiString fixedSys("FixedSys");
			font = TheFontLibrary->getFont(&fixedSys, 8.0f, false);
		}

		for (Int i = 0; i < NETWORK_DEBUG_LINES; ++i)
		{
			if (!m_networkDebugString[i])
			{
				m_networkDebugString[i] = TheDisplayStringManager->newDisplayString();
				m_networkDebugString[i]->setFont(font);
			}
		}
	}

	Real fps = ((BfmeNetworkStatsGlobalData *)TheWritableGlobalData)->m_framesPerSecondLimit * BfmeAverageFPSRatio;

	Real sleptTime = EngineSleepTimeTotal;
	Int sleptMinutes = sleptTime / 60000.0f;
	Int sleptSeconds = (sleptTime - sleptMinutes * 60000.0f) / 1000.0f;
	Int sleptTenths = (sleptTime - (sleptMinutes * 60000.0f + sleptSeconds * 1000.0f)) * 0.1f;

	UnsignedInt elapsed = timeGetTime() - EngineInitialFrameTime;
	Real totalTime = elapsed;
	Int totalMinutes = totalTime / 60000.0f;
	Int totalSeconds = (totalTime - totalMinutes * 60000.0f) / 1000.0f;
	Int totalTenths = (totalTime - (totalMinutes * 60000.0f + totalSeconds * 1000.0f)) * 0.1f;

	if (EngineLimitFrameRate)
	{
		unibuffer.format(L"FPS:%2.2f (%3d%% max) FPSLimit:%d, SCALAR:%1.2f, FSkipped:%d, Slept:%02dms, Delta:%02dms",
			fps, (Int)(BfmeAverageFPSRatio * 100.0f), TheGameEngine->getFramesPerSecondLimit(),
			g_Va00DBA2F8, SkippedClientFrames, BfmeLastSleptMS, BfmeLastFrameDeltaMS);
	}
	else
	{
		unibuffer.format(L"FPS:%2.2f (%3d%% max) FPSLimit:NA, SCALAR:%1.2f, FSkipped:%d, Slept:%02dms, Delta:%02dms",
			fps, (Int)(BfmeAverageFPSRatio * 100.0f),
			g_Va00DBA2F8, SkippedClientFrames, BfmeLastSleptMS, BfmeLastFrameDeltaMS);
	}
	unibuffer2.format(L", TSlept:%02d:%02d:%02d, Total:%02d:%02d:%02d",
		sleptMinutes, sleptSeconds, sleptTenths, totalMinutes, totalSeconds, totalTenths);
	unibuffer.concat(unibuffer2);
	m_networkDebugString[0]->setText(unibuffer);

	unibuffer.format(L"Session/Frame: %d/%d -- VER=%d, iniCRC=%d, cmdCRC=%d",
		TheGameLogic->getTimestamp(), TheGameLogic->getFrame(),
		((BfmeNetworkStatsGlobalData *)TheWritableGlobalData)->m_version.rva00237E1F(),
		((BfmeNetworkStatsGlobalData *)TheWritableGlobalData)->m_iniCRC,
		((BfmeNetworkStatsGlobalData *)TheWritableGlobalData)->m_cmdCRC);
	m_networkDebugString[1]->setText(unibuffer);

	if (TheNetwork)
	{
		unibuffer.format(L"Bandwidth IN: %.2f bytes/sec, %.2f packets/sec",
			TheNetwork->slot53(), TheNetwork->slot54());
		m_networkDebugString[2]->setText(unibuffer);
		unibuffer.format(L"Bandwidth OUT: %.2f bytes/sec, %.2f packets/sec",
			TheNetwork->slot55(), TheNetwork->slot56());
		m_networkDebugString[3]->setText(unibuffer);

		UnsignedInt packetRouterSlot = TheNetwork->slot44();
		if (packetRouterSlot >= 8)
			return;

		if (TheNetwork->slot43())
		{
			UnicodeString unused;
			AsciiString routerName(TheNetwork->slot47(packetRouterSlot));
			unibuffer.format(L"**** I (Slot %d:%S) am the packet router ****", packetRouterSlot, routerName.str());
			m_networkDebugString[7]->setText(unibuffer);
			unibuffer.format(L"Session/Frame: %d/%d", TheGameLogic->getTimestamp(), TheGameLogic->getFrame());
			m_networkDebugString[9]->setText(unibuffer);
		}
		else
		{
			AsciiString routerName(TheNetwork->slot47(packetRouterSlot));
			unibuffer.format(L"---- Other machine (Slot %d:%S) is the packet router ----", packetRouterSlot, routerName.str());
			m_networkDebugString[7]->setText(unibuffer);
			unibuffer.format(L"Frames behind the packet router: %d", TheNetwork->slot59());
			m_networkDebugString[8]->setText(unibuffer);
			unibuffer.format(L"Total # of times we've hit the run-ahead ceiling: %d times within %d frames",
				TheNetwork->slot60(), TheGameLogic->getFrame());
			m_networkDebugString[9]->setText(unibuffer);
		}

		for (Int i = 1; i < 8; ++i)
		{
			PlayerLeaveStatus *status = TheGameLogic->getPlayerLeaveStatus(i);
			if (status->m_notPresent)
				continue;

			if (status->m_status)
			{
				if (status->m_status == 2)
					unibuffer.format(L"Player %d(%S) was voted out on frame %d", i, status->m_playerName.str(), status->m_quitFrame);
				else if (status->m_status == 1)
					unibuffer.format(L"Player %d(%S) quit gracefully on frame %d", i, status->m_playerName.str(), status->m_quitFrame);
			}
			else
			{
				if (status->m_isHuman == 1)
				{
					unibuffer.format(L"AIPlayer %d(%S)", i, status->m_playerName.str());
				}
				else if (TheNetwork->slot43())
				{
					Int framesAhead = TheNetwork->slot62(i) - TheGameLogic->getFrame() + 1;
					if (framesAhead == -10)
						unibuffer.format(L"Player %d(%S) is on frame#: %d (%d) -- NETWORK SIGNAL FLATLINED (WAITING...)",
							i, status->m_playerName.str(), TheNetwork->slot62(i), framesAhead);
					else
						unibuffer.format(L"Player %d(%S) is on frame#: %d (%d)",
							i, status->m_playerName.str(), TheNetwork->slot62(i), framesAhead);
				}
				else
				{
					unibuffer.format(L"Player %d(%S) is active", i, status->m_playerName.str());
				}

				if (status->m_victoryFrame)
				{
					unibuffer2.format(L" -- Victorious on frame %d", status->m_victoryFrame);
					unibuffer.concat(unibuffer2);
				}
				else if (status->m_defeatFrame)
				{
					if (status->m_isHuman == 0)
						unibuffer2.format(L" -- Defeated on frame %d (OBSERVING)", status->m_defeatFrame);
					else
						unibuffer2.format(L" -- Defeated on frame %d", status->m_defeatFrame);
					unibuffer.concat(unibuffer2);
				}
			}
			m_networkDebugString[9 + i]->setText(unibuffer);
		}

		if (BfmeLastRunAheadCeilingHits != TheNetwork->slot60() && TheGameLogic->getFrame() > 5)
		{
			BfmeLastRunAheadCeilingHits = TheNetwork->slot60();
			BfmeNetworkRunAheadChangeFrame = TheGameLogic->getFrame();
		}
		unibuffer.format(L"No Run Ahead");
		m_networkDebugString[4]->setText(unibuffer);

		unibuffer = L"SequentialBuffers: ";
		for (Int j = 0; j < 9; ++j)
		{
			unibuffer2.format(L"%d ", TheNetwork->slot61(j));
			unibuffer.concat(unibuffer2);
		}
		m_networkDebugString[5]->setText(unibuffer);
	}
	else
	{
		unibuffer.format(L"");
		m_networkDebugString[3]->setText(unibuffer);
		m_networkDebugString[2]->setText(unibuffer);
		m_networkDebugString[4]->setText(unibuffer);
		m_networkDebugString[6]->setText(unibuffer);
	}
}
