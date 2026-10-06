// cl: /DNDEBUG /MD
// ?rva00263910@Rva00263910@@QAEXPBUCoord3D@@MH@Z
//
// retail 0x00263910 (297 bytes). AIUpdate goal-position helper: copy pos to
// local, when flag==0 adjust height from TheWritableGlobalData+0xD4 scaled by
// 0.5f and max with [1F0]+0x48 when Object flag 0x10 plus
// isSignificantlyAboveTerrain, clamp local x/y into TerrainLogic extents
// (slot 0x20) expanded by height, then StateMachine::setGoalPosition.
// Evidence: callees rowed 0x004D745C plus pin 0x0030ADDC; callers 0x00265667
// (26B) and 0x0026C04E (136B slot 14 of AIUpdate derivatives) pass this+own
// args; globals TheWritableGlobalData TheTerrainLogic 0.5f in use.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	bool isSignificantlyAboveTerrain() const;
	char m_pad04[4];
	struct Flags109 *m_flags109;
};

struct Flags109
{
	char m_pad00[0x109];
	unsigned char m_flags;
};

struct HeightHolder
{
	char m_pad00[0x48];
	float m_val;
};

class StateMachine
{
public:
	void setGoalPosition(const Coord3D *pos, float range);
};

class GlobalData
{
public:
	char m_pad00[0xD4];
	float m_val;
};

extern GlobalData *TheWritableGlobalData;

struct Extents
{
	Coord3D m_min;
	Coord3D m_max;
};

class TerrainLogic
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void getExtents(Extents *out);
};

extern TerrainLogic *TheTerrainLogic;

static const float &float_max(const float &a, const float &b)
{
	return (a > b) ? a : b;
}

class Rva00263910
{
public:
	void rva00263910(const Coord3D *pos, float range, int flag);
	void rva00265667(const Coord3D *pos, int flag);
	char m_pad00[8];
	Object *m_object; // +8
	char m_pad0C[0x30 - 0x0C];
	StateMachine *m_machine; // +0x30
	char m_pad34[0x1F0 - 0x34];
	HeightHolder *m_height; // +0x1F0
};

void Rva00263910::rva00263910(const Coord3D *pos, float range, int flag)
{
	Coord3D local;
	float h;
	if (pos != 0) {
		local.x = pos->x;
		local.y = pos->y;
		local.z = pos->z;
		if (flag == 0) {
			h = TheWritableGlobalData->m_val * 0.5f;
			if ((m_object->m_flags109->m_flags & 0x10) != 0) {
				if (m_object->isSignificantlyAboveTerrain()) {
					if (m_height != 0) {
						float v = m_height->m_val;
						h = float_max(h, v);
					}
				}
			}
			Extents e;
			TheTerrainLogic->getExtents(&e);
			float loX = e.m_min.x + h;
			if (loX > local.x)
				local.x = loX;
			float hiX = e.m_max.x - h;
			if (local.x > hiX)
				local.x = hiX;
			float loY = e.m_min.y + h;
			if (loY > local.y)
				local.y = loY;
			float hiY = e.m_max.y - h;
			if (local.y > hiY)
				local.y = hiY;
			m_machine->setGoalPosition(&local, range);
		} else {
			m_machine->setGoalPosition(&local, range);
		}
	} else {
		m_machine->setGoalPosition(0, range);
	}
}

// ?rva00265667@Rva00263910@@QAEXPBUCoord3D@@H@Z @0x00265667 (26B).
// Forwards this plus own args to rva00263910 with range from 3.4028235e+38f.
// Evidence: retail pushes flag then fld 3.4028235e+38f then pos and calls rowed
// 0x00263910 with unchanged ecx; ret 8 matches (pos flag); 15 callers pass pos plus flag.
void Rva00263910::rva00265667(const Coord3D *pos, int flag)
{
	rva00263910(pos, 3.4028235e+38f, flag);
}
