// cl: /DNDEBUG /MD /EHsc
// Pathfinder::SetDebugPathPosition (WorldBuilder name, pathfinder.cpp lines 5116..5120: copy the position into +0x4C).
// was ?rva002E74B5@Rva002E74B5@@QAEXPBUCoord3D@@@Z @0x002E74B5 17B
// Evidence: unlocks 0x00363930; copies 12B to +0x4C; caller passes Coord3D floats.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Pathfinder
{
public:
	void SetDebugPathPosition(const Coord3D *p);

private:
	char m_pad00[0x4C];
	Coord3D m_at4C;
};

void Pathfinder::SetDebugPathPosition(const Coord3D *p)
{
	m_at4C = *p;
}
