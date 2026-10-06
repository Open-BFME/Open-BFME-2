// cl: /O1 /DNDEBUG /MD /arch:SSE /GX
// ?rva0049924B@GateOpenAndCloseBehavior@@AAEX_N@Z @0x0049924B 138B: private helper;
// if +0x2C==1 return; if flag runs pinned 0x00498FAA; removes object from
// pathfind shim, sets state 1 via Object::rva0028B79C(9), clears two
// BfmeStrF9 vectors through Object+0xA8 setFlag(0/1), notifies via
// Object::rva0028AB75(true), re-adds to pathfind shim. Evidence: rowed
// callees 0x002E71AD 0x0028B79C 0x006BF3C0 0x0028AB75 0x002E7178 plus pin
// 0x00498FAA; callers 0x00499651 0x004996C8 0x004E8FE4 0x004E9021; neighbours
// GateOpenAndCloseBehaviorSlots/ Rva0024A797Grandchildren.
class Object;
class BfmeStrF9;
class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};
class BFMEPathfinderMapShim
{
public:
	void rva002E71AD(Object *object);
	void addObjectToPathfindMap(Object *object);
};
class AI
{
public:
	unsigned char m_pad00[0x10];
	BFMEPathfinderMapShim *m_10; // +0x10
};
extern AI *g_Va009FF0F8;
class Object
{
public:
	void rva0028B79C(int v);
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
	void rva0049924B(bool flag);
private:
	unsigned char m_pad00[0x08];
	const GateOpenAndCloseBehaviorModuleData *m_data08; // +0x08
	Object *m_object0C; // +0x0C
	unsigned char m_pad10[0x2C - 0x10];
	int m_2C; // +0x2C
};
void GateOpenAndCloseBehavior::rva0049924B(bool flag)
{
	if (m_2C == 1)
		return;
	if (flag)
		rva00498FAA();
	BFMEPathfinderMapShim *shim = g_Va009FF0F8->m_10;
	Object *obj = m_object0C;
	shim->rva002E71AD(obj);
	m_2C = 1;
	obj->rva0028B79C(9);
	const GateOpenAndCloseBehaviorModuleData *data = m_data08;
	BfmeObjF9 *f9 = &obj->m_objA8;
	for (BfmeStrF9 *p = data->m_vec2C.m_begin; p != data->m_vec2C.m_end; ++p)
		f9->setFlag(*p, 0);
	for (BfmeStrF9 *p = data->m_vec38.m_begin; p != data->m_vec38.m_end; ++p)
		f9->setFlag(*p, 1);
	obj->rva0028AB75(true);
	g_Va009FF0F8->m_10->addObjectToPathfindMap(obj);
}
