// ?Rva003BAAE4@@YGXABVAsciiString@@MMMM@Z
// partial score=0.9 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE
// ?Rva003BAAE4@@YGXABVAsciiString@@MMMM@Z @0x003BAAE4 150B: free stdcall AsciiString plus four floats resolving Coord via TerrainLogic slot 0x88 and CameraMarkerList::find to TacticalView slot 0x60.
// Evidence: ret 20 five args; push [ebp+8] call [eax+0x88] plus find row; test esi je; 3x movsd 12B copies from +0xc and +8 to [ebp-0xc]; movss+mulss scales plus cvtt int plus push 1; push eax marker plus lea [ebp-0xc]; call [edx+0x60]; caller 0x003CAB7A.
#include "ascii_string.h"
extern float g_00BBE358;

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
struct CameraMarker
{
	char m_pad[8];
	Coord3D m_pos;
};
class CameraMarkerList
{
public:
	CameraMarker *find(const AsciiString &name) const;
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
	virtual void s24(Coord3D *p, CameraMarker *m, int a, int b, float c, float d);
};
extern TacticalView *TheTacticalView;

// ?Rva003BAAE4@@YGXABVAsciiString@@MMMM@Z present-unmatched
void __stdcall Rva003BAAE4(const AsciiString &name, float a1, float a2, float a3, float a4)
{
	TerrainLogicPos *tp = TheTerrainLogic->s34(name);
	CameraMarker *m = ((CameraMarkerList *)TheTacticalView)->find(name);
	if (!tp && !m)
		return;
	Coord3D pos;
	if (tp)
		pos = tp->m_pos;
	if (m)
		pos = m->m_pos;
	TheTacticalView->s24(&pos, m, (int)(a1 * g_00BBE358), 1, a3 * g_00BBE358, a4 * g_00BBE358);
}
