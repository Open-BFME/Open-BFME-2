// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I. /O1 /G7 /arch:SSE /MD
// stlport
#include <vector>
// Native 0x002ACD6B..0x002ACE2B. WorldBuilder 0x00C1FC70 names
// Player::getProductionCostChangeBasedOnTemplate and Player.cpp:5305..5347.
// BFME2 target uses the list at +0x6F4 (WB +0x6FC), each modifier's filter
// at +0, float vector at +4/+8/+C, owner object ID at +0x10, flag at +0x14.
// Modifier ordering and saturating last-discount choice are target behavior;
// the original discount-entry class name remains unresolved.
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic* TheGameLogic;
class ThingTemplate;
class Player;
enum KindOfType { KINDOF_COST_SKIP = 68 };
enum ObjectStatusTypes { OBJECT_STATUS_COST_SKIP = 19 };
class Object {
public:
 bool isKindOf(KindOfType) const;
 bool testStatus(ObjectStatusTypes) const;
};
class ObjectFilter {
public:
 bool testTemplate(const ThingTemplate*, const Player*, const Player*);
};
struct ProductionCostModifier {
 ObjectFilter* filter;
 _STL::vector<float> changes;
 ObjectID object;
 bool appliesToAll;
};
struct ProductionCostNode {
 ProductionCostNode* next;
 ProductionCostNode* previous;
 ProductionCostModifier* modifier;
};
class Player {
public:
 float getProductionCostChangeBasedOnTemplate(const ThingTemplate*, bool);
private:
 unsigned char unknown[0x6F4];
 ProductionCostNode* modifiers;
};
float Player::getProductionCostChangeBasedOnTemplate(const ThingTemplate* tmplate, bool all)
{
 if(!tmplate)return 1.0f;
 unsigned count=0;
 float change=0.0f;
 for(ProductionCostNode* node=modifiers->next;node!=modifiers;node=node->next) {
  ProductionCostModifier* entry=node->modifier;
  Object* owner=TheGameLogic->findObjectByID(entry->object);
  if(owner && !owner->isKindOf(KINDOF_COST_SKIP) && !owner->testStatus(OBJECT_STATUS_COST_SKIP)) {
   if((all && entry->appliesToAll) || entry->filter->testTemplate(tmplate,0,0)) {
    if(count < entry->changes.size())change=entry->changes[count];
    ++count;
   }
  }
 }
 return change+1.0f;
}
