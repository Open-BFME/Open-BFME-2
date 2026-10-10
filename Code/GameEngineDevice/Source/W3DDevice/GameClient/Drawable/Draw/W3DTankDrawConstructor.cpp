// cl: /DNDEBUG /MD /EHsc
// ??0W3DTankDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000CEA6C, 192B
// (pinned; called by W3DTankDraw::friend_newModuleInstance 0x00064B44).
// Spelled from the Zero Hour / BFME1 W3DTankDraw constructor: base
// W3DScriptedModelDraw(thing, moduleData) (pin 0x000C0DD8), m_prevRenderObj
// NULL, the four TreadObjectInfo built through ??_H with the tread ctor at
// 0x000CDFB1 (byte-identical with W3DTankTruckDraw's, rowed there), each
// m_robj cleared, m_treadCount 0, m_lastDirection (1,0,0), then
// createEmitters() (0x000CE837, pinned here from this call).
// BFME2 deltas (target evidence): the two debris emitters are 12-byte handle
// members zeroed in place, destroyed in retail's unwind map (states 1/2)
// through the conditional destroy 0x002115C5, as in W3DTankDrawDestructor.cpp.
// The +0x0C/+0x10 vtables and the base's 0x2E8 size follow that file.
class Thing;
class ModuleData;
class RenderObjClass;

// 0x0004CBC0 is the handle unlink (row ?rva0004CBC0@RvaSmartPtr12@@QAEXXZ); the dtor is the inline null test around it.
class RvaSmartPtr12 { public: void rva0004CBC0(); };
struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	void *m_system;
	void *m_previous;
	void *m_next;
};

struct W3DTankDrawDebrisHandle
{
	W3DTankDrawDebrisHandle() : m_ptr0(0), m_ptr1(0), m_ptr2(0) {}
	~W3DTankDrawDebrisHandle()
	{
		if (m_ptr0 != 0)
			reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0();
	}
	void *m_ptr0;
	void *m_ptr1;
	void *m_ptr2;
};

class DrawModuleBase
{
public:
	virtual ~DrawModuleBase();
private:
	char m_pad04[8];
};

class DrawInterfaceA
{
public:
	virtual void a();
};

class DrawInterfaceB
{
public:
	virtual void b();
};

class W3DScriptedModelDraw : public DrawModuleBase, public DrawInterfaceA, public DrawInterfaceB
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DScriptedModelDraw();
private:
	char m_pad14[0x2E8 - 0x14];
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class W3DTankDraw : public W3DScriptedModelDraw
{
public:
	W3DTankDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DTankDraw();
	virtual void a();
	virtual void b();
protected:
	W3DTankDrawDebrisHandle m_treadDebrisLeft;
	W3DTankDrawDebrisHandle m_treadDebrisRight;
	RenderObjClass *m_prevRenderObj;
	enum { MAX_TREADS_PER_TANK = 4 };
	struct TreadObjectInfo
	{
		TreadObjectInfo();
		RenderObjClass *m_robj;
		int m_type;
		char m_materialSettings[0x0C];
	};
	TreadObjectInfo m_treads[MAX_TREADS_PER_TANK];
	int m_treadCount;
	Coord3D m_lastDirection;
	void createEmitters(void);
};

W3DTankDraw::W3DTankDraw(Thing *thing, const ModuleData *moduleData)
	: W3DScriptedModelDraw(thing, moduleData), m_prevRenderObj(0)
{
	for (int i = 0; i < MAX_TREADS_PER_TANK; i++)
		m_treads[i].m_robj = 0;

	m_treadCount = 0;
	m_lastDirection.x = 1.0f;
	m_lastDirection.y = 0.0f;
	m_lastDirection.z = 0.0f;

	createEmitters();
}
