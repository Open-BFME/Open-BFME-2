// ?apply@Rva004C167EOwner@@QAEXMPAUDamageInfo@@@Z
// partial score=0.988023952095808 date=2026-10-04
// cl: /O1 /MD /arch:SSE /G7
// ?apply@Rva004C167EOwner@@QAEXMPAUDamageInfo@@@Z
// RVA 00212980, DelayedDeathBody secondary BodyModule interface slot +80.
// Negative offsets address the primary module data and object through the
// unchanged interface receiver; the qualified owner preserves that provenance.
// Both upgrade predicates are evaluated. A transition clears the incoming
// damage flag and zeroes the amount according to module flag70.
class UpgradeTemplate; class Module; struct DamageInfo { unsigned char before24[0x24]; unsigned char flag24; };
enum NameKeyType;
class Player { public: bool hasUpgradeComplete(const UpgradeTemplate*); };
class Object { public:
 Player *getControllingPlayer() const;
 bool rva00290D2B(const UpgradeTemplate*) const;
 // Retail's Object::findModule is a protected member, so the mangled call
 // name carries that access; only the friend below may call it here.
protected:
 Module *findModule(NameKeyType) const;
 friend struct Rva004C167EOwner;
};
class NameKeyGenerator { public: unsigned int nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;
class LifetimeUpdate { public: void setLifetimeRange(unsigned int,unsigned int); };
class FXList { public: static void doFXObj(const FXList*,const Object*,const Object*); };
struct Rva004C167EData {
 unsigned char prefix[0x6C]; unsigned int time6C; bool flag70;
 unsigned char gap71[3]; const FXList *fx74; bool flag78;
 unsigned char gap79[3]; const UpgradeTemplate *upgrade7C;
};
struct Rva004C1395Owner { void apply(float,DamageInfo*); };
struct Rva004C167EOwner {
 // Unused virtual slot signatures are placeholders, not ABI claims.
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual float health();
 unsigned char beforeF0[0xec]; unsigned char started; unsigned char checked;
 Rva004C167EData *data() const {return *(Rva004C167EData**)((char*)this-12);}
 Object *object() const {return *(Object**)((char*)this-8);}
 void apply(float,DamageInfo*);
};
void Rva004C167EOwner::apply(float amount,DamageInfo *info)
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
   bool playerComplete=player && player->hasUpgradeComplete(module->upgrade7C);
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

// Donor revision1281192f semantic guide; BFME2 factory2515E7/ctor4C15B9
// and DelayedDeath moduledata constructor4C180A independently establish the
// target class family. Native4C167E-4C17CC proves secondary receiver+10,
// owner/data at-8/-C, tailflagsF0/F1, modulefields6C/70/74/78/7C and damageflag24.
// The base damage routine4C1395 is still unrowed; original method name unknown.

// Pending pin: ?apply@Rva004C1395Owner@@QAEXMPAUDamageInfo@@@Z ->0x004C1395.
// DelayedDeath ctor4C15B9 installs C5BB38 at+10; independently verified slot32 ->4C167E.
