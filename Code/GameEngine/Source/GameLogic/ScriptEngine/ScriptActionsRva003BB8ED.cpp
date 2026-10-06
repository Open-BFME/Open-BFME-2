// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB8EDReveal@@YGXABVAsciiString@@M0@Z, retail 0x003BB8ED, 95 bytes.
// Reveal/shroud circle at waypoint for player mask.
// Evidence: leaf lane; callees TerrainLogic slot 0x88 ScriptEngine rva00357475 ShroudManager rva00739A30 rva00739BE0; caller 0x003CBE39.
class AsciiString;
struct Pair00739BE0
{
	float x;
	float y;
};
struct TerrainLogicResult
{
	char m_pad00[0xc];
	Pair00739BE0 m_pair;
};
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
	virtual TerrainLogicResult *slot88(const AsciiString &name);
};
extern TerrainLogic *TheTerrainLogic;
class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matched);
};
extern class ScriptEngine *TheScriptEngine;
class PartitionManager;
extern PartitionManager *TheShroudManager;
class Rva00739A30
{
public:
	void rva00739A30(Pair00739BE0 *p, float f, int mask);
};
class Rva00739BE0
{
public:
	void rva00739BE0(Pair00739BE0 *p, float f, int mask);
};
void __stdcall Rva003BB8EDReveal(const AsciiString &where, float radius, const AsciiString &playerName)
{
	TerrainLogicResult *loc = TheTerrainLogic->slot88(where);
	if (loc == 0)
		return;
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	((Rva00739A30 *)TheShroudManager)->rva00739A30(&loc->m_pair, radius, mask);
	((Rva00739BE0 *)TheShroudManager)->rva00739BE0(&loc->m_pair, radius, mask);
}
