// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva003BC115@@YAXXZ @0x003BC115 14B: free setter of InGameUI byte +0x779 to 1.
// Evidence: mov ecx,[0x00DFEDF0] push 1 call 0x0029A61A ret; same global and
// callee as sibling 0x003BC107 (push 0); caller 0x003CC63A in ScriptActions.

extern class InGameUI *TheInGameUI;

class Rva0029A61AByteSlot
{
public:
	void set(unsigned char value);
};

#define Rva00DFEDF0 (*(Rva0029A61AByteSlot **)&TheInGameUI)

void Rva003BC115()
{
	Rva00DFEDF0->set(1);
}
