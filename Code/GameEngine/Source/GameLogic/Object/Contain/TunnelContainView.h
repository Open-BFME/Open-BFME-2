// TunnelContain class views shared by the TU and its behavior donors.
// Primary slot 33 returns the same tracker view as secondary rva0047DE12;
// the ctor installs the primary vptr and the object pointer remains at +8.
#ifndef TUNNEL_CONTAIN_VIEW_H
#define TUNNEL_CONTAIN_VIEW_H

#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"
class Thing;
class ModuleData;
class Player;
class Xfer;
class Object;
class ContainModuleInterface;
class Rva0047DEE1Rider;
class Rva0047DE6CRiderInterface;
class TurretStateMachine;
class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);
	char m_pad00[0x30];
	TurretStateMachine *m_stateMachine; // +0x30
};

class Rva0047DEE1Rider
{
public:
	virtual void x0();
	virtual void x1();
	virtual void x2();
	virtual void x3();
	virtual void x4();
	virtual void x5();
	virtual bool x6( int arg );
};

class ContainModuleInterface
{
public:
	virtual void c00();
	virtual void c01();
	virtual void c02();
	virtual void c03();
	virtual void c04();
	virtual void c05();
	virtual void c06();
	virtual void c07();
	virtual void c08();
	virtual void c09();
	virtual void c10();
	virtual void c11();
	virtual void c12();
	virtual void c13();
	virtual void c14();
	virtual void c15();
	virtual void c16();
	virtual void c17();
	virtual void c18();
	virtual void c19();
	virtual void c20();
	virtual void c21();
	virtual void c22();
	virtual void c23();
	virtual void c24();
	virtual void c25();
	virtual void c26();
	virtual void c27();
	virtual void c28();
	virtual void c29();
	virtual void c30();
	virtual Rva0047DE6CRiderInterface *c31();
	virtual void c32();
	virtual void c33();
	virtual void c34();
	virtual void c35();
	virtual void c36();
	virtual void c37();
	virtual void c38();
	virtual void c39();
	virtual void c40();
	virtual void removeFromContain(Object *obj, int exposeStealthUnits) = 0;
};

