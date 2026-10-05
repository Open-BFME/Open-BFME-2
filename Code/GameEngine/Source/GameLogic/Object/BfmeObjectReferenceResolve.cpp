// cl: /DNDEBUG /MD /EHsc /O1
//
// Ported from Open-BFME-1 GameEngine/Source/GameLogic/Object/BfmeObjectReferenceResolve.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?resolve@BfmeObjectReference@@QAEPAVObject@@XZ 0x003775F7 (28B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class Object;

struct BfmeObjectIdValue
{
	int m_id;
};

struct BfmeObjectIdSlot
{
	BfmeObjectIdValue *m_value;
};

class BfmeObjectReference
{
public:
	BfmeObjectIdSlot *getObjectIdSlot();
	Object *resolve();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

Object *BfmeObjectReference::resolve()
{
	if (this != 0) {
		BfmeObjectIdSlot *slot = getObjectIdSlot();
		return TheGameLogic->findObjectByID(slot->m_value->m_id);
	}
	return 0;
}
