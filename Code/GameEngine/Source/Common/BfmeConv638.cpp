// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv638.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoCSA@BfmeThingCSA@@QAEXPAX@Z 0x00264A86 (44B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeOutCSA
{
public:
	virtual void bfmeSpareCSA_0();
	virtual void bfmeSpareCSA_1();
	virtual void bfmeSpareCSA_2();
	virtual void bfmeSpareCSA_3();
	virtual void bfmeSpareCSA_4();
	virtual void bfmeBeginCSA();
	virtual void bfmeSpareCSA_6();
	virtual void bfmeSpareCSA_7();
	virtual void bfmeSendCSA(int code);
	virtual void bfmeSpareCSA_9();
	virtual void bfmeSpareCSA_10();
	virtual void bfmeSpareCSA_11();
	virtual void bfmeSpareCSA_12();
	virtual void bfmeSpareCSA_13();
	virtual void bfmeWriteVCSA(void *what);
};

// Native Object+8 owner call reaches the verified mobility body 0x002907A1.
// Reuse its Object thiscall bool() identity; keep the caller layout unchanged.
class Object
{
public:
	bool rva002907A1();
};

class BfmeThingCSA
{
public:
	unsigned char m_bfmeHead[8];
	Object *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSA *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSA(void *what);
};

void BfmeThingCSA::bfmeGoCSA(void *what)
{
	if (m_bfmeSub->rva002907A1())
	{
		m_bfmeOut->bfmeBeginCSA();
		m_bfmeVal = what;
		m_bfmeOut->bfmeSendCSA(0x29);
	}
}
