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

class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, float pointSize, bool bold);
};
extern FontLibrary *TheFontLibrary;

// The native debug display font description of the language data.
class GlobalLanguage
{
	char m_unreconstructed_000[0xC8];
public:
	AsciiString m_debugFontName;	// +0xC8
	Int m_debugFontSize;		// +0xCC
	Bool m_debugFontBold;		// +0xD0
};
extern GlobalLanguage *TheGlobalLanguageData;

class DisplayString
{
public:
	virtual void v00();
	virtual void setText(UnicodeString text);	// +0x04
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void setFont(GameFont *font);		// +0x18
};

class DisplayStringManager
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34();
	virtual DisplayString *newDisplayString();	// +0x38
};
extern DisplayStringManager *TheDisplayStringManager;

class NetworkInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C();
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C();
	virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C();
	virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C();
	virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C();
	virtual void vA0(); virtual void vA4(); virtual void vA8();
	virtual Bool isPacketRouter();				// +0xAC
	virtual UnsignedInt getPacketRouterSlot();		// +0xB0
	virtual void vB4(); virtual void vB8();
	virtual UnicodeString getPlayerName(Int slot);		// +0xBC
	virtual void vC0(); virtual void vC4(); virtual void vC8(); virtual void vCC();
	virtual void vD0();
	virtual Real getIncomingBytesPerSecond();		// +0xD4
	virtual Real getIncomingPacketsPerSecond();		// +0xD8
	virtual Real getOutgoingBytesPerSecond();		// +0xDC
	virtual Real getOutgoingPacketsPerSecond();		// +0xE0
	virtual void vE4(); virtual void vE8();
	virtual Int getFramesBehindPacketRouter();		// +0xEC
	virtual Int getRunAheadCeilingHits();			// +0xF0
	virtual Int getSequentialBuffer(Int index);		// +0xF4
	virtual Int getSlotFrame(Int slot);			// +0xF8
};
extern NetworkInterface *TheNetwork;

class GameEngine
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
	virtual void v40(); virtual void v44(); virtual void v48();
	virtual Int getFramesPerSecondLimit();			// +0x4C
};
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
		if (language && (fontName = &language->m_debugFontName, !((const StringBase<char> *)fontName)->isEmpty()))
		{
			font = TheFontLibrary->getFont(fontName, (Real)language->m_debugFontSize, language->m_debugFontBold);
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
			TheNetwork->getIncomingBytesPerSecond(), TheNetwork->getIncomingPacketsPerSecond());
		m_networkDebugString[2]->setText(unibuffer);
		unibuffer.format(L"Bandwidth OUT: %.2f bytes/sec, %.2f packets/sec",
			TheNetwork->getOutgoingBytesPerSecond(), TheNetwork->getOutgoingPacketsPerSecond());
		m_networkDebugString[3]->setText(unibuffer);

		UnsignedInt packetRouterSlot = TheNetwork->getPacketRouterSlot();
		if (packetRouterSlot >= 8)
			return;

		if (TheNetwork->isPacketRouter())
		{
			UnicodeString unused;
			AsciiString routerName(TheNetwork->getPlayerName(packetRouterSlot));
			unibuffer.format(L"**** I (Slot %d:%S) am the packet router ****", packetRouterSlot, routerName.str());
			m_networkDebugString[7]->setText(unibuffer);
			unibuffer.format(L"Session/Frame: %d/%d", TheGameLogic->getTimestamp(), TheGameLogic->getFrame());
			m_networkDebugString[9]->setText(unibuffer);
		}
		else
		{
			AsciiString routerName(TheNetwork->getPlayerName(packetRouterSlot));
			unibuffer.format(L"---- Other machine (Slot %d:%S) is the packet router ----", packetRouterSlot, routerName.str());
			m_networkDebugString[7]->setText(unibuffer);
			unibuffer.format(L"Frames behind the packet router: %d", TheNetwork->getFramesBehindPacketRouter());
			m_networkDebugString[8]->setText(unibuffer);
			unibuffer.format(L"Total # of times we've hit the run-ahead ceiling: %d times within %d frames",
				TheNetwork->getRunAheadCeilingHits(), TheGameLogic->getFrame());
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
				else if (TheNetwork->isPacketRouter())
				{
					Int framesAhead = TheNetwork->getSlotFrame(i) - TheGameLogic->getFrame() + 1;
					if (framesAhead == -10)
						unibuffer.format(L"Player %d(%S) is on frame#: %d (%d) -- NETWORK SIGNAL FLATLINED (WAITING...)",
							i, status->m_playerName.str(), TheNetwork->getSlotFrame(i), framesAhead);
					else
						unibuffer.format(L"Player %d(%S) is on frame#: %d (%d)",
							i, status->m_playerName.str(), TheNetwork->getSlotFrame(i), framesAhead);
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

		if (BfmeLastRunAheadCeilingHits != TheNetwork->getRunAheadCeilingHits() && TheGameLogic->getFrame() > 5)
		{
			BfmeLastRunAheadCeilingHits = TheNetwork->getRunAheadCeilingHits();
			BfmeNetworkRunAheadChangeFrame = TheGameLogic->getFrame();
		}
		unibuffer.format(L"No Run Ahead");
		m_networkDebugString[4]->setText(unibuffer);

		unibuffer = L"SequentialBuffers: ";
		for (Int j = 0; j < 9; ++j)
		{
			unibuffer2.format(L"%d ", TheNetwork->getSequentialBuffer(j));
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
