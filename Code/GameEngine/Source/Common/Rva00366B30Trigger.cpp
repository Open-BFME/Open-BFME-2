// cl: /MD
// ?rva00366B30@Rva00366B30@@QAE_NPBUCoord3D@@@Z 0x00366B30 71B walk PolygonTrigger list at +0x38 calling pointInTrigger; float Coord3D arg converted via cvttss2si to ICoord3D; callers in 0x00366B77; callees rowed pointInTrigger 0x002E3A13
struct Coord3D
{
	float x;
	float y;
	float z;
};

class ICoord3D
{
public:
	int x;
	int y;
	int z;
};

class PolygonTrigger
{
public:
	bool pointInTrigger(const ICoord3D &point);
	char m_pad00[0x3c];
	PolygonTrigger *m_next3C;
};

class Rva00366B30
{
public:
	bool rva00366B30(const Coord3D *point);
private:
	char m_pad00[0x38];
	PolygonTrigger *m_head38;
};

bool Rva00366B30::rva00366B30(const Coord3D *point)
{
	ICoord3D ic;
	ic.x = (int)point->x;
	ic.y = (int)point->y;
	ic.z = (int)point->z;
	PolygonTrigger *trig = m_head38;
	while (trig != 0) {
		if (trig->pointInTrigger(ic))
			return true;
		trig = trig->m_next3C;
	}
	return false;
}
