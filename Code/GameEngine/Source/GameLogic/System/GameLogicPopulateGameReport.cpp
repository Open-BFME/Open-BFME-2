// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// GameLogic::bfmePopulateGameReport, retail 0x00247378, 1463 bytes.
// Derived from GameLogic.cpp, Copyright 2025 Electronic Arts Inc., GPL-3.0-or-later.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameLogic/System/
// GameLogicPopulateGameReport.cpp (matched there at 0x00393880). Carried from
// the donor: the identity, the report sections and their order.
// Target facts read from this body, where BFME 2 differs from the donor:
// format takes a plain format string; lines are appended with
// concat(const AsciiString &) or concat(const char *); the game-mode line has
// three flags (GameInfo vtable +0x48/+0x4C/+0x50) and the local slot comes from
// +0x34; the slot name is the UnicodeString at GameSlot +0x30; leave status is
// recorded through setPlayerLeaveStatus; there is a -xLWCRC flag. Layout:
// report +0x54, details vector +0x58, command-line text +0x64, trailer +0x68,
// ready flag +0x6C; GameSlot start position +0x10, template +0x18, team +0x1C.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

namespace _STL
{
	template <class T> class allocator {};
	template <class T, class A = allocator<T> > class vector
	{
	public:
		int size() const { return (int)(_M_finish - _M_start); }
		void push_back(const T &value);
		T *_M_start;
		T *_M_finish;
		T *_M_end_of_storage;
	};
}

class GameSlot
{
public:
	Bool isHuman() const;
	Bool isAI() const;
	Int getStartPos() const { return m_startPos; }
	Int getPlayerTemplate() const { return m_playerTemplate; }
	Int getTeamNumber() const { return m_teamNumber; }
	const UnicodeString &getName() const { return m_name; }

private:
	char m_unrecovered00[0x10];
	Int m_startPos;
	char m_unrecovered14[4];
	Int m_playerTemplate;
	Int m_teamNumber;
	char m_unrecovered20[0x10];
	UnicodeString m_name;
};

class GameInfo
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30();
	virtual Int getLocalSlotNum() const;
	virtual void slot38(); virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual Bool isSkirmish();
	virtual Bool isMultiplayer();
	virtual Bool isSandBox();

	GameSlot *getSlot(Int slot);
	Int getSlotNum(AsciiString userName) const;
	AsciiString getMap() const;
};
extern GameInfo *TheGameInfo;

class PlayerTemplate
{
public:
	UnicodeString getDisplayName() const;
	AsciiString getName() const;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(Int index) const;
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};
extern GameTextInterface *TheGameText;

struct GlobalData
{
	char m_unrecovered0000[0x99C];
	Bool m_audioOn;
	Bool m_musicOn;
	char m_unrecovered099E[0x1100 - 0x99E];
	Bool m_fastGamePlay;
	char m_unrecovered1101[3];
	Int m_startingMoney;
};
extern GlobalData *TheGlobalData;

unsigned char Rva000308D0GetByte();

extern Bool TheXObjectCRC;
extern Bool TheXPartitionCRC;
extern Bool TheXCollisionCRC;
extern Bool TheXShroudCRC;
extern Bool TheXTaintCRC;
extern Bool TheXTerrainLogicCRC;
extern Bool TheXPlayerCRC;
extern Bool TheXAICRC;
extern Bool TheXLWCRC;
extern Bool TheVerifyClientCRC;
extern Bool TheDeepCRC;
extern Bool TheLiteCRC;
extern Bool TheBinaryDeepCRC;
extern Int TheDebugCRCFromFrame;
extern Int TheDebugCRCUntilFrame;
// Native RVA 0x009BC800: mutable four-byte interval initially 100.
// The command-line parser writes it and replay/game-info consumers read it.
Int NET_CRC_INTERVAL = 100;

class GameLogic
{
public:
	void bfmePopulateGameReport(GameInfo *game, Int *localSlot);
	void setPlayerLeaveStatus(Int slot, const AsciiString &name, Int status);

private:
	char m_unrecovered00[0x54];
	AsciiString m_gameReport;
	_STL::vector<AsciiString> m_gameReportDetails;
	AsciiString m_commandLineArguments;
	AsciiString m_gameReportTrailer;
	Bool m_gameReportReady;
};

