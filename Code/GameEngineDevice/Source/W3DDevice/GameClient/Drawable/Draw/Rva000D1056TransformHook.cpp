// ?rva000D1056@Rva000D1056@@QAEXHHH@Z
// Native 0x000D1056..0x000D1112 (188B), RET12.
// WB95F6D0 W3DBoatWakeModelDraw::reactToTransformChange is a matching
// callgraph/field-access lead. Keep neutral identity until target virtual
// ownership and argument types are independently established.
// Observed owner/name +4, Drawable +8, initialized flag10, renderer14,
// bound terrain-item18; three arguments are unused by retail.
// Same-valued second position-call PHI reproduces native EBX/EDI roles.
// Current126B terrain-item lookup and25B insert providers are reused.
// Canonical W3DGCData00DE2000 global and empty literal replace bank aliases.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include
// @0x000D1056 188B. If the object's position is off the origin, build
// a render object from the name at +4 and bind it through theHost.

#include "Lib/Coord3D.h"

class Drawable
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

class Rva0007F944Item;
class Rva0007F944Host
{
public:
	Rva0007F944Item *rva0007F9AD(float x, float y);
};

extern void *W3DGCData00DE2000;
#define theHost (reinterpret_cast<Rva0007F944Host*>(W3DGCData00DE2000))


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
	Drawable *m_obj;
	char m_padC[4];
	unsigned char m_flag;
	char m_pad11[3];
	RenderObjClass *m_render;
	Rva00081EA8 *m_bound;
};

void Rva000D1056::rva000D1056(int a, int b, int c)
{
	Drawable *obj = m_obj;
	if (obj == 0 || m_flag != 0)
		return;
	if (obj->getPosition()->x != 0.0f || (this?obj->getPosition():obj->getPosition())->y != 0.0f)
	{
		m_flag = 1;
		if (m_name == 0)
			return;
		Rva000D1056Text *text = m_name->m_text;
		const char *chars = text ? &text->m_chars : "";
		m_render = Create_Render_Obj(chars);
		if (m_render == 0 || theHost == 0)
			return;
		const Coord3D *first = obj->getPosition();
		const Coord3D *second = obj->getPosition();
		m_bound = reinterpret_cast<Rva00081EA8*>(theHost->rva0007F9AD(first->x, second->y));
		if (m_bound != 0)
			m_bound->rva00081EA8((Rva001408C0Target *)this);
	}
}
