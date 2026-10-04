// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva002A9BF2@Rva002A9BF2@@QAEPAXXZ @ 0x002A9BF2 (27B). Unlock lane difficulty
// getter shared by 13 callers. Evidence: GameWindow at this+0x2DC tail-jmps to
// rowed winGetUserData 0x005C4ACD when present else returns TheScriptEngine
// difficulty at global 0x009FE16C plus 0x1A4C4. Callers 0x00203F0E and
// 0x0058AF47 use ecx-this with no stack args and treat eax as int index.

class GameWindow
{
public:
	char _pad1C[0x1C];
	int m_unk1C;
	void *winGetUserData();
};

class ScriptEngine
{
public:
	char _pad[0x1A4C4];
	void *m_difficulty;
};

extern ScriptEngine *TheScriptEngine;

class Object;

class Rva002A9BF2
{
	char _pad[0x2DC];
	GameWindow *m_window;
public:
	void *rva002A9BF2();
	void rva002A9CCA(int val);
	void rva002A9D02(int a1, Object *obj, int a3);
};

void *Rva002A9BF2::rva002A9BF2()
{
	GameWindow *w = m_window;
	if (w != 0)
		return w->winGetUserData();
	return TheScriptEngine->m_difficulty;
}

void Rva002A9BF2::rva002A9CCA(int val)
{
	GameWindow *w = m_window;
	if (w != 0)
		w->m_unk1C = val;
}

// ?rva002A9D02@Rva002A9BF2@@QAEXHPAVObject@@H@Z @0x002A9D02 135B: this+0x2DC GameWindow plus ScriptEngine/AI globals plus Object calls. Evidence: same 0x2DC as Rva002A9BF2 siblings; callees rowed 0x002039B6 0x002E718A 0x002E7178 0x0028D99A 0x0028BD17 0x0028DA67; globals g_Va009FE16C g_Va009FF0F8 g_bfmeWorldRV; callers 0x002411DF 0x00241E17 0x003954B9 0x0048AC99.
class Rva002039B6Host
{
public:
	void rva002039B6();
};

class Object;

class BFMEPathfinderMapShim
{
public:
	void rva002E718A(Object *obj);
	void addObjectToPathfindMap(Object *obj);
};

class AI
{
public:
	char _pad[0x10];
	BFMEPathfinderMapShim *m_shim;
};

extern AI *g_Va009FF0F8;
extern ScriptEngine *g_Va009FE16C;

struct BfmeWorldRV
{
	char _pad[0x28];
	unsigned char m_28;
};

extern struct BfmeWorldRV *g_bfmeWorldRV;

class Object
{
public:
	void rva0028D99A(bool flag);
	void *rva0028BD17() const;
	void rva0028DA67();
};

class GameWindowVirt
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8(int a1, Object *obj);
};

class SecondVirt
{
public:
	virtual void w0();
	virtual void w1();
	virtual void w2();
	virtual void w3(int a1);
};

void Rva002A9BF2::rva002A9D02(int a1, Object *obj, int a3)
{
	((Rva002039B6Host *)g_Va009FE16C)->rva002039B6();
	g_Va009FF0F8->m_shim->rva002E718A(obj);
	g_Va009FF0F8->m_shim->addObjectToPathfindMap(obj);
	obj->rva0028D99A(true);
	if (m_window)
		((GameWindowVirt *)m_window)->v8(a1, obj);
	if (g_bfmeWorldRV)
		g_bfmeWorldRV->m_28 = 1;
	if (obj->rva0028BD17())
		((SecondVirt *)obj->rva0028BD17())->w3(a1);
	obj->rva0028DA67();
	(void)a3;
}
