// ?rva000D1056@Rva000D1056@@QAEXHHH@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000D1056 188B. If the object's position is off the origin, build
// a render object from the name at +4 and bind it through g_00DE2000.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class RenderObjClass;

RenderObjClass *Create_Render_Obj(const char *name);

struct Rva001408C0Target;

class Rva00081EA8
{
public:
	void rva00081EA8(Rva001408C0Target *target);
};

class Rva0007F9ADOwner
{
public:
	Rva00081EA8 *rva0007F9AD(float x, float y);
};

extern Rva0007F9ADOwner *g_00DE2000;
extern char g_00BBAC1C[];

struct Rva000D1056Text
{
	char m_pad[8];
	char m_chars;
};

struct Rva000D1056Name
{
	char m_pad[8];
	Rva000D1056Text *m_text;
};

class Rva000D1056
{
public:
	void rva000D1056(int a, int b, int c);

	char m_pad0[4];
	Rva000D1056Name *m_name;
	BFMERopeDrawable *m_obj;
	char m_padC[4];
	unsigned char m_flag;
	char m_pad11[3];
	RenderObjClass *m_render;
	Rva00081EA8 *m_bound;
};

void Rva000D1056::rva000D1056(int a, int b, int c)
{
	BFMERopeDrawable *obj = m_obj;
	if (obj == 0 || m_flag != 0)
		return;
	if (obj->getPosition()->x != 0.0f || obj->getPosition()->y != 0.0f)
	{
		m_flag = 1;
		if (m_name == 0)
			return;
		Rva000D1056Text *text = m_name->m_text;
		const char *chars = text ? &text->m_chars : g_00BBAC1C;
		m_render = Create_Render_Obj(chars);
		if (m_render == 0 || g_00DE2000 == 0)
			return;
		const Coord3D *first = obj->getPosition();
		const Coord3D *second = obj->getPosition();
		m_bound = g_00DE2000->rva0007F9AD(first->x, second->y);
		if (m_bound != 0)
			m_bound->rva00081EA8((Rva001408C0Target *)this);
	}
}
