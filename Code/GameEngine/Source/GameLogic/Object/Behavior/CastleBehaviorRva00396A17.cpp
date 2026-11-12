// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"

class Player;
class Team;

#include "../../../../Include/Common/Player.h"

extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/Rva002A8AB1Record.h"

#include "../../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

#include "../object.h"

class FoundationAIUpdate
{
public:
	virtual void rva00455B67(Player *oldOwner, Player *newOwner);
};

class CastleBehavior : public FoundationAIUpdate
{
public:
	virtual void onCapture(Player *oldPlayer, Player *newPlayer);
};

static __declspec(noinline) void rva00396999(_STL::vector<ObjectID> *vec, Player *oldPlayer, Player *newPlayer)
{
	Rva002A8AB1Record *oldRecord = TheSkirmishAIManager->rva002A8AB1(oldPlayer);
	Rva002A8AB1Record *newRecord = TheSkirmishAIManager->rva002A8AB1(newPlayer);
	ObjectID *end = vec->end();
	for (ObjectID *it = vec->begin(); it != end; ++it)
	{
		Object *object = TheGameLogic->findObjectByID(*it);
		if (object)
		{
			if (oldRecord)
				oldRecord->rva002C6A4E(object);
			if (newRecord)
				newRecord->rva002C6A3D(object);
			object->setTeam(newPlayer->getDefaultTeam());
		}
	}
}

// ?onCapture@CastleBehavior@@UAEXPAVPlayer@@0@Z, retail 0x00396A17: slot 9 of
// CastleBehavior's table 0x0081A780, onCapture in the sibling module tables
// (TransportContain, RadarUpgrade). It runs the FoundationAIUpdate base slot
// (0x00455B67, still address-named) and then hands every owned object to the
// new owner's default team.
void CastleBehavior::onCapture(Player *oldPlayer, Player *newPlayer)
{
	FoundationAIUpdate::rva00455B67(oldPlayer, newPlayer);
	rva00396999((_STL::vector<ObjectID> *)((char *)this + 0x50), oldPlayer, newPlayer);
	rva00396999((_STL::vector<ObjectID> *)((char *)this + 0x5c), oldPlayer, newPlayer);
	rva00396999((_STL::vector<ObjectID> *)((char *)this + 0x68), oldPlayer, newPlayer);
	rva00396999((_STL::vector<ObjectID> *)((char *)this + 0x74), oldPlayer, newPlayer);
}
