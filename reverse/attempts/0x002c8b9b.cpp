// ?rva002C8B9B@WeaponSet@@QAEXH@Z
// partial score=0.97 date=2026-10-05
// ?rva002C8B9B@WeaponSet@@QAEXH@Z
// partial score=0.97 date=2026-10-04
// ?rva002C8B9B@WeaponSet@@QAEXH@Z
// cl: /O1 /DNDEBUG /MD
//
// ?rva002C8B9B@WeaponSet@@QAEXH@Z, retail 0x002C8B9B, 107 bytes. Companion to
// the matched WeaponSet::setWeaponLock (0x002C8AAE) in
// WeaponSetSetWeaponLock.cpp and it reuses that file's layout evidence:
// m_weapons at +0x08, current weapon +0x20, lock status +0x24, owner ObjectID
// +0x3C. Called with arg 2 by the matched placeholder WeaponSet::updateWeaponSet
// 0x002C8C97, and via lea ecx,[esi+0x330] at 0x0028D8B6.
//
// Arg 2 always clears the lock; arg 1 only clears a TEMPORARY lock. On a clear
// it also drops the five weapon-slot model conditions 0x90..0x94 on the owner,
// built by matched placeholder row 0x000B6253 in a 0x4C-byte local and applied
// by matched placeholder row 0x001E42F2 (whose this is the Object).
//
// The `mov BYTE [ebp+8],2` the parent reads is not a flag byte: retail tests
// [ebp+0x8] against 2 and against 1 directly, so arg is an enum compared
// twice.
//
// The one shape that reproduces retail is duplicating the clearing store across
// two branches rather than sharing it after the guards:
//
//   mov eax,[esi+0x24] ; xor ecx,ecx ; cmp eax,ecx ; je RET
//   cmp [ebp+0x8],2    ; je CLEAR
//   cmp [ebp+0x8],1    ; jne RET
//   cmp eax,1          ; jne RET
// CLEAR:
//   cmp edi,ecx        ; mov [esi+0x24],ecx ; je RET
//   push 0x94..0x90, ecx
//
// Retail keeps ONE zero in ecx and spends it four times -- the lock compare,
// the owner null test, the status store and the mask `count` argument. Giving
// the clear its own store in each of an `if/else if/else` chain is what stops
// the optimizer from folding each use on its own into the shorter forms
// (`test eax,eax`, `test edi,edi`, `and [esi+0x24],0`, `push 0`) that a single
// shared store behind the guards produces.
enum ObjectID
{
	INVALID_ID = 0
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
class Object;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
// Placeholder rows: 0x000B6253 fills a 0x4C-byte (19-word) model-condition mask
// with up to five bits and returns it; 0x001E42F2 clears such a mask on an
// Object (its this is the Object).
class Rva000B6253
{
public:
	Rva000B6253 *rva000B6253(int count, unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
private:
	unsigned int m_words[19];
};
class Rva001E42F2
{
public:
	void rva001E42F2(const int *mask);
};
class Weapon;
class WeaponSet
{
public:
	void rva002C8B9B(int arg);
	WeaponLockType getLockStatus() const { return m_curWeaponLockedStatus; }
private:
	unsigned char m_pad00[8];
	Weapon *m_weapons[5]; // +0x08
	unsigned char m_pad1C[4];
	WeaponSlotType m_curWeapon; // +0x20
	WeaponLockType m_curWeaponLockedStatus; // +0x24
	unsigned char m_pad28[0x3C - 0x28];
	ObjectID m_ownerID; // +0x3C
};
// ?rva002C8B9B@WeaponSet@@QAEXH@Z present-unmatched
void WeaponSet::rva002C8B9B(int arg)
{
	Object *owner = TheGameLogic->findObjectByID(m_ownerID);
	if (getLockStatus() == NOT_LOCKED)
		return;
	if (arg == LOCKED_PERMANENTLY)
	{
		m_curWeaponLockedStatus = NOT_LOCKED;
	}
	else if (arg == LOCKED_TEMPORARILY && getLockStatus() == LOCKED_TEMPORARILY)
	{
		m_curWeaponLockedStatus = NOT_LOCKED;
	}
	else
	{
		return;
	}
	if (owner == 0)
		return;
	Rva000B6253 mask;
	Rva000B6253 *mp = mask.rva000B6253(0, 0x90, 0x91, 0x92, 0x93, 0x94);
	((Rva001E42F2 *)owner)->rva001E42F2((const int *)mp);
}
