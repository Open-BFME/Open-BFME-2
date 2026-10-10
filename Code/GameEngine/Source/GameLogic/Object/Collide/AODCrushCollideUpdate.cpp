// cl: /DNDEBUG /MD
// Retail 0x004BC2E6 (63 bytes): ?update@AODCrushCollide@@UAE?AW4UpdateSleepTime@@XZ.
// Identity: slot 0 of the vtable 0x00C5A254 that the matched AODCrushCollide
// dtor 0x004BBEDD installs at +0x10, the UpdateModuleInterface base of an
// UpdateModule (slots 1/2 are the shared UpdateModule defaults 0x00253376 /
// 0x0044DF8D seen in every update vtable), i.e. update(); it returns 1
// (UPDATE_SLEEP_NONE) or 0x3FFFFFFF (UPDATE_SLEEP_FOREVER). cl 7.1 compiles
// the override with the +0x10 subobject this, hence [esi-8] for the Object.
// Body: while the +0x2C flag is set and the +0x24 frame is behind
// TheGameLogic frame (+0x40), clear condition bit 1*32+9 and the flag.
// Members +0x24/+0x28/+0x2C as the matched ctor 0x004BC00D initialises them.
//
// Model-condition bits: the word array of the Object starts at +0x10C (the
// variable-index set/test in 0x00293A05 addresses [obj + word*4 + 0x10C]); a
// bit index is word*32 + bit. The accessors return the masked word rather
// than a bool and the update is a free __forceinline helper that calls the
// pinned condition-changed notifier 0x0028AE6D (?rva0028AE6D@Object@@QAEXXZ)
// only when the bit changed; this is the BFME1 HordeGarrisonContainCtor.cpp
// recipe (mask in a register and test/or on the member for a set, byte-narrowed
// test/and for a clear). With the array based at +0x110 instead, a word-0 access
// keeps the array address in a register (lea), which retail never does.

// AODCrushCollide::onCollide, retail 0x004BC0B8..0x004BC2E6, full 558B.
// Target identity: native ctor 0x004BC00D installs table VA 0x00C5A23C at
// complete-object +0x20; slot0 points here. Native RET12 and the actual
// collision response establish CollideModuleInterface's three-argument
// contract (other, location, normal), corroborated by the committed BFME1
// CollideModule.h. Location and normal are unused. The old update63 shares
// this exact object's fields, so this file owns both responses.
// Target fields: other/own body +0x25C flag+0x5C; destruction flag+0x438;
// condition bit41; frame+0x24; other ID+0x28; active+0x2C. Damage records
// occupy 0x7C bytes and call the existing actual Rva00263895Member owner,
// rather than adding a constructor alias. Data+0x2C is the rowed filter;
// data+0x08..0x1C are the size-selected FX/OCL pair. Other data names remain
// unknown. The two virtual forwarding contracts below retain unknown owners.
// Reference provenance: Open-BFME-1 575ba2b04743f190f069805fbdc59936123c45da,
// AODCrushCollideConstructor.cpp and AODCrushCollideUpdate.cpp establish the
// subsystem/layout relationship; they do not contain this collision body.
// All control flow, offsets and call destinations here follow native BFME2.
// Normal regional settings are /O1 /arch:SSE /G7. No pins or aliases added.

class Drawable; class DamageInfo; class Player;
struct Coord3D; class Object;
enum KindOfType { KIND_RAW_D7=0xd7 };
enum Relationship { ENEMIES, NEUTRAL, ALLIES };
template<class T> static __forceinline T &rawField(void *p, int offset) { return *(T *)((char *)p+offset); }
class Rva00263895Member {
public:
 Rva00263895Member() throw();
 unsigned char pad00[8];
 unsigned int sourceID;
 unsigned char pad0c[4];
 int kind;
 unsigned char pad14[8];
 int death;
 float amount;
 unsigned char tail24[0x7c-0x24];
};
class Rva2225E0Filter { public: bool accepts(Object *, Player *); };
class FXList { public: static void doFXObj(const FXList *,const Object *,const Object *); };
class ObjectCreationList { public: void create(void *,void *,void *); };
extern int g_Va00DBA4E4;

class Rva0010CConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};
class Object
{
public:
	void rva0028AE6D();
 bool isKindOf(KindOfType) const;
 Relationship getRelationship(const Object *) const;
 Player *getControllingPlayer() const;
 void attemptDamage(DamageInfo *);

	Drawable *getDrawable() const;
	unsigned char m_pad000[0x10C];
	Rva0010CConditionBits m_conditionBits; // +0x10C
};
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
class Thing;
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
 void friend_awakenUpdateModule(Object *,UpdateModule *,unsigned int);
