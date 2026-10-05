// ?rva00341C54@Rva00341C54@@QAE_NPAVObject@@@Z
// partial score=0.8 date=2026-10-05
// cl: /O1 /arch:SSE /DNDEBUG /MD
typedef bool Bool;
enum Relationship
{
	REL_ZERO = 0
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Object;
class Rva00390533
{
public:
	bool rva00390533();
};
class Rva002F23A6
{
public:
	bool rva002F23A6(Object *a, int b, int c, Coord3D *pos, Object *d);
};
class GameLogic
{
public:
	char m_pad00[0x1b4];
	int m_1b4;
};
extern GameLogic *TheGameLogic;
extern void *g_00DFEFF0;
extern void *g_00DFF0F8;
class Object
{
public:
	Relationship getRelationship(const Object *o) const;
	char m_pad00[0x38];
	Coord3D m_pos38; // +0x38
	char m_pad44[0x258 - 0x44];
	int m_258; // +0x258
	Rva00390533 *m_25c; // +0x25c
	char m_pad260[0x438 - 0x260];
	unsigned char m_flag438; // +0x438
};
class Rva00341C54
{
public:
	bool rva00341C54(Object *obj);
	Object *m_08; // +0x8
	int m_0c; // +0xc
};
void __cdecl Rva006CEC42(void *f, const char *fmt, double a, double b);

bool Rva00341C54::rva00341C54(Object *obj)
{
	if ((obj->m_flag438 & 1) == 0) {
		Rva00341C54 *self = this;
		if (((self->m_08->m_flag438 ^ obj->m_flag438) & 8) == 0) {
			if (self->m_08->getRelationship(obj) == REL_ZERO) {
				Rva00390533 *v = obj->m_25c;
				if (v == 0 || !v->rva00390533()) {
					Coord3D pos = obj->m_pos38;
					if (TheGameLogic->m_1b4 > 0) {
						if (g_00DFEFF0 != 0)
							Rva006CEC42(g_00DFEFF0, "FUCK OFF DESYNC: AIAttackFireDuringApproachState::computePath will call FindMeleeEngagmentLocation with pos=%f,%f", pos.x, pos.y);
					}
					Rva002F23A6 *helper = *(Rva002F23A6 **)((char *)g_00DFF0F8 + 0x10);
					return helper->rva002F23A6(self->m_08, self->m_0c, self->m_08->m_258 + 0x1cc, &pos, obj);
				}
			}
		}
	}
	return false;
}
