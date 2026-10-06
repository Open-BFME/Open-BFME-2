// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0028BB9E@BfmeSubBEC@@QAEPAXPAX@Z, retail 0x0028BB9E, 67 bytes.
// BfmeSubBEC filtered find: same holder layout as BfmeConv448FindBEC.cpp
// (list at +0x244, entry query at +0xC). Slot 0x20 returns a candidate,
// slot 0x00 tests it with the caller's pointer arg. Null arg returns null.
// Evidence: offset match to sibling bfmeFindBEC 0x0028BCB4, callers
// 0x0044E633 and 0x0028E01F pass through the same arg, unlock lane.
class BfmeGotBEC
{
public:
	virtual bool bfmeSpareBEC0(void *what);
	virtual void bfmeSpareBEC1();
	virtual void bfmeSpareBEC2();
	virtual void bfmeSpareBEC3();
	virtual void bfmeSpareBEC4();
	virtual void bfmeSpareBEC5();
	virtual void bfmeSpareBEC6();
	virtual void bfmeSpareBEC7();
	virtual void bfmeSpareBEC8();
	virtual void bfmeSpareBEC9();
	virtual void bfmeSpareBECA();
	virtual void bfmeSpareBECB();
	virtual void bfmeSpareBECC();
	virtual void bfmeSpareBECD();
	virtual void bfmeSpareBECE();
	virtual void bfmeSpareBECF();
	virtual void bfmeSpareBECG();
	virtual void bfmeSendBEC(int what);
};

class BfmeBECQuery
{
public:
	virtual void bfmeSpareBECQuery0();
	virtual void bfmeSpareBECQuery1();
	virtual void bfmeSpareBECQuery2();
	virtual void bfmeSpareBECQuery3();
	virtual void bfmeSpareBECQuery4();
	virtual void bfmeSpareBECQuery5();
	virtual void bfmeSpareBECQuery6();
	virtual void bfmeSpareBECQuery7();
	virtual BfmeGotBEC *bfmeSpareBECQuery8();
	virtual void bfmeSpareBECQuery9();
	virtual void bfmeSpareBECQuery10();
	virtual void bfmeSpareBECQuery11();
	virtual void bfmeSpareBECQuery12();
	virtual void bfmeSpareBECQuery13();
	virtual void bfmeSpareBECQuery14();
	virtual void bfmeSpareBECQuery15();
	virtual void bfmeSpareBECQuery16();
	virtual void bfmeSpareBECQuery17();
	virtual void bfmeSpareBECQuery18();
	virtual void bfmeSpareBECQuery19();
	virtual void bfmeSpareBECQuery20();
	virtual void bfmeSpareBECQuery21();
	virtual BfmeGotBEC *bfmeQueryBEC();
};

class BfmeBECEntry
{
public:
	char m_entryPad[12];
	BfmeBECQuery m_query;
};

class BfmeSubBEC
{
public:
	char m_subPad[0x244];
	BfmeBECEntry **m_entryList;
	void *rva0028BB9E(void *what);
};

void *BfmeSubBEC::rva0028BB9E(void *what)
{
	if (what == 0)
		return 0;
	BfmeBECEntry **cursor = m_entryList;
	BfmeBECEntry *candidate = *cursor;
	while (candidate != 0) {
		BfmeGotBEC *found = candidate->m_query.bfmeSpareBECQuery8();
		if (found != 0) {
			if (found->bfmeSpareBEC0(what))
				return found;
		}
		candidate = *++cursor;
	}
	return 0;
}
