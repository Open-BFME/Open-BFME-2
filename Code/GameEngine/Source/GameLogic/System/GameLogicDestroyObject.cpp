// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?destroyObject@GameLogic@@QAEXPAVObject@@@Z, retail 0x00242C09 (125 bytes).
//
// Deferred-destruction sequence ported from Open-BFME-1
// Code/GameEngine/Source/GameLogic/System/GameLogicDestroyObject.cpp with
// BFME2 layout repairs: status bit0 at Object+0x94, module array at +0x244
// with the behavior interface EMBEDDED at +0xC (vfptr, lea form), AI at
// +0x258 with setLocomotorGoalNone at virtual slot 136 (+0x220), and the
// destruction list at GameLogic+0x108. Callee pins all pre-derived:
// setStatus 0x23DB0E, destroyPath 0x262A8A, list push_back 0x1EC03C,
// onDestroy 0x28FC1D.

#include <list>

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class DestroyModuleInterface
{
public:
	virtual void onDestroy(void);
};

class BehaviorModuleInterface
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual DestroyModuleInterface *getDestroy(void);
};

class BehaviorModule
{
public:
	char m_pad00[12];
	BehaviorModuleInterface m_behavior;
};

class AIUpdateInterface
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1C(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2C(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3C(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4C(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5C(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual void slot6C(void);
	virtual void slot70(void);
	virtual void slot74(void);
	virtual void slot78(void);
	virtual void slot7C(void);
	virtual void slot80(void);
	virtual void slot84(void);
	virtual void slot88(void);
	virtual void slot8C(void);
	virtual void slot90(void);
	virtual void slot94(void);
	virtual void slot98(void);
	virtual void slot9C(void);
	virtual void slotA0(void);
	virtual void slotA4(void);
	virtual void slotA8(void);
	virtual void slotAC(void);
	virtual void slotB0(void);
	virtual void slotB4(void);
	virtual void slotB8(void);
	virtual void slotBC(void);
	virtual void slotC0(void);
	virtual void slotC4(void);
	virtual void slotC8(void);
	virtual void slotCC(void);
	virtual void slotD0(void);
	virtual void slotD4(void);
	virtual void slotD8(void);
	virtual void slotDC(void);
	virtual void slotE0(void);
	virtual void slotE4(void);
	virtual void slotE8(void);
	virtual void slotEC(void);
	virtual void slotF0(void);
	virtual void slotF4(void);
	virtual void slotF8(void);
	virtual void slotFC(void);
	virtual void slot100(void);
	virtual void slot104(void);
	virtual void slot108(void);
	virtual void slot10C(void);
	virtual void slot110(void);
	virtual void slot114(void);
	virtual void slot118(void);
	virtual void slot11C(void);
	virtual void slot120(void);
	virtual void slot124(void);
	virtual void slot128(void);
	virtual void slot12C(void);
	virtual void slot130(void);
	virtual void slot134(void);
	virtual void slot138(void);
	virtual void slot13C(void);
	virtual void slot140(void);
	virtual void slot144(void);
	virtual void slot148(void);
	virtual void slot14C(void);
	virtual void slot150(void);
	virtual void slot154(void);
	virtual void slot158(void);
	virtual void slot15C(void);
	virtual void slot160(void);
	virtual void slot164(void);
	virtual void slot168(void);
	virtual void slot16C(void);
	virtual void slot170(void);
	virtual void slot174(void);
	virtual void slot178(void);
	virtual void slot17C(void);
	virtual void slot180(void);
	virtual void slot184(void);
	virtual void slot188(void);
	virtual void slot18C(void);
	virtual void slot190(void);
	virtual void slot194(void);
	virtual void slot198(void);
	virtual void slot19C(void);
	virtual void slot1A0(void);
	virtual void slot1A4(void);
	virtual void slot1A8(void);
	virtual void slot1AC(void);
	virtual void slot1B0(void);
	virtual void slot1B4(void);
	virtual void slot1B8(void);
	virtual void slot1BC(void);
	virtual void slot1C0(void);
	virtual void slot1C4(void);
	virtual void slot1C8(void);
	virtual void slot1CC(void);
	virtual void slot1D0(void);
	virtual void slot1D4(void);
	virtual void slot1D8(void);
	virtual void slot1DC(void);
	virtual void slot1E0(void);
	virtual void slot1E4(void);
	virtual void slot1E8(void);
	virtual void slot1EC(void);
	virtual void slot1F0(void);
	virtual void slot1F4(void);
	virtual void slot1F8(void);
	virtual void slot1FC(void);
	virtual void slot200(void);
	virtual void slot204(void);
	virtual void slot208(void);
	virtual void slot20C(void);
	virtual void slot210(void);
	virtual void slot214(void);
	virtual void slot218(void);
	virtual void slot21C(void);
	virtual void setLocomotorGoalNone(void);
	void destroyPath(void);

	char m_pad004[0x13C];
	class Path *m_path;
	char m_pad144[0x26D];
	unsigned char m_flag3B1;
	unsigned char m_flag3B2;
	char m_pad3B3[5];
	unsigned char m_flag3B8;
};

class Path
{
public:
	~Path();
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool flag);
	void onDestroy(void);
	char m_pad00[0x94];
	unsigned char m_statusByte0;
	char m_pad95[0x244 - 0x95];
	BehaviorModule **m_modules;
	char m_pad248[0x258 - 0x248];
	AIUpdateInterface *m_ai;
};

class GameLogic
{
public:
	char m_pad00[0x108];
	_STL::list<Object *> m_objectsToDestroy;
	void destroyObject(Object *obj);
};

void GameLogic::destroyObject(Object *obj)
{
	if (!obj || (obj->m_statusByte0 & 1))
		return;
	for (BehaviorModule **m = obj->m_modules; *m; ++m)
	{
		DestroyModuleInterface *destroy = (*m)->m_behavior.getDestroy();
		if (destroy)
			destroy->onDestroy();
	}
	obj->setStatus(OBJECT_STATUS_NONE, true);
	AIUpdateInterface *ai = obj->m_ai;
	if (ai)
	{
		ai->setLocomotorGoalNone();
		ai->destroyPath();
	}
	m_objectsToDestroy.push_back(obj);
	obj->onDestroy();
}

// ?destroyPath@AIUpdateInterface@@QAEXXZ @0x00262A8A
void AIUpdateInterface::destroyPath(void)
{
	if (m_path)
		delete m_path;
	m_path = 0;
	m_flag3B1 = 0;
	m_flag3B8 = 0;
	m_flag3B2 = 0;
	setLocomotorGoalNone();
}
