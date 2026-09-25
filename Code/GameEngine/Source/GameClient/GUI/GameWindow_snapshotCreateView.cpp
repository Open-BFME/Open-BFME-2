// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?snapshotCreateView@GameWindow@@QAEXPAVGadgetCreateView@@_N@Z,
// retail 0x003146DC, 126 bytes. Dedicated TU.
//
// Snapshots the fields the gadget factory needs out of a live GameWindow
// into a 0x34-byte create view: the virtual slot-7 result, the words at
// +0x08/+0x0C/+0x10, an alias of the window block at +0x30 and the words at
// +0x1E0..+0x1F0. With clear set, the aliased block's word at +0x14 and its
// words at +0x19C/+0x1A0/+0x1A4 are zeroed.
//
// Codegen notes (all retail-measured): the view carries two spare words at
// +0x08/+0x0C (only offsets +0x00/+0x04/+0x10..+0x30 are touched here); the
// early copies run through eax while the window-block alias stays live in
// eax for the later ones; every read of the alias member reloads it, so it
// is volatile-qualified.
//
// Identity basis: the three callers (0x00317579, 0x0031C9DF, 0x0031CAD2)
// all pass the same register that the create wrapper also feeds to
// GameWindow::winGetUserData (0x005C4ACD), and all zero the view with the
// 0x34-byte zeroer at 0x0022239C first. Member names beyond offsets are
// provisional.

typedef int Int;

class GadgetCreateView
{
public:
	Int m_idOrUser;  // +0x00: filled by the caller after the snapshot
	Int m_x04;  // +0x04: window +0x08
	Int m_spare08;  // +0x08: untouched here
	Int m_spare0C;  // +0x0C: untouched here
	Int m_x10;  // +0x10: window +0x0C
	Int m_x14;  // +0x14: window +0x10
	void *m_instance;  // +0x18: virtual slot-7 result
	Int m_x1C;  // +0x1C: window +0x1E4
	Int m_x20;  // +0x20: window +0x1E0
	Int m_x24;  // +0x24: window +0x1E8
	Int m_x28;  // +0x28: window +0x1EC
	Int m_x2C;  // +0x2C: window +0x1F0
	void *volatile m_windowBlock;  // +0x30: window +0x30 (aliased)
};

// Opaque GameWindow stand-in: only the offsets this body touches exist.
// The real class is much larger; nothing else is spelled. The virtual at
// slot 7 (+0x1C) is declared after unused placeholders so the call below
// compiles to the retail indirect call; the placeholders are never defined
// or emitted.
class GameWindow
{
public:
	virtual void unusedSlot0();
	virtual void unusedSlot1();
	virtual void unusedSlot2();
	virtual void unusedSlot3();
	virtual void unusedSlot4();
	virtual void unusedSlot5();
	virtual void unusedSlot6();
	virtual void *fetchCreateInstance();
	void snapshotCreateView(GadgetCreateView *view, bool clear);
};

struct WindowBlockTail
{
	unsigned char m_pad[0x19C];
	Int m_clear0;
	Int m_clear1;
	Int m_clear2;
};

// ?snapshotCreateView@GameWindow@@QAEXPAVGadgetCreateView@@_N@Z
void GameWindow::snapshotCreateView(GadgetCreateView *view, bool clear)
{
	char *windowBlock;

	view->m_instance = fetchCreateInstance();
	view->m_x04 = *(Int *)((char *)this + 0x08);
	view->m_x10 = *(Int *)((char *)this + 0x0C);
	view->m_x14 = *(Int *)((char *)this + 0x10);
	windowBlock = (char *)this + 0x30;
	view->m_windowBlock = windowBlock;
	view->m_x20 = *(Int *)((char *)this + 0x1E0);
	view->m_x1C = *(Int *)((char *)this + 0x1E4);
	view->m_x24 = *(Int *)((char *)this + 0x1E8);
	view->m_x28 = *(Int *)((char *)this + 0x1EC);
	view->m_x2C = *(Int *)((char *)this + 0x1F0);

	if (clear)
	{
		*(Int *)(windowBlock + 0x14) = 0;
		((WindowBlockTail *)view->m_windowBlock)->m_clear0 = 0;
		((WindowBlockTail *)view->m_windowBlock)->m_clear1 = 0;
		((WindowBlockTail *)view->m_windowBlock)->m_clear2 = 0;
	}
}
