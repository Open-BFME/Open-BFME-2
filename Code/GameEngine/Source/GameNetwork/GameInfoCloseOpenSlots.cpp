// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?closeOpenSlots@GameInfo@@UAEXXZ retail 0x003FFE51 164B.
// BFME1/ZH GameInfo.cpp closeOpenSlots: every unoccupied slot is replaced by
// a fresh closed GameSlot. Target evidence: GameInfo vtable 0x008193C8 slot
// 17 (+0x44, the slot startGame 0x003FF271 calls), the rowed getSlot
// 0x003FF29F, isOccupied 0x003FF0FB, GameSlot constructor 0x003FFB4C, setState
// 0x003FFC28, copy constructor 0x002295D7, setSlot 0x003FFDFA and destructor
// 0x002294FD. BFME2's setState takes the connection info by address where ZH
// took an IP; the caller passes a zeroed address/port pair.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;

enum { MAX_SLOTS = 8 };

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1
};

struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : m_ip(0), m_port(0) {}
	unsigned int m_ip;
	unsigned short m_port;
};

class GameSlot
{
public:
	GameSlot();
	GameSlot(const GameSlot &);
	virtual ~GameSlot();
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
	bool isOccupied() const;
private:
	char m_pad04[0x1AC - 0x04];
};

class GameInfo
{
public:
	// Vtable 0x008193C8 slot 17 (+0x44); the others are not reconstructed here.
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void closeOpenSlots();

	GameSlot *getSlot(Int slotNum);
	void setSlot(Int slotNum, GameSlot slotInfo);
};

void GameInfo::closeOpenSlots()
{
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSlot *current = getSlot(i);
		if (!current->isOccupied())
		{
			GameSlot slot;
			GameSlotConnectInfo connectInfo;
			slot.setState(SLOT_CLOSED, UnicodeString::TheEmptyString, &connectInfo);
			setSlot(i, slot);
		}
	}
}