void GameLogic::bfmePopulateGameReport(GameInfo *game, Int *localSlot)
{
	if (game == 0 || localSlot == 0)
		return;

	m_gameReportReady = false;
	AsciiString line;

	m_gameReport.format("---------------------------------------------------------\nGAME REPORT:\n---------------------------------------------------------\n");

	line.format("  BuildType: RELEASE\n");
	m_gameReport.concat(line);

	AsciiString report;
	report.format("  Session Game #%d\n    Map Name: %s\n", m_gameReportDetails.size() + 1, game->getMap().str());

	line.format("    GameMode: isSkirmish:%d, isMultiplayer:%d, isSandBox:%d\n    Player List:\n",
		TheGameInfo->isSkirmish(), TheGameInfo->isMultiplayer(), TheGameInfo->isSandBox());
	report.concat(line);

	*localSlot = 0;
	for (Int i = 0; i < 8; ++i)
	{
		GameSlot *slot = game->getSlot(i);
		AsciiString slotName;
		slotName.translate(slot->getName());

		if (slot->isHuman() && game->getSlotNum(slotName) == game->getLocalSlotNum())
			*localSlot = i;

		AsciiString displayName;
		if (!slot->isHuman() && !slot->isAI())
		{
			line.format("      Slot %d: %s\n", i, slotName.str());
		}
		else
		{
			const PlayerTemplate *playerTemplate = ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate());
			if (slot->getPlayerTemplate() == -1)
				displayName = TheGameText->fetch("GUI:Random");
			else if (slot->getPlayerTemplate() == -2)
				displayName = TheGameText->fetch("GUI:Observer");
			else
				displayName = ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate())->getDisplayName();

			line.format("      Slot %d: %s(%s), %s %s, Team:%d, StartPos:%d\n",
				i, slotName.str(), displayName.str(),
				playerTemplate ? playerTemplate->getName().str() : "n/a",
				slot->isHuman() ? "Human" : "AI",
				slot->getTeamNumber(), slot->getStartPos());

			setPlayerLeaveStatus(i, slotName, slot->isHuman() ? 0 : 1);
		}
		report.concat(line);
	}

	m_gameReportDetails.push_back(report);

	m_commandLineArguments.format("  Important CommandLine Arguments:\n    System:");
	if (Rva000308D0GetByte())
		m_commandLineArguments.concat(" zeroFillMemory:ON");
	else
		m_commandLineArguments.concat(" zeroFillMemory:OFF");
	if (!TheGlobalData->m_audioOn)
		m_commandLineArguments.concat(" -noAudio");
	if (!TheGlobalData->m_musicOn)
		m_commandLineArguments.concat(" -noMusic");
	m_commandLineArguments.concat("\n    GamePlay:");
	if (TheGlobalData->m_fastGamePlay)
		m_commandLineArguments.concat(" -fastGamePlay");
	if (TheGlobalData->m_startingMoney)
	{
		line.format(" -startingMoney %d", TheGlobalData->m_startingMoney);
		m_commandLineArguments.concat(line);
	}

	m_commandLineArguments.concat("\n    Network:");
	if (TheXObjectCRC) m_commandLineArguments.concat(" -xObjectCRC");
	if (TheXPartitionCRC) m_commandLineArguments.concat(" -xPartitionCRC");
	if (TheXCollisionCRC) m_commandLineArguments.concat(" -xCollisionCRC");
	if (TheXShroudCRC) m_commandLineArguments.concat(" -xShroudCRC");
	if (TheXTaintCRC) m_commandLineArguments.concat(" -xTaintCRC");
	if (TheXTerrainLogicCRC) m_commandLineArguments.concat(" -xTerrainLogicCRC");
	if (TheXPlayerCRC) m_commandLineArguments.concat(" -xPlayerCRC");
	if (TheXAICRC) m_commandLineArguments.concat(" -xAICRC");
	if (TheXLWCRC) m_commandLineArguments.concat(" -xLWCRC");
	if (TheVerifyClientCRC) m_commandLineArguments.concat(" -verifyClientCRC");
	if (TheDeepCRC) m_commandLineArguments.concat(" -deepCRC");
	if (TheLiteCRC) m_commandLineArguments.concat(" -liteCRC");
	if (TheBinaryDeepCRC) m_commandLineArguments.concat(" -binaryDeepCRC");
	if (TheDebugCRCFromFrame != -1)
	{
		line.format(" -debugCRCFromFrame %d", TheDebugCRCFromFrame);
		m_commandLineArguments.concat(line);
	}
	if (TheDebugCRCUntilFrame != -1)
	{
		line.format(" -debugCRCUntilFrame %d", TheDebugCRCUntilFrame);
		m_commandLineArguments.concat(line);
	}

	line.format("\n    NetCRCInterval: %d\n", NET_CRC_INTERVAL);
	m_commandLineArguments.concat(line);

	m_gameReportTrailer.format("---------------------------------------------------------\n");
}
