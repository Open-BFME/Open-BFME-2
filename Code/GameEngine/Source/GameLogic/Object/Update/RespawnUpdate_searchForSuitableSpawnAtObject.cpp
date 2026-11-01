// cl: /MD /GX
//
// ?searchForSuitableSpawnAtObject@RespawnUpdate@@QAEPAVObject@@XZ, retail 0x004AF1CE, 143 bytes.
// A RespawnUpdate member (layout as RespawnUpdateCtor.cpp: +0x04 the module
// data, +0x08 the object; caller 0x004AFA17 in the unrowed 0x004AF92F): the
// closest object within 1000000 of ours that passes the 0x00260E2A filter
// (its controlling player) and the 0x002614EC one (the module data's +0x08,
// that player, true), or our own object when there is none.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline. The
// inline destructors only restore the base vftable, which cl drops here.
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD04, allow 0x00260E2A, slot 2 0x00260E1E: +0x08 a player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
enum UpdateSleepTime {UPDATE_SLEEP_FOREVER=0x3fffffff};
enum DisabledType;
enum ObjectStatusTypes;
class Player;
class ExitInterface;
class BodyModuleInterface;
class FXList;
class ThingTemplate;
class Image;
class AIUpdateInterface;
class INI;
class Object {public:
 ExitInterface *getObjectExitInterface() const;
 void restoreObjectToWorld(const Coord3D *);
 void rva001E42F2(const int *);
 void rva001E431E(const int *);
 void setStatus(ObjectStatusTypes,bool);
 bool clearDisabled(DisabledType);
 void setDisabledUntil(DisabledType,unsigned);
 Player *getControllingPlayer() const;
 __forceinline const Coord3D *getPosition() const {return &position;}
 __forceinline ThingTemplate *getTemplate() const {return m_template;}
 char pad00[4];ThingTemplate *m_template;char pad08[0x38-0x08];Coord3D position;char pad44[0x74-0x44];int m_heroKey;ObjectID producer;
 char pad7C[0x254-0x7C];BodyModuleInterface *body;AIUpdateInterface *ai;
 char pad25C[0x45C-0x25C];int handle;
};

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface {public:virtual void slot0()=0;};

class BehaviorModule:public ObjectModule,public BehaviorModuleInterface {public:virtual ~BehaviorModule();};

class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};

class UpdateModule:public BehaviorModule,public UpdateModuleInterface {public:virtual ~UpdateModule();protected:void setWakeFrame(Object *,UpdateSleepTime);private:unsigned nextWake;int index,reserved;};


class RespawnUpdate:public UpdateModule {
public:
	virtual UpdateSleepTime update();
	virtual NameKeyType getModuleNameKey() const;
	virtual float getPercentReady(int *out);
	virtual const Image *getDeadImage();
	void rva004AF182();
	void *rva004AF25D();
	Object *searchForSuitableSpawnAtObject();
	static void iniParseNewRuleForLevel(INI *, void *, void *, const void *);
	static void iniParseDefaultRule(INI *, void *, void *, const void *);
public:
	float health;
	const Image *deadImage;
	void *respawnTemplate;
	unsigned state;
	ObjectID spawnAt;
	int at34,at38,at3C;
	bool at40,at41;
};

class RespawnUpdateModuleData {
public:
	char pad00[8];
public:
	char filter08[4];
public:
	char pad0C[0x58-0x0C];
public:
	int conditions58[19];
public:
	int conditionsA4[19];
public:
	const FXList *deathFX,*reviveFX;
public:
	char padF8[8];
public:
	unsigned reviveTime;
public:
	int calcCostToBuild(int value);
public:
	int calcTimeToBuild(unsigned int value);
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;


Object *RespawnUpdate::searchForSuitableSpawnAtObject()
{
	Object *obj = m_object;
	const RespawnUpdateModuleData *md = reinterpret_cast<const RespawnUpdateModuleData *>(getModuleData());
	Rva00260E2AFilter player(obj->getControllingPlayer());
	Rva002614ECFilter same(md->filter08, obj->getControllingPlayer(), true);
	player.link(&same);
	Object *found = ThePartitionManager->getClosestObject(&obj->position, 1000000.0f, 0, &player);
	if (found == 0)
		found = obj;
	return found;
}
