// cl: /MD
// ?internalChangeHealth@DelayedDeathBody@@QAEXMPAUDamageInfo@@@Z
// RVA 004C167E, DelayedDeathBody secondary BodyModule interface slot +0x80.
// Negative offsets address the primary module data and object through the
// unchanged interface receiver; the qualified owner preserves that provenance.
// Both upgrade predicates are evaluated. A transition clears the incoming
// damage flag and zeroes the amount according to module flag70.
class UpgradeTemplate; class Module; struct DamageInfo { unsigned char before24[0x24]; unsigned char flag24; };
enum NameKeyType;
// Native Player predicate 0x2AB87D is the rowed const UpgradeTemplate bit test.
// NameKeyGenerator 0x148E1A returns the same 32-bit NameKeyType enum.
class Player { public: bool rva002AB87D(const UpgradeTemplate*) const; };
class Object { public:
 Player *getControllingPlayer() const;
 bool rva00290D2B(const UpgradeTemplate*) const;
 // Retail's Object::findModule is a protected member, so the mangled call
 // name carries that access; only the friend below may call it here.
protected:
 Module *findModule(NameKeyType) const;
 friend class DelayedDeathBody;
};
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;
class LifetimeUpdate { public: void setLifetimeRange(unsigned int,unsigned int); };
class FXList { public: static void doFXObj(const FXList*,const Object*,const Object*); };
struct Rva004C167EData {
 unsigned char prefix[0x6C]; unsigned int time6C; bool flag70;
 unsigned char gap71[3]; const FXList *fx74; bool flag78;
 unsigned char gap79[3]; const UpgradeTemplate *upgrade7C;
};
struct Rva004C1395Owner { void apply(float,DamageInfo*); };
class DelayedDeathBody
{
public:
 // Unused virtual slot signatures are placeholders, not ABI claims.
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual float health();
 unsigned char beforeF0[0xec]; unsigned char started; unsigned char checked;
 Rva004C167EData *data() const {return *(Rva004C167EData**)((char*)this-12);}
 Object *object() const {return *(Object**)((char*)this-8);}
 void internalChangeHealth(float,DamageInfo*);
};
void DelayedDeathBody::internalChangeHealth(float amount,DamageInfo *info)
{
 Object *obj=object();
 const Rva004C167EData *module=data();
 Player *player=obj->getControllingPlayer();
 bool transitioned=false;
 if(!started) {
  if(!(checked && info && info->flag24==1)) {
   if(!module->flag78) goto finish;
   if(!(health()+amount<=0.0f)) goto finish;
  }
  if(module->upgrade7C) {
   bool playerComplete=player && player->rva002AB87D(module->upgrade7C);
   bool objectComplete=obj->rva00290D2B(module->upgrade7C);
   if(!playerComplete && !objectComplete) goto finish;
  }
  LifetimeUpdate *lifetime=(LifetimeUpdate*)object()->findModule((NameKeyType)TheNameKeyGenerator->nameToKey("LifetimeUpdate"));
  if(lifetime) lifetime->setLifetimeRange(module->time6C,module->time6C);
  if(!started) FXList::doFXObj(module->fx74,object(),0);
  info->flag24=0;
  started=1;
  transitioned=true;
 }
finish:
 if((checked || started) && (data()->flag70 || transitioned)) amount=0;
 if(started==1 && info && info->flag24==1) amount=-health();
 ((Rva004C1395Owner*)this)->apply(amount,info);
}

// Provenance: semantic donor Open-BFME-1 1281192f, retained unchanged at
// 6583b3c1ff21db4a561285717028fdafc780b7db in game/GameEngine/Source/
// GameLogic/Object/Body/DelayedDeathBody.cpp. The method name remains unknown.
// Target evidence: factory 0x2515E7 and ctor 0x4C15B9 establish the family;
// ctor installs vtable VA 0xC5BB38 at +0x10, slot +0x80 points to this body.
// Native [0x4C167E,0x4C17CC) ends RET8 and proves the secondary receiver,
// owner/data at -8/-12, flags +0xF0/+0xF1, data +0x6C/+0x70/+0x74/+0x78/
// +0x7C and damage flag +0x24 independently of the donor layout.
// At 0x4C17C0 retail calls 0x4C1395 with this unchanged, a float and the
// DamageInfo pointer. RespawnBody ctor 0x4C12EB installs VA 0xC5B8F0 at +0x10;
// its slot +0x80 points to that same RET8 body. The callee retains an address
// name because its original method identity has not been established.