typedef void (__cdecl *Rva004F553FCb)(void *data, void *user);
typedef void (__cdecl *ContainIterateFunc)(Object *object, void *user);
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum Relationship
{
	ENEMIES = 0
};
enum ObjectID;
class TunnelTracker
{
public:
	bool isInContainer(ObjectID id);
	void removeFromContain(ObjectID id, int exposeStealthUnits);
	void healObjects(float frames);
	void updateNemesis(const Object *target);
	void iterateContained(ContainIterateFunc cb, void *user, bool reverse);
	void addToContainList(Object *obj);
	int getContainMax() const;
	bool isValidContainerFor(Object *obj, bool checkCapacity);
};
class Rva004F5436 { public: int rva004F5436(class BfmeTab1026 *tab); };
class Rva00466398 { public: inline __declspec(noinline) Rva0036AE51ListView rva00466398(); };
class Rva004F56FC
{
public:
	void rva004F56FC(Object *obj);
	bool rva004F571B(const Object *object);
};
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
class Drawable { public: void setDrawableHidden(bool hidden); };
struct Rva0047DD2DTemplate { char pad[0x115]; unsigned char m_kindOf115; char pad116[0x554 - 0x116]; unsigned int occlusionDelay; };
#include "../../../Common/Thing/thing.h"
enum DisabledType { DISABLED_HELD = 3 };
class DamageInfo;
struct TunnelDamageInfoView { char pad[8]; ObjectID sourceID; };
class BodyModuleInterface {
public:
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03(); virtual void b04();
    virtual void b05(); virtual void b06(); virtual void b07(); virtual void b08(); virtual void b09();
    virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14();
    virtual const TunnelDamageInfoView *getLastDamageInfo() const;	// +0x3C
    virtual unsigned int getLastDamageTimestamp() const;		// +0x40
};
class Object : public Thing {
public:
    Player *getControllingPlayer() const;
    bool clearDisabled(DisabledType type);
    void rva0028DCC4();
    enum Relationship getRelationship(const Object *that) const;
    BodyModuleInterface *getBodyModule() const { return body; }
    ContainModuleInterface *getContain() const { return m_contain; }
    AIUpdateInterface *getAI() const { return m_ai; }
    const Rva0047DD2DTemplate *getTemplate() const { return (const Rva0047DD2DTemplate *)m_template; }
    char pad60[0xB8-0x60]; float m_geometryBoundingRadius; // GeometryInfo at +0xA8, bounding radius at its +0x10
    char padBC[0x250-0xBC]; ContainModuleInterface *m_contain;
    BodyModuleInterface *body;
    AIUpdateInterface *m_ai;
    char pad25C[0x428-0x25C]; unsigned int safeOcclusionFrame;
    char pad42C[0x454-0x42c]; bool flag454;
};
extern GameLogic *TheGameLogic;
class Player
{
public:
	TunnelTracker *getTunnelSystem() const { return m_tunnelSystem; }
	unsigned char m_pad000[0x2E8];
	TunnelTracker *m_tunnelSystem; // WB names the list visitor; the sibling manager is the same tracker.
};
// The ctor emits this chain's vftables: a slot whose owner is unnamed is pure, so
// the table holds __purecall instead of an undefined placeholder.
struct B00
{
	virtual ~B00();
	virtual void p01() = 0;
	virtual void p02() = 0;
	virtual void xfer(Xfer *xfer);
	virtual void p04() = 0;
	virtual void p05() = 0;
	virtual void p06() = 0;
	virtual void p07() = 0;
	virtual void onDelete();
	virtual void p09() = 0;
	virtual void p10() = 0;
	virtual void p11() = 0;
	virtual void p12() = 0;
	virtual void p13() = 0;
	virtual void p14() = 0;
	virtual void p15() = 0;
	virtual void p16() = 0;
	virtual void p17() = 0;
	virtual void p18() = 0;
	virtual void p19() = 0;
	virtual void p20() = 0;
	virtual void p21() = 0;
	virtual void rvaPrimary58() = 0;
	virtual void p23() = 0;
	virtual void p24() = 0;
	virtual void p25() = 0;
	virtual void p26() = 0;
	virtual void p27() = 0;
	virtual void p28() = 0;
	virtual void p29() = 0;
	virtual void p30() = 0;
	virtual void p31() = 0;
	virtual int p32(Object *obj) = 0;
	virtual Rva0036AE51ListView rva0047DD0F();
	const ModuleData *m_moduleData;
	Object *m_object;
};
struct B0C { virtual void f0C() = 0; };
struct B10 { virtual UpdateSleepTime update(); int m_14; int m_18; Object *m_1C; };
class Rva00479DCD
{
	public:
	virtual void f20() = 0;
	void rva00479DCD(Object *obj, int exposeStealthUnits);
};
struct B20 : public Rva00479DCD
{
	virtual void c01() = 0;
	virtual void c02() = 0;
	virtual void c03() = 0;
	virtual void c04() = 0;
	virtual void c05() = 0;
	virtual void c06() = 0;
	virtual void c07() = 0;
	virtual void c08() = 0;
	virtual void c09() = 0;
	virtual void c10() = 0;
	virtual void c11() = 0;
	virtual void c12() = 0;
	virtual void c13() = 0;
	virtual void c14() = 0;
	virtual void c15() = 0;
	virtual void c16() = 0;
	virtual void c17() = 0;
	virtual void c18() = 0;
	virtual void c19() = 0;
	virtual void c20() = 0;
	virtual void c21() = 0;
	virtual void c22() = 0;
	virtual void onRemoving(Object *object);
	virtual void c24() = 0;
	virtual void onSelling();
	virtual void c26() = 0;
	virtual void c27() = 0;
	virtual void c28() = 0;
	virtual void c29() = 0;
	virtual void c30() = 0;
	virtual void c31() = 0;
	virtual void c32() = 0;
	virtual void c33() = 0;
	virtual void c34() = 0;
	virtual void c35() = 0;
	virtual void c36() = 0;
	virtual void c37() = 0;
	virtual void c38() = 0;
	virtual void c39() = 0;
	virtual void c40() = 0;
	virtual void removeFromContain(Object *obj, int exposeStealthUnits);
	virtual void dispatch42(bool flag) = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual bool rva0047DF44(int id);
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void dispatch68(void (__cdecl *callback)(Object *, Object *), Object *object, bool flag) = 0;
};
struct B24 { virtual void f24() = 0; };
class DamageInfo;
class DieMuxData { public: bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const; };
struct TunnelContainModuleDataView { char pad[8]; DieMuxData m_dieMuxData; char pad09[0x98 - 0x09]; bool m_healTunnelSystem; char pad99[0xD4 - 0x99]; float m_framesForFullHeal; };
struct B28 { virtual void onDie(const DamageInfo *damageInfo); };
struct B2C { virtual void f2C() = 0; };
struct B30 { virtual void f30() = 0; };
class ContainIface34
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual bool s03() = 0;
	virtual void rva0047DE30();
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void s21() = 0;
	virtual void s22() = 0;
	virtual void s23() = 0;
	virtual void s24() = 0;
	virtual void s25() = 0;
	virtual void s26() = 0;
	virtual void s27() = 0;
	virtual int getContainMax() const;
	virtual void s29() = 0;
	virtual void s30() = 0;
	virtual void s31() = 0;
	virtual void s32() = 0;
	virtual void s33() = 0;
	virtual void s34() = 0;
	virtual void s35() = 0;
	virtual void s36() = 0;
	virtual void s37() = 0;
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool a3);
	virtual void s39() = 0;
	virtual void s40() = 0;
	virtual void s41() = 0;
	virtual void s42() = 0;
	virtual void s43() = 0;
	virtual void s44() = 0;
	virtual void s45() = 0;
	virtual void s46() = 0;
	virtual void s47() = 0;
	virtual void addToContainList(Object *obj);
	virtual void s49() = 0;
	virtual void s50() = 0;
	virtual void s51() = 0;
	virtual void s52() = 0;
	virtual void s53() = 0;
	virtual void s54() = 0;
	virtual void s55() = 0;
	virtual void s56() = 0;
	virtual void s57() = 0;
	virtual void s58() = 0;
	virtual void s59() = 0;
	virtual void s60() = 0;
	virtual void s61() = 0;
	virtual void s62() = 0;
	virtual void s63() = 0;
	virtual void s64() = 0;
	virtual void s65() = 0;
	virtual void s66() = 0;
	virtual void s67() = 0;
	virtual void s68() = 0;
	virtual int rva0047DDD9(void *arg);
	virtual Rva0036AE51ListView rva0047DE12();
	virtual void s71() = 0;
	virtual void s72() = 0;
	virtual void iterateContained(Rva004F553FCb cb, void *user, unsigned int flags) = 0;
};
class GarrisonContain
	: public B00, public B0C, public B10, public B20, public B24, public B28, public B2C, public B30
	, public ContainIface34
{
public:
	virtual ~GarrisonContain();
	virtual void onRemoving(Object *object);
	virtual UpdateSleepTime update();
};
class HordeGarrisonContain : public GarrisonContain
{
protected:
	virtual void xfer(Xfer *xfer);
public:
	HordeGarrisonContain(Thing *thing, const ModuleData *moduleData);
	virtual ~HordeGarrisonContain();
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool a3);
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class TunnelContain : public HordeGarrisonContain
{
public:
	TunnelContain(Thing *thing, const ModuleData *moduleData);
	virtual ~TunnelContain();
	virtual void removeFromContain(Object *obj, int exposeStealthUnits);
	virtual void onDelete();
	virtual bool rva0047DF44(int id);
	virtual void onRemoving(Object *object);
	virtual void onSelling();
	virtual UpdateSleepTime update();
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool a3);
	virtual void iterateContained(Rva004F553FCb cb, void *user, unsigned int flags);
	virtual void rva0047DE30();
	virtual void addToContainList(Object *obj);
	virtual void onDie(const DamageInfo *damageInfo);
	virtual Rva0047DEE1Rider *rva0047DEE1(int arg);
	void rva0047DF81();
	virtual int getContainMax() const;
	virtual int rva0047DDD9(void *arg);
	virtual Rva0036AE51ListView rva0047DE12();
	virtual Rva0036AE51ListView rva0047DD0F();
protected:
	virtual void xfer(Xfer *xfer);
	void scatterToNearbyPosition(Object *rider);
private:
	char m_pad9AC[0x9AC];
	bool m_flag9B0;
	bool pending;
public:
	virtual NameKeyType getModuleNameKey() const;
};

#endif
