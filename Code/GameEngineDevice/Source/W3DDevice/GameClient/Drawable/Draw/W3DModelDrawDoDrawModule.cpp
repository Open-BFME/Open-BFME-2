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

#include "../../../../../../GameEngine/Include/Common/ScalarTypes.h"


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
#include "../../../../../Include/W3DDevice/GameClient/Rva001F384AByteZeroSetter.h"

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
#include "../../../../../Include/W3DDevice/GameClient/Gen_0075EF90.h"
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
#include "../../../../../../GameEngine/Include/GameClient/Rva002716Holder.h"
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
#include "../../../../../../GameEngine/Include/Common/Rva000BFDFE.h"
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

#if defined(BFME2_MODERN)
#include "../../../../../../GameEngine/Include/Common/ModernRenderPhase.h"
// Unit interpolation between client updates. doDrawModule runs once per update
// (30 Hz) and sets each model's transform and animation; presentations in
// between only render. Each model keeps its last three poses stamped with the
// client frame of their update. A presentation shows every model at one shared
// client time that advances evenly with real time about one update behind
// (modernShownClientTime), then restores the update's pose. An update can run
// more than one client frame (RotWK 2.01's game.dat does every fifth), so poses
// are placed by client frame, not by update. Entries hold a reference, so a
// model released between updates stays valid until it is pruned at the next
// update. Large jumps (teleports, spawns) are not blended.
struct ModernPose
{
	double frame;			// game time (client frames) of the update that drew it
	Matrix3D transform;
	// Skeletal animation: BFME 2's scripted draw advances its slot frames once per
	// client update and pushes them to the model (Set_Animation, manual mode).
	bool anim;
	void *motion0, *motion1;	// slot 0; slot 1 while the two are blended, else 0
	float frame0, frame1, blend;
	int mode0, mode1;		// slot modes (1 loop, 5 loop backwards, ...)
};
enum { MODERN_POSES = 3 };
// The last three samples of something that changes only now and then (at logic
// steps), with the game time each arrived. Shown one sample interval behind:
// at game time `when` it is between the two samples around `when - interval`,
// so a new sample continues the motion instead of jumping to it.
struct ModernSampleTrack
{
	Matrix3D value[3];
	double time[3];
	bool onTick[3];			// arrived in the first update of a logic step
	int count;
	double delay;			// smoothed logic-step gap: how far behind to show
	void push(const Matrix3D &m, double t, bool tick)
	{
		if (!count)
			delay = 0.0;
		if (count && time[count - 1] == t)
		{
			value[count - 1] = m;	// changed again within this update
			return;
		}
		if (count == 3)
		{
			for (int k = 1; k < 3; ++k)
			{
				value[k - 1] = value[k];
				time[k - 1] = time[k];
				onTick[k - 1] = onTick[k];
			}
			count = 2;
		}
		value[count] = m;
		time[count] = t;
		onTick[count] = tick;
		++count;
		// Logic-step gaps vary by a client frame (RotWK adds a frame every
		// fifth update); following each gap exactly would step the shown time
		// back and forth, so follow their running average.
		double gap = interval();
		if (gap >= 2.5 && gap <= 13.0)
			delay = delay > 0.0 ? delay + 0.2 * (gap - delay) : gap;
	}
	double interval() const { return count >= 2 ? time[count - 1] - time[count - 2] : 0.0; }
	bool sample(double when, Matrix3D &out) const
	{
		if (count < 2)
			return false;
		double at = when - (delay > 0.0 ? delay : interval());
		for (int k = count - 1; k > 0; --k)
		{
			if (at >= time[k - 1] || k == 1)
			{
				double gap = time[k] - time[k - 1];
				if (gap <= 0.0)
					return false;
				double t = (at - time[k - 1]) / gap;
				if (t < 0.0) t = 0.0;
				if (t > 1.0) t = 1.0;
				Vector3 p = value[k - 1].Get_Translation(), q = value[k].Get_Translation();
				float dx = q.X - p.X, dy = q.Y - p.Y, dz = q.Z - p.Z;
				if (dx * dx + dy * dy + dz * dz > 1000.0f * 1000.0f)
					return false;	// teleport
				Matrix3D::Lerp(value[k - 1], value[k], (float)t, out);
				return true;
			}
		}
		return false;
	}
};
struct ModernFrameTrack
{
	float value[3];
	double time[3];
	bool onTick[3];
	int count;
	void push(float v, double t, bool tick)
	{
		if (count && time[count - 1] == t)
		{
			value[count - 1] = v;
			return;
		}
		if (count == 3)
		{
			for (int k = 1; k < 3; ++k)
			{
				value[k - 1] = value[k];
				time[k - 1] = time[k];
				onTick[k - 1] = onTick[k];
			}
			count = 2;
		}
		value[count] = v;
		time[count] = t;
		onTick[count] = tick;
		++count;
	}
	double interval() const { return count >= 2 ? time[count - 1] - time[count - 2] : 0.0; }
};
struct ModernModelHistory
{
	RenderObjClass *object;
	ModernPose poses[MODERN_POSES];	// oldest first; poses[count-1] is the latest
	int count;
	unsigned serial;		// update that last drew it
	Matrix3D saved;
	bool applied;
	int animMode;			// the model's own mode, read back when applied
	bool animApplied;
	// Logic-stepped motion: what retail does not interpolate (projectiles,
	// construction progress) changes only at logic ticks. The last two distinct
	// transforms and slot 0 frames, with the game time each first appeared.
	ModernSampleTrack steps;	// distinct transforms
	void *animStepMotion;
	ModernFrameTrack animSteps;	// distinct slot 0 frames of animStepMotion
	// Eased motion: horde members move fast after each logic tick and slow down
	// before the next (retail eases them toward the tick's target). Sample them
	// once per logic step and show them evenly between samples, one step behind.
	ModernSampleTrack ticks;
	double tickBase;
	float firstStep, lastStep;	// per-client-frame step: first and latest of this logic step
	float ease;			// smoothed first/last step ratio (1 = even motion)
	float easeWeight;		// 0 = shown as updated, 1 = eased between logic steps
	double easeTime;	// presentation time easeWeight was last moved
	bool easedMode;			// with hysteresis, so a model does not flip between paths
	// The drawable that owns the model; one without an object (the building
	// placement preview following the cursor) is always shown as updated.
	const void *drawable;
	bool hasObject;
};
// HLodClass slots as the scripted draw and setPauseAnimation reach them:
// Set_Animation +0xB4 (slot 45), Peek_Animation_And_Info +0x208 (slot 130).
#define MODERN_ANIM_SLOT(n) virtual void modernSlot##n();
class ModernAnimatedModel
{
public:
	MODERN_ANIM_SLOT(0) MODERN_ANIM_SLOT(1) MODERN_ANIM_SLOT(2) MODERN_ANIM_SLOT(3) MODERN_ANIM_SLOT(4) MODERN_ANIM_SLOT(5) MODERN_ANIM_SLOT(6) MODERN_ANIM_SLOT(7) MODERN_ANIM_SLOT(8) MODERN_ANIM_SLOT(9)
	MODERN_ANIM_SLOT(10) MODERN_ANIM_SLOT(11) MODERN_ANIM_SLOT(12) MODERN_ANIM_SLOT(13) MODERN_ANIM_SLOT(14) MODERN_ANIM_SLOT(15) MODERN_ANIM_SLOT(16) MODERN_ANIM_SLOT(17) MODERN_ANIM_SLOT(18) MODERN_ANIM_SLOT(19)
	MODERN_ANIM_SLOT(20) MODERN_ANIM_SLOT(21) MODERN_ANIM_SLOT(22) MODERN_ANIM_SLOT(23) MODERN_ANIM_SLOT(24) MODERN_ANIM_SLOT(25) MODERN_ANIM_SLOT(26) MODERN_ANIM_SLOT(27) MODERN_ANIM_SLOT(28) MODERN_ANIM_SLOT(29)
	MODERN_ANIM_SLOT(30) MODERN_ANIM_SLOT(31) MODERN_ANIM_SLOT(32) MODERN_ANIM_SLOT(33) MODERN_ANIM_SLOT(34) MODERN_ANIM_SLOT(35) MODERN_ANIM_SLOT(36) MODERN_ANIM_SLOT(37) MODERN_ANIM_SLOT(38) MODERN_ANIM_SLOT(39)
	MODERN_ANIM_SLOT(40) MODERN_ANIM_SLOT(41) MODERN_ANIM_SLOT(42) MODERN_ANIM_SLOT(43)
	virtual void setBlendAnimation(void *motion0, float frame0, void *motion1, float frame1, float percentage);	// +0xB0
	virtual void setAnimation(void *motion, float frame, int mode);	// +0xB4
	MODERN_ANIM_SLOT(46) MODERN_ANIM_SLOT(47) MODERN_ANIM_SLOT(48) MODERN_ANIM_SLOT(49)
	MODERN_ANIM_SLOT(50) MODERN_ANIM_SLOT(51) MODERN_ANIM_SLOT(52) MODERN_ANIM_SLOT(53) MODERN_ANIM_SLOT(54) MODERN_ANIM_SLOT(55) MODERN_ANIM_SLOT(56) MODERN_ANIM_SLOT(57) MODERN_ANIM_SLOT(58) MODERN_ANIM_SLOT(59)
	MODERN_ANIM_SLOT(60) MODERN_ANIM_SLOT(61) MODERN_ANIM_SLOT(62) MODERN_ANIM_SLOT(63) MODERN_ANIM_SLOT(64) MODERN_ANIM_SLOT(65) MODERN_ANIM_SLOT(66) MODERN_ANIM_SLOT(67) MODERN_ANIM_SLOT(68) MODERN_ANIM_SLOT(69)
	MODERN_ANIM_SLOT(70) MODERN_ANIM_SLOT(71) MODERN_ANIM_SLOT(72) MODERN_ANIM_SLOT(73) MODERN_ANIM_SLOT(74) MODERN_ANIM_SLOT(75) MODERN_ANIM_SLOT(76) MODERN_ANIM_SLOT(77) MODERN_ANIM_SLOT(78) MODERN_ANIM_SLOT(79)
	MODERN_ANIM_SLOT(80) MODERN_ANIM_SLOT(81) MODERN_ANIM_SLOT(82) MODERN_ANIM_SLOT(83) MODERN_ANIM_SLOT(84) MODERN_ANIM_SLOT(85) MODERN_ANIM_SLOT(86) MODERN_ANIM_SLOT(87) MODERN_ANIM_SLOT(88) MODERN_ANIM_SLOT(89)
	MODERN_ANIM_SLOT(90) MODERN_ANIM_SLOT(91) MODERN_ANIM_SLOT(92) MODERN_ANIM_SLOT(93) MODERN_ANIM_SLOT(94) MODERN_ANIM_SLOT(95) MODERN_ANIM_SLOT(96) MODERN_ANIM_SLOT(97) MODERN_ANIM_SLOT(98) MODERN_ANIM_SLOT(99)
	MODERN_ANIM_SLOT(100) MODERN_ANIM_SLOT(101) MODERN_ANIM_SLOT(102) MODERN_ANIM_SLOT(103) MODERN_ANIM_SLOT(104) MODERN_ANIM_SLOT(105) MODERN_ANIM_SLOT(106) MODERN_ANIM_SLOT(107) MODERN_ANIM_SLOT(108) MODERN_ANIM_SLOT(109)
	MODERN_ANIM_SLOT(110) MODERN_ANIM_SLOT(111) MODERN_ANIM_SLOT(112) MODERN_ANIM_SLOT(113) MODERN_ANIM_SLOT(114) MODERN_ANIM_SLOT(115) MODERN_ANIM_SLOT(116) MODERN_ANIM_SLOT(117) MODERN_ANIM_SLOT(118) MODERN_ANIM_SLOT(119)
	MODERN_ANIM_SLOT(120) MODERN_ANIM_SLOT(121) MODERN_ANIM_SLOT(122) MODERN_ANIM_SLOT(123) MODERN_ANIM_SLOT(124) MODERN_ANIM_SLOT(125) MODERN_ANIM_SLOT(126) MODERN_ANIM_SLOT(127) MODERN_ANIM_SLOT(128) MODERN_ANIM_SLOT(129)
	virtual void *peekAnimation(float &frame, int &numFrames, int &mode, float &multiplier);	// +0x208
};
#undef MODERN_ANIM_SLOT
// The scripted draw's slot 0 (W3DModelDraw +0x110, 0x1C bytes per slot) and the
// second slot's motion (+0x12C), whose presence means a blend is being pushed.
struct ModernAnimSlotView
{
	void *motion;
	float frame, previous, unused;
	int mode, direction;
	char flags[4];
};
// HAnimClass slot 5 is the frame count (as the scripted draw calls it).
class ModernMotionView
{
public:
	virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
	virtual int frameCount();
};
// Frame between the last two updates. Loops (slot mode 1 forwards, 5 backwards)
// may have wrapped; a larger change (ping-pong turn, restart) is not blended.
static float modernAnimFrame(float previous, float current, int mode, float last, float alpha)
{
	if (last <= 0.0f)
		return current;
	float delta = current - previous;
	if (mode == 1 && delta < 0.0f)
		delta += last;
	else if (mode == 5 && delta > 0.0f)
		delta -= last;
	if (delta > last * 0.5f || delta < -last * 0.5f)
		return current;
	float frame = previous + alpha * delta;
	if (frame > last)
		frame -= last;
	else if (frame < 0.0f)
		frame += last;
	return frame;
}
enum { MODERN_MODEL_CAPACITY = 4096 };
static ModernModelHistory s_modernModels[MODERN_MODEL_CAPACITY];
static int s_modernModelCount = 0;
static unsigned s_modernVisualSerial = 1;
// The client frame of the latest update and when it ran (W3DDisplayDraw.cpp).
extern double g_modernClientStamp;
extern double g_modernTickBase;
extern bool g_modernTickStarted;
extern __int64 g_modernClientFrameTime;
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *);
static ModernPose *modernLatestPose(ModernModelHistory &entry)
{
	return entry.count ? &entry.poses[entry.count - 1] : 0;
}
// The entry's pose for this update's client frame, created (at `transform`, or
// at the model's own transform) when this update has not recorded one yet.
static ModernPose *modernPoseForUpdate(RenderObjClass *object, const Matrix3D *transform, ModernModelHistory **owner = 0)
{
	ModernModelHistory *found = 0;
	for (int i = 0; i < s_modernModelCount; ++i)
	{
		if (s_modernModels[i].object == object)
		{
			found = &s_modernModels[i];
			break;
		}
	}
	if (!found)
	{
		if (s_modernModelCount >= MODERN_MODEL_CAPACITY)
			return 0;
		found = &s_modernModels[s_modernModelCount++];
		object->Add_Ref();
		found->object = object;
		found->count = 0;
		found->applied = false;
		found->animApplied = false;
		found->steps.count = 0;
		found->animSteps.count = 0;
		found->animStepMotion = 0;
		found->ticks.count = 0;
		found->tickBase = -1.0;
		found->firstStep = found->lastStep = 0.0f;
		found->ease = 1.0f;
		found->easedMode = false;
		found->easeWeight = 0.0f;
		found->easeTime = 0.0;
		found->drawable = 0;
		found->hasObject = true;
	}
	if (owner)
		*owner = found;
	ModernModelHistory &entry = *found;
	entry.serial = s_modernVisualSerial;
	ModernPose *latest = modernLatestPose(entry);
	// An update that adds no game time (a paused game) replaces the latest pose.
	if (!latest || latest->frame != g_modernClientStamp)
	{
		if (entry.count == MODERN_POSES)
		{
			for (int k = 1; k < MODERN_POSES; ++k)
				entry.poses[k - 1] = entry.poses[k];
			--entry.count;
		}
		latest = &entry.poses[entry.count++];
		latest->frame = g_modernClientStamp;
		latest->anim = false;
		latest->transform = transform ? *transform : object->Get_Transform();
	}
	if (transform)
		latest->transform = *transform;
	return latest;
}
static void modernCaptureModel(RenderObjClass *object, const Matrix3D &transform, const void *drawable, bool hasObject)
{
	if (g_modernRenderPhase != MODERN_RENDER_UPDATE)
		return;
	ModernModelHistory *entry = 0;
	if (!modernPoseForUpdate(object, &transform, &entry) || !entry)
		return;
	entry->drawable = drawable;
	entry->hasObject = hasObject;
	// Eased-motion bookkeeping: the step per client frame since the previous
	// pose; at the first update of a logic step, judge the last step's shape
	// (first vs last step) and sample the pose.
	if (entry->count >= 2)
	{
		const ModernPose &before = entry->poses[entry->count - 2];
		double frames = g_modernClientStamp - before.frame;
		if (frames > 0.01 && frames < 3.5)
		{
			Vector3 p = before.transform.Get_Translation(), q = transform.Get_Translation();
			float step = (float)(sqrt((double)((q.X - p.X) * (q.X - p.X) + (q.Y - p.Y) * (q.Y - p.Y))) / frames);
			if (entry->tickBase != g_modernTickBase)
			{
				if (entry->lastStep > 0.05f && entry->firstStep > 0.05f)
					entry->ease = entry->ease * 0.7f + 0.3f * (entry->firstStep / entry->lastStep);
				else
					entry->ease = entry->ease * 0.7f + 0.3f;	// not moving: drift back to even
				entry->firstStep = step;
			}
			entry->lastStep = step;
		}
	}
	if (entry->tickBase != g_modernTickBase)
	{
		entry->tickBase = g_modernTickBase;
		entry->ticks.push(transform, g_modernClientStamp, true);
	}
	// Eased mode with hysteresis: in above 1.3, out below 1.1.
	if (!entry->easedMode && entry->ease > 1.3f)
		entry->easedMode = true;
	else if (entry->easedMode && entry->ease < 1.1f)
		entry->easedMode = false;
	// Track distinct transforms and when each first appeared.
	const ModernSampleTrack &s = entry->steps;
	if (!s.count || memcmp(&s.value[s.count - 1], &transform, sizeof(Matrix3D)) != 0)
		entry->steps.push(transform, g_modernClientStamp, g_modernTickStarted);
}
// After doDrawModule pushed the slots to the model (rva000B3B2B).
static void modernCaptureAnimation(RenderObjClass *object, const void *draw)
{
	if (g_modernRenderPhase != MODERN_RENDER_UPDATE || !object)
		return;
	const ModernAnimSlotView *slot0 = (const ModernAnimSlotView *)((const char *)draw + 0x110);
	const ModernAnimSlotView *slot1 = slot0 + 1;
	float blendRemaining = *(const float *)((const char *)draw + 0x90);
	float blendDuration = *(const float *)((const char *)draw + 0x94);
	if (!slot0->motion)
		return;
	{
		// A model that only animates (its transform unchanged) gets its pose here.
		ModernModelHistory *entry = 0;
		ModernPose *pose = modernPoseForUpdate(object, 0, &entry);
		if (!pose || !entry)
			return;
		// Track distinct slot 0 frames of one motion and when each first appeared.
		if (entry->animStepMotion != slot0->motion || slot1->motion)
		{
			entry->animStepMotion = slot1->motion ? 0 : slot0->motion;
			entry->animSteps.count = 0;
			entry->animSteps.push(slot0->frame, g_modernClientStamp, g_modernTickStarted);
		}
		else if (entry->animSteps.value[entry->animSteps.count - 1] != slot0->frame)
			entry->animSteps.push(slot0->frame, g_modernClientStamp, g_modernTickStarted);
		pose->anim = true;
		pose->motion0 = slot0->motion;
		pose->frame0 = slot0->frame;
		pose->mode0 = slot0->mode;
		pose->motion1 = slot1->motion;
		pose->frame1 = slot1->frame;
		pose->mode1 = slot1->mode;
		// what rva000B3B2B pushed with the two motions
		pose->blend = blendDuration != 0.0f ? 1.0f - blendRemaining / blendDuration : 1.0f;
		return;
	}
}
void modernBeginModelUpdate()
{
	// Drop models that the last update did not draw (gone, hidden or culled).
	int kept = 0;
	for (int i = 0; i < s_modernModelCount; ++i)
	{
		ModernModelHistory &entry = s_modernModels[i];
		if (entry.serial != s_modernVisualSerial)
		{
			entry.object->Release_Ref();
			continue;
		}
		if (kept != i)
			s_modernModels[kept] = entry;
		++kept;
	}
	s_modernModelCount = kept;
	++s_modernVisualSerial;
}
// The client time every model is shown at: it runs at the measured client frame
// rate (30/s, or 36/s with RotWK's extra frame), about one update behind the
// latest update, is pulled gently toward that target and never goes back.
static double s_modernClientRate = 0.0;
static double s_modernRateStamp = 0.0;
static __int64 s_modernRateTime = 0;
static double s_modernShownTime = 0.0;
static __int64 s_modernShownQpc = 0;
static bool s_modernShownValid = false;
static double modernShownClientTime()
{
	__int64 now, frequency;
	QueryPerformanceCounter(&now);
	QueryPerformanceFrequency(&frequency);
	double freq = (double)frequency;
	double latest = g_modernClientStamp;
	if (g_modernClientFrameTime != s_modernRateTime)
	{
		// A new update: measure the game-time rate across it (a paused game
		// adds nothing and keeps the last rate).
		double step = latest - s_modernRateStamp;
		if (s_modernRateTime && step > 0.0 && step < 30.0 && g_modernClientFrameTime > s_modernRateTime)
		{
			double measured = step * freq / (double)(g_modernClientFrameTime - s_modernRateTime);
			if (measured > 5.0 && measured < 200.0)
				s_modernClientRate = s_modernClientRate > 0.0 ? s_modernClientRate * 0.9 + measured * 0.1 : measured;
		}
		else if (step != 0.0)
			s_modernShownValid = false;	// first update, reset or a long stall
		s_modernRateStamp = latest;
		s_modernRateTime = g_modernClientFrameTime;
	}
	double rate = s_modernClientRate > 0.0 ? s_modernClientRate : 30.0;
	double lag = rate / 30.0;	// one update's worth of client frames
	double since = (double)(now - g_modernClientFrameTime) / freq;
	double target = latest + since * rate - lag;
	double shown;
	if (!s_modernShownValid)
		shown = target;
	else
	{
		shown = s_modernShownTime + (double)(now - s_modernShownQpc) / freq * rate;
		shown += (target - shown) * 0.1;
		if (shown < s_modernShownTime)
			shown = s_modernShownTime;
	}
	if (shown > latest)
		shown = latest;
	if (shown < latest - 3.0)
		shown = latest - 3.0;
	s_modernShownTime = shown;
	s_modernShownQpc = now;
	s_modernShownValid = true;
	return shown;
}
// The two poses around client time `when` and the fraction between them.
static bool modernBracket(const ModernModelHistory &entry, double when, int &from, float &fraction)
{
	for (int k = entry.count - 1; k > 0; --k)
	{
		const ModernPose &a = entry.poses[k - 1];
		const ModernPose &b = entry.poses[k];
		if (a.frame <= when || k == 1)
		{
			double gap = b.frame - a.frame;
			if (gap < 0.01 || gap > 3.5)
				return false;	// no game time between them, or not consecutive updates
			double t = (when - a.frame) / gap;
			if (t < 0.0) t = 0.0;
			if (t > 1.0) t = 1.0;
			from = k - 1;
			fraction = (float)t;
			return true;
		}
	}
	return false;
}
// The game time this presentation shows, for other position sources (decals).
double g_modernShownTime;
bool g_modernShownActive;
void modernApplyModelInterpolation(float alpha)
{
	(void)alpha;
	double when = modernShownClientTime();
	g_modernShownTime = when;
	g_modernShownActive = true;
	int blended = 0, moving = 0, steppedCount = 0, steppedAnims = 0, easedCount = 0;
	for (int i = 0; i < s_modernModelCount; ++i)
	{
		ModernModelHistory &entry = s_modernModels[i];
		entry.applied = false;
		// Only models drawn by the latest update.
		if (entry.serial != s_modernVisualSerial || !entry.count)
			continue;
		const ModernPose &latest = entry.poses[entry.count - 1];
		const Matrix3D &actual = entry.object->Get_Transform();
		bool overwritten = memcmp(&actual, &latest.transform, sizeof(Matrix3D)) != 0;
		int from;
		float fraction;
		Matrix3D visual = latest.transform;
		bool blend = false, stepped = false;
		// The placement preview follows the cursor every update: never one logic
		// step behind, only between its last updates.
		bool ghost = !entry.hasObject;
		// Moved only at logic steps (its last two changes arrived at the start of
		// a logic step, 2.5..13 client frames apart) and not since: projectiles.
		const ModernSampleTrack &s = entry.steps;
		double interval = s.interval();
		if (!ghost && s.count >= 2 && s.onTick[s.count - 1] && s.onTick[s.count - 2] &&
			interval >= 2.5 && interval <= 13.0 &&
			memcmp(&latest.transform, &s.value[s.count - 1], sizeof(Matrix3D)) == 0 &&
			s.sample(when, visual))
		{
			blend = stepped = true;
			++steppedCount;
		}
		// Eased between logic steps (horde members): evenly between the samples
		// taken at the start of each logic step.
		// The eased path shows a model a logic step further behind than the
		// bracket does, so switching paths outright moves it back (or ahead) by
		// a step; cross over during about three logic steps instead, slower
		// than the model moves, so it only slows down or speeds up.
		const ModernSampleTrack &ticks = entry.ticks;
		double tickInterval = ticks.interval();
		Matrix3D tickVisual;
		bool tickOk = !stepped && !ghost && ticks.count >= 2 && tickInterval >= 2.5 && tickInterval <= 13.0 &&
			ticks.time[ticks.count - 1] > when - 13.0 && ticks.sample(when, tickVisual);
		double sinceWeight = when - entry.easeTime;
		entry.easeTime = when;
		if (sinceWeight < 0.0) sinceWeight = 0.0;
		if (sinceWeight > 3.0) sinceWeight = 3.0;
		float weightStep = (float)(sinceWeight / 18.0);
		if (!tickOk)
			entry.easeWeight = 0.0f;
		else if (entry.easedMode)
			entry.easeWeight = entry.easeWeight + weightStep < 1.0f ? entry.easeWeight + weightStep : 1.0f;
		else
			entry.easeWeight = entry.easeWeight - weightStep > 0.0f ? entry.easeWeight - weightStep : 0.0f;
		if (!stepped && tickOk && entry.easeWeight >= 1.0f)
		{
			visual = tickVisual;
			blend = stepped = true;
			++easedCount;
		}
		if (!stepped)
			blend = modernBracket(entry, when, from, fraction);
		if (blend && !stepped)
		{
			const ModernPose &a = entry.poses[from];
			const ModernPose &b = entry.poses[from + 1];
			Vector3 p = a.transform.Get_Translation(), q = b.transform.Get_Translation();
			float dx = q.X - p.X, dy = q.Y - p.Y, dz = q.Z - p.Z;
			if (dx * dx + dy * dy + dz * dz > 100.0f * 100.0f && !ghost)
				blend = false;	// teleport or spawn
			else if (memcmp(&a.transform, &b.transform, sizeof(Matrix3D)) == 0 && from + 1 == entry.count - 1)
				blend = false;	// still
			else
			{
				Matrix3D::Lerp(a.transform, b.transform, fraction, visual);
				++moving;
			}
			// Trace one moving model's presented position (J: x, y, client time, fraction)
			// and the two poses around it (j: from x/y, to x/y).
			static RenderObjClass *s_traced = 0;
			static unsigned s_tracedSerial = 0;
			if (blend && dx * dx + dy * dy > 0.0001f && (s_traced == entry.object || s_tracedSerial + 2 < s_modernVisualSerial))
			{
				s_traced = entry.object;
				s_tracedSerial = s_modernVisualSerial;
				Vector3 shown = visual.Get_Translation();
				modernTrace('J', shown.X, shown.Y, when, fraction);
				modernTrace('j', p.X, p.Y, q.X, q.Y);
			}
		}
		if (!stepped && tickOk && entry.easeWeight > 0.0f)
		{
			Matrix3D shownAsUpdated = visual;
			Matrix3D::Lerp(shownAsUpdated, tickVisual, entry.easeWeight, visual);
			blend = true;
			++easedCount;
		}
		// Logic that runs after the draw pass (a 5 Hz tick) writes the raw logic
		// pose into the model; retail overwrote it before its next render, so
		// show the draw-pass pose here as well and restore the logic one after.
		if (!blend && !overwritten)
			continue;
		entry.saved = actual;
		entry.object->Set_Transform(visual);
		entry.applied = true;
		++blended;
	}
	int animated = 0, noAnim = 0, blending = 0, unchanged = 0, replaced = 0, jumped = 0;
	for (int i = 0; i < s_modernModelCount; ++i)
	{
		ModernModelHistory &entry = s_modernModels[i];
		entry.animApplied = false;
		if (entry.serial != s_modernVisualSerial || !entry.count)
			continue;
		const ModernPose &latest = entry.poses[entry.count - 1];
		int from;
		float fraction;
		// Slot 0 frame that changes only at logic steps (construction progress):
		// between its samples around one step ago, like a projectile.
		const ModernFrameTrack &f = entry.animSteps;
		double animInterval = f.interval();
		if (latest.anim && !latest.motion1 && f.count >= 2 && entry.animStepMotion == latest.motion0 &&
			f.onTick[f.count - 1] && f.onTick[f.count - 2] &&
			f.value[f.count - 1] == latest.frame0 && animInterval >= 2.5 && animInterval <= 13.0)
		{
			double at = when - animInterval;
			int k = f.count - 1;
			while (k > 1 && at < f.time[k - 1])
				--k;
			double gap = f.time[k] - f.time[k - 1];
			double t = gap > 0.0 ? (at - f.time[k - 1]) / gap : 1.0;
			if (t < 0.0) t = 0.0;
			if (t >= 1.0 && k == f.count - 1) { ++unchanged; continue; }
			if (t > 1.0) t = 1.0;
			ModernAnimatedModel *model = (ModernAnimatedModel *)entry.object;
			float frame, multiplier;
			int frames, mode;
			if (model->peekAnimation(frame, frames, mode, multiplier) != latest.motion0 || frame != latest.frame0) { ++replaced; continue; }
			float last = (float)((ModernMotionView *)latest.motion0)->frameCount() - 1.0f;
			float visual = modernAnimFrame(f.value[k - 1], f.value[k], latest.mode0, last, (float)t);
			entry.animMode = mode;
			model->setAnimation(latest.motion0, visual, mode);
			entry.animApplied = true;
			++animated;
			++steppedAnims;
			continue;
		}
		if (!latest.anim || !modernBracket(entry, when, from, fraction)) { ++noAnim; continue; }
		const ModernPose &a = entry.poses[from];
		const ModernPose &b = entry.poses[from + 1];
		if (!a.anim || a.motion0 != b.motion0 || a.motion1 != b.motion1) { ++noAnim; continue; }
		if (a.frame0 == b.frame0 && (!b.motion1 || a.frame1 == b.frame1) && from + 1 == entry.count - 1) { ++unchanged; continue; }
		ModernAnimatedModel *model = (ModernAnimatedModel *)entry.object;
		float frame, multiplier;
		int frames, mode;
		void *playing = model->peekAnimation(frame, frames, mode, multiplier);
		float last0 = (float)((ModernMotionView *)b.motion0)->frameCount() - 1.0f;
		float visual0 = modernAnimFrame(a.frame0, b.frame0, b.mode0, last0, fraction);
		if (latest.motion1)
		{
			// The two blended motions: the model is still in its two-motion mode
			// (peek reports none) unless something set a single animation since.
			if (playing || b.motion1 != latest.motion1 || b.motion0 != latest.motion0) { ++replaced; continue; }
			float last1 = (float)((ModernMotionView *)b.motion1)->frameCount() - 1.0f;
			float visual1 = modernAnimFrame(a.frame1, b.frame1, b.mode1, last1, fraction);
			float weight = a.blend + (b.blend - a.blend) * fraction;
			model->setBlendAnimation(b.motion0, visual0, b.motion1, visual1, weight);
			++blending;
		}
		else
		{
			// Only while the model still plays what the update pushed.
			if (b.motion1 || playing != latest.motion0 || frame != latest.frame0 || b.motion0 != latest.motion0) { ++replaced; continue; }
			if (visual0 == latest.frame0 && from + 1 == entry.count - 1) { ++jumped; continue; }
			entry.animMode = mode;
			model->setAnimation(b.motion0, visual0, mode);
		}
		entry.animApplied = true;
		++animated;
	}
	modernTrace('I', (double)blended, (double)moving, (double)s_modernModelCount, (double)animated);
	// Why models were not animated: k = no usable poses, blend applied, frame
	// unchanged, model replaced/changed since the update (+ jump in the high digits).
	modernTrace('k', (double)noAnim, (double)blending, (double)unchanged, (double)(replaced + 1000 * jumped));
	// h: models and animations shown between logic-tick steps.
	modernTrace('h', (double)steppedCount, (double)steppedAnims, when, (double)easedCount);
}
void modernRestoreModelInterpolation()
{
	g_modernShownActive = false;
	for (int i = 0; i < s_modernModelCount; ++i)
	{
		ModernModelHistory &entry = s_modernModels[i];
		if (entry.animApplied)
		{
			const ModernPose &latest = entry.poses[entry.count - 1];
			ModernAnimatedModel *model = (ModernAnimatedModel *)entry.object;
			if (latest.motion1)
				model->setBlendAnimation(latest.motion0, latest.frame0, latest.motion1, latest.frame1, latest.blend);
			else
				model->setAnimation(latest.motion0, latest.frame0, entry.animMode);
			entry.animApplied = false;
		}
		if (!entry.applied)
			continue;
		entry.object->Set_Transform(entry.saved);
		entry.applied = false;
	}
}
#endif
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
#if defined(BFME2_MODERN)
		modernCaptureModel(m_renderObject, mtx, getDrawable(), getDrawable()->getObject() != 0);
#endif

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
#if defined(BFME2_MODERN)
	modernCaptureAnimation(m_renderObject, this);
#endif
	m_radiusDecal.update();
	handleClientRecoil();
}
