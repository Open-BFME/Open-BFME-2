// cl: /DNDEBUG /MD
//
// ?rva002D78A4@Radar@@QAEPAVObject@@PAVRadarObject@@PAUICoord2D@@@Z @0x002D78A4 102B Radar list search: walks a RadarObject
// list (m_object at +4, m_next at +8), runs rowed worldToRadar on each
// Object pos at +0x38 into a stack ICoord2D, and returns the first Object
// whose radar cell is within +-1 of the target ICoord2D. Evidence: same
// this as rowed worldToRadar; caller 0x002D834E passes m_localObjectList
// +0x18 then m_objectList +0x14 with a localPixelToRadar ICoord2D;
// prev/next are Radar_radarToWorld / findDrawPositions with same flags.

struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_pos; // +0x38
};

class RadarObject
{
public:
	virtual void *deleteInstance(int pool);
	Object *m_object; // +0x04
	RadarObject *m_next; // +0x08
};

class Radar
{
public:
	bool worldToRadar(const Coord3D *world, ICoord2D *radar);
	Object *rva002D78A4(RadarObject *list, ICoord2D *target);
};

Object *Radar::rva002D78A4(RadarObject *list, ICoord2D *target)
{
	if (list == 0 || target == 0)
		return 0;
	for (RadarObject *node = list; node != 0; node = node->m_next)
	{
		Object *obj = node->m_object;
		if (obj == 0)
			continue;
		ICoord2D tmp;
		worldToRadar(&obj->m_pos, &tmp);
		if (tmp.x >= target->x - 1 && tmp.x <= target->x + 1
			&& tmp.y >= target->y - 1 && tmp.y <= target->y + 1)
			return obj;
	}
	return 0;
}
