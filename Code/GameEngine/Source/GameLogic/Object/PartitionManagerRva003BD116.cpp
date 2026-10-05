// cl: /O1
// ?Rva003BD116Set@@YGXPAVParameter@@PAX@Z retail 0x003BD116 61 bytes.
// Teleport-like set: obj = g_Va009FE16C->getUnitNamed(p1); pos = TheTerrainLogic slot 0x88(p2); if pos then obj->rva0029660C(pos+0xC, 0). Evidence: callees rowed 0x003588E7 pin 0x0029660C; caller 0x003CE7AC; neighbours Rva003BD0C8 prev Rva003BD153 next same /O1.
class Parameter;
class Object;
struct Coord3D { float x, y, z; };
class Object
{
public:
	void rva0029660C(const Coord3D *pos, int flag);
};
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern ScriptEngine *g_Va009FE16C;
class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
	virtual void *s34(void *p);
};
extern TerrainLogic *TheTerrainLogic;

void __stdcall Rva003BD116Set(Parameter *p1, void *p2)
{
	Object *obj = g_Va009FE16C->getUnitNamed(p1);
	if (obj == 0)
		return;
	void *base = TheTerrainLogic->s34(p2);
	if (base == 0)
		return;
	obj->rva0029660C((const Coord3D *)((const char *)base + 0xC), 0);
}
