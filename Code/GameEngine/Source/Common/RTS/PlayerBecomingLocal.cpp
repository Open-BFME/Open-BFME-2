// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Clean ZH Player.cpp::becomingLocalPlayer supplies semantics; native2ADFF2
// and its owned PlayerList caller prove identity and BF2 field/call differences.
// Native fields: Player color280/night284; template kind byte113; Object
// contain250/team304; disguise descriptor player38/active3C; time-of-day134.
// Target adds condition300 SpecialDisguiseUpdate notification before the ZH
// disguise-color loop and omits the final ControlBar dirty call. Existing
// address-owned Radar owner and one-word partition-result call views preserve
// their proven pointer ABIs; original descriptor types remain unresolved.
#include "../PartitionRangeQueryCallView.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
enum KindOfType { KIND_ZERO=0 };
enum Relationship { ALLIES=2 };
#include "../../../../Libraries/Include/Lib/RGBColor.h"
template<int N> class PlayerLocalSlots:public PlayerLocalSlots<N-1>{public:virtual void slot(char(*)[N])=0;};
template<> class PlayerLocalSlots<0>{};
#include "../../../Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;
struct Rva002D76C6Owner;
#include "../../../Include/Common/Radar.h"
extern Radar *TheRadar;
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../Include/GameClient/Drawable.h"
#include "../Thing/thing.h"
class Module;
class Team;
class Player;
class SpecialDisguiseUpdate {public:void rva004B04B2(bool);};
#include "../../../Include/Common/ThingTemplate.h"
class ContainLocalView:public PlayerLocalSlots<20>{public:virtual void recalcApparent()=0;};
class Rva00373EC6 {public:unsigned char pad[0x38];int playerIndex;unsigned disguise;};
class Object:public Thing {
friend class Player;protected:Module *findModule(NameKeyType)const;
public:bool isKindOf(KindOfType)const;Rva00373EC6 *rva0028F4BC();int getIndicatorColor()const;int getNightIndicatorColor()const;
 unsigned char pad60[0x250-0x60];ContainLocalView *contain;unsigned char pad254[0x304-0x254];Team *team;
};
#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
class BfmeMemberRV {public:bool bfmeAskRV();};
struct BfmeResultA
{
public:
	BfmeResultA();
	BfmeResultA(const BfmeResultA&);
	~BfmeResultA();
	void *m_value; // +0x00
};
class BfmeResultForwardA {public:BfmeResultA bfmeForwardResultA();};
extern PartitionManager *ThePartitionManager;
#include "../../../Include/Common/Player.h"
void Player::becomingLocalPlayer(bool yes)
{
 if(yes){
  GameClient *client=TheGameClient;
  if(client){RGBColor rgb;rgb.setFromInt(m_color);client->setTeamColor((int)(rgb.red*255),(int)(rgb.green*255),(int)(rgb.blue*255));}
  if(ThePartitionManager){
   BfmeResultA iter=((BfmeResultForwardA*)ThePartitionManager)->bfmeForwardResultA();
   for(Object *object=((BfmeWideResult*)&iter)->next();object;object=((BfmeWideResult*)&iter)->next()){
    ContainLocalView *contain=object->contain;
    if(contain){contain->recalcApparent();TheRadar->removeObject((Rva002D76C6Owner*)object);TheRadar->addObject(object);}
    if(object->isKindOf((KindOfType)300)){
     static NameKeyType key=TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
     SpecialDisguiseUpdate *module=(SpecialDisguiseUpdate*)object->findModule(key);
     if(module)module->rva004B04B2(getRelationship(object->team)==ALLIES && ((BfmeMemberRV*)this)->bfmeAskRV());
    }
    if(object->m_template->m_kindof[2] & 0x1000000U){
     Drawable *draw=object->getDrawable();
     if(draw){
      Rva00373EC6 *update=object->rva0028F4BC();
      if(update && update->disguise){
       Player *disguised=ThePlayerList->getNthPlayer(update->playerIndex);
       if(getRelationship(object->team)!=ALLIES && ((BfmeMemberRV*)this)->bfmeAskRV()){
        if(TheWritableGlobalData->m_timeOfDay==4)draw->setIndicatorColor(disguised->m_nightColor);else draw->setIndicatorColor(disguised->m_color);
       }else{
        if(TheWritableGlobalData->m_timeOfDay==4)draw->setIndicatorColor(object->getNightIndicatorColor());else draw->setIndicatorColor(object->getIndicatorColor());
       }
       TheRadar->removeObject((Rva002D76C6Owner*)object);TheRadar->addObject(object);
      }
     }
    }
   }
  }
 }
}
