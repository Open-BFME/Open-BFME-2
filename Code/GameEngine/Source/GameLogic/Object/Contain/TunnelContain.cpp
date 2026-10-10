// cl: /O1 /MD /G7
// TunnelContain.cpp: TunnelContain overrides retail links from this TU (tu_map
// approved), folded from two split units with these exact flags. The contain
// interface at +0x34 carries both overrides: rva0047DE30 in slot 4 and
// rva0047DCDF in slot 73.
//
// ?rva0047DCDF@TunnelContain@@UAEXP6AXPAX0@Z0I@Z @0x0047DCDF 48B.
// Target evidence: the only reference to this body is slot 73 of the vtable
// 0x00C475A4, which the matched TunnelContain ctor 0x0047DC41 and dtor
// 0x0047DB3A install at +0x34 -- the contain interface base of the
// OpenContain-family layout (vptrs at +0, +0xC, +0x10, +0x20, +0x24, +0x28,
// +0x2C, +0x30, +0x34). It is therefore TunnelContain's override of that
// interface's slot 73; the slot's name is not established, hence the address
// name. cl 7.1 compiles an override of a non-primary base's virtual with the
// base subobject's this and folds the adjustment into the member accesses,
// which is why retail reads the Object pointer at TunnelContain+0x1C as
// [ecx-0x18] (no adjustor thunk; the honest class model reproduces it).
// Body: when bit 0 of the flags is set, forwards (callback, user data,
// bit 3 of the flags) to the rowed visitor 0x004F553F on the +0x2E8 member
// of the controlling player of the Object at +0x1C (that field's meaning is
// not asserted; it is the one the body dereferences). /G7 gives the byte
// form of the flag extraction (shr ebx,3; and bl,1).
class Thing;
class ModuleData;
class Player;
class Object;
typedef void (__cdecl *Rva004F553FCb)(void *data, void *user);
typedef void (__cdecl *ContainIterateFunc)(Object *object, void *user);
class TunnelTracker
{
public:
	void iterateContained(ContainIterateFunc cb, void *user, bool reverse);
	void addToContainList(Object *obj);
};
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
class Object : public Thing {
public:
    Player *getControllingPlayer() const;
    bool clearDisabled(DisabledType type);
    void rva0028DCC4();
    char pad44[0x428-0x44]; unsigned int safeOcclusionFrame;
    char pad42C[0x454-0x42c]; bool flag454;
};
extern GameLogic *TheGameLogic;
class Player
{
public:
	unsigned char m_pad000[0x2E8];
	TunnelTracker *m_2E8; // WB names the list visitor; the sibling manager is the same tracker.
};
struct B00 { virtual void f00(); virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07(); virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void rvaPrimary58(); const ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); int m_14; int m_18; Object *m_1C; };
struct B20 { virtual void f20(); virtual void c01(); virtual void c02(); virtual void c03(); virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07(); virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19(); virtual void c20(); virtual void c21(); virtual void c22(); virtual void onRemoving(Object *object); };
struct B24 { virtual void f24(); };
class DamageInfo;
class DieMuxData { public: bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const; };
struct TunnelContainModuleDataView { char pad[8]; DieMuxData m_dieMuxData; };
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
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
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
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void rva0047DCDF(Rva004F553FCb cb, void *user, unsigned int flags) = 0;
};
class GarrisonContain
	: public B00, public B0C, public B10, public B20, public B24, public B28, public B2C, public B30
	, public ContainIface34
{
public:
	virtual void onRemoving(Object *object);
};
class TunnelContain : public GarrisonContain
{
public:
	virtual void onRemoving(Object *object);
	virtual void rva0047DCDF(Rva004F553FCb cb, void *user, unsigned int flags);
	virtual void rva0047DE30();
	virtual void addToContainList(Object *obj);
	virtual void onDie(const DamageInfo *damageInfo);
	void rva0047DF81();
private:
	char m_pad9AC[0x9AC];
	unsigned char m_flag9B0;
	unsigned char m_flag9B1;
};
void TunnelContain::rva0047DCDF(Rva004F553FCb cb, void *user, unsigned int flags)
{
	if (!(flags & 1))
		return;
	Player *player = m_1C->getControllingPlayer();
	player->m_2E8->iterateContained((ContainIterateFunc)cb, user, (flags >> 3) & 1);
}

// ?rva0047DE30@TunnelContain@@UAEXXZ, retail 0x0047DE30, 60 bytes.
// TunnelContain chain method: virtual slot03 check then controlling-player 0x2E8 manager rva004F56FC add of m_object plus flag bytes at +0x9B0/+0x9B1.
// Layout: 8-base OpenContain family per TunnelContainRva0047DCDF (Iface34 at +0x34) so [esi-0x2C] is B00 m_object at +8; Player m_2E8 is Rva004F56FC per Rva004F56FCAdd caller 0x0047DE30; slot03 bool tentative. Evidence: chain via 0x004F56FC plus neighbours DCDF DF44.
void TunnelContain::rva0047DE30()
{
	if (!s03())
		return;
	m_flag9B0 = 0;
	Player *player = m_object->getControllingPlayer();
	if (player == 0)
		return;
	Rva004F56FC *mgr = (Rva004F56FC *)player->m_2E8;
	if (mgr == 0)
		return;
	mgr->rva004F56FC(m_object);
	m_flag9B1 = 1;
}

// ?addToContainList@TunnelContain@@UAEXPAVObject@@@Z, retail 0x0047DC75,
// 19 bytes: slot 40 of the contain interface at +0x34 (vtable 0x008475B8,
// whose slot 68 is rva0047DCDF above). Zero Hour's TunnelContain::
// addToContainList: the object joins the owning player's tunnel system
// (+0x2E8, rowed TunnelTracker::addToContainList 0x004F56E5, reached by a
// tail jump). BFME 2 keeps no null checks, like rva0047DCDF.
void TunnelContain::addToContainList(Object *obj)
{
	Player *owningPlayer = m_1C->getControllingPlayer();
	owningPlayer->m_2E8->addToContainList(obj);
}

// ?onDie@TunnelContain@@UAEXPBVDamageInfo@@@Z, retail 0x0047DFD9, 38 bytes:
// the only slot of the die interface at +0x28 (vtable 0x008475B4). Zero
// Hour's TunnelContain::onDie: the module data's DieMuxData (+0x08) must
// apply to the object, then the unregistering Zero Hour does inline is the
// rowed rva0047DF81 0x0047DF81 on the whole object.
void TunnelContain::onDie(const DamageInfo *damageInfo)
{
	Object *obj = m_object;
	const TunnelContainModuleDataView *data = (const TunnelContainModuleDataView *)m_moduleData;
	if (!data->m_dieMuxData.isDieApplicable(obj, damageInfo))
		return;
	rva0047DF81();
}

// ZH TunnelContain onRemoving guides release/position/show; native base is GarrisonContain.
// Native reads454 and554/428 and dispatches primary58 after the +20 override.
void TunnelContain::onRemoving(Object *obj)
{
    GarrisonContain::onRemoving(obj);
    obj->clearDisabled(DISABLED_HELD);
    if (!obj->flag454) obj->rva0028DCC4();
    obj->setPosition(m_object->getPosition());
    if (obj->getDrawable()) {
        obj->safeOcclusionFrame = TheGameLogic->getFrame() + obj->getTemplate()->occlusionDelay;
        obj->getDrawable()->setDrawableHidden(false);
    }
    rvaPrimary58();
}