private:
	unsigned char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;
class AODCrushCollideIface20
{
public:
	virtual void onCollide(Object *,const Coord3D *,const Coord3D *);
};
class AODCrushCollide : public UpdateModule, public AODCrushCollideIface20
{
public:
	virtual UpdateSleepTime update();
 virtual void onCollide(Object *,const Coord3D *,const Coord3D *);
private:
	unsigned int m_24;
	int m_28;
	bool m_2C;
};
UpdateSleepTime AODCrushCollide::update()
{
	if (m_2C)
	{
		if (m_24 < TheGameLogic->getFrame())
		{
			clearModelConditionBit(m_object, 1 * 32 + 9);
			m_2C = false;
		}
		return UPDATE_SLEEP_NONE;
	}
	return UPDATE_SLEEP_FOREVER;
}

class Rva004BC0B8Listener { public:
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
 virtual void slot48();
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
 virtual void notify(Object *,Object *);
};
class Rva004BC0B8State { public:
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
 virtual Rva004BC0B8Listener *lookup();
};

void AODCrushCollide::onCollide(Object *other,const Coord3D *,const Coord3D *)
{
 if (!other) return;
 void *otherBody=rawField<void *>(other,0x25c);
 Object *self=m_object;
 if (otherBody && rawField<bool>(otherBody,0x5c)) return;
 if (rawField<unsigned char>(self,0x438)&1) return;
 if (self->isKindOf(KIND_RAW_D7)) return;
 void *selfBody=rawField<void *>(self,0x25c);
 if (selfBody && rawField<bool>(selfBody,0x5c)) return;
 if (other->getRelationship(self)==ALLIES) return;
 void *update=rawField<void *>(self,0x274);
 if (update) {
  void *state=rawField<void *>(update,0x250);
  if(state) {
   Rva004BC0B8Listener *listener=((Rva004BC0B8State *)state)->lookup();
   if(listener) {
    listener->notify(self,other);
   }
  }
 }
 if(rawField<unsigned char>(other,0x438)&1) return;
 otherBody=rawField<void *>(other,0x25c);
 if (!otherBody || rawField<bool>(otherBody,0x5c)) return;
 if(!m_2C) {
  m_2C=true;
  if (!self->m_conditionBits.test(41)) {
   self->m_conditionBits.set(41);
   self->rva0028AE6D();
  }
  TheGameLogic->friend_awakenUpdateModule(self,this,TheGameLogic->getFrame()+2*g_Va00DBA4E4);
  m_24=TheGameLogic->getFrame()+2*g_Va00DBA4E4;
 }
 m_24=TheGameLogic->getFrame()+2*g_Va00DBA4E4;
 Rva00263895Member damage;
 void *data=(void *)m_moduleData;
 bool selected=((Rva2225E0Filter *)((char *)data+0x2c))->accepts(other,self->getControllingPlayer());
 float amount;
 if (selected) {
  damage.kind=rawField<int>(data,0x30);
  damage.death=rawField<int>(data,0x34);
  amount=rawField<float>(data,0x38);
 } else {
  damage.kind=rawField<int>(data,0x20);
  damage.death=rawField<int>(data,0x24);
  amount=rawField<float>(data,0x28);
 }
 damage.sourceID=rawField<unsigned int>(self,0x74);
 damage.amount=amount;
 other->attemptDamage((DamageInfo *)&damage);
 m_28=rawField<int>(other,0x74);
 if(selected) {
  Rva00263895Member selfDamage;
  selfDamage.kind=rawField<int>(data,0x3c);
  selfDamage.death=rawField<int>(data,0x40);
  selfDamage.amount=rawField<float>(data,0x44);
  selfDamage.sourceID=rawField<unsigned int>(other,0x74);
  self->attemptDamage((DamageInfo *)&selfDamage);
 }
 signed char size=rawField<signed char>(rawField<void *>(other,4),0x5f5);
 const FXList *fx;
 ObjectCreationList *ocl;
 switch(size) {
 case 0: fx=rawField<const FXList *>(data,8);ocl=rawField<ObjectCreationList *>(data,0xc);break;
 case 1: fx=rawField<const FXList *>(data,0x10);ocl=rawField<ObjectCreationList *>(data,0x14);break;
 default: fx=rawField<const FXList *>(data,0x18);ocl=rawField<ObjectCreationList *>(data,0x1c);break;
 }
 if (fx) FXList::doFXObj(fx,other,self);
 if (ocl) ocl->create(other,self,0);
}
