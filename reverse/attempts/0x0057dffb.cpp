// ?rva0057DFFB@Rva0057DFFB@@QAE_N_N@Z
// partial score=0.75 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva0057DFFB@Rva0057DFFB@@QAE_N_N@Z @0x0057DFFB 65B
// Retail boundary 0x0057DFFB..0x0057E03B (65 bytes). Two independent checks
// agree: the Ghidra inventory lists FUN_0097dffb with size 65, and the next
// independent body starts at 0x0057E03C - the 28-byte deleting destructor of
// GMapMetaData (??_GMapMetaData@@QAEPAXI@Z, matched in
// Common/FamilyDeletingDtors.cpp). The structural queue's "lanUpdateSlotList,
// 107 bytes" label is wrong on both counts and is deliberately not inherited.
//
// Target facts, every one read from retail bytes at 0x0057DFFB:
//  - thiscall taking one stack bool (ret 4); the result is a bool in AL.
//  - +0x1C selects the path: 0 refreshes, 1 calls 0x0057DB97, every other
//    value returns true without doing anything.
//  - +0x18 is an Rva0043DA65 *: 0x0057DB97 loads it into ECX and calls
//    rva0043DA65() on it the same way (mov ecx,[esi+0x18]), and the 18-byte
//    0x0057E24B setter writes that object's +8 through the same load.
//  - rva0043DA65() supplies updateMapStartSpots' GameInfo* argument, cast from
//    its int exactly as MpGameSetupSlots.cpp already casts it.
//  - +0x30 is passed as updateMapStartSpots' GameWindow** argument and its
//    first entry is tested for null before the call.
//
// Receiver evidence, and why the class is address-qualified: 0x0043A0C1 calls
// this body on &this+0x18 with true, and 0x00443EA8 calls it on &this+0x60
// with false (0x00443EA8 is an MpGameSetup method - it invokes the rowed
// MpGameSetup::rva0043DB6E on `this` at 0x00443F6C). Both callers put the same
// sub-object type at a fixed offset of a larger screen object, and 0x0057E24B,
// 0x0057DB97, 0x0057E058 and 0x0057E25D are called on that same sub-object
// from the same neighbourhood, all reaching +0x18/+0x1C/+0x30. No vtable slot
// and no ledger row names this class, so no original spelling is asserted; no
// reference tree was consulted for it. That +0x30 is an inline array rather
// than a GameWindow** member is an inference: updateMapStartSpots indexes
// eight entries through the pointer, and only entry 0 is tested here.
//
// updateMapStartSpots is the rowed 0x00303AE9 body
// (?updateMapStartSpots@@YAXPAVGameInfo@@QAPAVGameWindow@@_N@Z, matched in
// GUICallbacks/Menus/SkirmishMapStartSpots.cpp), which is what fixes the
// +0x30 argument as GameWindow**.
class GameInfo;
class GameWindow;
void updateMapStartSpots(GameInfo *myGame, GameWindow *buttons[], bool onLoadScreen);

// Private pointer view; layout and mangled name are those of the rowed
// 0x0043DA65 getter (?rva0043DA65@Rva0043DA65@@QAEHXZ, matched in
// Common/Rva0043DA65Getter.cpp). Nothing here instantiates it.
class Rva0043DA65
{
public:
	int rva0043DA65();
};

class Rva0057DFFB
{
public:
	bool rva0057DFFB(bool onLoadScreen);
	void rva0057DB97(); // 0x0057DB97: called with ECX=this, no stack arguments

private:
	unsigned char m_pad00[0x18];
	Rva0043DA65 *m_game; // +0x18; its +8 int is what 0x0057E24B writes
	int m_mode;          // +0x1C
	unsigned char m_pad20[0x30 - 0x20];
	GameWindow *m_buttons[8]; // +0x30
};

bool Rva0057DFFB::rva0057DFFB(bool onLoadScreen)
{
	switch (m_mode)
	{
	case 0:
	{
		GameInfo *game = (GameInfo *)m_game->rva0043DA65();
		if (!game || !m_buttons[0])
			return false;
		updateMapStartSpots(game, m_buttons, onLoadScreen);
		break;
	}
	case 1:
		rva0057DB97();
		break;
	}
	return true;
}