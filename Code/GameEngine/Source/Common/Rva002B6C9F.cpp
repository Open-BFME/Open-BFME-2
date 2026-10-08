// cl: /MD
// ?rva002B6CE5@Rva002B6C9F@@QAE_NHHH@Z @0x002B6CE5 51B: __thiscall bool
// probe. Returns the rowed 0x2B2C40 check ANDed with the normalized pinned
// 0x2B6BCF stage; the AND form shares the bare-pops exit (al still 0 from
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
// address-derived except rowed callees and the 0x2B6BCF pin.
struct Arg54;

class Rva002B2C40
{
public:
	bool rva002B2C40(Arg54 *a, Arg54 *b);
};

class Rva002B6BCF
{
public:
	char rva002B6BCF(int a1, int a2, int a3, int *pa3);
};

struct LivingWorldArmy;
class ArmySummaryEntry;

class LivingWorldLogic
{
public:
	bool CanMoveArmyMember_internal(LivingWorldArmy *army, ArmySummaryEntry *entry, LivingWorldArmy *target, bool checkRoom);
};

class Rva003193EC
{
public:
	bool rva003193EC(int v);
};

class Rva002B6C9F
{
public:
	bool rva002B6C9F(int a1, int a2, int a3);
	bool rva002B6CE5(int a1, int a2, int a3);
	bool rva002B8019(int a1, int a2, int a3);
};

bool Rva002B6C9F::rva002B6C9F(int a1, int a2, int a3)
{
	if (!((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)a1, (Arg54 *)a3))
		return false;
	else if (!((Rva002B6BCF *)this)->rva002B6BCF(a1, a2, a3, &a1))
		return false;
	else {
		unsigned char r = ((Rva003193EC *)a3)->rva003193EC(a1);
		return r;
	}
}

bool Rva002B6C9F::rva002B6CE5(int a1, int a2, int a3)
{
	if (((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)a1, (Arg54 *)a3)) {
		return ((Rva002B6BCF *)this)->rva002B6BCF(a1, a2, a3, &a3);
	}
}

// ?rva002B8019@Rva002B6C9F@@QAE_NHHH@Z @0x002B8019 44B: the same 0x2B2C40
// gate in front of LivingWorldLogic::CanMoveArmyMember_internal with the
// room check on; shares rva002B6CE5's bare-pops exit.
bool Rva002B6C9F::rva002B8019(int a1, int a2, int a3)
{
	if (((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)a1, (Arg54 *)a3)) {
		return ((LivingWorldLogic *)this)->CanMoveArmyMember_internal(
			(LivingWorldArmy *)a1, (ArmySummaryEntry *)a2, (LivingWorldArmy *)a3, true);
	}
}
