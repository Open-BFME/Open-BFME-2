// cl: /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// rva00528CEB  ?rva00528CEB@@YA?AURva00528CEBResult@@PAVObject@@@Z
// retail 0x00528CEB..0x00528F03 (536B)  WorldBuilder twin 0x013C8E60 (1030B)
// in PalantirCommandInterface.cpp (asserts at lines 229 and 246:
// `TheGameLogic != NULL` and `result.mode == MODE_RANK`).
//
// Returns by value a 12-byte {mode rank progress} record for an object.
// A live LifetimeUpdate (+0x28 clear) a TemporarilyDefectUpdate with a
// nonzero end frame (status 0x3E) or a ToggleHiddenSpecialAbilityUpdate whose
// module data enables +0xC8 (status 0x10) select the timer mode (1) and its
// progress is (end - now) / (end - start) clamped to [0 1]. Otherwise the
// rank mode (0) asks ComputeObjectRankValues (0x005C3000); the override
// template from 0x002911B7 forces rank 1. Failure or an empty timer gives
// mode 2.
//
// Target facts: cdecl with a hidden return pointer (callers 0x00529BA3
// 0x00529BE7 0x00529C10 in 0x00529B6E pop two dwords and copy 12 bytes);
// three function-local NameKeyType statics guarded by bits 1 2 4 of
// 0x00E0497C; callee rows nameToKey 0x00148E1A findModule 0x0028B6D6
// testStatus 0x0004E536 ComputeObjectRankValues 0x005C3000 and the
// pinned 0x002911B7. The function and record names are address-derived.

#include "../../../../Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;

enum ObjectStatusTypes
{
	OBJECT_STATUS_10 = 0x10,
	OBJECT_STATUS_3E = 0x3E
};

class ThingTemplate
{
	char m_pad000[0x5E7];

public:
	Bool m_rankDisplay; // +0x5E7
};

class Module;
class Object;
struct Rva00528CEBResult;
Rva00528CEBResult rva00528CEB(Object *obj);

class Object
{
	friend Rva00528CEBResult rva00528CEB(Object *obj);
protected:
	Module *findModule(NameKeyType key) const;
public:
	Bool testStatus(ObjectStatusTypes status) const;
	ThingTemplate *rva002911B7();
	ThingTemplate *getTemplate() const { return m_template; }

private:
	void *m_vtbl;
	ThingTemplate *m_template; // +0x04
};

bool ComputeObjectRankValues(const Object &obj, Int &rank, Real &progress);

class LifetimeUpdate
{
	char m_pad00[0x20];

public:
	UnsignedInt m_dieFrame; // +0x20
	UnsignedInt m_startFrame; // +0x24
	Bool m_finished; // +0x28
};

class TemporarilyDefectUpdate
{
	char m_pad00[0x20];

public:
	UnsignedInt m_endFrame; // +0x20
	UnsignedInt m_startFrame; // +0x24
};

struct ToggleHiddenSpecialAbilityUpdateModuleData
{
	char m_pad00[0x7C];
	UnsignedInt m_duration; // +0x7C
	char m_pad80[0xC8 - 0x80];
	Bool m_showProgress; // +0xC8
};

class ToggleHiddenSpecialAbilityUpdate
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual UnsignedInt getStartFrame(); // slot 0x64

	const ToggleHiddenSpecialAbilityUpdateModuleData *getData() const { return m_data; }

private:
	const ToggleHiddenSpecialAbilityUpdateModuleData *m_data; // +0x04
};

enum
{
	MODE_RANK = 0,
	MODE_TIMER = 1,
	MODE_NONE = 2
};

struct Rva00528CEBResult
{
	Rva00528CEBResult() : mode(MODE_NONE), rank(0), progress(0.0f) {}

	Int mode;
	Int rank;
	Real progress;
};

Rva00528CEBResult rva00528CEB(Object *obj)
{
	Rva00528CEBResult result;
	result.mode = MODE_RANK;
	UnsignedInt start;
	UnsignedInt end;

	static NameKeyType lifetimeKey = TheNameKeyGenerator->nameToKey("LifetimeUpdate");
	LifetimeUpdate *lifetime = (LifetimeUpdate *)obj->findModule(lifetimeKey);
	if (lifetime != 0 && !lifetime->m_finished)
	{
		result.mode = MODE_TIMER;
		start = lifetime->m_startFrame;
		end = lifetime->m_dieFrame;
	}
	else if (obj->testStatus(OBJECT_STATUS_3E))
	{
		static NameKeyType defectKey = TheNameKeyGenerator->nameToKey("TemporarilyDefectUpdate");
		TemporarilyDefectUpdate *defect = (TemporarilyDefectUpdate *)obj->findModule(defectKey);
		if (defect != 0 && defect->m_endFrame > 0)
		{
			result.mode = MODE_TIMER;
			start = defect->m_startFrame;
			end = defect->m_endFrame;
		}
	}
	else if (obj->testStatus(OBJECT_STATUS_10))
	{
		static NameKeyType hiddenKey = TheNameKeyGenerator->nameToKey("ToggleHiddenSpecialAbilityUpdate");
		ToggleHiddenSpecialAbilityUpdate *hidden = (ToggleHiddenSpecialAbilityUpdate *)obj->findModule(hiddenKey);
		if (hidden != 0 && hidden->getData()->m_showProgress)
		{
			result.mode = MODE_TIMER;
			start = hidden->getStartFrame();
			end = start + hidden->getData()->m_duration;
		}
	}

	if (result.mode == MODE_TIMER)
	{
		if (end <= start)
		{
			result.mode = MODE_NONE;
		}
		else
		{
			UnsignedInt now = TheGameLogic->getFrame();
			result.progress = (Real)(end - now) / (Real)(end - start);
			if (now > end || result.progress < 0.0f)
				result.progress = 0.0f;
			else if (result.progress > 1.0f)
				result.progress = 1.0f;
		}
	}
	else
	{
		Bool isOverride = false;
		ThingTemplate *tmpl = obj->rva002911B7();
		if (tmpl != 0)
			isOverride = true;
		else
			tmpl = obj->getTemplate();
		if (!tmpl->m_rankDisplay || !ComputeObjectRankValues(*obj, result.rank, result.progress))
			result.mode = MODE_NONE;
		else if (isOverride)
			result.rank = 1;
	}
	return result;
}
