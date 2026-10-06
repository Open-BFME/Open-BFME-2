// cl: /DNDEBUG /MD
//
// ?rva002D834E@Radar@@QAEPAVObject@@PBUICoord2D@@@Z retail 0x002D834E 71B.
// Radar pixel pick: null-guard pixel then localPixelToRadar into a stack
// ICoord2D then search m_localObjectList +0x18 then m_objectList +0x14 via
// rowed searchListForRadarLocationMatch. Evidence: thiscall with ret 4 and same this as rowed
// localPixelToRadar 0x002D81EC and searchListForRadarLocationMatch 0x002D78A4; member offsets
// from RadarRva002D78A4.cpp comment; prev Radar_screenPixelToWorld.cpp gives
// TU and flags.

struct ICoord2D
{
	int x;
	int y;
};

class Object;
class RadarObject;

class Radar
{
public:
	bool localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar);
	Object *searchListForRadarLocationMatch(RadarObject *list, ICoord2D *target);
	Object *rva002D834E(const ICoord2D *pixel);

private:
	char m_pad14[0x14];
	RadarObject *m_objectList; // +0x14
	RadarObject *m_localObjectList; // +0x18
};

Object *Radar::rva002D834E(const ICoord2D *pixel)
{
	ICoord2D radar;
	if (pixel == 0)
		return 0;
	if (!localPixelToRadar(pixel, &radar))
		return 0;
	Object *obj = searchListForRadarLocationMatch(m_localObjectList, &radar);
	if (obj != 0)
		return obj;
	return searchListForRadarLocationMatch(m_objectList, &radar);
}
