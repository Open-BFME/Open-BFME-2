// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BC96FDo@@YGXPAVParameter@@H@Z @0x003BC96F 39B: script set Object+0x264 inner +0x28 from second arg.
// Evidence: push [esp+4] mov ecx,[0xDFE16C]=g_Va009FE16C call rowed getUnitNamed 0x003588E7 test eax je; mov eax,[eax+0x264] test je; mov ecx,[esp+8] mov [eax+0x28],ecx ret 8; caller 0x003CDC3E; sibling Rva003E514F same +0x264 pattern with +0x24.
class Parameter
{
};

class ObjectInner003BC96F
{
public:
	char m_pad[0x28];
	int m_28;
};

class Object
{
public:
	char m_pad[0x264];
	ObjectInner003BC96F *m_264;
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003BC96FDo(Parameter *param, int val)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	ObjectInner003BC96F *inner = obj->m_264;
	if (inner == 0)
		return;
	inner->m_28 = val;
}
