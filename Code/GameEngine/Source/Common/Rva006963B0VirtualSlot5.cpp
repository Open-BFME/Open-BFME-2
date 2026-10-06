// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva006963B0VirtualSlot5.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?rva006963B0ForwardSlot5@@YGHPAURva006963B0Receiver@@HH@Z 0x000518EC (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Retail 0x006963B0: a stdcall wrapper forwarding two arguments to slot five.
struct Rva006963B0Receiver
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual int slot5(int first, int second);
};

int __stdcall rva006963B0ForwardSlot5(Rva006963B0Receiver *receiver, int first, int second)
{
	return receiver->slot5(first, second);
}
