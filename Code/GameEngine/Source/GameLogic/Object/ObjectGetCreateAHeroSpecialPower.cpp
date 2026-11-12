// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// Object::GetCreateAHeroSpecialPower, retail 0x002912DC (48B), and the module
// lookup it calls, retail 0x0028F2C4 (34B).
//
// Target facts: 0x0028F2C4 walks the null-terminated behavior pointer list at
// Object +0x244 (the list Object::findModule 0x0028B6D6 walks) and returns the
// first module whose module data (+4) holds the int argument at +4, else NULL.
// GetCreateAHeroSpecialPower bounds-checks its index against the pointer-sized
// vector at Object +0x4A4 (its size is also read by 0x0028F2E6), looks the
// entry up through 0x0028F2C4 and returns what rowed 0x004B554F reports for the
// found module (module data +0x118 behind +4), or NULL when out of range.
//
// Donor/lead facts: the name GetCreateAHeroSpecialPower and the "Index out of
// range" assertion (line 12750, compiled out of retail) come from the
// WorldBuilder lead for Object.cpp. Structural inference: the +4 data field is
// a module tag key compared like ZH's ModuleData::getModuleTagNameKey; the
// lookup keeps its address-derived name because no target evidence names it.

#include <vector>
#include "ascii_string.h"

#include "../../../Include/Common/Overridable.h"
#include "../../../Include/Common/SpecialPower.h"

class Rva004B555F
{
public:
	const AsciiString &rva004B555F();
};

class Rva004B554FHolder
{
public:
	int rva004B554F() const;
};

class ModuleData
{
public:
	int getTagKey() const { return m_tagKey; }

private:
	void *m_vtbl;
	int m_tagKey; // +0x04
};

class BehaviorModule : public Rva004B555F
{
public:
	const ModuleData *getModuleData() const { return m_data; }

private:
	void *m_vtbl;
	ModuleData *m_data; // +0x04
};

enum KindOfType
{
	KIND_12C = 0x12c
};

enum Relationship
{
	REL_0 = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class ThingTemplate;
class Team;
#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class Rva004B0333
{
public:
	void *rva004B0333();
};

#include "../../../Include/Common/Rva002A7DD0.h"

class Rva00373EC6
{
public:
	char m_pad[0x3c];
	void *m_ptr3c;
};


class Object
{
public:
	ThingTemplate *rva002911B7();
	bool isKindOf(KindOfType kind) const;
	Rva00373EC6 *rva0028F4BC();
	const SpecialPowerTemplate *GetCreateAHeroSpecialPower(unsigned int index);
	BehaviorModule *rva0028F2C4(int key) const;
	const AsciiString &rva00292330(const AsciiString &name);

protected:
	Module *findModule(NameKeyType key) const;
private:
	unsigned char m_pad000[0x244];
	BehaviorModule **m_behaviors; // +0x244
	unsigned char m_pad248[0x304 - 0x248];
	Team *m_team304; // Native display-template paths read this relation owner.
	unsigned char m_pad308[0x4A4 - 0x308];
	_STL::vector<int> m_createAHeroPowers; // +0x4A4
};

BehaviorModule *Object::rva0028F2C4(int key) const
{
	BehaviorModule **behaviorModule = m_behaviors;
	for (; *behaviorModule != 0; behaviorModule++)
	{
		BehaviorModule *m = *behaviorModule;
		if (key == m->getModuleData()->getTagKey())
			return m;
	}
	return 0;
}

const SpecialPowerTemplate *Object::GetCreateAHeroSpecialPower(unsigned int index)
{
	const SpecialPowerTemplate *result = 0;
	if (index < m_createAHeroPowers.size())
	{
		int entry = m_createAHeroPowers[index];
		result = (const SpecialPowerTemplate *)((const Rva004B554FHolder *)rva0028F2C4(entry))->rva004B554F();
	}
	return result;
}

const AsciiString &Object::rva00292330(const AsciiString &name)
{
	for (unsigned int i = 0; i < m_createAHeroPowers.size(); ++i)
	{
		const SpecialPowerTemplate *power = GetCreateAHeroSpecialPower(i);
		const SpecialPowerTemplate *finalOverride = (const SpecialPowerTemplate *)power->friend_getFinalOverride();
		if (((const StringBase<char> &)name).compareNoCase((const StringBase<char> &)finalOverride->m_name) == 0)
		{
			BehaviorModule *module = rva0028F2C4(m_createAHeroPowers[i]);
			if (module != 0)
				return module->rva004B555F();
		}
	}
	return AsciiString::TheEmptyString;
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// Retail 0x002911B7..0x00291298, 225 bytes, RET 0. The matched portrait
// caller 0x00294759 establishes the returned ThingTemplate pointer. Native
// kind 0x12c selects the SpecialDisguiseUpdate module, while the other path
// uses the template at the owned 0x0028F4BC result +0x3c; local-player state
// and team relationship gate both paths. Original lexical method name unknown.
// Module key static initialization has the native guard-clear EH action.
// One null exit and a zero-code fence on the final successful return retain
// retail's common tail layout, with every existing compiler flag unchanged.
ThingTemplate *Object::rva002911B7()
{
	if (isKindOf(KIND_12C)) {
		if (((Rva002A7DD0 *)ThePlayerList)->rva002A7DD0())
			goto failed;
		Team *team = m_team304;
		Player *pl = ThePlayerList->m_local;
		if (pl->getRelationship(team) != REL_0)
			goto failed;
		static NameKeyType s_key = TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
		Module *mod = findModule(s_key);
		if (mod == 0)
			goto failed;
		return (ThingTemplate *)((Rva004B0333 *)mod)->rva004B0333();
	} else {
		Rva00373EC6 *p = rva0028F4BC();
		if (p == 0)
			goto failed;
		if (p->m_ptr3c == 0)
			goto failed;
		if (((Rva002A7DD0 *)ThePlayerList)->rva002A7DD0())
			goto failed;
		Team *team2 = m_team304;
		Player *player = ThePlayerList->m_local;
		if (player->getRelationship(team2) == REL_0) { _ReadWriteBarrier(); return (ThingTemplate *)p->m_ptr3c; }
		goto failed;
	}
failed: return 0;
}
