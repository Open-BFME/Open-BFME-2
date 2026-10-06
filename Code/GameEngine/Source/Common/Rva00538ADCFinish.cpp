// ?rva00538ADC@BfmeQuickMatchScreenBase@@UAEXXZ
// cl: /DNDEBUG /MD /EHsc
//
// Slot 8 (offset 0x20) of vtable 0x00839608, retail 0x00538ADC 43B.
// Drains the screen's window list: for each window it calls slot 7 (offset
// 0x1C) with the window, then TheWindowManager (0x00DFEF1C) slot 0x8C with the
// same window, and repeats from the head until the head is null.
//
// The do/while is load-bearing: it is what keeps VC7 top-testing the loop
// (mov edi,[esi+8] / test edi,edi / je out at the top, with the trailing
// `jmp 0x538AE4` back-edge), which is retail's shape. Every equivalent spelling
// -- `for(;;)` with break, `while`, plain `goto`, and `for` with a reload
// increment -- rotates to a bottom-tested loop with an initial jmp at
// 0x00538AE4, which is the same 43 bytes and the same registers but the wrong
// branch layout.
//
// Null-this guard gives push esi/mov esi,ecx/test esi,esi with esi=this and
// edi=the window, matching retail.

class GameWindow
{
public:
	int dummy;
};

class GameWindowManager
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void managerSlot35(GameWindow *w);
};

extern GameWindowManager *TheWindowManager;

class BfmeQuickMatchScreenBase
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4(bool flag);
	virtual void slot5();
	virtual void slot6(void *p);
	virtual void slot7(GameWindow *w);
	virtual void rva00538ADC();

private:
	void *m_04;
	GameWindow *m_head;
	int m_0C;
	int m_10;
	bool m_14;
	char m_pad15[3];
	int m_18;
	int m_1C;
	int m_20;
};

void BfmeQuickMatchScreenBase::rva00538ADC()
{
	if (this == 0)
		return;

	GameWindow *w = m_head;
	do {
		if (w == 0)
			break;
		slot7(w);
		TheWindowManager->managerSlot35(w);
		w = m_head;
	} while (w != 0);
}