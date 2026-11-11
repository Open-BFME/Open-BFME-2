// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /ICode/GameEngine/Source/Common /ICode/Libraries/Include /Ireference/shims/bfmealloc
// stlport
//
// AITargetHeuristicEnemyStructure.cpp (WorldBuilder 0x01504010 names the file).
// ?findBestTarget@AITargetHeuristicEnemyStructure@@QAEXPAVAITarget@@PAVPlayer@@1@Z,
// retail 0x005735C6, 440 bytes, RET12; EH handler 0x0079AEBD, unwind funclet
// 0x0079AEB5 (the vote map's ~map 0x00286921).
// Each of the attacker's units votes for its nearest valid enemy structure
// (isValidTarget 0x00573512); the structure with the most votes becomes the
// target, weighted by the skirmish-AI manager's +0x884 value.
// The vote map is map<ObjectID, int>: keyed by Object +0x74 (the object ID),
// signed compare at node +0x10 (folded _M_find 0x00388F63), int count at +0x14
// (folded operator[] 0x0028932C), destroyed by the map<ObjectID, int> tree chain
// 0x00286852 -> 0x00286656 -> 0x00286183.
// /EHs and the bfmealloc shim are the tree family's own settings
// (stlport_map_int_ptr_tree_dtor.cpp): with them the COMDAT copies this unit
// emits (~_Rb_tree, clear, _M_erase, map ctor/dtor, _M_find) equal retail's bodies;
// /EHsc drops the dtor's EH frame and the default allocator calls deallocate.
#include "GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
#include <map>
#include <vector>

// The vote map's operator[] is the rowed out-of-line provider 0x0028932C; this unit
// does not instantiate it (declaration-only, as retail's /O1 caller sees it).
namespace _STL { template <> int &map<ObjectID, int>::operator[](const ObjectID &); }

class Player;
#include "../../../../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;
extern GameLogic *TheGameLogic;
#include "../../../../../../Include/Common/Rva005C4AD1LeaField.h"
typedef _STL::vector<ObjectID> IdRange;
struct Record { Rva005C4AD1LeaField *units; void *reserved; Rva005C4AD1LeaField *structures; };
class Object { public: char pad[0x38]; Coord3D pos; char pad44[0x74 - 0x44]; ObjectID id; };
struct Thing;
#include "../../../../../../Include/GameLogic/AITarget.h"
#include "../../../../../../Include/Common/AITargetHeuristicEnemyStructure.h"

void AITargetHeuristicEnemyStructure::findBestTarget(AITarget *target, Player *attacker, Player *defender)
{
	Record *myStats = (Record *)TheSkirmishAIManager->rva002A8F24(attacker);
	IdRange *units = (IdRange *)myStats->units->get();
	Record *enemyStats = (Record *)TheSkirmishAIManager->rva002A8F24(defender);
	IdRange *structures = (IdRange *)enemyStats->structures->get();
	_STL::map<ObjectID, int> votes;
	for (ObjectID *it = units->begin(); it != units->end(); ++it) {
		Object *unit = TheGameLogic->findObjectByID(*it);
		if (!unit)
			continue;
		ObjectID best = INVALID_OBJECT_ID;
		float bestDistance = -1.0f;
		for (ObjectID *objectID = structures->begin(); objectID != structures->end(); ++objectID) {
			Object *obj = TheGameLogic->findObjectByID(*objectID);
			if (obj && (unsigned char)isValidTarget((Thing *)obj, attacker)) {
				float dx = obj->pos.x - unit->pos.x;
				float dy = obj->pos.y - unit->pos.y;
				float distance = dx * dx + dy * dy;
				if (bestDistance < 0.0f || distance < bestDistance) {
					bestDistance = distance;
					best = obj->id;
				}
			}
		}
		if (best) {
			_STL::map<ObjectID, int>::iterator i = votes.find(best);
			if (i != votes.end())
				++i->second;
			else
				votes[best] = 1;
		}
	}
	if (!votes.empty()) {
		ObjectID building = INVALID_OBJECT_ID;
		int maximum = 0;
		for (_STL::map<ObjectID, int>::iterator i = votes.begin(); i != votes.end(); ++i) {
			if (i->second > maximum) {
				building = i->first;
				maximum = i->second;
			}
		}
		target->setTarget(TheGameLogic->findObjectByID(building), TheSkirmishAIManager->field_884);
	}
}
