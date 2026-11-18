// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

// ??0Rva0037BB53@@QAE@XZ @0x0037BADD 112B: identity inferred
// from constructor shape shared with retail SkirmishGameInfoCtor.cpp;
// distinct vtable/global values leave donor identity unproven. The class is
// the one whose virtual dtor 0x0037BB53 is rowed as ??1Rva0037BB53 and whose
// callers (0x0037BBED, AptSaveLoad 0x0043684C) construct it through this
// ctor, so it carries that address name (was Rva0037BADD).
#include "../../Include/Common/ScalarTypes.h"

class GameSlot
{
public:
	GameSlot();
	virtual ~GameSlot();
private:
	char m_storage[0x1A8];
};

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	virtual void reset();
	void setSlotPointer(int index, GameSlot *slot);
private:
	char m_storage[0xD8];
};

class Rva0037BB53 : public GameInfo
{
public:
	Rva0037BB53();
	virtual ~Rva0037BB53();
private:
	GameSlot m_skirmishSlot[8];
};

Rva0037BB53::Rva0037BB53()
{
	for (Int i = 0; i < 8; ++i)
		setSlotPointer(i, &m_skirmishSlot[i]);
}
