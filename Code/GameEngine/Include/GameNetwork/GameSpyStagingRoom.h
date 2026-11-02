// Target facts (addresses are retail RVAs unless marked VA):
// Constructors 004FDE4D/003835F4 call GameInfo at 00400A07/00382FA7,
// then store VA 00C19440 at +0 (004FDE82/00383632). GameInfo occupies 0xDC.
// Destructor 00382C4A does not store a derived table; it calls 00400A7F,
// which restores VA 00C193C8 at 00400A92 and Snapshot's VA 00BBB554 at
// 00400AE7. These are base teardown tables. The class is polymorphic.
// VA 00C19440 has 24 slots, followed by the class-name literal at 00C194A0:
// 00383768, 000B3FD0, 0038374D, 004FDAC7, 000D43D0, 0047A6A9,
// 004FDC78, 0044827C, 00383753, 0038375A, 004FDC73, 004FF09F,
// 004FDBAA, 004FDBF5, 004FDA62, 003FF39E, 0040052C, 003FFE51,
// 003FF9E2, 003FF3B5, 003FF3E3, 00383761, 0022C4DF, 004FDA42.
// Slot 0 calls destructor 00382C4A and global delete; slot 2 returns the
// class-name literal. Slots 8/9/21 read +100C/+1010/+1004. Slot 23 calls
// GameInfo::init at 004FDA45, passes pointer +101C to FreeGame (00606EE0)
// at 004FDA57, then clears it at 004FDA5D. Unknown slots keep neutral names.
// Constructors and destructor pass +DC, stride 0x1E0 and count 8 to vector
// lifetime helpers. cleanUpSlotPointers 004FDA17 walks that same array.
// Copy 003835F4 and destructor 00382C4A prove four AsciiStrings at
// +FDC/+FE8/+FFC/+1000, bytes +FEC/+FED/+FF4, word +1008 and dwords
// +FE0/+FE4/+FF0/+FF8/+1004/+100C/+1010/+1014/+1018/+101C.
// addStagingRoom 003857EB allocates 0x1020 bytes at 00385871, then calls
// 004FDE4D at 00385885. removeStagingRoom 003837D3 returns with ret 0x1020
// and reads the by-value room's ID at +FE0. sizeof is therefore 0x1020.
// Copy call 00385815 and destructor call 0038376B prove that
// their rowed bodies remain out of line. Assignment call 0038589A targets
// 00382E73, currently rowed under Rva00382E73; it must not be synthesized.
// Other rowed methods: getGameSpySlot 004FDA3D, rva004FDEFF 004FDEFF,
// launchWOTRMPGame 004FE126, generateGameSpyGameResultsPacket 004FE35F,
// launchGame 004FED35.
// startGame tests byte +FF4 at 004FF11B; the join request 005A57BA reads
// word +1008 at 005A59A0/005A59B7 before the ladder lookup.
// Donor facts: Zero Hour StagingRoomGameInfo.h supplies getID's name and
// a transport pointer between ID and localName (opaque here at +FE4).
// Its isQMGame and getLadderPort accessors name the flag and word above.
// Its UnicodeString game name and smaller layout do not describe retail.
#pragma once
#ifndef __BFME2_GAMESPYSTAGINGROOM_H_
#define __BFME2_GAMESPYSTAGINGROOM_H_

#include "GameInfo.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class GameSpyGameSlot;
class LivingWorldBattle;

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyStagingRoom();
	GameSpyStagingRoom(const GameSpyStagingRoom &);
	GameSpyStagingRoom &operator=(const GameSpyStagingRoom &);
	virtual ~GameSpyStagingRoom();
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
	virtual void *vslot21();
	virtual void vslot23();

	void cleanUpSlotPointers();
	GameSpyGameSlot *getGameSpySlot(int);
	void rva004FDEFF(LivingWorldBattle *);
	void launchWOTRMPGame();
	AsciiString generateGameSpyGameResultsPacket(bool, bool);
	void launchGame();
	int getID() const { return m_id; }
	bool isQMGame() { return m_fieldFF4; }
	unsigned short getLadderPort() const { return m_field1008; }

	char m_slots[8 * 0x1E0];
	AsciiString m_fieldFDC;
	int m_id;
	void *m_fieldFE4;
	AsciiString m_fieldFE8;
	bool m_fieldFEC;
	bool m_fieldFED;
	int m_fieldFF0;
	bool m_fieldFF4;
	int m_fieldFF8;
	AsciiString m_fieldFFC;
	AsciiString m_field1000;
	int m_field1004;
	unsigned short m_field1008;
	int m_field100C;
	int m_field1010;
	int m_field1014;
	int m_field1018;
	void *m_field101C;
};

typedef char GameSpyStagingRoomSizeCheck[sizeof(GameSpyStagingRoom) == 0x1020 ? 1 : -1];

extern GameSpyStagingRoom *TheGameSpyGame;

#endif
