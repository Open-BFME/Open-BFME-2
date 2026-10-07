// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva003BCFC9Set@@YGX_N@Z @0x003BCFC9 11B: free forwarder to PartitionManager::rva007397A0.
// Evidence: mov ecx,[0x00DFE74C] jmp 0x007397A0; callee is PartitionManager
// shroud thunk void(bool); slot 0xDFE74C is TheShroudManager (PartitionManager*
// view per W3DPropBuffer); caller 0x003CE614 in ScriptActions dispatch.

extern class Rva002D3627Host *TheRva002D3627Host;

class PartitionManager
{
public:
	void rva007397A0(bool value);
};
extern PartitionManager *TheShroudManager;


void __stdcall Rva003BCFC9Set(bool value)
{
	TheShroudManager->rva007397A0(value);
}

// ?Rva003BD412Set@@YGXE@Z @0x003BD412 13B: free forwarder to rowed Rva004E432ASet.
// Evidence: push dword [esp+4] call 0x004E432A pop ecx ret 4; callee is
// void(unsigned char) in Rva0050E9D3Enable.cpp; caller 0x003CEC92 in huge
// dispatch; Rva0050E9D3Enable.cpp names 0x003BD412 as dword forwarder.
void Rva004E432ASet(unsigned char value);
void __stdcall Rva003BD412Set(unsigned char value)
{
	Rva004E432ASet(value);
}

// ?Rva003BD405Set@@YGXE@Z @0x003BD405 13B: free forwarder to rowed Rva0043CCDASet.
// Evidence: push dword [esp+4] call 0x0043CCDA pop ecx ret 4; callee is
// void(unsigned char) in Rva0050E9D3Enable.cpp; caller 0x003CEC81 in huge
// dispatch. Chain lane on 0x0043CCDA.
void Rva0043CCDASet(unsigned char value);
void __stdcall Rva003BD405Set(unsigned char value)
{
	Rva0043CCDASet(value);
}

// ?doFlashObjectivesButton@ScriptActions@@IAEXH@Z @0x003BD444 21B: guarded forwarder to rowed Rva002D382E::rva002D382E.
// Evidence: cmp [esp+4],0 jl ret; mov ecx,[0x00DFF028] jmp 0x002D382E; callee is
// void(int) thiscall in Rva002D381DCalls.cpp (index 1 of 0/1/2 family via same
// global); caller 0x003CECDB in huge dispatch beside 0x003BD405/0x003BD412 siblings.
class Rva002D382E
{
public:
	void rva002D382E(int seconds);
};

#define TheRva002D382E (*(Rva002D382E **)&TheRva002D3627Host)

class ScriptActions
{
protected:
	void doFlashObjectivesButton(int value);
	void rva003BD42F(int value);
	void doFlashPlanningModeButton(int value);
};

void ScriptActions::doFlashObjectivesButton(int value)
{
	if (value >= 0)
		TheRva002D382E->rva002D382E(value);
}

// ?doFlashPlanningModeButton@ScriptActions@@IAEXH@Z @0x003BD459 21B: guarded forwarder to rowed Rva002D383F::rva002D383F.
// Evidence: cmp [esp+4],0 jl ret; mov ecx,[0x00DFF028] jmp 0x002D383F; callee is
// void(int) thiscall in Rva002D381DCalls.cpp (index 2 of 0/1/2 family via same
// global); caller 0x003CECEF in huge dispatch; sibling of 0x003BD444 above.
class Rva002D383F
{
public:
	void rva002D383F(int seconds);
};

#define TheRva002D383F (*(Rva002D383F **)&TheRva002D3627Host)

void ScriptActions::doFlashPlanningModeButton(int value)
{
	if (value >= 0)
		TheRva002D383F->rva002D383F(value);
}

// Native3BD42F..3BD444 RET4. Index0 sibling of the two independently
// established ScriptActions button forwarders above. Original button name
// remains unknown; target2D381D and singleton slot DFF028 are proven.
class Rva002D381D {public:void rva002D381D(int seconds);};
void ScriptActions::rva003BD42F(int value)
{
 if(value>=0) ((Rva002D381D*)TheRva002D3627Host)->rva002D381D(value);
}
