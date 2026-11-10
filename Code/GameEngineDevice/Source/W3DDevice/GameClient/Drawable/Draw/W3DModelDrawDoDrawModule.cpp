// ?doDrawModule@W3DModelDraw@@UAEXPBVMatrix3D@@@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// W3DModelDraw::doDrawModule, retail 0x000C7BC4 (1563 B, vtable slot of W3DModelDraw).
// Zero Hour W3DModelDraw::doDrawModule reshaped onto the BFME 2 layout (class views
// below); the Zero Hour definition in W3DModelDraw.cpp is removed with this row.
// The two unrowed per-frame helpers are pinned: rva000C6E1A (0xC6E1A) and
// rva000BD6C2 (0xBD6C2).
// The dead BfmeParticleSystemHandle block before the closing calls stands for
// retail's compiled-out debug code: it carries the hidden temp numbering that
// makes the +0x6A branch's inlined Rotate_Z evaluate c*Row00 first (wave7 T1
// gen_eh_if0; its content is unrecovered).
#include <math.h>
#include "ascii_string.h"
#include "Coord3D.h"
#include "matrix3d.h"
#include "GameLogicObjectLookupView.h"

#define SLOT(n) virtual void slot##n();
#define ISLOT(n) virtual void islot##n();

typedef float Real;
typedef unsigned int UnsignedInt;

extern GameLogic *TheGameLogic;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct DoDrawGlobalDataView
{
	char m_pad00[0xD45];
	bool m_bD45;
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class DoDrawTerrainLogicView
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18)
	virtual void getGroundHeight(Real x, Real y, Real *z, int a, int b);
};

class ParticleSystem
{
public:
	void destroy();
};
ParticleSystem *Make001FCBD7();
#include "../../../../../../GameEngine/Include/Common/RvaSmartPtr12.h"
class BfmeParticleSystemHandle
{
public:
	__forceinline BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &r) throw()
	{
		*(RvaSmartPtr12 *)this = *(const RvaSmartPtr12 *)&r;
		return *this;
	}
	__forceinline ~BfmeParticleSystemHandle() throw()
	{
		if (system)
			((RvaSmartPtr12 *)this)->rva0004CBC0();
	}
	void clear()
	{
		if (system)
		{
			((RvaSmartPtr12 *)this)->rva0004CBC0();
			system = 0;
		}
	}
	operator bool() const { return system != 0; }
	ParticleSystem *operator->() const { return !system ? Make001FCBD7() : system; }
	ParticleSystem *system;
	BfmeParticleSystemHandle *previous, *next;
};
class ParticleSystemTemplate;
#include "../../../../../../GameEngine/Include/GameClient/ParticleSys.h"
extern ParticleSystemManager *TheParticleSystemManager;
struct Rva001F3899Arg;
#include "../../../../../../GameEngine/Include/GameLogic/Module/Rva001F3899Slot.h"
class Rva001F384AByteZeroSetter
{
public:
	void disable();
};

#include "../../../../../../GameEngine/Include/Common/ThingTemplate.h"
class DoDrawSlaveView
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10)
	virtual bool isHidden();
};
struct DoDrawSlaveOwner
{
	char m_pad00[0x250];
	DoDrawSlaveView *m_slave;
};
struct DoDrawUpdateView
{
	char m_pad00[4];
	bool m_active;
	char m_pad05[0x34 - 5];
	int m_state;
};
class Object
{
public:
	char m_pad00[0x1C0];
	Real m_orientation;
	char m_pad1C4[0x274 - 0x1C4];
	DoDrawSlaveOwner *m_owner274;
	char m_pad278[0x438 - 0x278];
	unsigned char m_flags438;
};
class Gen_0075EF90
{
public:
	Gen_0075EF90 &bfmeAssign(const Gen_0075EF90 &);
};
class View;
class Drawable
{
public:
	void draw(View *view);
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getObject() const { return m_object; }
	char m_pad00[0x04];
	const ThingTemplate *m_template;
	char m_pad08[0x68 - 0x08];
	Gen_0075EF90 *m_68;
	char m_pad6C[0xFC - 0x6C];
	Object *m_object;
};
class Rva002716Holder
{
public:
	void Rva002716ACBroadcast();
};
#include "../../../../../../GameEngine/Include/GameClient/View.h"
extern View *TheTacticalView;
#include "../../../../../../GameEngine/Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;
#include "../../../../../../GameEngine/Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

#include "../../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
bool Rva0010E676_SetEmissive(RenderObjClass *robj, Real r, Real g, Real b);

class W3DScriptedModelDraw
{
public:
	void rva000B710D(Matrix3D &mtx);
public: void rva000BD6C2(); };
class Rva000BFDFE
{
public:
	void rva000C0386();
};
class Rva000B3B2BArg;
class Rva000B3B2B
{
public:
	void rva000B3B2B(Rva000B3B2BArg *o);
};
class RadiusDecal
{
public:
	void update();
	char m_pad00[4];
};

