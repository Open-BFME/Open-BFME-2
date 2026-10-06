// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva003BC107@@YAXXZ @0x003BC107 14B: free clearer of InGameUI byte +0x779.
// Evidence: mov ecx,[0x00DFEDF0] push 0 call 0x0029A61A ret; global is
// TheInGameUI per GameLogicSetGamePaused; callee sets [ecx+0x779]=al;
// caller 0x003CC62E in ScriptActions dispatch.

extern class InGameUI *TheInGameUI;

class Rva0029A61AByteSlot
{
public:
	void set(unsigned char value);
};

#define Rva00DFEDF0 (*(Rva0029A61AByteSlot **)&TheInGameUI)

void Rva003BC107()
{
	Rva00DFEDF0->set(0);
}
