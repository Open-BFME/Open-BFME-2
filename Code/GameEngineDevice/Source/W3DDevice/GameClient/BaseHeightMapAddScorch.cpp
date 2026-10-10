// ?addScorch@BaseHeightMapRenderObjClass@@QAEXVVector3@@MW4Scorches@@@Z
// Ref: Open-BFME-1@575ba2b04743f190f069805fbdc59936123c45da
// game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp addScorch.
// Ring-buffer algorithm follows that donor; target array E0/stride1C and state
// 3790/3794/3798 are independently proven by native67EA3..67FCD (298B).
// Target identity: W3DGameClient::addScorch4C7A8 calls67EA3 on
// TheTerrainRenderObject. User-defined Vector3 copy preserves float stores.
// cl: /O1 /DNDEBUG /MD /Oi- /arch:SSE
// Target signature follows the REL32 call from W3DGameClient::addScorch.
// The array and state offsets are independently established by target bytes.

class Vector3
{
public:
	float x;
	float y;
	float z;
    Vector3() {}
    __forceinline Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) {}
    __forceinline Vector3 &operator=(const Vector3 &v) { x=v.x; y=v.y; z=v.z; return *this; }
};

enum Scorches
{
	SCORCHES_UNKNOWN = 0
};

extern "C" double __cdecl fabs(double v);

struct ScorchEntry00067EA3
{
	char unreconstructed00[4];
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
	m_entries[slot].position = pos;
	m_entries[slot].radius = radius;
	m_entries[slot].kind = type;
	m_entries[slot].active = 0;
	++m_count;
	m_flag3794 = 0;
}
