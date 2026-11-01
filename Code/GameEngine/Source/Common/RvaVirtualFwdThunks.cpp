// Seven retail virtual-forward thunks (7-8B each). Retail shape per member:
// mov ecx, [ecx+adj], mov eax, [ecx], jmp [eax+slot]. Each forwards through
// a pointer owned at a fixed displacement from this to one virtual slot:
// 0x005E6817: adj +4, slot 0x00 (1st); 0x005E681E: adj +4, slot 0x18 (7th);
// 0x005E6826: adj +4, slot 0x14 (6th); 0x005E682E: adj +4, slot 0x10 (5th);
// 0x005E6836: adj +4, slot 0x08 (3rd);
// 0x005E683E: adj +4, slot 0x04 (2nd, two stack args from callers 0x005CE130 0x005CE804);
// 0x005E3AA2: adj -8 (pointer kept 8 below this), slot 0x0C (4th).
// Slot/owner identities unproven; names are address-derived.
// One ledger row per thunk.

// Native caller42C879 forwards GameMessage* and tests the full int result.
// Correct the existing thunk owner ABI; its seven target bytes stay unchanged.
class GameMessage;

class Rva005E3AA2Outer
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
};

class Rva005E3AA2Mid
{
public:
	void fwd();
};

void Rva005E3AA2Mid::fwd()
{
	Rva005E3AA2Outer *outer = *(Rva005E3AA2Outer *const *)((char *)this - 8);
	outer->slot3();
}
