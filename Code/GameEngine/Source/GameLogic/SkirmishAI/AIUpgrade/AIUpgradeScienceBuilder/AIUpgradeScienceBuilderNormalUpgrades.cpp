// cl: /O1 /GX- /arch:SSE2 /MD /ICode/GameEngine/Source/Common
// Native 00597983..00597B32 full RET body; WB 01533650 names
// AIUpgradeScienceBuilder::buildNormalUpgrades as a callgraph lead only.
// Keep the existing address-qualified provider name rather than assert that identity.
// Owner14, record vector24/28, config160/16C, budget94, cost2C and
// flags34/result40 are target accesses corroborated by the matched siblings.
// Slot6 schedules the chosen record. Config floats C8..D4 are observed ranges;
// complete class and configuration extents remain unresolved.
// The historical 59710E void row has an established int-return call pin;
// both this native caller and matched 5978ED consume EAX. Preserve that ABI.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Player { public: char pad00[0x94]; unsigned money; };
#include "../../../Object/object.h"
class Rva004E9378 { public: bool rva004E9378(); };
class Rva005970ED {
 public: int rva0059710E(int);
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void build(Player *,int);
 float delay; ObjectID id; char pad0C[0x2c-0x0c]; int cost; int command; bool upgrading; char pad35[0x40-0x35]; int result;
};
class Rva005978ED { public: Rva005970ED *rva005978ED(); };
struct ScienceUpgradeConfig { char pad00[0xc8]; float min0,max0,min1,max1; };
struct Rva002A8AB1Record
{
public:
	int get16C() const { return m_16C; }
	char m_pad00[0x160];
	ScienceUpgradeConfig *config; // +0x160
	char m_pad164[0x8];
	int m_16C; // +0x16C
};
#include "../../../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;
float GetGameLogicRandomValueReal(float,float,char *,int);
class Rva00597983
{
public:
	void rva00597983();
	char m_pad00[0x14];
private:
	Player *owner; // +0x14
	char m_pad18[0xC];
	Rva005970ED **begin; // +0x24
	Rva005970ED **end; // +0x28
};
void Rva00597983::rva00597983()
{
 unsigned count=0;
 Rva005970ED **finish=end;
 for (Rva005970ED **i=begin;i!=finish;++i) {
  if (!((Rva004E9378 *)*i)->rva004E9378() && (*i)->upgrading) ++count;
 }
 Rva002A8AB1Record *ai=TheSkirmishAIManager->rva002A8AB1(owner);
 unsigned limit;
 switch(ai->m_16C) { case 1:limit=1;break;case 2:limit=3;break;default:return; }
 if (count>=limit) return;
 float factor=(float)(count+1);
 unsigned funds=owner->money;
 Rva005970ED *selected=((Rva005978ED *)this)->rva005978ED();
 if (!selected) {
  for (Rva005970ED **i=begin,**last=end;i!=last;++i) {
   Rva005970ED *item=*i;
   if (!item->upgrading) {
    int command=item->command; ObjectID id=item->id;
    if (!TheGameLogic->findObjectByID(id)->rva00294ADD(command) &&
     (!selected || item->cost<selected->cost) && funds>=item->cost*factor) {
    if (item->rva0059710E((int)owner)!=3) selected=item;
    }
   }
  }
 }
 if (selected) {
  selected->upgrading=true;
  switch(selected->result) {
   case 0:selected->delay=GetGameLogicRandomValueReal(ai->config->min0,ai->config->max0,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUpgrade\\AIUpgradeScienceBuilder\\AIUpgradeScienceBuilder.cpp",0x18b);break;
   case 1:selected->delay=GetGameLogicRandomValueReal(ai->config->min1,ai->config->max1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUpgrade\\AIUpgradeScienceBuilder\\AIUpgradeScienceBuilder.cpp",0x18e);break;
   case 2:selected->delay=-1.0f;break;
  }
  selected->build(owner,0);
 }
}
