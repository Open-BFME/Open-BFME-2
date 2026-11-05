// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BAD15@ScriptActions@@QAEXABVAsciiString@@MM0@Z @0x003BAD15 239B: free two strings plus two floats resolving two Terrain coords to four TacticalView calls.
// Evidence: ret 16 four args; push [ebp+8] call Terrain s34 je; movss [ebp-0xc] triple; push [ebp+0x14] call s34 je; TV s60 with 1 0 0 and zeros; lea [ebp-0x18] TV s94; fld [ebp+0x10] TV s88 with zeros; fld [ebp+0xc] TV s7c with zeros; caller 0x003CABBF.
#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Include/GameLogic/TerrainLogic.h"
#include "../../../Include/GameLogic/Waypoint.h"
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
extern class View *TheTacticalView;

void ScriptActions::Rva003BAD15(const AsciiString &asciiString, float zoom, float pitch, const AsciiString &lookAtWaypointName)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(asciiString);
	if (!way)
		return;
	Coord3D ca;
	ca.x = way->getLocation()->x;
	ca.y = way->getLocation()->y;
	ca.z = way->getLocation()->z;
	Waypoint *lookAtWaypoint = TheTerrainLogic->getWaypointByName(lookAtWaypointName);
	if (!lookAtWaypoint)
		return;
	Coord3D cb;
	cb.x = lookAtWaypoint->getLocation()->x;
	cb.y = lookAtWaypoint->getLocation()->y;
	cb.z = lookAtWaypoint->getLocation()->z;
	((TacticalView *)TheTacticalView)->s24(&ca, 0, 0, 1, 0.0f, 0.0f);
	((TacticalView *)TheTacticalView)->s37(&cb);
	((TacticalView *)TheTacticalView)->s34(pitch, 0.0f, 0.0f);
	((TacticalView *)TheTacticalView)->s31(zoom, 0.0f, 0.0f);
}
