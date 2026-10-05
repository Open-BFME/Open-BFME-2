// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE
// ?Rva003BAD15@@YGXABVAsciiString@@MM0@Z @0x003BAD15 239B: free two strings plus two floats resolving two Terrain coords to four TacticalView calls.
// Evidence: ret 16 four args; push [ebp+8] call Terrain s34 je; movss [ebp-0xc] triple; push [ebp+0x14] call s34 je; TV s60 with 1 0 0 and zeros; lea [ebp-0x18] TV s94; fld [ebp+0x10] TV s88 with zeros; fld [ebp+0xc] TV s7c with zeros; caller 0x003CABBF.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};
struct TerrainLogicPos
{
	char m_pad[0xC];
	Coord3D m_pos;
};
class TerrainLogic
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual TerrainLogicPos *s34(const AsciiString &name);
};
extern TerrainLogic *TheTerrainLogic;

class TacticalView
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24(Coord3D *a, int b, int c, int d, float e, float f);
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31(float a, float b, float c);
	virtual void s32();
	virtual void s33();
	virtual void s34(float a, float b, float c);
	virtual void s35();
	virtual void s36();
	virtual void s37(Coord3D *p);
};
extern TacticalView *TheTacticalView;

void __stdcall Rva003BAD15(const AsciiString &n0, float f1, float f2, const AsciiString &n3)
{
	TerrainLogicPos *a = TheTerrainLogic->s34(n0);
	if (!a)
		return;
	Coord3D ca;
	ca.x = a->m_pos.x;
	ca.y = a->m_pos.y;
	ca.z = a->m_pos.z;
	TerrainLogicPos *b = TheTerrainLogic->s34(n3);
	if (!b)
		return;
	Coord3D cb;
	cb.x = b->m_pos.x;
	cb.y = b->m_pos.y;
	cb.z = b->m_pos.z;
	TheTacticalView->s24(&ca, 0, 0, 1, 0.0f, 0.0f);
	TheTacticalView->s37(&cb);
	TheTacticalView->s34(f2, 0.0f, 0.0f);
	TheTacticalView->s31(f1, 0.0f, 0.0f);
}
