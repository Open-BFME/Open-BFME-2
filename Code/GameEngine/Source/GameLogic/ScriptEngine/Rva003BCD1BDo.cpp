// cl: /O1
// ?Rva003BCD1BDo@@YGXPAVParameter@@@Z @0x003BCD1B 42B: script fire special power slot 0x44.
// Evidence: push [esp+4] mov ecx,[0xDFE16C]=g_Va009FE16C call rowed getUnitNamed 0x003588E7 test je; push 0x2d mov ecx,eax call rowed findSpecialPowerModuleInterface 0x00290E22 test je; mov edx,[eax] mov ecx,eax call [edx+0x44] ret 4; caller 0x003CDCD0; sibling Rva003BCCC6Do same 0x2d pattern.
class Parameter;
class Object;

class SpecialPowerModuleInterface
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
	virtual void slot17();
};

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};

class Object
{
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003BCD1BDo(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	SpecialPowerModuleInterface *sp = obj->findSpecialPowerModuleInterface((SpecialPowerType)0x2d);
	if (sp == 0)
		return;
	sp->slot17();
}
