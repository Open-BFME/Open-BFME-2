// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva0020E100ForwardAndFinish.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?forwardAndFinish@Rva0020E100Owner@@QAEXXZ 0x004BDC03 (25B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeSubFCB
{
public:
	void bfmeCallFCB(void *value, int kind);
};

class Rva0020E100Owner
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void finish();

	void forwardAndFinish();

private:
	char m_pad04[0x20 - 0x04];
	void *m_value;
	int m_kind;
};

void Rva0020E100Owner::forwardAndFinish()
{
	BfmeSubFCB *helper = *reinterpret_cast<BfmeSubFCB **>(reinterpret_cast<char *>(this) - 8);
	helper->bfmeCallFCB(m_value, m_kind);
	finish();
}
