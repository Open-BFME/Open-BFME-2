// cl: /Ireference/shims/bfme2_ascii
// ?Rva003BC1A0Forward@@YAXXZ @0x003BC1A0 18B: script forwards TheTerrainLogic to TheRadar slot 0x10.
// Evidence: mov ecx,[0xDFF070]=TheRadar push [0xDFEC50]=TheTerrainLogic mov eax,[ecx] call [eax+0x10] ret; caller 0x003CC86C.
class TerrainLogic;
class Radar
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04(TerrainLogic *t);
};
extern Radar *TheRadar;
extern TerrainLogic *TheTerrainLogic;

void __cdecl Rva003BC1A0Forward()
{
	TheRadar->s04(TheTerrainLogic);
}
