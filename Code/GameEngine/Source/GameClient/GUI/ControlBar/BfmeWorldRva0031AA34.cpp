// cl: /DNDEBUG /MD
// ?rva0031AA34@BfmeWorldRV@@QAEXH@Z @ 0x0031AA34 23B: BfmeWorldRV flag set at
// +0x28 then InGameUI slot47 call. Evidence: sibling 0x0031AA4B shares
// +0x28/slot47 shape plus caller 0x002A38E9 plus rowed TheInGameUI.
class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47(int a);
};

extern InGameUI *TheInGameUI;

struct BfmeWorldRV
{
public:
	void rva0031AA34(int unused);

private:
	char m_pad00[0x28];
	unsigned char m_0028;
};

void BfmeWorldRV::rva0031AA34(int unused)
{
	(void)unused;
	m_0028 = 1;
	TheInGameUI->slot47(0);
}
