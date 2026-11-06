// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
#define BFME_SNAPSHOT_NAME_SLOT
// BF1 AssistedTargetingUpdate_makeFeedbackLaser.cpp9cbfb551 and ZH
// makeFeedbackLaser supply identity/creation spine. BFME2 native486F35
// removes ZH setPosition and uses4-arg Laser init36355C, team Player+2EC.
// Native486F35..487010 RET12; static key LaserUpdate nativeguardE038B8.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include <string.h>
#pragma function(memset)
class Team;class ThingTemplate;class Drawable;class ClientUpdateModule;
#include "../../../../Include/Common/Player.h"
#include "../../../Common/Thing/thing.h"
#include "../../../../Include/GameClient/Drawable.h"
#include "../object.h"
struct CreateMask {unsigned words[4];};
#include "../../../../Include/Common/ThingFactory.h"
enum NameKeyType {NAMEKEY_INVALID=0};
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class ClientUpdateModule {};
class LaserUpdate:public ClientUpdateModule {public:void initLaser(const Object *,const Coord3D *,const Coord3D *,int);};
extern GameLogic *TheGameLogic;
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
class AssistedTargetingUpdate : public UpdateModule {
public:
 AssistedTargetingUpdate(Thing *,const ModuleData *);
 virtual ~AssistedTargetingUpdate();
 virtual NameKeyType getModuleNameKey() const;
 virtual UpdateSleepTime update();
protected:
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName() const;
 virtual void xfer(Xfer *);
private:
 void makeFeedbackLaser(const ThingTemplate *,const Object *,const Object *);
};
void AssistedTargetingUpdate::makeFeedbackLaser(const ThingTemplate *laserTemplate,const Object *from,const Object *to) {
 if(!m_object->getControllingPlayer()) return;
 Team *team=m_object->getControllingPlayer()->m_defaultTeam;
 CreateMask mask;memset(&mask,0,sizeof(mask));
 Object *laser=TheThingFactory->newObject(laserTemplate,team,&mask,(ObjectID)0);
 if(!laser) return;
 Drawable *draw=laser->getDrawable();
 static const NameKeyType key=TheNameKeyGenerator->nameToKey("LaserUpdate");
 LaserUpdate *update=(LaserUpdate*)draw->findClientUpdateModule(key);
 if(!update){TheGameLogic->destroyObject(laser);return;}
 update->initLaser(m_object,&from->m_cachedPos,&to->m_cachedPos,0);
}
