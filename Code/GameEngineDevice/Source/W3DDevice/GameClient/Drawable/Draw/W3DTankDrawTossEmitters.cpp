// cl: /O1 /G7 /arch:SSE /MD
// ?tossEmitters@W3DTankDraw@@IAEXXZ, retail 0x000CE7B4, 131 bytes (pinned callee of loadPostProcess 0x000CEA39).
// Twin guide: the verified W3DTankTruckDraw tossEmitters (W3DTankTruckDrawTossEmitters.cpp, three handles); the
// W3DTankDraw view has two handles at +0x2E8/+0x2F4 observed in the ctor/createEmitters. Handle teardown is the inline
// null test around the rowed unlink 0x0004CBC0; the handle's volatile read keeps retail's redundant null-or-Make chases.
// Structural inference (not target evidence): the first handle test is written as the constant-true equal-arm
// conditional (1 ? E : E); it changes cl's expression tree and puts the frame/register roles on retail's.
// null test around the rowed unlink 0x0004CBC0; the volatile m_system keeps retail's redundant null-or-Make chases.
class Rva001F384AByteZeroSetter {
public:
    void disable();
};
class Rva001F3852ByteOneSetter
{
public:
	void enable();
};
struct Rva001F3C43Arg {
    char m_pad[0x74];
    int m_value;
};
class Rva001F3C43Slot {
public:
    void set(const Rva001F3C43Arg *arg);
};
class ParticleSystem : public Rva001F3C43Slot {
public:
    void destroy();
    void rva001F45F4(bool enabled) throw();
};
// 0x0004CBC0 is the handle unlink (row ?rva0004CBC0@RvaSmartPtr12@@QAEXXZ); the dtor is the inline null test around it.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../../../reference/shims/wwmath/Vector2.h"
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that) throw();
	ParticleSystem *m_system; // +0x00
	void *m_previous; // +0x04
	void *m_next; // +0x08
};
class BfmeParticleSystemHandle : public RvaSmartPtr12
{
public:
	BfmeParticleSystemHandle()
	{
		m_system = 0;
		m_previous = 0;
		m_next = 0;
	}
	~BfmeParticleSystemHandle() throw()
	{
		if (m_system != 0)
			rva0004CBC0();
	}
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make001FCBD7();
		return m_system;
	}
	// A volatile read keeps retail's redundant null-or-Make chases.
	__forceinline ParticleSystem *const volatile &systemRef() const
	{
		return *(ParticleSystem *const volatile *)&m_system;
	}
	__forceinline ParticleSystem *getRaw() const
	{
		return *(ParticleSystem *const volatile *)&m_system;
	}
	ParticleSystem *get() const
	{
		ParticleSystem *p = getRaw();
		if (!p)
			p = Make001FCBD7();
		return p;
	}
};
class W3DTankDrawModuleData;
struct DrawableView;
class Xfer;
class Matrix3D;
class Thing;
class ModuleData;
class RenderObjClass;
class DrawModuleBase
{
public:
	virtual ~DrawModuleBase();
	const W3DTankDrawModuleData *m_moduleData; // +0x04
	DrawableView *m_drawable; // +0x08
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
class W3DModelDraw : public DrawModuleBase, public DrawInterfaceA, public DrawInterfaceB
{
public:
	virtual void setHidden(bool h);
	virtual void setFullyObscuredByShroud(bool v);
	virtual void doDrawModule(const Matrix3D *transformMtx);
protected:
	virtual void loadPostProcess(void);
	char m_pad14[0x49 - 0x14];
	bool m_fullyObscuredByShroud; // +0x49
	char m_pad4A[0x2E8 - 0x4A];
};
class W3DScriptedModelDraw : public W3DModelDraw
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DScriptedModelDraw();
protected:
	virtual void xfer(Xfer *xfer);
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};

struct Material_Override
{
	int Struct_ID;
	Vector2 customUVOffset;
};

class W3DTankDraw : public W3DScriptedModelDraw
{
public:
	W3DTankDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DTankDraw();
	virtual void a();
	virtual void b();
	virtual void setHidden(bool h);
	virtual void setFullyObscuredByShroud(bool v);
	virtual void doDrawModule(const Matrix3D *transformMtx);
	virtual NameKeyType getModuleNameKey() const;
	void rva000CE09E();
	void rva000CE0EA();
protected:
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);
	BfmeParticleSystemHandle m_treadDebrisLeft;
	BfmeParticleSystemHandle m_treadDebrisRight;
	RenderObjClass *m_prevRenderObj;
	enum { MAX_TREADS_PER_TANK = 4 };
	struct TreadObjectInfo
	{
		TreadObjectInfo();
		RenderObjClass *m_robj;
		int m_type;
		Material_Override m_materialSettings;
	};
	TreadObjectInfo m_treads[MAX_TREADS_PER_TANK];
	int m_treadCount;
	Coord3D m_lastDirection;
	const W3DTankDrawModuleData *getW3DTankDrawModuleData() const { return m_moduleData; }
	void createEmitters(void);
	void tossEmitters(void);
	void updateTreadObjects(void);
	void updateTreadPositions(float uvDelta);
};
void W3DTankDraw::tossEmitters()
{
    if ((1 ? (m_treadDebrisLeft.getRaw()) : (m_treadDebrisLeft.getRaw()))) {
        m_treadDebrisLeft.get()->set(0);
        m_treadDebrisLeft.get()->destroy();
        if (m_treadDebrisLeft.getRaw()) {
            m_treadDebrisLeft.rva0004CBC0();
            m_treadDebrisLeft.m_system = 0;
        }
    }
    if (m_treadDebrisRight.getRaw()) {
        m_treadDebrisRight.get()->set(0);
        m_treadDebrisRight.get()->destroy();
        if (m_treadDebrisRight.getRaw()) {
            m_treadDebrisRight.rva0004CBC0();
            m_treadDebrisRight.m_system = 0;
        }
    }
}
