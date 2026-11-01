// cl: /DNDEBUG /MD /EHs-c-
// ?rva004A7E67@Rva004A7E67@@QAE_NPAVObject@@H@Z @0x004A7E67 273B
// Dock rally-point jitter / gatherer-countdown: 2*radius vs rowed Object::rva00263763,
// out-of-range jitters Thing position via GetGameLogicRandomValue(-4,4) lines 87/88
// then setPosition; else countdown at +0x68 with IfaceA slot 95 / IfaceB slot 3 checks,
// BuildListInfo gatherer broadcast or GameLogic::destroyObject. Evidence: chain packet
// (all callees rowed), prev Rva004A7E43Slot + next SupplyWarehouseDockUpdateModuleData,
// this-0x18 owner / this-0x1c aux interior-this pattern, TheGameLogic extern.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

#include "SupplyWarehouseDockUpdateNative.h"
#include "../../../../Common/Thing/thing.h"

class Object : public Thing
{
public:
    float rva00263763(const void *other) const;
    char m_unmodelled60[0xB8 - 0x60];
    float m_radius; // +B8
    char m_unmodelledBC[0x258 - 0xBC];
    void *m_iface; // +258
};

class GameLogic;
extern GameLogic *TheGameLogic;
#include "../../../../Common/GameLogicObjectLookupView.h"

int __cdecl GetGameLogicRandomValue(int lo, int hi, char *file, int line);

struct Rva002716Holder
{
	void Rva0027164EBroadcast(int a, int b);
};

class IfaceB
{
public:
	virtual void b0();
	virtual void b1();
	virtual void b2();
	virtual bool check(int n);
};

class IfaceA
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
	virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69();
	virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73(); virtual void s74();
	virtual void s75(); virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83(); virtual void s84();
	virtual void s85(); virtual void s86(); virtual void s87(); virtual void s88(); virtual void s89();
	virtual void s90(); virtual void s91(); virtual void s92(); virtual void s93(); virtual void s94();
	virtual IfaceB *s95();
};

bool SupplyWarehouseDockUpdate::rva004A7E67(Object *object, int unused)
{
	if (m_boxesStored == 0)
		return false;
	float r = object->m_radius;
	float rr = r + r;
	float e = object->rva00263763(m_object);
	if (e > rr * rr) {
		Coord3D p;
		p.x = object->m_cachedPos.x;
		p.y = object->m_cachedPos.y;
		p.z = object->m_cachedPos.z;
		p.x += (float)GetGameLogicRandomValue(-4, 4, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\DockUpdate\\SupplyWarehouseDockUpdate.cpp", 0x57);
		p.y += (float)GetGameLogicRandomValue(-4, 4, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\DockUpdate\\SupplyWarehouseDockUpdate.cpp", 0x58);
		object->setPosition(&p);
		return false;
	}
	--m_boxesStored;
	IfaceA *ifaceA = (IfaceA *)object->m_iface;
	IfaceB *ifaceB = ifaceA->s95();
	if (ifaceB == 0 || !ifaceB->check(m_boxesStored)) {
		++m_boxesStored;
		return false;
	}
	if (m_boxesStored != 0 || *(unsigned char *)((char *)m_moduleData + 0x14) == 0) {
		Rva002716Holder *h = (Rva002716Holder *)m_object->getDrawable();
		if (h != 0)
			h->Rva0027164EBroadcast(*(int *)((char *)m_moduleData + 0x10), m_boxesStored);
		return true;
	}
	TheGameLogic->destroyObject(m_object);
	return false;
}
