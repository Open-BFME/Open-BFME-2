// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB79DDo@@YGXPAVParameter@@PAX@Z @0x003BB79D 69B: free stdcall mapping Parameter to Object then Radar+Eva on Object+0x38.
// Target evidence: push [esp+4] ScriptEngine::getUnitNamed 0x003588E7 test je then lea esi [eax+0x38] test je then fld g_00BC2918 Radar 0x009FF070 via pin 0x002D88A4 with extra+float then g_00DFDC30 via pin 0x001DDAE1 ret 8; caller 0x003CBD09.
class Parameter;
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad[0x38];
	Coord3D m_pos;
};
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *);
};
extern class ScriptEngine *TheScriptEngine;
class Radar;
extern Radar *TheRadar;
class Rva002D88A4
{
public:
	void rva002D88A4(Coord3D *pos, void *extra, float scale);
};
class Rva001DDAE1
{
public:
	void rva001DDAE1(Coord3D *pos);
};
extern class Eva *TheEva;
extern float g_00BC2918;
void __stdcall Rva003BB79DDo(Parameter *p, void *extra)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	const Coord3D *pos = o->getPosition();
	if (!pos)
		return;
	((Rva002D88A4 *)TheRadar)->rva002D88A4((Coord3D *)pos, extra, g_00BC2918);
	(*(Rva001DDAE1 **)&TheEva)->rva001DDAE1((Coord3D *)pos);
}
