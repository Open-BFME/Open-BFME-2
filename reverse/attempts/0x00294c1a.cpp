// ?rva00294C1A@Object@@QAEXTObjectExperienceVictim@@TObjectExperienceFlag@@M@Z
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD
// Retail Object gap: the existing 0x00294C1A pin and BloodthirstyUpdate
// caller prove the Object receiver and victim/bool/float ABI. ZH Object.cpp
// scoreTheKill supplies the experience-grant purpose; BFME2 splits that
// role into this worker and adds modifier and contained-object routing.
// Native +0x264 tracker, +0x47C flag, and vslots 48/142 are target facts.
class Object;
union ObjectExperienceVictim { Object *object; float points; };
union ObjectExperienceFlag { bool flag; float bonus; };
class Rva0039ADF3 { public: bool rva0039AE04() const; };
class Rva0039ACBD { public: int rva0039ACBD(const Object *,bool); };
class Rva0039AF9B { public: float rva0039AF9B(float); };
class ExperienceTracker { public: void rva0039B315(float,bool,bool,bool,bool); unsigned char pad[0x20]; unsigned char flag; };
class AttributeModifierPoolUpdate { public: bool rva00403448(int,float*,int,int); };
class ObjectVirtualView {
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
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
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void grant(Object *,float);
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void slot118();
	virtual void slot119();
	virtual void slot120();
	virtual void slot121();
	virtual void slot122();
	virtual void slot123();
	virtual void slot124();
	virtual void slot125();
	virtual void slot126();
	virtual void slot127();
	virtual void slot128();
	virtual void slot129();
	virtual void slot130();
	virtual void slot131();
	virtual void slot132();
	virtual void slot133();
	virtual void slot134();
	virtual void slot135();
	virtual void slot136();
	virtual void slot137();
	virtual void slot138();
	virtual void slot139();
	virtual void slot140();
	virtual void slot141();
	virtual int query();
};
class ObjectExpSink { public: virtual void grant(float); };
int Rva0047FDFEGet(void *);
enum ObjectStatusTypes { STATUS_CONSTRUCTION=2, STATUS_39=0x39, STATUS_32=0x32 };
enum KindOfType { KINDOF_84=0x84 };
enum Relationship { ENEMIES=0,NEUTRAL=1,ALLIES=2 };
enum WeaponSlotType { PRIMARY=0 };
class Rva002C9400ByteField { public: unsigned char get() const; };
class Weapon { public: char pad[4]; Rva002C9400ByteField *info; };
struct ObjectExperienceTemplate { char pad[0x11f]; unsigned char flags11f; };
class Object {
public:
 void rva00294C1A(ObjectExperienceVictim,ObjectExperienceFlag,float);
 bool rva0029493F(Object *,int);
 int rva002957FC();
 bool canCrushOrSquishNoAlly(Object *,int);
 bool testStatus(ObjectStatusTypes) const;
 __forceinline ExperienceTracker *getExperienceTracker() const { return tracker; }
 bool isKindOf(KindOfType) const;
 Relationship getRelationship(const Object *) const;
 const Weapon *getCurrentWeapon(WeaponSlotType *) const;
 void *rva0029439D();
 Object *rva002931F5(bool);
private:
 AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
 char pad0[4]; ObjectExperienceTemplate *tmpl;
 char pad8[0x118-8];
 unsigned int flags;
 char pad11c[0x264-0x11c];
 ExperienceTracker *tracker;
 char pad268[0x47c-0x268];
 unsigned char experienceFlag;
};
// The unions model reuse of four-byte argument slots, as in the BFME1
// Rva001C9380Object donor at 9cbfb551fe20dae985f91f2319d8997287b6a705.
// This raw ABI view preserves the pre-existing pointer/bool/float call ABI.
void Object::rva00294C1A(ObjectExperienceVictim victim,ObjectExperienceFlag flag,float scale) {
 if (tracker && ((Rva0039ADF3*)tracker)->rva0039AE04()) {
  if (victim.object->testStatus(STATUS_CONSTRUCTION)) return;
  victim.points=((Rva0039ACBD*)victim.object->tracker)->rva0039ACBD(this,flag.flag)*scale;
  float &points=victim.points;
  flag.bonus=1.0f;
  AttributeModifierPoolUpdate *pool=findAttributeModifierPoolUpdate();
  if (pool && pool->rva00403448(6,&flag.bonus,0,1)) points *= flag.bonus;
  ObjectVirtualView *receiver=(ObjectVirtualView*)rva0029439D();
  if (receiver) {
   scale=points;
   Object *related=rva002931F5(false);
   if (related->getExperienceTracker()) scale=((Rva0039AF9B*)related->getExperienceTracker())->rva0039AF9B(points);
   receiver->grant(this,scale);
  } else tracker->rva0039B315(points,true,true,true,false);
  if (points>0.0f) {
   experienceFlag |= tracker->flag;
   ObjectExpSink *sink=(ObjectExpSink*)Rva0047FDFEGet(this);
   if (sink) sink->grant(points);
  }
 }
}
bool Object::rva0029493F(Object *victim,int mode) {
 if (!canCrushOrSquishNoAlly(victim,mode)) return false;
 if (testStatus(STATUS_39) || testStatus(STATUS_32) || isKindOf(KINDOF_84)) return true;
 if (getRelationship(victim)!=ENEMIES) return false;
 const Weapon *weapon=getCurrentWeapon(0);
 if (weapon && !weapon->info->get()) return false;
 return true;
}
int Object::rva002957FC() {
 if (!(tmpl->flags11f & 1)) return false;
 ObjectVirtualView *receiver=(ObjectVirtualView*)rva0029439D();
 if (receiver) return receiver->query();
 unsigned int value=flags;
 unsigned int mask=1;
 return ((unsigned char)(value >> 7) & (unsigned char)mask)!=0 || ((unsigned char)(value >> 9) & (unsigned char)mask)!=0;
}
