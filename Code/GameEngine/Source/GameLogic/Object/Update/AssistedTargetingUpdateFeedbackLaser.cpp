// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// BF1 AssistedTargetingUpdate_makeFeedbackLaser.cpp9cbfb551 and ZH
// makeFeedbackLaser supply identity/creation spine. BFME2 native486F35
// removes ZH setPosition and uses4-arg Laser init36355C, team Player+2EC.
// Native486F35..487010 RET12; static key LaserUpdate nativeguardE038B8.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include <string.h>
#pragma function(memset)
class Team;class ThingTemplate;class Drawable;class ClientUpdateModule;
class Player {public:char pad[0x2EC];Team *team;};
#include "../../../Common/Thing/thing.h"
#include "../../../../Include/GameClient/Drawable.h"
class Object:public Thing {public:Player *getControllingPlayer() const;};
struct CreateMask {unsigned words[4];};
enum ObjectID; class ThingFactory {public:Object *newObject(const ThingTemplate *,Team *,const CreateMask *,ObjectID);};extern ThingFactory *TheThingFactory;
enum NameKeyType {NAMEKEY_INVALID=0};
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class ClientUpdateModule {};
class LaserUpdate:public ClientUpdateModule {public:void initLaser(const Object *,const Coord3D *,const Coord3D *,int);};
extern GameLogic *TheGameLogic;
class AssistedTargetingUpdate {public:char pad[8];Object *object;private:void makeFeedbackLaser(const ThingTemplate *,const Object *,const Object *);};
void AssistedTargetingUpdate::makeFeedbackLaser(const ThingTemplate *laserTemplate,const Object *from,const Object *to) {
 if(!object->getControllingPlayer()) return;
 Team *team=object->getControllingPlayer()->team;
 CreateMask mask;memset(&mask,0,sizeof(mask));
 Object *laser=TheThingFactory->newObject(laserTemplate,team,&mask,(ObjectID)0);
 if(!laser) return;
 Drawable *draw=laser->getDrawable();
 static const NameKeyType key=TheNameKeyGenerator->nameToKey("LaserUpdate");
 LaserUpdate *update=(LaserUpdate*)draw->findClientUpdateModule(key);
 if(!update){TheGameLogic->destroyObject(laser);return;}
 update->initLaser(object,&from->m_cachedPos,&to->m_cachedPos,0);
}
