// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv639.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoCSD@BfmeThingCSD@@QAEXPAX0@Z 0x00264B16 (56B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeOutCSD
{
public:
	virtual void bfmeSpareCSD_0();
	virtual void bfmeSpareCSD_1();
	virtual void bfmeSpareCSD_2();
	virtual void bfmeSpareCSD_3();
	virtual void bfmeSpareCSD_4();
	virtual void bfmeBeginCSD();
	virtual void bfmeSpareCSD_6();
	virtual void bfmeSpareCSD_7();
	virtual void bfmeSendCSD(int code);
	virtual void bfmeSpareCSD_9();
	virtual void bfmeSpareCSD_10();
	virtual void bfmeSpareCSD_11();
	virtual void bfmeSpareCSD_12();
	virtual void bfmeSpareCSD_13();
	virtual void bfmeWriteVCSD(void *what);
};

// Native Object+8 owner call reaches the verified mobility body 0x002907A1.
// Reuse its Object thiscall bool() identity; keep the caller layout unchanged.
class Object
{
public:
	bool rva002907A1();
};

class BfmeThingCSD
{
public:
	unsigned char m_bfmeHead[8];
	Object *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSD *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSD(void *one, void *two);
};

void BfmeThingCSD::bfmeGoCSD(void *one, void *two)
{
	if (m_bfmeSub->rva002907A1())
	{
		m_bfmeOut->bfmeBeginCSD();
		m_bfmeVal = two;
		m_bfmeOut->bfmeWriteVCSD(one);
		m_bfmeOut->bfmeSendCSD(0x14);
	}
}
