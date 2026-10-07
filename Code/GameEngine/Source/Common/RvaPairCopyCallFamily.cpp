// cl: /Oy-
// Three pair-copy-calls (30B each): push ebp, mov ebp, esp, push ecx x2,
// copy [ebp+8]/[ebp+0x0C] to [ebp-8]/[ebp-4], lea eax, [ebp-8], push eax,
// call <worker>, leave, ret 8. Each copies its 8-byte pair argument to a
// local and passes its address to a stdcall worker. /O1 gives the
// push-ecx prolog and leave epilog; /Oy- keeps the ebp frame.
// 0x002BFCF5 (-> 0x002BFA86), 0x003A37DC (-> 0x002ADCE1; row keeps the
// peer Rva000427195::rva003A37DC VideoPair pin),
// 0x005258F8 (-> 0x00525407). Worker identities unproven (opaque pins);
// new names are address-derived. One ledger row per call.

struct VideoPair
{
	int x;
	int y;
};

void __stdcall Rva002BFA86Worker(VideoPair *pair);
void __stdcall Rva002ADCE1Worker(VideoPair *pair);
void __stdcall Rva00525407Worker(VideoPair *pair);

void __stdcall Rva002BFCF5(VideoPair pair)
{
	VideoPair tmp = pair;
	Rva002BFA86Worker(&tmp);
}

class Rva000427195
{
public:
	void rva003A37DC(VideoPair pair);
};

// Rva000427195::rva003A37DC is defined with its retail-matched body in Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarVideoMapErase.cpp (0x003A37DC).

void __stdcall Rva005258F8(VideoPair pair)
{
	VideoPair tmp = pair;
	Rva00525407Worker(&tmp);
}
