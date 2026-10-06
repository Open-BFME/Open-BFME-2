// cl: /O1 /DNDEBUG /MD /EHsc
// ??0SkirmishGameInfo@@QAE@XZ retail 0x0022C45B 112B.
// Zero Hour's inline SkirmishGameInfo() (GameNetwork/GameInfo.h): construct
// the eight slot records, then point the base GameInfo's slot array at them
// through setSlotPointer (0x003FF332). Target evidence: the base constructor
// call ??0GameInfo@@QAE@XZ 0x00400A07, the vftable 0x00BE7480 whose slot 0
// is the matched ??_GSkirmishGameInfo 0x0022C4FA, and the eight 0x1AC-byte
// records at +0xDC built by the EH vector constructor iterator with the
// GameSlot constructor 0x003FFB4C and destructor 0x002294FD, the same array
// the matched destructor 0x0022C516 tears down. Unlike that destructor (which
// stores no vftable), the constructor installs one, so the class is not
// novtable here.
typedef int Int;

enum { MAX_SLOTS = 8 };

class GameSlot
{
public:
	GameSlot();
	virtual ~GameSlot();
private:
	char m_pad04[0x1AC - 0x04];
};

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	void setSlotPointer(Int index, GameSlot *slot);
private:
	char m_pad04[0xDC - 0x04];
};

class SkirmishGameInfo : public GameInfo
{
public:
	SkirmishGameInfo();
	virtual ~SkirmishGameInfo();
private:
	GameSlot m_skirmishSlot[MAX_SLOTS]; // +0xDC
};

SkirmishGameInfo::SkirmishGameInfo()
{
	for (Int i = 0; i < MAX_SLOTS; ++i)
		setSlotPointer(i, &m_skirmishSlot[i]);
}
