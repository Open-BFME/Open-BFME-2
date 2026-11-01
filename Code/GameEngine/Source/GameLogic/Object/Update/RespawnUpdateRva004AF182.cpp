// cl: /MD
// RespawnUpdate entry RVA 0x004AF182, native [4AF182,4AF1CE), RET.
// RespawnBody::apply's proved lookup of "RespawnUpdate" calls this entry
// at 4C14A8 and 4C14CA. The constructor at 4AF096 independently establishes
// the module/object pointers (+4/+8) and state/timer fields (+2C/+30).
// Module data supplies two 0x4C-byte condition sets at +C and +58.
// The original method name is unknown; retain its target address.

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

class Rva001E42F2 { public: void rva001E42F2(const int *); };
struct RespawnUpdateData004AF182 {
    unsigned char before0C[0xC];
    int conditions0C[19];
    int conditions58[19];
};

void RespawnUpdate::rva004AF182()
{
    Object *obj = m_object;
    const RespawnUpdateData004AF182 *md = reinterpret_cast<const RespawnUpdateData004AF182 *>(getModuleData());
    if (state != 0) {
        ((Rva001E42F2 *)obj)->rva001E42F2(md->conditions0C);
        ((Rva001E42F2 *)obj)->rva001E42F2(md->conditions58);
        obj->clearDisabled((DisabledType)4);
        setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
        spawnAt = INVALID_OBJECT_ID;
        state = 2;
    }
}
