// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BC421Do@@YGXPAVParameter@@H@Z @0x003BC421 69B: script action on a named unit's +0x250 interface.
// Evidence: rowed getUnitNamed 0x003588E7 then +0x250 null check then slot 0x114 gate with 0 then slot 0x110 with bfmeGoBGB 0x003BC40D plus 0 and 3; same TheScriptEngine and stdcall shape as Rva003BC259Remove; caller 0x003CD0EC in dispatch; second arg unused per retail.
class Parameter;
class Object;
class BfmeSubBGB;

int __cdecl bfmeGoBGB(BfmeSubBGB *sub);

class Iface00250
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
	virtual void s65(); virtual void s66(); virtual void s67();
	virtual void slot68(int (__cdecl *cb)(BfmeSubBGB *), int a, int b);
	virtual int slot69(int a);
};

class Object
{
public:
	char m_pad[0x250];
	Iface00250 *m_250; // +0x250
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};

extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003BC421Do(Parameter *param, int unused)
{
	(void)unused;
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	Iface00250 *iface = obj->m_250;
	if (iface == 0)
		return;
	if (iface->slot69(0) == 0)
		return;
	iface->slot68(bfmeGoBGB, 0, 3);
}
