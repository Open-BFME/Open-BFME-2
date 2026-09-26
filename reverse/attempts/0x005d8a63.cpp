// ?rva005D8A63@Rva005D8964@@UAE_NPAVObject@@@Z
// partial score=0.93 date=2026-09-26
// ?rva005D8A63@Rva005D8964@@UAE_NPAVObject@@@Z
// partial score=0.93 date=2026-09-26
// cl: /O2 /MD /arch:SSE
class Object;
class ThingTemplate
{
public:
	unsigned char m_pad[0x108];
	unsigned char m_kindByte108;
};
class AIUpdateInterface
{
public:
	Object* getCurrentVictim() const;
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
	char m_pad0[4];
	ThingTemplate* m_template;
	char m_pad8[0x38 - 8];
	Coord3D m_position;
	char m_pad44[0x258 - 0x38 - sizeof(Coord3D)];
	AIUpdateInterface* m_ai;
};
class Rva005D8964
{
public:
	virtual ~Rva005D8964();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual bool slot07(Object* obj);
	virtual bool rva005D8A63(Object* obj);
};
bool Rva005D8964::rva005D8A63(Object* obj)
{
	Object* victim = obj->m_ai->getCurrentVictim();
	if (victim == 0)
		return false;
	const Coord3D* a = &obj->m_position;
	const Coord3D* b = &victim->m_position;
	float dx = b->x - a->x;
	float dy = b->y - a->y;
	float dz = b->z - a->z;
	float distSq = dz * dz + dy * dy + dx * dx;
	return distSq >= 22500.0f;
}
