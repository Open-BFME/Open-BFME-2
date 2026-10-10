// ?rva0039E5B9@Team@@QAEXPAUCoord3D@@@Z
// partial score=0.9 date=2026-10-10
// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0039E5B9@Team@@QAEXPAUCoord3D@@@Z @0x0039E5B9 (167B).
// Team::rva0039E5B9(Coord3D *pos): writes the average member position (team
// centre) into *pos. Retail iterates the member DLINK via the rowed
// iterate_TeamMemberList (0x263864) and DLINK_ITERATOR<Object>::advance
// (0x263526), sums the three floats at Object+0x38/+0x3c/+0x40 with no call
// (direct position members), then scales by 1.0f/count. No empty-team guard:
// retail divides by zero (1.0f/0.0f) when the team has no members.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	// +0x38: retail reads three floats here while averaging (no call, so
	// direct members, not getPosition()).
	Coord3D m_position;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva0039E5B9(Coord3D *pos);
};

void Team::rva0039E5B9(Coord3D *pos)
{
	Coord3D total = { 0.0f, 0.0f, 0.0f };
	int count = 0;
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	for (; !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		total.x += obj->m_position.x;
		total.y += obj->m_position.y;
		total.z += obj->m_position.z;
		++count;
	}
	float invCount = 1.0f / (float)count;
	total.x *= invCount;
	total.y *= invCount;
	total.z *= invCount;
	*pos = total;
}
