// ?addScorch@BaseHeightMapRenderObjClass@@QAEXVVector3@@MW4Scorches@@@Z
// partial score=0.9227 date=2026-10-05
// ?addScorch@BaseHeightMapRenderObjClass@@QAEXVVector3@@MW4Scorches@@@Z present-unmatched
// cl: /O1 /DNDEBUG /MD /Oi- /arch:SSE
// Target signature follows the REL32 call from W3DGameClient::addScorch.
// The array and state offsets are independently established by target bytes.

class Vector3
{
public:
	float x;
	float y;
	float z;
};

enum Scorches
{
	SCORCHES_UNKNOWN = 0
};

extern "C" double __cdecl fabs(double v);

struct ScorchEntry00067EA3
{
	float unk00;
	Vector3 position;
	float radius;
	int kind;
	unsigned char active;
	char pad[3];
};

class BaseHeightMapRenderObjClass
{
public:
	void addScorch(Vector3 pos, float radius, Scorches type);
private:
	unsigned char m_pad[0xE0];
	ScorchEntry00067EA3 m_entries[500];
	int m_count;
	int m_flag3794;
	int m_head;
};

void BaseHeightMapRenderObjClass::addScorch(Vector3 pos, float radius, Scorches type)
{
	float estimate = radius * 0.25f;
	for (int i = 0; i < m_count; ++i)
	{
		ScorchEntry00067EA3 *entry = &m_entries[i];
		if (!(fabs(pos.x - entry->position.x) < estimate))
			continue;
		if (!(fabs(pos.y - entry->position.y) < estimate))
			continue;
		if (!(fabs(radius - entry->radius) < estimate))
			continue;
		if (entry->kind != type)
			continue;
		m_entries[i].active = 0;
		return;
	}
	int slot = m_count;
	if (slot >= 500)
	{
		slot = m_head;
		int next = (slot + 1) % 500;
		m_head = next;
		--m_count;
	}
	ScorchEntry00067EA3 *selected = &m_entries[slot];
	Vector3 *position = &selected->position;
	position->x = pos.x;
	position->y = pos.y;
	position->z = pos.z;
	selected->radius = radius;
	selected->kind = type;
	selected->active = 0;
	++m_count;
	m_flag3794 = 0;
}
