// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x003C4245 (RVA 0x003C4245) size 116: script apply power to named target.
// Evidence: ScriptEngine 0xDFE16C getUnitNamed then lookupUnitByValue then SpecialPowerStore 0xE02D4C findSpecialPowerTemplate then BfmeSubBEC rva0028BB9E then vtable+0x2c with 0x40000.
#include "ascii_string.h"

class Parameter;
class Object;
class SpecialPowerTemplate;

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};

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

class BfmeSubBEC
{
public:
	void *rva0028BB9E(void *p);
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

void __stdcall Rva003C4245Do(Parameter *param, const AsciiString &a, const AsciiString &b)
{
	Object *src = TheScriptEngine->getUnitNamed(param);
	Object *target = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(b);
	const SpecialPowerTemplate *tmpl = TheSpecialPowerStore->findSpecialPowerTemplate(a);
	if (src == 0 || tmpl == 0 || target == 0)
		return;
	void *bec = ((BfmeSubBEC *)src)->rva0028BB9E((void *)tmpl);
	if (bec == 0)
		return;
	((BecSlot *)bec)->v11(target, 0x40000);
}
