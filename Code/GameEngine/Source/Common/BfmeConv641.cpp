// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv641.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoCSF@BfmeThingCSF@@QAEXPAX0@Z 0x00263133 (56B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeOutCSF
{
public:
	virtual void bfmeSpareCSF_0();
	virtual void bfmeSpareCSF_1();
	virtual void bfmeSpareCSF_2();
	virtual void bfmeSpareCSF_3();
	virtual void bfmeSpareCSF_4();
	virtual void bfmeBeginCSF();
	virtual void bfmeSpareCSF_6();
	virtual void bfmeSpareCSF_7();
	virtual void bfmeSendCSF(int code);
	virtual void bfmeSpareCSF_9();
	virtual void bfmeSpareCSF_10();
	virtual void bfmeSpareCSF_11();
	virtual void bfmeSpareCSF_12();
	virtual void bfmeSpareCSF_13();
	virtual void bfmeWriteVCSF(void *what);
};

// Native Object+8 owner call reaches the verified mobility body 0x002907A1.
// Reuse its Object thiscall bool() identity; keep the caller layout unchanged.
class Object
{
public:
	bool rva002907A1();
};

class BfmeThingCSF
{
public:
	unsigned char m_bfmeHead[8];
	Object *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSF *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSF(void *one, void *two);
};

void BfmeThingCSF::bfmeGoCSF(void *one, void *two)
{
	if (m_bfmeSub->rva002907A1())
	{
		m_bfmeOut->bfmeBeginCSF();
		m_bfmeOut->bfmeWriteVCSF(one);
		m_bfmeVal = two;
		m_bfmeOut->bfmeSendCSF(0x39);
	}
}
