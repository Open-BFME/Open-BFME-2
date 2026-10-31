// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include /Ireference/shims/iniexception /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// BannerCarrier update394 directly calls this native214B spawn helper.
// BFME1 update donor final contained-object helper supplies its semantic
// relation; target retail/WB establish slot95 cap,98 count,99 spawn.
// Original internal method name remains unknown. W3DBridge::setEnabled
// is the existing folded +110 Boolean setter provider; the receiver here
// is Player's +3BC credit view, not established as a W3DBridge instance.
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Common/Snapshot.h"
#include <vector>
class Object;

class Player;

class FXList;

class Module;

class UpgradeTemplate;

class Gen_0028EF10;

struct ObjectInner04;

class Rva00496B48;

struct BfmeMorphCondition;

struct BfmeExpLevelDraw;

enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };

enum KindOfType { KINDOF_DUMMY=0 };

enum ObjectStatusTypes { STATUS_DUMMY=0 };

enum NameKeyType
{
	NK_UNKNOWN = 0
};

template<int N> class BannerSlots : public BannerSlots<N-1> { public: virtual void gap(char (*)[N])=0; };

template<> class BannerSlots<0> {};

class AIUpdateInterface : public BannerSlots<142> { public:
 virtual void chooseLocomotorSet(int set); // slot 142, 0x238
 bool isMoving() const;
 char pad04[0x3B1-4]; bool pending; // +0x3B1
};

class BannerContainResult : public BannerSlots<36> { public: virtual bool testRefresh(int *,unsigned)=0; };

class BannerContain : public BannerSlots<31> { public: virtual BannerContainResult *getHorde()=0; };

class BannerSpawnHorde:public BannerSlots<95> {
public: virtual unsigned cap()=0; virtual void slot96()=0;virtual void slot97()=0;
 virtual unsigned count()=0;virtual Object *spawn(void *)=0;
};

class W3DBridge { public: void setEnabled(bool); char pad00[0x110];bool enabled; };

class Player { public: char pad00[0x3BC];W3DBridge credits; };

class Object { public:
 bool isKindOf(KindOfType) const;
 bool testStatus(ObjectStatusTypes) const; // 0x0004E536
 bool hasUpgrade(const UpgradeTemplate *) const;
 Object *rva002931F5(bool);
 int rva0028AF76() const;
 Player *getControllingPlayer() const; // 0x0028AFA9
 void *rva0028C197() const; // 0x0028C197
 void rva0028CFB2(const int *clearFlags, const int *setFlags);
 void updateShroudNow(); // 0x0028C11A
 const Coord3D *getPosition() const { return &m_position; }
 AIUpdateInterface *getAI() const { return m_ai; }
 char pad00[4]; ObjectInner04 *m_04; // +0x04
 char matrix[0x30]; // +0x08
 Coord3D m_position; // +0x38
 char pad44[0x24C-0x44]; Gen_0028EF10 *m_stats; BannerContain *m_contain; // +0x24C, +0x250
 char pad254[4]; AIUpdateInterface *m_ai; // +0x258
 char pad25C[0x274-0x25C]; Object *m_containedBy; // +0x274
protected:
 Module *findModule(NameKeyType key) const;
};

class FXList
{
public:
	static void doFXObj(const FXList *,const Object *,const Object *); // 0x000B2235
};

class Rva00496B48
{
public:
	bool rva00496B48();
	char m_pad00[0x8];
private:
	Object *m_obj08; // +0x08
};

// Field identity is retail's own INI table at 0x00C4F9E8; the +0x18/+0x24 element
// classes keep the names the ledger's vector destructor rows carry.
class BannerCarrierUpdateModuleData : public Snapshot
{
public:
	BannerCarrierUpdateModuleData();
	virtual ~BannerCarrierUpdateModuleData();
	AsciiString rva00496DA3(const AsciiString &name) const;
	const FXList *getFX() const { return m_bannerMorphFX; }
	int m_unused04; // +0x04
	unsigned m_idleSpawnRate; // +0x08
	unsigned m_meleeFreeUnitSpawnTime; // +0x0C
	int m_diedRespawnTime; // +0x10
	int m_meleeFreeBannerReSpawnTime; // +0x14
	_STL::vector<BfmeMorphCondition *> m_morphConditions; // +0x18
	_STL::vector<BfmeExpLevelDraw *> m_expLevelDraws; // +0x24
	const FXList *m_bannerMorphFX; // +0x30
	const FXList *m_unitSpawnFX; // +0x34
	bool m_replenishNearbyHorde; // +0x38
	bool m_replenishAllNearbyHordes; // +0x39
	unsigned char m_pad3A[2]; // +0x3A
	float m_scanHordeDistance; // +0x3C
	AsciiString m_upgradeRequired; // +0x40
};

class BannerBase { public: virtual void slot0();
 Object *getObject() const { return object; }
 const BannerCarrierUpdateModuleData *data; Object *object;
};

class BannerOther { public: virtual void slot0(); };

class UpdateModuleInterface { public: virtual UpdateSleepTime update()=0; };

class BannerCarrierUpdate : public BannerBase, public BannerOther, public UpdateModuleInterface {
public:
 virtual UpdateSleepTime update();
 void rva004973CF(); bool rva00496BD2(Object *); void rva00496E05(void *entry, bool playFX);
public:
	virtual NameKeyType getModuleNameKey() const;
};

bool BannerCarrierUpdate::rva00496BD2(Object *obj) {
 Object *container=obj->m_containedBy;
 if(container) {
  BannerContain *contain=container->m_contain;
  if(!contain) return false;
  BannerSpawnHorde *bannerSpawnHorde=reinterpret_cast<BannerSpawnHorde *>(contain->getHorde());
  if(bannerSpawnHorde) {
   unsigned cap=bannerSpawnHorde->cap();
   unsigned count=bannerSpawnHorde->count();
   if(count<cap) {
    if(!reinterpret_cast<Rva00496B48 *>(this)->rva00496B48()) return false;
    Player *player=container->getControllingPlayer();
    W3DBridge *credits=&player->credits;
    bool enabled=credits->enabled;
    credits->setEnabled(false);
    Object *created=bannerSpawnHorde->spawn(obj->matrix);
    if(created) {
     const BannerCarrierUpdateModuleData *bannerSpawnConfig=data;
     created->updateShroudNow();
     const FXList *fx=bannerSpawnConfig->m_unitSpawnFX;
     if(fx) FXList::doFXObj(fx,created,0);
     credits->setEnabled(enabled);
     return true;
    }
    credits->setEnabled(enabled);
   }
  }
 }
 return false;
}
