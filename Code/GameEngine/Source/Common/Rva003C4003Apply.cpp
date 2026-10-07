// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva003C4003Apply@@YGXPAVParameter@@ABVAsciiString@@PAX@Z @0x003C4003 109B.
// Sibling of 0x003C41BA: resolve unit via ScriptEngine then SpecialPowerTemplate
// by name, filter via BfmeSubBEC, then apply via TerrainLogic helper and slot
// 0x30 virtual. Evidence: rowed getUnitNamed 0x003588E7 via g_Va009FE16C,
// rowed findSpecialPowerTemplate 0x0029B6EB via TheSpecialPowerStore, rowed
// BfmeSubBEC 0x0028BB9E, TerrainLogic virtual +0x88, StringBase copy 0x000365F0;
// prev/next share // cl: /O1; caller 0x003CC71D.
#include "ascii_string.h"

class Parameter;
class Object;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};

extern class ScriptEngine *TheScriptEngine;

class TerrainLogic
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
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void *v34(void *arg);
};

extern TerrainLogic *TheTerrainLogic;

class SpecialPowerTemplate;
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class BfmeSubBEC
{
public:
	void *rva0028BB9E(void *found);
};

class Rva003C4003Target
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12(void *helperSub, int flags);
};

void __stdcall Rva003C4003Apply(Parameter *p, const AsciiString &name, void *arg3)
{
	Object *obj = TheScriptEngine->getUnitNamed(p);
	const SpecialPowerTemplate *found = TheSpecialPowerStore->findSpecialPowerTemplate(name);
	if (obj != 0 && found != 0)
	{
		void *sub = ((BfmeSubBEC *)obj)->rva0028BB9E((void *)found);
		if (sub != 0)
		{
			void *helper = TheTerrainLogic->v34(arg3);
			if (helper != 0)
				((Rva003C4003Target *)sub)->w12((void *)((char *)helper + 0xc), 0x40000);
		}
	}
}
