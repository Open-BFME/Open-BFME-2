// cl: /DNDEBUG /MD
//
// ?setIndestructible@ActiveBody@@UAEX_N@Z @0x004BF186 98B.
// Target evidence: slot 33 (+0x84) of the body-interface vtable at +0x10,
// installed by ActiveBody's own vtable 0x00C5B5B0 and inherited unchanged by
// the Highlander, Immortal, Respawn, Oathbreaker and PorcupineFormation body
// vtables. Callers that pass Indestructible map/script flags use the same
// slot (ObjectUpdateObjValuesFromMapProperties, ScriptActions, BridgeObject).
// The body is Zero Hour's ActiveBody::setIndestructible (store the flag,
// mirror it onto the bridge's four towers). cl 7.1
// compiles an override of a non-primary base's virtual with the base
// subobject's this and folds the adjustment into the member accesses: the
// Object pointer at +8 is read as [ecx-8] and the flag at +0xC7 as [ecx+0xB7].
// Body: stores the bool at +0xC7, and when the object's template has kind bit
// 0x40 of byte +0x10A set, asks the rowed BridgeBehavior helper 0x00456556
// for the bridge interface and forwards the bool through body-module vslot
// +0x84 to each of the four tower objects it names (ids from vslot +4, looked
// up with the rowed GameLogic::findObjectByID 0x00049DC5). Structural
// inference: the tower's body module is held in a local before its null test
// so it is loaded once, as retail.
class Thing;
class ModuleData;
#include "../../../Common/GameLogicObjectLookupView.h"
class BridgeBehaviorInterface
{
public:
	virtual void s00();
	virtual ObjectID getTowerID(int which) = 0; // +4
};
class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(class Object *obj);
};
class BodyIface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
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
	virtual void setIndestructible(bool v) = 0; // +0x84
};
#include "../../../../Include/Common/ThingTemplate.h"
class Object
{
public:
	unsigned char m_pad000[4];
	ThingTemplate *m_template;
	unsigned char m_pad008[0x254 - 8];
	BodyIface *m_254;
};
extern GameLogic *TheGameLogic;
struct B00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
class Iface10
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
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
	virtual void setIndestructible(bool v) = 0;
};
class ActiveBody : public B00, public B0C, public Iface10
{
public:
	virtual void setIndestructible(bool v);
private:
	unsigned char m_pad014[0xC7 - 0x14];
	bool m_C7;
};
void ActiveBody::setIndestructible(bool v)
{
	m_C7 = v;
	Object *obj = m_object;
	if (((const unsigned char *)obj->m_template->m_kindof)[2] & 0x40)
	{
		BridgeBehaviorInterface *bbi = BridgeBehavior::getBridgeBehaviorInterfaceFromObject(obj);
		if (bbi)
		{
			for (int i = 0; i < 4; ++i)
			{
				Object *tower = TheGameLogic->findObjectByID(bbi->getTowerID(i));
				if (tower)
				{
					BodyIface *body = tower->m_254;
					if (body)
						body->setIndestructible(v);
				}
			}
		}
	}
}
