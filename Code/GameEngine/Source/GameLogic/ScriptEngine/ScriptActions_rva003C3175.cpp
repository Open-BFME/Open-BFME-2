// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C3175Do@ScriptActions@@QAEXABVAsciiString@@_N@Z @0x003C3175 126B: lookup unit by value then DualWeaponBehavior module flag via cached NameKey. Evidence: rowed lookupUnitByValue 0x358752 via g_Va009FE16C nameToKey PBD 0x148E1A via TheNameKeyGenerator findModule 0x28B6D6 StringBase copy 0x365F0 globals g_Va00E02DCC g_00E02DC8 DualWeaponBehavior literal; caller 0x003CE542; ret 0x8 stdcall.
#include "ascii_string.h"

enum NameKeyType { NK_NONE = 0 };

#include "../../../Include/Common/Module.h"

// DualWeaponBehavior's flag byte at +0x20; only the store is recovered.
class DualWeaponBehaviorView : public Module
{
public:
	char m_pad08[0x18];
	unsigned char m_20;
};

class Object;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend void ScriptActions::Rva003C3175Do(const AsciiString &, bool);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);
};
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C3175Do(const AsciiString &name, bool flag)
{
	Object *obj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue((AsciiString &)name);
	if (obj == 0)
		return;
	static NameKeyType dualKey = TheNameKeyGenerator->nameToKey("DualWeaponBehavior");
	Module *module = obj->findModule(dualKey);
	if (module == 0)
		return;
	((DualWeaponBehaviorView *)module)->m_20 = flag;
}
