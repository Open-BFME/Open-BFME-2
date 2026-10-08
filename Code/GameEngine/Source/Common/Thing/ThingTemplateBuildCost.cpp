// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD
// stlport
#include <algorithm>
// Target 0x0033A69A..0x0033A77F. ZH/BFME1 ThingTemplate::calcCostToBuild
// supplies the faction and handicap purpose; BFME2/WB BCB960 adds a builder
// interface factor, production modifiers, explicit price and AI discount.
// Existing address-derived signatures/providers are preserved. Arg2 is a
// builder address carried by the current int ABI view, not a boolean flag.
#include "ascii_string.h"
inline float CappedDiscount(const float& value) { return 1.0f > value ? value : 1.0f; }
class ThingTemplate;
class Object { public: void* rva0028BC94(); };
class PriceBuilderInterface { public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual float slot26(const ThingTemplate*);
};
class Handicap { public:
 enum HandicapType { BUILDCOST=0 };
 float getHandicap(HandicapType,const ThingTemplate*) const;
};
class Player { public:
 unsigned char gap00[0x3C]; Handicap handicap;
 float getProductionCostChangeBasedOnTemplate(const ThingTemplate*,bool);
};
class Rva002AD5ED { public: float rva002AD5ED(const AsciiString&); };
class Rva002A9BF2 { public: void* rva002A9BF2(); };
struct Rva002A8AB1Record;
class Rva002A8F24 { public:
 unsigned char gap00[0x850]; float discount;
 Rva002A8AB1Record* rva002A8AB1(void*);
};
// Reuse the data-ledger provider, defined by Rva005EEA20Find.cpp.
extern Rva002A8F24* g_00DFEEF8;
class Overridable;
class Rva0033A68A { public: Overridable* rva0033A68A(); };
class ThingTemplate { public:
 unsigned char gap00[0x64]; AsciiString name;
 unsigned char gap68[0x5DA-0x68]; unsigned short buildCost;
 int rva0033A69A(const Player*,int,int) const;
};
int ThingTemplate::rva0033A69A(const Player*player,int builderAddress,int price) const
{
 int baseCost;
 if(price==-1)baseCost=((const ThingTemplate*)((Rva0033A68A*)this)->rva0033A68A())->buildCost;
 else baseCost=price;
 if(!player)return baseCost;
 float builderFactor=1.0f;
 if(builderAddress) {
  PriceBuilderInterface*module=(PriceBuilderInterface*)((Object*)builderAddress)->rva0028BC94();
  if(module)builderFactor=module->slot26(this);
 }
 float factionFactor=((Rva002AD5ED*)player)->rva002AD5ED(name)+1.0f;
 factionFactor*=((Player*)player)->getProductionCostChangeBasedOnTemplate(this,false);
 float handicap=player->handicap.getHandicap(Handicap::BUILDCOST,this); float cost=baseCost; cost*=handicap;cost*=factionFactor;cost*=builderFactor;
 if((int)((Rva002A9BF2*)player)->rva002A9BF2()==3 && g_00DFEEF8->rva002A8AB1((void*)player)) {
  return (int)(cost*(1.0f-CappedDiscount(g_00DFEEF8->discount)));
 }
 return (int)cost;
}
