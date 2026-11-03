// Target facts (addresses are retail RVAs unless marked VA):
// GameInfo constructors 00382FA7/00400A07 store VA 00C193C8 at +0; destructor
// 00400A7F restores it before member cleanup and VA 00BBB554 afterwards.
// GameSlot constructors 002295D7/003FFB4C store VA 00BE7420; destructor
// 002294FD destroys +1A8, +64, +34 and +30, then restores VA 00BBB554.
// The final destructor store is Snapshot teardown, not a competing own table.
// Both classes therefore inherit the registered four-byte Snapshot base.
// VA 00BE7420 has seven slots: 002296EC, 000B3FD0, 002296E6, 003FF616,
// 003FF50C, 000D43D0, 000D43D0. Getter 002296E6 returns "GameSlot".
// VA 00C193C8 has 23 slots: 003830CE, 000B3FD0, 0037BB4D, 003FFA3C,
// 000D43D0, 000D43D0, 00401015, 0022C4CB, 0022C4CF, 0022C4D4,
// 003FFF8F, 003FF271, 003FF312, 003FF2D6, 003FF9B4, 003FF39E,
// 0040052C, 003FFE51, 003FF9E2, 003FF3B5, 003FF3E3, 000D43D0, 0022C4DF.
// GameInfo copy 00382FA7 copies strings +04/+40, bytes +10/+11/+12/+8C,
// eight slots +18, two address dwords +38/+3C, ten dwords +60, a
// 0x30-byte Version at +90, pointer +C8 and four dwords +CC: extent DC.
// GameSlot copy 002295D7 copies state +04, bytes +08/+09/+0A, dwords
// +0C..+2C, strings +30/+34, dwords +38..+44, byte +48, dwords +4C..+5C,
// byte +60, CreateAHeroData +64 (0x140 bytes), byte +1A4 and string +1A8:
// extent 1AC. setSlot 003FFDFA consumes that extent by value.
// SkirmishGameInfo constructor 0022C45B calls GameInfo's constructor, then
// constructs eight slots of stride 1AC at +DC, independently fixing both sizes.
// reset 003FF50C and saveOffOriginalInfo 003FF0D4 prove the original triple
// +24/+28/+2C. isHuman 003FF0F1 tests state 6; isAI 003FF127 tests 2..5;
// isOccupied 003FF0FB also tests byte +1A4; isObserver 003FF165 tests +18=-2.
// reset 003FFF8F proves inGame +10, inProgress +11, map +40, CRC +44,
// size +48, mask +4C, seed +50, integer +5C, rules +60 and 16-byte tail +CC.
// ParseAsciiStringToGameInfo 0040116B inlines setMapContentsMask (+4C, 00401EDC).
// Rowed copies/destructors and the rowed methods below stay out of line.
// Snapshot's existing capitalized/name-slot switches select the inherited API;
// those declarations override its existing slots and do not add virtual slots.
// Without the name slot, GameSlot overrides slot 2 under Snapshot's crc
// spelling, so the class stays concrete for setSlot's by-value parameter.
// Donor facts: Zero Hour GameInfo.h supplies the established accessor and
// scalar names; unidentified slots and storage retain neutral names.
#pragma once
#ifndef __BFME2_GAMEINFO_H_
#define __BFME2_GAMEINFO_H_

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class Image;
class CreateAHeroData;
class TreeHintOpaque0043671B;
struct BfmeNetAddress;
struct GameSlotConnectInfo;
enum SlotState;

class GameSlot : public Snapshot
{
public:
	GameSlot();
	GameSlot(const GameSlot &);
	virtual ~GameSlot();
protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();
#else
	virtual void loadPostProcess();
#endif
#ifndef BFME_SNAPSHOT_NAME_SLOT
	virtual void crc(Xfer *);
#endif
public:
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;
#endif
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &);
#else
	virtual void DoXfer(Xfer *);
#endif
#else
	virtual void xfer(Xfer *);
#endif
	virtual void reset();
	virtual void *vslot05();
	virtual void *vslot06();

	GameSlot &rva002DBAB9(const GameSlot &);
	void setState(SlotState, UnicodeString, const GameSlotConnectInfo *);
	void unAccept();
	void setMapAvailability(bool);
	void setPlayerTemplate(int);
	void saveOffOriginalInfo();
	int getApparentPlayerTemplate() const;
	int getApparentColor() const;
	int getApparentStartPos() const;
	UnicodeString getApparentPlayerTemplateDisplayName() const;
	bool isHuman() const;
	bool isOccupied() const;
	bool isAI() const;
	bool isObserver() const;
	bool isOpen() const;
	bool isPlayer(AsciiString) const;
	bool isPlayer(UnicodeString) const;
	bool isPlayer(const BfmeNetAddress *) const;
	bool disconnected() const;
	unsigned char encodeHero() const;
	bool decodeHero(unsigned char);
	void rva003FF5F2(const AsciiString &);
	void rva0037AD8D(const CreateAHeroData &);
	void *rva004479B1();

	void setAccept() { m_isAccepted = true; }
	bool isAccepted() const { return m_isAccepted; }
	bool hasMap() const { return m_hasMap; }
	int getState() const { return m_state; }
	void setColor(int value) { m_color = value; }
	int getColor() const { return m_color; }
	void setStartPos(int value) { m_startPos = value; }
	int getStartPos() const { return m_startPos; }
	int getPlayerTemplate() const { return m_playerTemplate; }
	void setTeamNumber(int value) { m_teamNumber = value; }
	int getTeamNumber() const { return m_teamNumber; }
	int getOriginalColor() const { return m_origColor; }
	int getOriginalStartPos() const { return m_origStartPos; }
	int getOriginalPlayerTemplate() const { return m_origPlayerTemplate; }
	UnicodeString getName() const { return m_name; }
	void setName(UnicodeString value) { m_name = value; }
	void mute(bool value) { m_isMuted = value; }
	bool isMuted() const { return m_isMuted; }
	void setLastFrameInGame(unsigned int value) { m_lastFrameInGame = value; }
	unsigned int lastFrameInGame() const { return m_lastFrameInGame; }
	void markAsDisconnected() { m_disconnected = true; }

	int m_state;
	bool m_isAccepted;
	bool m_hasMap;
	bool m_isMuted;
	int m_color;
	int m_startPos;
	int m_field14;
	int m_playerTemplate;
	int m_teamNumber;
	int m_field20;
	int m_origColor;
	int m_origStartPos;
	int m_origPlayerTemplate;
	UnicodeString m_name;
	AsciiString m_field34;
	unsigned int m_field38;
	unsigned short m_field3C;
	int m_field40;
	unsigned int m_lastFrameInGame;
	bool m_disconnected;
	int m_field4C;
	int m_field50;
	int m_field54;
	int m_field58;
	int m_field5C;
	bool m_field60;
	unsigned char m_pad61[3];
	unsigned char m_field64[0x140];
	bool m_field1A4;
	AsciiString m_field1A8;
};

