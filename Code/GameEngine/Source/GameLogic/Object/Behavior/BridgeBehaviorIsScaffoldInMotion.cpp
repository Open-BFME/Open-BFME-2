// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// Retail 0x004573D4, 75B. Identity is the matching ZH method plus its same
// list/object/interface traversal in BFME 1's BridgeBehaviorOnHealing.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db). Retail bytes
// independently place the list-head pointer at this+0xE0 and ObjectID at
// node+8; the donor's full-class offset +0x400 does not apply here.

typedef bool Bool;
enum ObjectID { INVALID_OBJECT_ID = 0 };
enum ScaffoldMotion { STM_STILL = 0 };

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions();
	virtual void setMotion(int motion);
	virtual ScaffoldMotion getCurrentMotion() const;
};

class BridgeScaffoldBehavior
{
public:
	static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *object);
};

struct RetailScaffoldNode
{
	RetailScaffoldNode *next;
	RetailScaffoldNode *previous;
	ObjectID objectID;
};

class BridgeBehavior
{
public:
	virtual Bool isScaffoldInMotion();

private:
	unsigned char m_unmodelled04[0xDC];
	RetailScaffoldNode *m_scaffoldListHead;	///< retail this+0xE0
};

Bool BridgeBehavior::isScaffoldInMotion()
{
	RetailScaffoldNode *node = m_scaffoldListHead->next;
	if (node != m_scaffoldListHead)
	{
		do
		{
			Object *object = TheGameLogic->findObjectByID(node->objectID);
			if (object != 0)
			{
				BridgeScaffoldBehaviorInterface *scaffold =
					BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);
				if (scaffold != 0 && scaffold->getCurrentMotion() != STM_STILL)
					return true;
			}
			node = node->next;
		} while (node != m_scaffoldListHead);
	}
	return false;
}
