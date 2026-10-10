// ?rva00483B3D@Rva00483B3D@@QAEHXZ
// partial score=0.93 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
//
// ?rva00483B3D@Rva00483B3D@@QAEHXZ, retail 0x00483B3D, 102 bytes (secondary-base update).
// Schedules the next heal frame (current frame + the module data delay at +0x0C), asks the
// owning object (this-8) to attempt healing by the data amount at +0x10 through the rowed
// 0x0028FE55, then sleeps forever (0x3FFFFFFF) when its body (object +0x254) reports equal
// health values (slots 4 and 6) and otherwise returns the frames until the next heal.
// Evidence: target bytes and the rowed callee; names and the primary-base split are neutral.

class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva00483B3DFrames
{
	char m_pad[0x40];
	unsigned int m_frame40;
};

struct Rva00483B3DData
{
	char m_pad[0x0C];
	unsigned int m_delay0C;
	float m_amount10;
};

class Rva00483B3DBody
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual float health();
	virtual void v05();
	virtual float maxHealth();
};

class Object
{
public:
	void attemptHealing(float amount, const Object *source);
	char m_pad[0x254];
	Rva00483B3DBody *m_body254;
};

struct Rva00483B3DOuter
{
	Rva00483B3DData *m_data;
	Object *m_object;
};

class Rva00483B3D
{
public:
	int rva00483B3D();
private:
	char m_pad[0x18];
	unsigned int m_nextFrame18;
};

int Rva00483B3D::rva00483B3D()
{
	Rva00483B3DOuter *outer = (Rva00483B3DOuter *)((char *)this - 0x0C);
	unsigned int now = ((Rva00483B3DFrames *)TheGameLogic)->m_frame40;
	Rva00483B3DData *data = outer->m_data;
	m_nextFrame18 = data->m_delay0C + now;
	outer->m_object->attemptHealing(data->m_amount10, 0);
	Rva00483B3DBody *body = outer->m_object->m_body254;
	if (body->health() == body->maxHealth())
		return 0x3FFFFFFF;
	return m_nextFrame18 - now;
}
