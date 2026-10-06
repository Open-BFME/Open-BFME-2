// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCEFBDo@@YGXPAVParameter@@@Z @0x003BCEFB 52B: script getUnitNamed then iface slot 0x18 then global slot 0x68.
// Evidence: push [esp+4] mov ecx,[0xDFE16C]=g_Va009FE16C call rowed getUnitNamed 0x003588E7 test eax je; mov ecx,eax call rowed rva0028BCF4 0x0028BCF4 mov edx,[eax] mov ecx,eax call [edx+0x18] test eax je; mov ecx,[0xE027B8]=g_00A027B8 mov edx,[ecx] push eax call [edx+0x68] ret 4; caller 0x003CE740; sibling Rva003BC96FDo same getUnitNamed stdcall shape.
class Parameter
{
};

class Rva003BCEFBIface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void *s06();
};

class Object
{
public:
	void *rva0028BCF4() const;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;

class Rva00A027B8
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26(void *arg);
};
extern class Rva00A027B8 *g_00A027B8;

void __stdcall Rva003BCEFBDo(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	Rva003BCEFBIface *iface = (Rva003BCEFBIface *)obj->rva0028BCF4();
	void *res = iface->s06();
	if (res == 0)
		return;
	g_00A027B8->slot26(res);
}
