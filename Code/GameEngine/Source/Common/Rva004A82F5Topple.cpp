// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva004A82F5@Rva004A82F5@@QAEXPAVObject@@HH@Z @0x004A82F5 150B ret 0xC.
// Topple the owner at this-0x18 away from src when src's level is higher.
// A zero height is replaced by the object at src+0x274.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char rva00294815();
	signed char rva0028CE7B() const;
	float rva0028AC7D() const;
	void topple(const Coord3D *dir, float speed, unsigned int options);
	char m_beforePos[0x38];
	Coord3D m_pos;
};

class Rva004A82F5
{
public:
	void rva004A82F5(Object *src, int unusedA, int unusedB);
};

void Rva004A82F5::rva004A82F5(Object *src, int unusedA, int unusedB)
{
	if (src == 0)
		return;
	char level = src->rva00294815();
	if (level <= (*(Object **)((char *)this - 0x18))->rva0028CE7B())
		return;
	const Coord3D *ownerPos = &(*(Object **)((char *)this - 0x18))->m_pos;
	Coord3D delta;
	delta.x = ownerPos->x;
	delta.y = ownerPos->y;
	delta.x -= src->m_pos.x;
	delta.y -= src->m_pos.y;
	delta.z = 0.0f;
	float height = src->rva0028AC7D();
	if (height == 0.0f)
	{
		Object *other = *(Object **)((char *)src + 0x274);
		if (other != 0)
			height = other->rva0028AC7D();
	}
	(*(Object **)((char *)this - 0x18))->topple(&delta, height, 0);
}
