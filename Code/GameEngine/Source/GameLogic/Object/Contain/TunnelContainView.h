// Existing TunnelContain view shared by its seed and primary list getter.
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
class TunnelTracker
{
public:
	void healObjects(float frames);
	void updateNemesis(const Object *target);
	void iterateContained(ContainIterateFunc cb, void *user, bool reverse);
	void addToContainList(Object *obj);
	int getContainMax() const;
	bool isValidContainerFor(Object *obj, bool checkCapacity);
};
class Rva004F5436 { public: int rva004F5436(class BfmeTab1026 *tab); };
class Rva00466398 { public: Rva0036AE51ListView rva00466398(); };
class Rva004F56FC
{
public:
	void rva004F56FC(Object *obj);
};
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
class Drawable { public: void setDrawableHidden(bool hidden); };
struct Rva0047DD2DTemplate { char pad[0x554]; unsigned int occlusionDelay; };
class Thing {
public:
    void setPosition(const Coord3D *position);
    Drawable *getDrawable() const;
    const Coord3D *getPosition() const { return &position; }
    const Rva0047DD2DTemplate *getTemplate() const { return objectTemplate; }
private:
    char pad0[4]; const Rva0047DD2DTemplate *objectTemplate;
    char pad8[0x38-8]; Coord3D position;
};
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
    char pad44[0x254-0x44]; BodyModuleInterface *body;
    char pad258[0x428-0x258]; unsigned int safeOcclusionFrame;
    char pad42C[0x454-0x42c]; bool flag454;
};
extern GameLogic *TheGameLogic;
class Player
{
public:
	TunnelTracker *getTunnelSystem() const { return m_2E8; }
	unsigned char m_pad000[0x2E8];
	TunnelTracker *m_2E8; // WB names the list visitor; the sibling manager is the same tracker.
};
struct B00 { virtual void f00(); virtual void p01(); virtual void p02(); virtual void xfer(Xfer *xfer); virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07(); virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void rvaPrimary58(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual Rva0036AE51ListView rva0047DD0F(); const ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual UpdateSleepTime update(); int m_14; int m_18; Object *m_1C; };
struct B20 { virtual void f20(); virtual void c01(); virtual void c02(); virtual void c03(); virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07(); virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19(); virtual void c20(); virtual void c21(); virtual void c22(); virtual void onRemoving(Object *object); virtual void c24(); virtual void onSelling(); };
struct B24 { virtual void f24(); };
class DamageInfo;
class DieMuxData { public: bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const; };
struct TunnelContainModuleDataView { char pad[8]; DieMuxData m_dieMuxData; char pad09[0x98 - 0x09]; bool m_healTunnelSystem; char pad99[0xD4 - 0x99]; float m_framesForFullHeal; };
struct B28 { virtual void onDie(const DamageInfo *damageInfo); };
struct B2C { virtual void f2C(); };
struct B30 { virtual void f30(); };
class ContainIface34
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual bool s03();
	virtual void rva0047DE30();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual int getContainMax() const;
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool a3);
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void addToContainList(Object *obj);
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	virtual int rva0047DDD9(void *arg);
	virtual Rva0036AE51ListView rva0047DE12();
	virtual void s71();
	virtual void s72();
	virtual void iterateContained(Rva004F553FCb cb, void *user, unsigned int flags) = 0;
};
class GarrisonContain
	: public B00, public B0C, public B10, public B20, public B24, public B28, public B2C, public B30
	, public ContainIface34
{
public:
	virtual void onRemoving(Object *object);
	virtual UpdateSleepTime update();
};
class HordeGarrisonContain : public GarrisonContain
{
protected:
	virtual void xfer(Xfer *xfer);
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool a3);
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class TunnelContain : public HordeGarrisonContain
{
public:
	virtual void onRemoving(Object *object);
	virtual void onSelling();
	virtual UpdateSleepTime update();
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool a3);
	virtual void iterateContained(Rva004F553FCb cb, void *user, unsigned int flags);
	virtual void rva0047DE30();
	virtual void addToContainList(Object *obj);
	virtual void onDie(const DamageInfo *damageInfo);
	void rva0047DF81();
	virtual int getContainMax() const;
	virtual int rva0047DDD9(void *arg);
	virtual Rva0036AE51ListView rva0047DE12();
	virtual Rva0036AE51ListView rva0047DD0F();
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad9AC[0x9AC];
	bool m_flag9B0;
	bool m_flag9B1;
public:
	virtual NameKeyType getModuleNameKey() const;
};

#endif
