// cl: /O1 /DNDEBUG /MD
// ?rva00262B53@Rva00262B53@@QAE_NPBUCoord3D@@@Z @0x00262B53 42B unlock via Pathfinder pin.
// Evidence: thiscall with ret 4 and bool return; global g_Va009FF0F8 AI plus 0x10 pathfinder; callee rva002F477E pin with object plus from plus to plus 0; neighbours AIUpdateInterface /O1.
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Object
{
public:
	char m_pad[0x38];
	Coord3D m_38;
};
class Pathfinder
{
public:
	bool rva002F477E(Object *obj, const Coord3D *from, const Coord3D *to, int x);
};
class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_10;
};
extern AI *g_Va009FF0F8;
class Rva00262B53
{
public:
	bool rva00262B53(const Coord3D *pos);
private:
	char m_pad[8];
	Object *m_8;
};
bool Rva00262B53::rva00262B53(const Coord3D *pos)
{
	if (!pos)
		return false;
	Object *obj = m_8;
	Pathfinder *pf = g_Va009FF0F8->m_10;
	return pf->rva002F477E(obj, &obj->m_38, pos, 0);
}
