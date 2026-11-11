// cl: /MD
// ?rva002B6CE5@Rva002B6C9F@@QAE_NHHH@Z @0x002B6CE5 51B: __thiscall bool
// probe. Returns the rowed 0x2B2C40 check ANDed with the normalized rowed
// 0x2B6BCF stage (LivingWorldLogic::CanMoveArmyMembers_internal); the AND
// form shares the bare-pops exit (al still 0 from
// the first test, so no xor is emitted).
// Evidence: retail
//   push ebp; mov ebp,esp; push esi; push [ebp+0x10]; mov esi,ecx
//   push [ebp+8]; call 0x2B2C40; test al,al; je EXIT
//   lea eax,[ebp+0x10]; push eax; push [ebp+0x10]; mov ecx,esi
//   push [ebp+0xC]; push [ebp+8]; call 0x2B6BCF
//   test al,al; setne al
//   EXIT: pop esi; pop ebp; ret 0xC
// Note the 4th 0x2B6BCF arg is &a3 here (its 70B sibling at 0x2B6C9F
// passes &a1 instead).
// ?rva002B6C9F@Rva002B6C9F@@QAE_NHHH@Z @0x002B6C9F 70B: the longer sibling.
// Fails on a failed 0x2B2C40 check or a failed 0x2B6BCF stage (passing &a1),
// else returns the rowed 0x3193EC check on the third argument through a
// ternary, which is what gives retail's test al,al / setne al tail.
// Boundary: 51B [0x2B6CE5,0x2B6D18); prev ret, next prologue. Names
// address-derived except rowed callees. The ternary on the bool
// CanMoveArmyMembers_internal result gives retail's test al,al / setne al.
struct Arg54;

class Rva002B2C40
{
public:
	bool rva002B2C40(Arg54 *a, Arg54 *b);
};

struct LivingWorldArmy;
class ArmySummaryEntry;
namespace _STL { template<class T> class allocator; template<class T, class A> class vector; }

#include "../../Include/GameLogic/LivingWorldLogic.h"

class Rva003193EC
{
public:
	bool rva003193EC(int v);
};

#include "../../Include/GameClient/Rva002B6C9F.h"

bool Rva002B6C9F::rva002B6C9F(int army, int a2, int target)
{
	if (!((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)army, (Arg54 *)target))
		return false;
	else if (!((LivingWorldLogic *)this)->CanMoveArmyMembers_internal((LivingWorldArmy *)army, *(const _STL::vector<int, _STL::allocator<int> > *)a2, (LivingWorldArmy *)target, &army))
		return false;
	else {
		unsigned char hasRoom = ((Rva003193EC *)target)->rva003193EC(army);
		return hasRoom;
	}
}

bool Rva002B6C9F::rva002B6CE5(int army, int a2, int target)
{
	if (((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)army, (Arg54 *)target)) {
		return ((LivingWorldLogic *)this)->CanMoveArmyMembers_internal((LivingWorldArmy *)army, *(const _STL::vector<int, _STL::allocator<int> > *)a2, (LivingWorldArmy *)target, &target) ? true : false;
	}
}

// ?rva002B8019@Rva002B6C9F@@QAE_NHHH@Z @0x002B8019 44B: the same 0x2B2C40
// gate in front of LivingWorldLogic::CanMoveArmyMember_internal with the
// room check on; shares rva002B6CE5's bare-pops exit.
bool Rva002B6C9F::rva002B8019(int army, int entry, int target)
{
	if (((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)army, (Arg54 *)target)) {
		return ((LivingWorldLogic *)this)->CanMoveArmyMember_internal(
			(LivingWorldArmy *)army, (ArmySummaryEntry *)entry, (LivingWorldArmy *)target, true);
	}
}

// ?rva002B6D18@Rva002B6D18@@QAE_NHHHH@Z @0x002B6D18 109B: the army-member
// swap predicate (WB D90640). Both armies pass the 0x2B2C40 gate; each then
// passes the 0x2B6BCF movement gate with its arguments mirrored around the
// other, so the second call takes the first army's cached out-arg. The final
// room check runs on the army whose cached difference is positive and the
// check is written as a negated early return, which is what puts the failed
// path on the fall-through (test al,al / jne trueret / xor al,al). Duplicating
// the room call in both arms (rather than one shared local) is what makes
// each arm push its own positive difference, as retail does.
class Rva002B6D18
{
public:
	bool rva002B6D18(int a1, int a2, int a3, int a4);
};

bool Rva002B6D18::rva002B6D18(int a1, int a2, int a3, int a4)
{
	int y = a3, x = a1;
	if (!((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)x, (Arg54 *)y))
		return false;
	if (!((LivingWorldLogic *)this)->CanMoveArmyMembers_internal((LivingWorldArmy *)x, *(const _STL::vector<int, _STL::allocator<int> > *)a2, (LivingWorldArmy *)y, &a3))
		return false;
	if (!((LivingWorldLogic *)this)->CanMoveArmyMembers_internal((LivingWorldArmy *)y, *(const _STL::vector<int, _STL::allocator<int> > *)a4, (LivingWorldArmy *)x, &a1))
		return false;
	if (a3 > a1) {
		if (!((Rva003193EC *)y)->rva003193EC(a3 - a1))
			return false;
	}
	else {
		if (!((Rva003193EC *)x)->rva003193EC(a1 - a3))
			return false;
	}
	return true;
}
