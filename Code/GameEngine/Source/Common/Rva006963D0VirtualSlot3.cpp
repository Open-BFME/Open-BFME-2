// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva006963D0VirtualSlot3.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?rva006963D0ForwardSlot3@@YGHPAURva006963D0Receiver@@HH@Z 0x00051900 (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Retail 0x006963D0: a stdcall wrapper forwarding two arguments to slot three.
struct Rva006963D0Receiver
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual int slot3(int first, int second);
};

int __stdcall rva006963D0ForwardSlot3(Rva006963D0Receiver *receiver, int first, int second)
{
	return receiver->slot3(first, second);
}
