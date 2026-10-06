// cl: /DNDEBUG /MD /GX
// ?rva004992D5@GateOpenAndCloseBehavior@@AAEX_N0@Z @0x004992D5 149B: private helper
// with two flags; if +0x2C==2 then first flag must hold else return; second flag
// runs pinned 0x00498FAA; removes object from pathfind shim, sets state 2 via
// Object::rva0028B78A(9), sets two BfmeStrF9 vectors through Object+0xA8
// setFlag(1/0), notifies via Object::rva0028AB75(true), re-adds to pathfind
// shim. Evidence: rowed callees 0x002E71AD 0x0028B78A 0x006BF3C0 0x0028AB75
// 0x002E7178 plus pin 0x00498FAA; callers 0x0049939B 0x004E8FA5 0x004E906D;
// neighbour GateOpenAndCloseBehaviorRva0049924B.
class Object;
class BfmeStrF9;
class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};
class Pathfinder
{
public:
	void RemoveObjectFromPathfindMapKeepingGateFlags(Object *object);
	void AddObjectToPathfindMap(Object *object);
};
class AI
{
public:
	unsigned char m_pad00[0x10];
	Pathfinder *m_10; // +0x10
};
extern AI *g_Va009FF0F8;
class Object
{
public:
	void rva0028B78A(int v);
	void rva0028AB75(bool v);
private:
	unsigned char m_pad00[0xA8];
public:
	BfmeObjF9 m_objA8; // +0xA8
};
class BfmeStrF9
{
public:
	unsigned char m_pad[4];
};
struct GateVec
{
	BfmeStrF9 *m_begin;
	BfmeStrF9 *m_end;
	BfmeStrF9 *m_cap;
};
class GateOpenAndCloseBehaviorModuleData
{
public:
	unsigned char m_pad00[0x2C];
	GateVec m_vec2C; // +0x2C
	GateVec m_vec38; // +0x38
};
class GateOpenAndCloseBehavior
{
private:
	void rva00498FAA();
	void rva004992D5(bool a, bool b);
private:
	unsigned char m_pad00[0x08];
	const GateOpenAndCloseBehaviorModuleData *m_data08; // +0x08
	Object *m_object0C; // +0x0C
	unsigned char m_pad10[0x2C - 0x10];
	int m_2C; // +0x2C
};
void GateOpenAndCloseBehavior::rva004992D5(bool a, bool b)
{
	if (m_2C == 2)
	{
		if (!a)
			return;
	}
	if (b)
		rva00498FAA();
	Pathfinder *shim = g_Va009FF0F8->m_10;
	Object *obj = m_object0C;
	shim->RemoveObjectFromPathfindMapKeepingGateFlags(obj);
	m_2C = 2;
	obj->rva0028B78A(9);
	const GateOpenAndCloseBehaviorModuleData *data = m_data08;
	for (BfmeStrF9 *p = data->m_vec2C.m_begin; p != data->m_vec2C.m_end; ++p)
		(&obj->m_objA8)->setFlag(*p, 1);
	for (BfmeStrF9 *p = data->m_vec38.m_begin; p != data->m_vec38.m_end; ++p)
		(&obj->m_objA8)->setFlag(*p, 0);
	obj->rva0028AB75(true);
	g_Va009FF0F8->m_10->AddObjectToPathfindMap(obj);
}
