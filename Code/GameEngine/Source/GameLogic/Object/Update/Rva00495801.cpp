// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00495801@Rva00495801@@QAEHPAVRva00495801Arg@@@Z, retail 0x00495801 (63 bytes).
// Identity: unlock hunt predicate issuing AI hunt then locking weapon slot;
// pred virtual slot 0x1b8 gates aiHunt CMD_FROM_AI on arg+0x20, then
// Object at +0x08 setWeaponLock slot *(+0x24+0x80) LOCKED_TEMPORARILY,
// returns 1. Callers in CommandButtonHunt area 0x0049590F; callees rowed
// aiHunt 0x002AE657 and setWeaponLock 0x00290B24.
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};
#include "../object.h"
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
// The argument is the object's AIUpdateInterface: slot 110 (+0x1B8) is isIdle
// and aiHunt runs on its AICommandInterface base at +0x20. The placeholder
// type keeps the function's ledger name, which a caller in
// Rva004958AEUpdate.cpp spells.
class Rva00495801Arg : public AIUpdateInterface
{
};
struct Rva00495801W
{
	unsigned char m_pad00[0x80];
	WeaponSlotType m_weaponSlot; // +0x80
};
class Rva00495801
{
public:
	int rva00495801(Rva00495801Arg *arg);
private:
	unsigned char m_pad00[8];
	Object *m_obj08; // +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	Rva00495801W *m_p24; // +0x24
};
int Rva00495801::rva00495801(Rva00495801Arg *arg)
{
	Object *obj = m_obj08;
	if (arg->isIdle())
		arg->aiHunt(CMD_FROM_AI);
	Rva00495801W *w = m_p24;
	obj->setWeaponLock(w->m_weaponSlot, LOCKED_TEMPORARILY);
	return 1;
}