class GameInfo : public Snapshot
{
public:
	GameInfo();
	GameInfo(const GameInfo &);
	virtual ~GameInfo();
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();
#else
	virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;
#endif
#else
	virtual void crc(Xfer *);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &);
#else
	virtual void DoXfer(Xfer *);
#endif
#else
	virtual void xfer(Xfer *);
#endif
	virtual void *vslot04();
	virtual void *vslot05();
	virtual const Image *rva00401015(int);
	virtual int vslot07();
	virtual int vslot08();
	virtual int vslot09();
	virtual void reset();
	virtual void startGame(int);
	virtual bool amIHost() const;
	virtual int getLocalSlotNum() const;
	virtual void resetAccepted();
	virtual void resetStartSpots();
	virtual void adjustSlotsForMap();
	virtual void closeOpenSlots();
	virtual bool isSkirmish();
	virtual bool isMultiPlayer();
	virtual bool isSandbox();
	virtual void *vslot21();
	virtual UnicodeString vslot22() const;

	void init();
	void clearSlotList();
	int getNumPlayers() const;
	int getNumNonObserverPlayers() const;
	int getNumOpenOrOccupiedSlots() const;
	int getMaxPlayers();
	void enterGame();
	void endGame();
	void setSlot(int, GameSlot);
	GameSlot *getSlot(int);
	const GameSlot *getConstSlot(int) const;
	int getSlotNum(AsciiString) const;
	void setSlotPointer(int, GameSlot *);
	void setMap(AsciiString);
	void setMapForwarder(AsciiString);
	AsciiString getMap() const;
	void setMapCRC(unsigned int);
	void setMapSize(unsigned int);
	void setSeed(int);
	void rva0033F898(int);
	void rva003FF1A7(int);
	bool rva003FF457() const;
	bool isHeroDataReadyForSlot(unsigned short) const;
	bool isPlayerPreorder(int);
	void markPlayerAsPreorder(int);
	bool isColorTaken(int, int = -1) const;
	bool isStartPositionTaken(int, int = -1) const;

	int getGameID() const { return m_gameID; }
	void setInGame() { m_inGame = true; }
	bool isInGame() const { return m_inGame; }
	bool isGameInProgress() const { return m_inProgress; }
	void setGameInProgress(bool value) { m_inProgress = value; }
	unsigned int getMapCRC() const { return m_mapCRC; }
	unsigned int getMapSize() const { return m_mapSize; }
	void setMapContentsMask(int value) { m_mapMask = value; }
	int getMapContentsMask() const { return m_mapMask; }
	int getSeed() const { return m_seed; }
	int getUseStats() const { return m_useStats; }
	void setUseStats(int value) { m_useStats = value; }
	void setCRCInterval(int value) { m_crcInterval = value < 100 ? value : 100; }
	int getCRCInterval() const { return m_crcInterval; }
	bool haveWeSurrendered() { return m_surrendered; }
	void markAsSurrendered() { m_surrendered = true; }

	UnicodeString m_field04;
	int m_preorderMask;
	int m_crcInterval;
	bool m_inGame;
	bool m_inProgress;
	bool m_surrendered;
	int m_gameID;
	GameSlot *m_slot[8];
	unsigned int m_field38;
	unsigned short m_field3C;
	AsciiString m_mapName;
	unsigned int m_mapCRC;
	unsigned int m_mapSize;
	int m_mapMask;
	int m_seed;
	int m_useStats;
	int m_field58;
	int m_field5C;
	int m_field60[10];
	int m_field88;
	bool m_field8C;
	unsigned char m_pad8D[3];
	unsigned char m_field90[0x30];
	int m_fieldC0;
	int m_fieldC4;
	TreeHintOpaque0043671B *m_fieldC8;
	int m_fieldCC[4];
};

typedef char GameInfoSizeCheck[sizeof(GameInfo) == 0xDC ? 1 : -1];
typedef char GameSlotSizeCheck[sizeof(GameSlot) == 0x1AC ? 1 : -1];

extern GameInfo *TheGameInfo;

#endif
