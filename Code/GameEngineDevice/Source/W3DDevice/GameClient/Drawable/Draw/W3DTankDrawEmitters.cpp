// ?createEmitters@W3DTankDraw@@IAEXXZ
// Retail CE837..CE960 is the 297-byte createEmitters body called by the
// independently rowed W3DTankDraw constructor CEA6C and tail wrapper CEA4B.
// Reference: BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d,
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankDrawCreateEmitters.cpp;
// Zero Hour W3DTankDraw.cpp provides the same two-emitter sequence. Target
// fields: handles2E8/2F4, moduleData4 names188/18C, drawable8. Each is
// observed in this body and independently corroborated by constructor/dtor.
// The native handle temporary conditionally calls the existing 4CBC0 unlink
// helper via RvaSmartPtr12::rva0004CBC0, as in ParticleSystemManagerFindByID.
// Callees use existing neutral providers for drawable-ID attachment and the
// stop byte setter; their original method names remain donor facts. No new pins.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

typedef bool Bool;
enum { FALSE = 0, TRUE = 1 };

class ParticleSystemTemplate;
class Rva0055A88BDwordField;

class Rva001F3C20Slot { public: void set(const Rva0055A88BDwordField *) throw(); };
struct Rva001F3C43Arg;
class Rva001F3852ByteOneSetter
{
public:
	void enable();
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

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const throw();
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *sysTemplate, Bool createSlaves) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

class MultiIniFieldParse;

class W3DModelDrawModuleData
{
public:
	W3DModelDrawModuleData();
public:
	virtual ~W3DModelDrawModuleData();
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class W3DTankDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DTankDrawModuleData();
public:
	virtual ~W3DTankDrawModuleData();
private:
	unsigned char m_basePad[0x188 - 4];
public:
	AsciiString m_treadDebrisLeft;
public:
	AsciiString m_treadDebrisRight;
public:
	float m_treadAnimationRate;
public:
	float m_treadPivotSpeedFraction;
public:
	float m_treadDriveSpeedFraction;
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

struct W3DTankDrawDebrisHandle
{
	void *m_ptr0;
	void *m_ptr1;
	void *m_ptr2;
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

void W3DTankDraw::createEmitters()
{
	Bool disabled = FALSE;
	ParticleSystem *nullSystem = 0;
	if (m_treadDebrisLeft.m_system == nullSystem)
	{
		const ParticleSystemTemplate *sysTemplate;
		sysTemplate = TheParticleSystemManager->findTemplate(
			m_moduleData->m_treadDebrisLeft);
		if (sysTemplate)
		{
			m_treadDebrisLeft = TheParticleSystemManager->createParticleSystem(
				sysTemplate, TRUE);
			Rva0055A88BDwordField *drawable = (Rva0055A88BDwordField *)m_drawable;
			((Rva001F3C20Slot *)m_treadDebrisLeft.operator->())->set(drawable);
			m_treadDebrisLeft->rva001F45F4(disabled);
			((Rva001F3852ByteOneSetter *)m_treadDebrisLeft.operator->())->enable();
		}
	}
	if (!m_treadDebrisRight)
	{
		const ParticleSystemTemplate *sysTemplate;
		sysTemplate = TheParticleSystemManager->findTemplate(
			m_moduleData->m_treadDebrisRight);
		if (sysTemplate)
		{
			m_treadDebrisRight = TheParticleSystemManager->createParticleSystem(
				sysTemplate, TRUE);
			Rva0055A88BDwordField *drawable = (Rva0055A88BDwordField *)m_drawable;
			((Rva001F3C20Slot *)m_treadDebrisRight.operator->())->set(drawable);
			m_treadDebrisRight->rva001F45F4(disabled);
			((Rva001F3852ByteOneSetter *)m_treadDebrisRight.operator->())->enable();
		}
	}
}
