// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?getDockUpdateInterface@Object@@QAEPAVDockUpdateInterface@@XZ, retail
// 0x0028BCB4, 32 bytes: Zero Hour Object::getDockUpdateInterface. Walks the
// NULL-terminated behavior-module array at Object+0x244 and returns the first
// non-NULL result of virtual slot 22 (+0x58) of each module's +0xC
// BehaviorModuleInterface subobject, as the sibling Object scans
// getSpecialPowerModule 0x0028BB9E and getSpawnBehaviorInterface 0x0028BCD4
// do. Target evidence: AIDockState::onEnter-shaped caller 0x00341695 calls
// it at 0x003416B4 on StateMachine::getGoalObject's result (0x003416A7),
// returns -2 (STATE_FAILURE) on NULL, then hands the goal to the owner's
// +0x258 AI interface and news the 0x40-byte AIDockMachine. 19 of its 23
// retail REL32 callers lie in the AIDockMachine code 0x005440DB..0x00544BA8,
// mostly state methods of the classes its ctor 0x005448A1 registers
// (Rva005447ED, Rva0054482D, Rva0054484A, Rva00544884, Rva00544867), each on
// the machine goal object, driving the result's dock slots. ZH
// AIDockState::onEnter has that sequence (getMachineGoalObject,
// getDockUpdateInterface, STATE_FAILURE,
// ai->ignoreObstacle, newInstance(AIDockMachine)). Inference: slot 22 is
// BFME 2's BehaviorModuleInterface::getDockUpdateInterface. Formerly the
// placeholder BfmeSubBEC::bfmeFindBEC (named by the GoBEC caller 0x00483BBB).
class DockUpdateInterface
{
public:
	virtual void bfmeSpareBEC0();
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
	virtual void bfmeSpareBECQuery8();
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
	virtual DockUpdateInterface *bfmeQueryBEC();
};

class BfmeBECEntry
{
public:
	char m_entryPad[12];
	BfmeBECQuery m_query;
};

class Object
{
public:
	char m_subPad[0x244];
	BfmeBECEntry **m_entryList;
	DockUpdateInterface *getDockUpdateInterface();
};

DockUpdateInterface *Object::getDockUpdateInterface()
{
	BfmeBECEntry **cursor = m_entryList;
	BfmeBECEntry *candidate = *cursor;
	while (candidate != 0) {
		DockUpdateInterface *found = candidate->m_query.bfmeQueryBEC();
		if (found != 0)
			return found;
		candidate = *++cursor;
	}
	return (DockUpdateInterface *)candidate;
}
