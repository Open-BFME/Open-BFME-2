// ?rva005D89F0@Rva005D8964@@QAE_NPAVObject@@@Z
// partial score=0.88 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD
//
// ?rva005D89F0@Rva005D8964@@QAE_NPAVObject@@@Z, retail 0x005D89F0 (115 bytes, ret 4, this unused). Sits
// between the Rva005D8964 spell-book family's base dtor and its derived dtors (vtable 0xC76190); whether
// the argument's current victim is within 50 units (squared distance 2500.0 at 0x00C761BC).
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;		// +0x38
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai;	// +0x258
};

class Rva005D8964
{
public:
	bool rva005D89F0(Object *source);
};

bool Rva005D8964::rva005D89F0(Object *source)
{
	Object *victim = source->m_ai->getCurrentVictim();
	if (victim != 0) {
		float dx = victim->m_position.x - source->m_position.x;
		float dy = victim->m_position.y - source->m_position.y;
		float dz = victim->m_position.z - source->m_position.z;
		return dz * dz + dy * dy + dx * dx <= 2500.0f;
	}
	return false;
}