namespace _STL
{
struct _Rb_tree_node_base;
template <class _Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}
struct DoDrawIDNode
{
	char m_pad00[8];
	DoDrawIDNode *m_left;
	char m_pad0C[4];
	int m_value;
};
struct DoDrawIDIterator
{
	DoDrawIDNode *m_node;
	DoDrawIDIterator(DoDrawIDNode *doDrawIDNode) : m_node(doDrawIDNode) {}
	const int &operator*() const { return m_node->m_value; }
	bool operator!=(const DoDrawIDIterator &o) const { return m_node != o.m_node; }
	DoDrawIDIterator &operator++()
	{
		m_node = (DoDrawIDNode *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)m_node);
		return *this;
	}
};
struct DoDrawIDSet
{
	DoDrawIDNode *m_header;
	UnsignedInt m_count;
	UnsignedInt size() const { return m_count; }
	DoDrawIDIterator begin() const { return DoDrawIDIterator(m_header->m_left); }
	DoDrawIDIterator end() const { return DoDrawIDIterator(m_header); }
};
struct DoDrawBits
{
	UnsignedInt m_bits[19];
	bool test(int i) const { return (m_bits[i >> 5] >> (i & 31)) & 1; }
};
struct DoDrawVector
{
	void *m_begin;
	void *m_end;
	void *m_limit;
	bool empty() const { return m_begin == m_end; }
};

template <class T> inline const T &doDrawMin(const T &a, const T &b) { return b < a ? b : a; }

struct W3DModelDrawModuleData
{
	char m_pad00[0x14];
	AsciiString m_particleName;
	char m_pad18[0x69 - 0x18];
	bool m_bfmeFlag69;
	bool m_bfmeFlag6A;
	char m_pad6B[0x108 - 0x6B];
	bool m_b108;
	char m_pad109[0x136 - 0x109];
	bool m_b136;
	char m_pad137[0x15D - 0x137];
	bool m_b15D;
	char m_pad15E;
	bool m_b15F;
};

class DrawModulePrimary
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61)
	virtual void slot62();
	const W3DModelDrawModuleData *m_moduleData;	// 0x04
	Drawable *m_drawable;				// 0x08
};
class DrawModuleInterface
{
public:
	ISLOT(00) ISLOT(01) ISLOT(02) ISLOT(03) ISLOT(04) ISLOT(05) ISLOT(06) ISLOT(07)
	ISLOT(08) ISLOT(09) ISLOT(10) ISLOT(11) ISLOT(12) ISLOT(13) ISLOT(14) ISLOT(15)
	ISLOT(16) ISLOT(17) ISLOT(18) ISLOT(19) ISLOT(20) ISLOT(21) ISLOT(22) ISLOT(23)
	ISLOT(24) ISLOT(25) ISLOT(26)
	virtual void ifaceSlot27(int a);
	ISLOT(28)
	virtual void ifaceSlot29();
};

class W3DModelDraw : public DrawModulePrimary, public DrawModuleInterface
{
public:
	virtual void doDrawModule(const Matrix3D *transformMtx);
	void rva000C6E1A();
	/* the rowed W3DScriptedModelDraw::rva000BD6C2 */ __declspec(dllimport) __forceinline void rva000BD6C2() { ((W3DScriptedModelDraw *)this)->rva000BD6C2(); }
protected:
	void handleClientTurretPositioning();
	void handleClientRecoil();
	const W3DModelDrawModuleData *getW3DModelDrawModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }
	void adjustTransformMtx(Matrix3D &mtx) { ((W3DScriptedModelDraw *)this)->rva000B710D(mtx); }
	bool testModelCondition239() const { return m_conditionBits.test(239); }
private:
	char m_pad10[0x1C - 0x10];
	BfmeParticleSystemHandle m_particleSystem;	// 0x1C
	char m_pad28[0x4A - 0x28];
	bool m_b4A;
	bool m_b4B;
	char m_pad4C[0x50 - 0x4C];
	RenderObjClass *m_renderObject;			// 0x50
	char m_pad54[0x58 - 0x54];
	DoDrawUpdateView *m_58;
	char m_pad5C[0x68 - 0x5C];
	DoDrawVector m_vec68;
	DoDrawVector m_vec74;
	char m_pad80[0xA0 - 0x80];
	bool m_bA0;
	char m_padA1[3];
	int m_A4;
	DoDrawIDSet m_drawIDs;				// 0xA8
	char m_padB0[0xBC - 0xB0];
	int m_BC;
	char m_padC0[0x17C - 0xC0];
	DoDrawBits m_conditionBits;		// 0x17C
	bool m_b1C8;
	bool m_b1C9;
	char m_pad1CA[0x1D0 - 0x1CA];
	RadiusDecal m_radiusDecal;			// 0x1D0
	char m_pad1D4[0x270 - 0x1D4];
	bool m_fading;					// 0x270
	UnsignedInt m_fadeTotal;			// 0x274
	UnsignedInt m_fadeElapsed;			// 0x278
	UnsignedInt m_fadeLastFrame;			// 0x27C
	Real m_fadeColor[3];				// 0x280
};

