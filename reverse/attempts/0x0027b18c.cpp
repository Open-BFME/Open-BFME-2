// ?rva0027B18C@Drawable@@QAEXPAUDamageInfo@@@Z
// partial score=0.9045927228090382 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common
// Native 27B18C..27B47F RET4; unnamed WB CB7E40 supplies damage/EVA control flow.
// BF1 f989 / ZH Drawable lack this BF2 notification method; existing partition
// filter callers guide filter lifetime, while target vftables prove the slots.
#include "PartitionRangeQueryCallView.h"
struct Coord3D {float x,y,z;};
enum KindOfType {RvaKind0=0};
enum ObjectID {INVALID_ID=0};
class Player{public:char pad[0x54];int index;bool isLocalPlayer()const;};
struct DamageInfo{char pad0[8];ObjectID source;unsigned playerMask;int damageType;int p14;int p18;int p1c;char pad20[5];bool report;char pad26[0x70-0x26];float amount;};
struct BfmeDamageTemplate{char pad[0x10e];unsigned char flag10e;char pad10f[4];unsigned char flag113;char pad114[4];unsigned char flag118;char pad119[0x580-0x119];int event580,event584,event588,event58c;float range;unsigned delay;int event598;};
class Drawable;
class Object{public:void*vp;BfmeDamageTemplate*data;char pad08[0x38-8];Coord3D position;char pad44[0x260-0x44];void*radarInfo;Player*getControllingPlayer()const;bool isKindOf(KindOfType)const;bool rva00293926(KindOfType);bool rva00294471(void*,int);};
class Thing{public:Drawable*getDrawable()const;};
enum EvaEventID {EVA_INVALID=-1};
class Eva{public:bool isEventBlockedByTimeout(EvaEventID)const;bool isEventAboutToPlay(EvaEventID)const;void reportEvaEvent(int,const Coord3D*,int);};extern Eva*TheEva;
class Radar{public:void rva002D8B9D(Object*);};extern Radar*TheRadar;
class GameLogic{public:char pad[0x40];unsigned frame;Object*findObjectByID(ObjectID);};extern GameLogic*TheGameLogic;
class Rva002D3756{public:void rva002D3756(void*);};extern "C" Rva002D3756*g_pRva003BD424;
class BFMERopeDrawable{public:const Coord3D*getPosition()const;};
class Rva00271B03{public:void rva00271B03();};
class Rva000421C8{public:Rva000421C8():m_next(0){}virtual~Rva000421C8(){}virtual bool allow(Object*)=0;virtual int getPlayerMask();Rva000421C8*link(Rva000421C8*);Rva000421C8*m_next;};
class Rva00271B3CFilter:public Rva000421C8{public:Rva00271B3CFilter(int e):event(e){}virtual bool allow(Object*);int event;};
class Rva00260E2AFilter:public Rva000421C8{public:Rva00260E2AFilter(Player*p):player(p){}virtual bool allow(Object*);virtual int getPlayerMask();Player*player;};
extern PartitionManager*ThePartitionManager;
class Drawable{public:void rva0027B18C(DamageInfo*);char pad00[4];BfmeDamageTemplate*data;char pad08[0xfc-8];Object*object;char pad100[0x388-0x100];unsigned nextFrame;char pad38c[0x440-0x38c];bool active440;};
void Drawable::rva0027B18C(DamageInfo*damage){
Object*obj=object;if(!obj)return;
if((obj->data->flag10e&0x40)&&(obj->data->flag118&0x40))return;
Player*player=obj->getControllingPlayer();const BfmeDamageTemplate*templ;
if(!(damage->amount>0.0f)||damage->damageType==10||damage->damageType==7||damage->p1c==22||damage->p18==2||(damage->playerMask&(1<<player->index))||!player->isLocalPlayer())return;
templ=data;
if(damage->report){if(obj->radarInfo)TheRadar->rva002D8B9D(obj);
if(templ){Object*attacker=TheGameLogic->findObjectByID(damage->source);int event=templ->event598,other;
if(event!=-1&&!obj->isKindOf((KindOfType)157)&&!obj->rva00293926((KindOfType)63)&&!obj->rva00293926((KindOfType)37)&&attacker&&!attacker->rva00294471(player,1)){other=templ->event58c;}
else if(damage->damageType==23&&templ->event588!=-1){event=templ->event588;other=-1;}
else if(damage->damageType!=23&&attacker&&((Thing*)attacker)->getDrawable()&&((Thing*)attacker)->getDrawable()->active440&&templ->event584!=-1){event=templ->event584;other=templ->event58c;}
else{event=templ->event580;other=templ->event58c;}
if(event!=-1){
unsigned now=TheGameLogic->frame;
if(nextFrame<=now&&(TheEva->isEventBlockedByTimeout((EvaEventID)event)||TheEva->isEventAboutToPlay((EvaEventID)event))&&other!=-1)TheEva->reportEvaEvent(other,&obj->position,0);
else TheEva->reportEvaEvent(event,&obj->position,0);
float range=templ->range;
if(range<=0.0f||templ->event580==-1)((Rva00271B03*)this)->rva00271B03();
else{Rva00271B3CFilter eventFilter(templ->event580);Rva00260E2AFilter playerFilter(player);eventFilter.link(&playerFilter);
BfmeWideResult objects=ThePartitionManager->iterateObjectsInRange(((BFMERopeDrawable*)this)->getPosition(),range,2,&eventFilter,0);
for(Object*o=objects.next();o;o=objects.next())if(((Thing*)o)->getDrawable())((Rva00271B03*)((Thing*)o)->getDrawable())->rva00271B03();}
}
}
}
if(data->flag113&4)g_pRva003BD424->rva002D3756(obj);
}
