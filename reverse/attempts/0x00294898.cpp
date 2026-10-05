// ?rva00294898@Object@@QAE_NPAV1@H@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /MD /GX /arch:SSE
// ?rva00294898@Object@@QAE_NPAVObject@@H@Z @0x00294898 167B
// Object method via +0x38 Coord3D (Object::m_pos per next TU), +0x258 AIUpdateInterface
// per ObjectRva0028ACA0, +0x248 flag byte; callees Object rva00294815 pin 0x00294815
// Object rva0028CE7B pin 0x0028CE7B AI isMoving pin Rva001E3591 row Pathfinder row.
// Evidence: 4 unclaimed callers; global g_Va009FF0F8 AI+0x10 Pathfinder; unblocks 0x0029493F.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Pathfinder;

class AIUpdateInterface
{
public:
	bool isMoving() const;
};

class Rva001E3591
{
public:
	bool rva001E3591();
};

class Pathfinder
{
public:
	bool rva002F477E(Object *obj, const Coord3D *a, const Coord3D *b, int v);
};

class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_10;
};
extern AI *g_Va009FF0F8;

class Object
{
public:
	bool rva00294898(Object *other, int mode);
	char rva00294815();
	signed char rva0028CE7B() const;
private:
	char m_pad000[0x38];
	Coord3D m_pos;
	char m_pad044[0x248 - 0x44];
	unsigned char m_248;
	char m_pad249[0x258 - 0x249];
	AIUpdateInterface *m_ai;
};

// ?rva00294898@Object@@QAE_NPAV1@H@Z present-unmatched
bool Object::rva00294898(Object *other, int mode)
{
	if (other == 0)
		return false;
	char tmp = rva00294815();
	if (tmp == 0)
		return false;
	if (other->rva0028CE7B() < tmp)
		goto aiCheck;
	return false;
aiCheck:
	AIUpdateInterface *ai = m_ai;
	if (ai != 0) {
		Rva001E3591 *p = *(Rva001E3591 **)((char *)ai + 0x140);
		if (ai->isMoving()) {
			if (p != 0) {
				if (p->rva001E3591())
					goto checkMode;
			}
		}
	}
	Pathfinder *pf = g_Va009FF0F8->m_10;
	if (pf->rva002F477E(this, &m_pos, &other->m_pos, 0) == false)
		return false;
checkMode:
	if (mode == 1 || mode == 2) {
		if (other->m_248 != 0)
			goto retTrue;
	}
	if (mode == 0)
		goto secondCompare;
	if (mode != 2)
		return false;
secondCompare:
	if (tmp <= other->rva0028CE7B())
		return false;
retTrue:
	return true;
}