void W3DModelDraw::doDrawModule(const Matrix3D *transformMtx)
{
	if (!m_bA0 && m_A4)
		return;

	const W3DModelDrawModuleData *w3DModelDrawModuleData = getW3DModelDrawModuleData();
	if (w3DModelDrawModuleData->m_b15D)
	{
		if (!TheGameLogic->isInMultiplayerGame())
			return;
		if (((DoDrawGlobalDataView *)TheWritableGlobalData)->m_bD45)
			return;
	}
	if (w3DModelDrawModuleData->m_b15F && m_BC)
		return;

	m_bA0 = false;

	if (testModelCondition239() && !w3DModelDrawModuleData->m_particleName.isEmpty())
	{
		Vector3 v = transformMtx->Get_Translation();
		Coord3D pos = *(const Coord3D *)&v;
		((DoDrawTerrainLogicView *)TheTerrainLogic)->getGroundHeight(pos.x, pos.y, &pos.z, 0, 0);
		if (m_particleSystem)
		{
			((Rva001F3899Slot *)m_particleSystem.operator->())->set(*(const Rva001F3899Arg *)&pos);
		}
		else
		{
			const ParticleSystemTemplate *particleSystemTemplate = TheParticleSystemManager->findTemplate(w3DModelDrawModuleData->m_particleName);
			if (particleSystemTemplate)
			{
				m_particleSystem = TheParticleSystemManager->createParticleSystem(particleSystemTemplate, true);
				if (m_particleSystem)
				{
					((Rva001F3899Slot *)m_particleSystem.operator->())->set(*(const Rva001F3899Arg *)&pos);
					((Rva001F384AByteZeroSetter *)m_particleSystem.operator->())->disable();
				}
			}
		}
	}
	else if (m_particleSystem)
	{
		m_particleSystem->destroy();
		m_particleSystem.clear();
	}

	((Rva000BFDFE *)this)->rva000C0386();

	if (m_renderObject)
	{
		Matrix3D mtx(true);
		if (getDrawable()->getTemplate()->m_kindof[6] & 0x10000)
		{
			mtx.Set_Translation(transformMtx->Get_Translation());
			mtx.Rotate_Z(TheTacticalView->getAngle());
		}
		else if (!w3DModelDrawModuleData->m_bfmeFlag69 && !w3DModelDrawModuleData->m_bfmeFlag6A)
		{
			mtx = *transformMtx;
		}
		else
		{
			mtx.Set_Translation(transformMtx->Get_Translation());
			if (w3DModelDrawModuleData->m_bfmeFlag6A)
			{
				Object *obj = getDrawable()->getObject();
				Real angle;
				if (TheInGameUI)
					angle = TheInGameUI->rva0029B3C1(obj);
				else
					angle = obj->m_orientation;
				mtx.Rotate_Z(angle);
			}
		}
		adjustTransformMtx(mtx);
		m_renderObject->Set_Transform(mtx);

		if (m_fading)
		{
			UnsignedInt now = TheGameClient->getFrame();
			UnsignedInt delta = now - m_fadeLastFrame;
			m_fadeLastFrame = now;
			UnsignedInt elapsed = m_fadeElapsed + delta;
			m_fadeElapsed = doDrawMin(m_fadeTotal, elapsed);
			Real frac = (Real)m_fadeElapsed / (Real)m_fadeTotal;
			Rva0010E676_SetEmissive(m_renderObject, frac * m_fadeColor[0], frac * m_fadeColor[1], frac * m_fadeColor[2]);
			if (m_fadeElapsed >= m_fadeTotal)
				m_fading = false;
		}
	}

	handleClientTurretPositioning();
	rva000C6E1A();

	if (w3DModelDrawModuleData->m_b108)
		ifaceSlot27(0);

	if (m_drawIDs.size())
	{
		for (DoDrawIDIterator it = m_drawIDs.begin(); it != m_drawIDs.end(); ++it)
		{
			Drawable *draw = TheGameClient->findDrawableByID((DrawableID)*it);
			if (draw)
			{
				if (getDrawable()->m_68 && draw->m_68)
					draw->m_68->bfmeAssign(*getDrawable()->m_68);
				((Rva002716Holder *)draw)->Rva002716ACBroadcast();
				draw->draw(0);
			}
		}
	}

	slot62();
	rva000BD6C2();

	Object *obj = getDrawable()->getObject();
	DoDrawSlaveOwner *owner;
	if (obj && (owner = obj->m_owner274) != 0 && !w3DModelDrawModuleData->m_b136 && !owner->m_slave->isHidden())
	{
		if (!m_b4B)
			m_b4B = true;
	}
	else if (m_b4A && m_b4B)
	{
		m_b4B = false;
	}

	if (obj && m_58 && m_58->m_state == 1 && (obj->m_flags438 & 1))
	{
		m_b4B = true;
		m_58->m_active = false;
	}

	if ((!m_vec74.empty() && m_b1C9) || (!m_vec68.empty() && m_b1C8))
		ifaceSlot29();

	if (0)
	{
		BfmeParticleSystemHandle debugHandle;
	}
	((Rva000B3B2B *)this)->rva000B3B2B((Rva000B3B2BArg *)m_renderObject);
	m_radiusDecal.update();
	handleClientRecoil();
}
