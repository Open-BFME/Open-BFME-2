// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmelist
// stlport
// Native484B6B..484C3C RET0. Constructor484A67 installs secondary
// update table84A438 at complete+10. The preceding owned destructor ends
// at484B6B and the next deleting destructor starts at484C3C, proving extent.
// BF1 clean PassiveAreaEffectBehavior_update.cpp at575ba2b04 is the guide;
// target adds upgrade gating and returns nonzero module delay instead of1.
#include <list>
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Common/GameLogicObjectLookupView.h"
#include "../../../../Include/Common/ObjectModule.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class UpgradeTemplate;
class UpgradeCenter {public:const UpgradeTemplate *findUpgrade(const AsciiString&)const;};
extern UpgradeCenter *TheUpgradeCenter;
enum ObjectStatusTypes { status2 = 2 };
class PassiveAreaEffectBehavior;
class Player;
class BodyModule;
class AttributeModifierPoolUpdate;
class FXList;
class Object
{
	friend class PassiveAreaEffectBehavior;
public:
	void *rva0028BD17() const;
	bool testStatus(ObjectStatusTypes) const;
	bool hasUpgrade(const UpgradeTemplate *) const;
	int getID() const { return id; }
	Player *getControllingPlayer() const;
	bool rva0028C264(int *out, int frames);
	bool attemptHealingFromSoleBenefactor(float amount, const Object *source, unsigned int delay);
	bool addAttributeModifierToPool(const AsciiString &name, int value);
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	BodyModule *getBodyModule() const { return m_body; }
private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
public:
	char pad[0x38];
	Coord3D position; // +0x38
	char pad44[0x74 - 0x44];
	int id; // +0x74
private:
	char pad78[0x254 - 0x78];
	BodyModule *m_body; // +0x254
	char pad258[0x438 - 0x258];
	unsigned char m_438; // +0x438, bit 0 effectively dead
};
// Existing Object::testStatus uses the enum spelling below.
class Rva00484B6BCheckInterface {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual bool s2C();
};
struct AreaData
{
	char m_pad00[0x08];
	float m_effectRadius; // +0x08
	float m_healPercentPerSecond; // +0x0C
	unsigned int m_pingDelay; // +0x10
	const AsciiString *m_14Begin; // +0x14
	const AsciiString *m_14End; // +0x18
	char m_pad1C[0x20 - 0x1C];
	char m_allowFilter; // +0x20
	char m_pad21[0x24 - 0x21];
	AsciiString m_upgradeRequired; // +0x24
	bool m_nonStackable; // +0x28
	int m_antiCategories; // +0x2C
	const FXList *m_30; // +0x30
	const FXList *m_34; // +0x34
};
extern GameLogic *TheGameLogic;
class Thing;
class ModuleData;
class Xfer;

enum NameKeyType
{
	NK_UNKNOWN = 0
};


class BehaviorModuleBase
{
private:
	virtual ~BehaviorModuleBase();
public:
	const AreaData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
};

class PassiveAreaEffectBehavior : public UpdateModule
{
public:
	PassiveAreaEffectBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~PassiveAreaEffectBehavior();
	virtual void slot01() = 0;
	virtual void slot02() = 0;

protected:
	virtual void xfer(Xfer *xfer);

public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void rva00484C8B();
	virtual void rva004848E6(Object *obj);
	virtual void rva0048491F(Object *obj);
	virtual void rva00484A08(Object *obj);
	virtual UpdateSleepTime update();

private:
	unsigned int m_20; // +0x20
	_STL::list<int> m_trackedIds; // +0x24, runtime watch list
};
UpdateSleepTime PassiveAreaEffectBehavior::update()
{
 const AreaData *data=m_moduleData;
 Object *owner=m_object;
 unsigned delay=data->m_pingDelay;
 if(!delay)delay=1;
 if(!data->m_upgradeRequired.isEmpty()){
  const UpgradeTemplate *upgrade=TheUpgradeCenter->findUpgrade(data->m_upgradeRequired);
  if(!upgrade||!owner->hasUpgrade(upgrade))return (UpdateSleepTime)delay;
 }
 Rva00484B6BCheckInterface *iface=(Rva00484B6BCheckInterface*)owner->rva0028BD17();
 if(iface){if(iface->s2C())return (UpdateSleepTime)delay;}else if(owner->testStatus(status2))return (UpdateSleepTime)delay;
 if(owner->m_438&1)return UPDATE_SLEEP_FOREVER;
 unsigned frame=TheGameLogic->getFrame();
 if(frame-m_20>=data->m_pingDelay){
  rva00484C8B();
  m_20=frame;
 }
 for(_STL::list<int>::iterator it=m_trackedIds.begin();it!=m_trackedIds.end();++it){
  Object *affected=TheGameLogic->findObjectByID((ObjectID)*it);
  if(affected)rva004848E6(affected);
 }
 return (UpdateSleepTime)delay;
}
