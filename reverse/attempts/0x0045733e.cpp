// ?removeScaffolding@BridgeBehavior@@UAEXXZ
// partial score=0.8866666666666667 date=2026-10-10
// Banked whole BridgeBehaviorIsScaffoldInMotion.cpp home, not a match.
// removeScaffolding: native 0x0045733E..0x004573D4, RET at 0x004573D3.
// BFME 1 donor 575ba2b04743f190f069805fbdc59936123c45da: purpose and control flow.
// WB1139040 names the target. Native independently proves all view offsets,
// canonical global addresses, virtual slots and call targets used below.
// 150/150 extent and all resolved relocations; .8866666667 similarity: ESI/EDI
// allocation differs. Direct donor, real list iterator and sibling /G6 produce
// that same register-only wall. Existing 75B sibling remains exact.
// Includes are relative to the intended normal Code home, not this evidence path.
// cl: -O1 -arch:SSE -G7 -MD -EHsc -DNDEBUG -DWIN32 -D_WINDOWS
// Retail 0x004573D4, 75B. Identity is the matching ZH method plus its same
// list/object/interface traversal in BFME 1's BridgeBehaviorOnHealing.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db). Retail bytes
// independently place the list-head pointer at this+0xE0 and ObjectID at
// node+8; the donor's full-class offset +0x400 does not apply here.

typedef bool Bool;
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
enum ScaffoldMotion { STM_STILL = 0 };

class Object;

extern GameLogic *TheGameLogic;

class BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions();
	virtual void setMotion(int motion);
	virtual ScaffoldMotion getCurrentMotion() const;
	virtual void reverseMotion();
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


// Native accessed views. Canonical globals retain their actual class types.
class __single_inheritance BodyModuleInterface;
struct BridgeOwnerView {
    char pad00[0x38]; Coord3D position;
    char pad44[0x254-0x44]; BodyModuleInterface *body;
};
struct BridgeTerrainView { char pad00[0xC4]; int layer; };
class __single_inheritance TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class Pathfinder { public: void SetBridgeStateRepaired(int layer,bool repaired); };
class AI;
extern AI *TheAI;
struct BridgeAIView { char pad00[0x10]; Pathfinder *pathfinder; };
class Rva0029FB3BMember { public: void reset(); };

class BridgeBehavior
{
public:
	virtual Bool isScaffoldInMotion();
	virtual void removeScaffolding();

private:
	unsigned char m_unmodelled04[0xDD-4];
	bool m_scaffoldPresent;
	char m_padDE[2];
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

// BFME1 575ba2b BridgeBehaviorOnHealing.cpp provides this purpose/control flow.
// BFME2 WB1139040 names removeScaffolding; native receiverDD/E0, owner-18,
// body254/slot20, terrain slotA4 and BridgeC4 are independently observed.
void BridgeBehavior::removeScaffolding()
{
    if(!m_scaffoldPresent)return;
    RetailScaffoldNode *node=m_scaffoldListHead->next;
    if(node!=m_scaffoldListHead) {
        do {
            Object *object=TheGameLogic->findObjectByID(node->objectID);
            if(object) {
                BridgeScaffoldBehaviorInterface *scaffold=BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);
                scaffold->reverseMotion();
            }
            node=node->next;
        } while(node!=m_scaffoldListHead);
    }
    ((Rva0029FB3BMember*)&m_scaffoldListHead)->reset();
    m_scaffoldPresent=false;
    BridgeOwnerView *object=*(BridgeOwnerView**)((char*)this-0x18);
    typedef int (BodyModuleInterface::*DamageState)() const;
    if((object->body->**(DamageState*)(*(char**)object->body+0x20))()!=3) {
        typedef BridgeTerrainView* (TerrainLogic::*FindBridge)(const Coord3D*);
        BridgeTerrainView *bridge=(TheTerrainLogic->**(FindBridge*)(*(char**)TheTerrainLogic+0xA4))(&object->position);
        if(bridge)((BridgeAIView*)TheAI)->pathfinder->SetBridgeStateRepaired(bridge->layer,true);
    }
}
