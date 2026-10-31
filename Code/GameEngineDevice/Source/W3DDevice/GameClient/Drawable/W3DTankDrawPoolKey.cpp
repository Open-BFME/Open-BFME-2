// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@W3DTankDraw@@UBE?AW4NameKeyType@@XZ @0xCE9EE
// (69B): cached pool-name key for W3DTankDraw. The class
// identity comes from the pool-name string the body pushes
// ("W3DTankDraw"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../../reference/shims/wwmath/Vector2.h"
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

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// ?getModuleNameKey@W3DTankDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DTankDraw::getModuleNameKey() const
{
	static NameKeyType TheW3DTankDrawPoolKey =
		TheNameKeyGenerator->nameToKey("W3DTankDraw");
	return TheW3DTankDrawPoolKey;
}
