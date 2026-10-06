// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva003C45D4Apply@@YGXPAVParameter@@ABVAsciiString@@@Z @0x003C45D4 81B.
// Script unit helper: getUnitNamed via g_Va009FE16C, nameToKey via
// TheNameKeyGenerator, level lookup via g_00DFECC4 and rowed 0x0028951F,
// then rowed 0x0039B24F on the +0x264 link with (input 0 true) and clear
// byte at +0x20. Evidence: chain via 0x0039B24F; rowed callees; globals
// g_Va009FE16C TheNameKeyGenerator g_00DFECC4; caller 0x003CDBDB; ret 8.
#include "ascii_string.h"

class Parameter;
class Object;
class Overridable;

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern class ScriptEngine *TheScriptEngine;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva0028951F
{
public:
	const Overridable *rva0028951F(int key);
};
extern Rva0028951F *g_00DFECC4;

struct Rva0039B24FInput;

class Rva0039B24F
{
public:
	void rva0039B24F(Rva0039B24FInput *input, int v, bool flag);
	char m_pad[0x20];
	unsigned char m_20alias;
};

struct UnitLink264
{
	char m_pad[0x264];
	Rva0039B24F *m_link;
};

void __stdcall Rva003C45D4Apply(Parameter *param, const AsciiString &name)
{
	Object *unit = TheScriptEngine->getUnitNamed(param);
	if (!unit)
		return;
	int key = TheNameKeyGenerator->nameToKey(name);
	const Overridable *lvl = g_00DFECC4->rva0028951F(key);
	if (!lvl)
		return;
	UnitLink264 *link = (UnitLink264 *)unit;
	link->m_link->rva0039B24F((Rva0039B24FInput *)lvl, 0, true);
	link->m_link->m_20alias = 0;
}
