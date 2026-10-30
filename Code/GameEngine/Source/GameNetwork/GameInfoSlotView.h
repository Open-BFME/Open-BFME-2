#ifndef BFME2_GAME_INFO_SLOT_VIEW_H
#define BFME2_GAME_INFO_SLOT_VIEW_H

// Private view shared by GameInfo.cpp and its GameSlot construction/state donors.
// The existing target bodies establish a 0x1AC-byte slot, the Snapshot
// vtable order, and the owning members at +0x30, +0x34, +0x64 and +0x1A8.
#include "ascii_string.h"
#include "unicode_string.h"

class Xfer;
struct BfmeNetAddress;

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};

class Rva0022CE19SnapshotBase
{
public:
	inline virtual ~Rva0022CE19SnapshotBase() {}
	// Retail's base table 0x00BBB554 holds __purecall in slots 1-3.
	virtual void loadPostProcess() = 0;
	virtual const char *typeName() const = 0;
	virtual void xfer(Xfer *) = 0;
};

class CreateAHeroData : public Rva0022CE19SnapshotBase
{
	unsigned char fields[0x13C];

public:
	CreateAHeroData(int a = 0, int b = 0, int c = 0,
		const UnicodeString &name = UnicodeString::TheEmptyString,
		int d = -1, int color = 0xFF707070, int e = -1);
	virtual ~CreateAHeroData();
	virtual void loadPostProcess();
	virtual const char *typeName() const;
	virtual void xfer(Xfer *);
	CreateAHeroData &operator=(const CreateAHeroData &that);
};

struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : m_nat(0), m_port(0) {}
	int m_nat;
	unsigned short m_port;
	unsigned short m_pad;
};

class GameSlot : public Rva0022CE19SnapshotBase
{
	friend class GameInfo;
public:
	GameSlot();
	virtual ~GameSlot();
	// Existing GameInfo.cpp accessors use this same 0x1AC-byte slot view.
	GameSlot(const GameSlot &);
	GameSlot &rva002DBAB9(const GameSlot &other);
	bool isOccupied() const;
	void rva003FF5F2(const AsciiString &other);
	bool isHuman() const;
	bool isAI() const;
	bool isPlayer(AsciiString userName) const;
	bool isPlayer(UnicodeString userName) const;
	bool isPlayer(const BfmeNetAddress *other) const;
	void saveOffOriginalInfo();
	void setPlayerTemplate(int playerTemplate);
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
	// Table 0x00BE7420 slot 2 is the literal getter 0x002296E6, slot 3 the
	// rowed xfer 0x003FF616.
	virtual const char *typeName() const { return "GameSlot"; }
	virtual void xfer(Xfer *);
	virtual void reset();

protected:
	virtual void loadPostProcess();

private:
	int m_state;
	bool m_isAccepted, m_hasMap, m_isMuted;
	int m_color, m_startPos, m_bfme14, m_playerTemplate, m_teamNumber;
	int m_bfme20, m_origColor, m_origStartPos, m_origPlayerTemplate;
	UnicodeString text30;
	AsciiString text34;
	GameSlotConnectInfo connect38;
	unsigned int word40, word44;
	unsigned char flag48;
	unsigned int word4C, word50, word54, word58, word5C;
	unsigned char flag60;
	CreateAHeroData hero64;
	unsigned char flag1A4;
	AsciiString m_name;
};

#endif
