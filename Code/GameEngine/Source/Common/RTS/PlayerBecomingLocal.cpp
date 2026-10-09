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
class RGBColor {public:void setFromInt(int);float red,green,blue;};
template<int N> class PlayerLocalSlots:public PlayerLocalSlots<N-1>{public:virtual void slot(char(*)[N])=0;};
template<> class PlayerLocalSlots<0>{};
class GameClient:public PlayerLocalSlots<32>{public:virtual void setTeamColor(int,int,int)=0;};
extern GameClient *TheGameClient;
struct Rva002D76C6Owner;
class Radar {public:void removeObject(Rva002D76C6Owner*);void addObject(Object*);};
extern Radar *TheRadar;
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Drawable {public:void setIndicatorColor(int);};
class Thing {public:Drawable *getDrawable()const;};
class Module;
class Team;
class Player;
class SpecialDisguiseUpdate {public:void rva004B04B2(bool);};
struct ThingTemplate {unsigned char pad[0x113];unsigned char kind;};
class ContainLocalView:public PlayerLocalSlots<20>{public:virtual void recalcApparent()=0;};
class Rva00373EC6 {public:unsigned char pad[0x38];int playerIndex;unsigned disguise;};
class Object:public Thing {
public:bool isKindOf(KindOfType)const;Module *findModule(NameKeyType)const;Rva00373EC6 *rva0028F4BC();int getIndicatorColor()const;int getNightIndicatorColor()const;
 unsigned vptr;ThingTemplate *tmplate;unsigned char pad8[0x250-8];ContainLocalView *contain;unsigned char pad254[0x304-0x254];Team *team;
};
class PlayerList {public:Player *getNthPlayer(int);};
extern PlayerList *ThePlayerList;
class GlobalData {public:unsigned char pad[0x134];int timeOfDay;};
extern GlobalData *TheWritableGlobalData;
class BfmeMemberRV {public:bool bfmeAskRV();};
struct BfmeResultA {void *m_value;BfmeResultA();BfmeResultA(const BfmeResultA&);~BfmeResultA();};
class BfmeResultForwardA {public:BfmeResultA bfmeForwardResultA();};
extern PartitionManager *ThePartitionManager;
class Player {
public:void becomingLocalPlayer(bool);Relationship getRelationship(const Team*)const;
 unsigned char pad[0x280];int color,nightColor;
};
void Player::becomingLocalPlayer(bool yes)
{
 if(yes){
  GameClient *client=TheGameClient;
  if(client){RGBColor rgb;rgb.setFromInt(color);client->setTeamColor((int)(rgb.red*255),(int)(rgb.green*255),(int)(rgb.blue*255));}
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
    if(object->tmplate->kind&1){
     Drawable *draw=object->getDrawable();
     if(draw){
      Rva00373EC6 *update=object->rva0028F4BC();
      if(update && update->disguise){
       Player *disguised=ThePlayerList->getNthPlayer(update->playerIndex);
       if(getRelationship(object->team)!=ALLIES && ((BfmeMemberRV*)this)->bfmeAskRV()){
        if(TheWritableGlobalData->timeOfDay==4)draw->setIndicatorColor(disguised->nightColor);else draw->setIndicatorColor(disguised->color);
       }else{
        if(TheWritableGlobalData->timeOfDay==4)draw->setIndicatorColor(object->getNightIndicatorColor());else draw->setIndicatorColor(object->getIndicatorColor());
       }
       TheRadar->removeObject((Rva002D76C6Owner*)object);TheRadar->addObject(object);
      }
     }
    }
   }
  }
 }
}
