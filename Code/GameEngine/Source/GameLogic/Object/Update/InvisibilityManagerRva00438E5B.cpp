// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /ICode/GameEngine/Source/Common
//
// ?rva00438E5B@Rva00439E0C@@QAE_NPAVObject@@HPAURva004393D6@@PAURva004389DBInfo@@I@Z,
// retail 0x00438E5B (277 bytes).  Called by InvisibilityManager::detected
// 0x00439E0C and the per-object update 0x0043979D with the state the
// detection walk 0x0043966A returned, the object's record, the walk's info
// and a duration; its receiver is that manager (TheGameLogic +0x178).
//
// Target evidence: an unchanged state (Object::rva0028F4EF) returns false.
// Otherwise the state is applied (0x004384F2); an info +0x20 request turns a
// newly revealed object's ToggleHiddenSpecialAbilityUpdate module off while
// the owner still has status 0x10 (vftable slot 23, turnOff in
// ToggleHiddenSpecialAbilityUpdateSlots23And24.cpp).  Entering state 2 plays
// the info's +0x0C FX list when coming from state 0 and arms the record
// (0x00438C6C, with the info's +0x04 byte) and returns true; leaving state 2
// plays the info's +0x08 FX list when going to state 0 and stamps the logic
// frame into the record's +0x0C word.  The 0x0043822E/0x00438C6C neighbours
// carry the record words' meaning; field names are neutral.
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Module
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void turnOff();	// slot 23 (+0x5C)
};

class Object
{
	friend class Rva00439E0C;
public:
	bool testStatus(ObjectStatusTypes bit) const;
	int rva0028F4EF();
protected:
	Module *findModule(NameKeyType key) const;
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

struct Rva004393D6
{
	void *m_node;
	int m_04;
	int m_08;
	unsigned int m_0c;	// +0x0C, frame the object left state 2
};

struct Rva004389DBInfo
{
	Object *m_detector;	// +0x00
	bool m_04;	// +0x04
	const FXList *m_08;	// +0x08, played on leaving state 2 for state 0
	const FXList *m_0c;	// +0x0C, played on entering state 2 from state 0
	char m_pad10[0x10];
	bool m_20;	// +0x20
};

class Rva00439E0C
{
public:
	bool rva00438E5B(Object *obj, int state, Rva004393D6 *record, Rva004389DBInfo *info, unsigned int duration);
	void rva004384F2(Object *obj, int val);
	void rva00438C6C(Object *obj, void *payload, int duration, bool flag);
};

bool Rva00439E0C::rva00438E5B(Object *obj, int state, Rva004393D6 *record, Rva004389DBInfo *info, unsigned int duration)
{
	int previous = obj->rva0028F4EF();
	if (state != previous)
	{
		rva004384F2(obj, state);
		if (info->m_20 && previous == 0 && state != 0)
		{
			static NameKeyType key_ToggleHiddenSpecialAbilityUpdate = TheNameKeyGenerator->nameToKey("ToggleHiddenSpecialAbilityUpdate");
			Module *toggle = obj->findModule(key_ToggleHiddenSpecialAbilityUpdate);
			if (toggle && obj->testStatus((ObjectStatusTypes)0x10))
				toggle->turnOff();
		}
		if (state == 2)
		{
			if (previous == 0 && info->m_0c)
				FXList::doFXObj(info->m_0c, obj, 0);
			rva00438C6C(obj, record, duration, info->m_04);
			return true;
		}
		if (previous == 2)
		{
			if (state == 0 && info->m_08)
				FXList::doFXObj(info->m_08, obj, 0);
			record->m_0c = TheGameLogic->getFrame();
		}
	}
	return false;
}
