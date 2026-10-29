// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// Retail 0x003C4245 (RVA 0x003C4245) size 116: script apply power to named target.
// Evidence: ScriptEngine 0xDFE16C getUnitNamed then lookupUnitByValue then SpecialPowerStore 0xE02D4C findSpecialPowerTemplate then Object::getSpecialPowerModule then vtable+0x2c with 0x40000.
#include "ascii_string.h"

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
};

class Parameter;
class Object;
class SpecialPowerTemplate;

#include "../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString s);
};

class SpecialPowerStore;

extern SpecialPowerStore *TheSpecialPowerStore;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString s);
};

class BecSlot
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
	virtual void v11(Object *target, int flags);
};

void ScriptActions::doNamedFireSpecialPowerAtNamed(Parameter *param, const AsciiString &asciiString, const AsciiString &b)
{
	Object *src = TheScriptEngine->getUnitNamed(param);
	Object *target = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(b);
	const SpecialPowerTemplate *specialPowerTemplate = TheSpecialPowerStore->findSpecialPowerTemplate(asciiString);
	if (src == 0 || specialPowerTemplate == 0 || target == 0)
		return;
	void *bec = src->getSpecialPowerModule(specialPowerTemplate);
	if (bec == 0)
		return;
	((BecSlot *)bec)->v11(target, 0x40000);
}
