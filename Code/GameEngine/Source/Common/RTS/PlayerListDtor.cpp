// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// ??1PlayerList@@UAE@XZ, retail 0x002A79A9, 122 bytes.
// Virtual dtor over vtable 0x00BFD618 (slot 0 deleting dtor at 0x002A7ED5
// calls this body). Destroys the 20 Player pointers at +0x18 through the
// virtual deleteInstance slot 0 with 0 return-fed to the rowed operator
// delete at 0x0002FD60 (ternary null path xors eax), nulls each slot, zeroes
// ThePlayerList at 0x00DFEEE8, restores the Snapshot secondary vptr at +0x0C
// to 0x00BBB554 (Snapshot's inline virtual destructor), then calls the rowed GameEngineDeletingBase dtor
// at 0x001B4E74 for the primary base (AsciiString at +0x08). Layout from the
// rowed siblings getNthPlayer 0x002A7A29 and findPlayerWithNameKey 0x002A7A41
// (count at +0x14, array at +0x18, bound 20 not 32, key at +0x50) plus local
// at +0x10. Donor BFME1 PlayerListDestructorThunk.cpp (loop delete plus null
// plus ThePlayerList zero, 32 entries) and ZH PlayerList.cpp dtor (try init
// plus loop delete). Shape follows FireWeaponCollideDtor (tracked-pointer
// virtual release slot 0 with 0 return-fed to operator delete).

class Xfer;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
	virtual void postProcessLoad();
	virtual void reset();
	virtual void update();
	virtual void draw();

private:
	char m_pad[8]; // +0x04..+0x0B keeps Snapshot at +0x0C (retail array +0x18)
};

// BFME 2's Snapshot has a virtual destructor (the deleting-destructor
// adjustor thunk at 0x002A7ECD sits in PlayerList's Snapshot table) whose
// inline body only restores Snapshot's vptr (??_7Snapshot@@6B@, 0x00BBB554).
#include "Common/Snapshot.h"

class Player
{
public:
	virtual void *deleteInstance(int flags);
};

class PlayerList : public SubsystemInterface, public Snapshot
{
public:
	virtual ~PlayerList();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void newGame();
	virtual void newMap();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	Player *m_local; // +0x10
	int m_playerCount; // +0x14
	Player *m_players[20]; // +0x18
};
extern PlayerList *ThePlayerList;

PlayerList::~PlayerList()
{
	for (int i = 0; i < 20; ++i)
	{
		Player *p = m_players[i];
		::operator delete(p ? p->deleteInstance(0) : 0);
		m_players[i] = 0;
	}

	ThePlayerList = 0;
}
