// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB76EDo@@YGXPAUCoord3D@@PAX@Z @0x003BB76E 47B: free stdcall Coord+extra to Radar+Eva.
// Target evidence: fld g_00BC2918 Radar 0x009FF070 via pin 0x002D88A4 with extra+float then g_00DFDC30 via pin 0x001DDAE1 ret 8; caller 0x003CBCE8.
struct Coord3D
{
	float x;
	float y;
	float z;
};
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
void __stdcall Rva003BB76EDo(Coord3D *pos, void *extra)
{
	((Rva002D88A4 *)TheRadar)->rva002D88A4(pos, extra, g_00BC2918);
	(*(Rva001DDAE1 **)&TheEva)->rva001DDAE1(pos);
}
