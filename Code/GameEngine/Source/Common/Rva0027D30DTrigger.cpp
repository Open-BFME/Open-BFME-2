// cl: /MD
// ?rva0027D30D@Rva0027D30D@@QAEXPAUCoord3D@@H@Z, retail 0x0027D30D, 58 bytes.
// Thiscall counter plus trigger pointer: converts float triple at [ebp+8]
// via cvttss2si to ICoord3D temp, calls rowed
// ?pointInTrigger@PolygonTrigger@@QAE_NABVICoord3D@@@Z on [esi+4], inc [esi]
// if true. ret 8 means second int arg is dummy like neighbour Rva0027D347.
// Evidence: callee row PolygonTrigger_pointInTrigger, caller 0x0027E4BD.
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
};

class Rva0027D30D
{
public:
	void rva0027D30D(Coord3D *p, int dummy);
private:
	int m_count;
	PolygonTrigger *m_trigger;
};

void Rva0027D30D::rva0027D30D(Coord3D *p, int dummy)
{
	ICoord3D tmp;
	tmp.x = (int)p->x;
	tmp.y = (int)p->y;
	tmp.z = (int)p->z;
	if (m_trigger->pointInTrigger(tmp))
		++m_count;
}
