// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Native [000CE3E3,000CE6E6),771B, RET4. W3DTankDraw::doDrawModule, the Zero
// Hour W3DTankDraw.cpp body adapted to BFME 2: the speed comes from the
// object's 0x0028AC7D accessor, the tread turning state and drive speed from
// the AI update (+0x258) and its +0x1F0 companion, and the treads scroll
// without the ZH isMotive test. Debris emitters are the +0x2E8/+0x2F4
// particle-system handles (null handle -> Make001FCBD7). Early outs skip
// the W3DModelDraw::doDrawModule (0x000C7BC4) tail call exactly as retail.

// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>

#include "ascii_string.h"
#include "../../../../../../GameEngine/Source/Common/Thing/thing.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../../../reference/shims/wwmath/Vector2.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

struct ParticleSystemView
{
	unsigned char m_pad000[0x130];
	Coord3D m_velocityMultiplier;
	Real m_burstCountMultiplier;
};

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

class View
{
public:
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03();
	virtual void vf04(); virtual void vf05(); virtual void vf06(); virtual void vf07();
	virtual void vf08(); virtual void vf09(); virtual void vf10(); virtual void vf11();
	virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15();
	virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
	virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27();
	virtual void vf28(); virtual void vf29();
	virtual Bool isCameraMovementFinished(void);	// slot 30 (+0x78)
	virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34();
	virtual void vf35(); virtual void vf36(); virtual void vf37(); virtual void vf38();
	virtual void vf39(); virtual void vf40(); virtual void vf41(); virtual void vf42();
	virtual void vf43(); virtual void vf44(); virtual void vf45(); virtual void vf46();
	virtual void vf47(); virtual void vf48(); virtual void vf49(); virtual void vf50();
	virtual void vf51(); virtual void vf52(); virtual void vf53();
	virtual Bool isTimeFrozen(void);	// slot 54 (+0xD8)
};
extern View *TheTacticalView;

class Rva00203B08
{
public:
	bool rva0020424FF();
};

class Rva00203ACEByteField
{
public:
	unsigned char get() const;
};

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

class Rva00270260
{
public:
	bool rva00270260();
};

class Rva002627E8
{
public:
	Real rva002627E8() const;
};

struct TurnStateView
{
	unsigned char m_pad000[0xA8];
	Int m_turning;
};

struct AIUpdateView
{
	unsigned char m_pad000[0x1F0];
	TurnStateView *m_turnState;
};

class Object : public Thing
{
public:
	Real rva0028AC7D() const;

	unsigned char m_pad[0x258 - sizeof(Thing)];
	AIUpdateView *m_ai;
	void *m_physics;
};

struct DrawableView
{
	unsigned char m_pad000[0xFC];
	Object *m_object;
};

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

// W3DModelDraw vftable slots this unit dispatches through; only slot 49 is named.
class W3DModelDrawSlots
{
public:
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03();
	virtual void vf04(); virtual void vf05(); virtual void vf06(); virtual void vf07();
	virtual void vf08(); virtual void vf09(); virtual void vf10(); virtual void vf11();
	virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15();
	virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
	virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27();
	virtual void vf28(); virtual void vf29(); virtual void vf30(); virtual void vf31();
	virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
	virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39();
	virtual void vf40(); virtual void vf41(); virtual void vf42(); virtual void vf43();
	virtual void vf44(); virtual void vf45(); virtual void vf46(); virtual void vf47();
	virtual void vf48();
	virtual void *getRenderObject(void);	// slot 49 (+0xC4)
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

// ?doDrawModule@W3DTankDraw@@UAEXPBVMatrix3D@@@Z
void W3DTankDraw::doDrawModule(const Matrix3D *transformMtx)
{
	const Real DEBRIS_THRESHOLD = 0.00001f;

	if (TheTacticalView->isTimeFrozen() && !TheTacticalView->isCameraMovementFinished())
		return;
	if (((Rva00203B08 *)TheScriptEngine)->rva0020424FF())
		return;
	if (((Rva00203ACEByteField *)TheScriptEngine)->get())
		return;
	if (((W3DModelDrawSlots *)this)->getRenderObject() == 0)
		return;
	if (((W3DModelDrawSlots *)this)->getRenderObject() != m_prevRenderObj)
		updateTreadObjects();

	Object *obj = m_drawable->m_object;
	if (obj == 0)
		return;
	if (obj->m_physics == 0)
		return;

	Real velMag = obj->rva0028AC7D();
	if (velMag > DEBRIS_THRESHOLD && !((Rva00270260 *)m_drawable)->rva00270260() && !m_fullyObscuredByShroud)
		rva000CE09E();
	else
		rva000CE0EA();

	Coord3D velMult;
	velMag = (Real)sqrt(velMag);
	velMult.x = 0.5f * velMag + 0.1f;
	if (velMult.x > 1.0f)
		velMult.x = 1.0f;
	velMult.y = velMult.x;
	velMult.z = velMag + 0.1f;
	if (velMult.z > 1.0f)
		velMult.z = 1.0f;

	if (m_treadDebrisLeft.getRaw()) {
		((ParticleSystemView *)m_treadDebrisLeft.get())->m_velocityMultiplier = velMult;
		((ParticleSystemView *)m_treadDebrisLeft.get())->m_burstCountMultiplier = velMult.z;
	}
	if (m_treadDebrisRight.getRaw()) {
		((ParticleSystemView *)m_treadDebrisRight.get())->m_velocityMultiplier = velMult;
		((ParticleSystemView *)m_treadDebrisRight.get())->m_burstCountMultiplier = velMult.z;
	}

	if (m_treadCount) {
		AIUpdateView *ai = obj->m_ai;
		TurnStateView *turnState = ai ? ai->m_turnState : 0;
		if (turnState == 0)
			return;
		Int turn = turnState->m_turning;
		Real treadScrollSpeed = getW3DTankDrawModuleData()->m_treadAnimationRate;
		Real maxSpeed = ((Rva002627E8 *)ai)->rva002627E8();
		if (turn != 0 && obj->rva0028AC7D() / maxSpeed < getW3DTankDrawModuleData()->m_treadPivotSpeedFraction) {
			Coord3D dir;
			obj->getUnitDirectionVector2D(dir);
			Real angleToGoal = dir.x * m_lastDirection.x + dir.y * m_lastDirection.y;
			if (fabs(1.0f - angleToGoal) > 0.00001f) {
				if (turn == -1)
					updateTreadPositions(-treadScrollSpeed);
				else
					updateTreadPositions(treadScrollSpeed);
			}
			m_lastDirection = dir;
		} else if (obj->rva0028AC7D() / maxSpeed >= getW3DTankDrawModuleData()->m_treadDriveSpeedFraction) {
			TreadObjectInfo *pTread = m_treads;
			for (Int i = 0; i < m_treadCount; i++) {
				Real offset_u = pTread->m_materialSettings.customUVOffset.X - treadScrollSpeed;
				offset_u = offset_u - (Real)floor(offset_u);
				pTread->m_materialSettings.customUVOffset.Set(offset_u, 0);
				pTread++;
			}
		}
	}
	W3DModelDraw::doDrawModule(transformMtx);
}
