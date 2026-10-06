// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?Rva003BFA77Do@@YGXABVParameter@@H@Z @0x003BFA77 76B.
// Script unit damage via getUnitNamed then DamageInfo 0x7C with int amount
// as float and fixed 8.
// Evidence: rowed getUnitNamed Rva00263895Member ctor, pin attemptDamage,
// extern g_Va009FE16C, caller 0x003CB8B7, ret 8, SSE movss.
#include "ascii_string.h"

class Parameter;
class Object;
class DamageInfo;

class Rva00263653
{
public:
	char m_pad00[0x04];
	int m_04;
	char m_pad08[0x0C - 0x08];
	int m_0C;
	char m_pad10[0x18 - 0x10];
	int m_18;
	float m_1C;
	char m_pad20[0x68 - 0x20];
};

class Rva00263895Member
{
public:
	Rva00263895Member();
	void *m_vtbl;
	Rva00263653 m_mem;
	char m_tail10[0x7C - 0x6C];
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};

class Object
{
public:
	void attemptDamage(DamageInfo *info);
};

extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003BFA77Do(const Parameter &p, int amount)
{
	Object *obj = TheScriptEngine->getUnitNamed((Parameter *)&p);
	if (obj == 0)
		return;
	Rva00263895Member dmg;
	float f = (float)amount;
	dmg.m_mem.m_18 = 0;
	dmg.m_mem.m_04 = 0;
	dmg.m_mem.m_0C = 8;
	dmg.m_mem.m_1C = f;
	obj->attemptDamage((DamageInfo *)&dmg);
}
