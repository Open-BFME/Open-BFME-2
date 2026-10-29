// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??0Rva0009D55BProduct@@QAE@XZ retail 0x0009D55B..0x0009D6E8 (397 bytes EH).
// Product of the W3D game client factory 0x0004C8DD (vtable 0x00BC4738;
// new 0x1D4). Runs the LivingWorld constructor 0x002C0120 (its unwind
// funclet 0x00760638 calls the base dtor 0x002BFB2D) then stores vtable
// 0x00BC89C8 and initialises its own members: six zeroed words (+0xC0)
// two 1.0 floats (+0xD8) five float triples (+0xE0 zero / +0xEC 0.9 /
// +0xF8 +0x104 +0x110 zero) then 0 / 10.0 at +0x11C/+0x120 and 1.0 / 0 /
// pi/6 at +0x134..+0x13C; four 12-byte elements at +0x140 built through
// the vector constructor iterator 0x00001423 with the folded trivial ctor
// 0x0047A6A9; zeroed words and floats at +0x188..+0x1AC; two zeroed int
// pairs (+0x1B0 +0x1B8); an STLport vector at +0x1C0 (folded _Vector_base
// ctor 0x00211E58) and two zeroed words. The deleting dtor 0x0009D9A1 and
// dtor 0x0009D6FA are rowed under the opaque name Rva009D6FA. Member
// meanings element types and the class name are unresolved.
//
// ??1Rva0009D55BProduct@@UAE@XZ retail 0x0009D6FA..0x0009D862 (360 bytes EH),
// the destructor the deleting dtor 0x0009D9A1 calls (pin ??1Rva009D6FA).
// After the rowed 0x0009AB85 shutdown it takes the three render objects at
// +0xC8/+0xCC/+0xD0 out of the +0xC4 scene (scene slot 3) when they report
// being in it (slot 123), releases the five ref-counted words +0xC0..+0xD0
// (inline Release_Ref, Delete_This slot 0) and clears each, then unwinds
// the +0x1D0 texture reference (Release_Ref 0x0021ED10) and the +0x1C0
// vector before the LivingWorld destructor 0x002BFB2D.
#include <vector>
#include "ascii_string.h"
// The +0x1C0 vector's storage is freed inline through the game free
// (0x00030830), as in the sibling water-object units.
void Rva00030830FreeAllocation(void *);
namespace _STL {
 template<> inline void allocator<int>::deallocate(int *p, size_type) const { if (p) Rva00030830FreeAllocation(p); }
}

// 12-byte element whose out-of-line default constructor is the ICF-folded
// trivial ctor 0x0047A6A9 (rowed as ??0ICoord3D@@QAE@XZ among others).
#include "../../../../Libraries/Include/Lib/ICoord3D.h"
#include "../../../../../reference/shims/wwmath/Vector2.h"

struct Rva0009D55BVec3
{
	float x, y, z;
	Rva0009D55BVec3(float v) : x(v), y(v), z(v) {}
	Rva0009D55BVec3 &operator=(const Rva0009D55BVec3 &v) { x = v.x; y = v.y; z = v.z; return *this; }
};

struct Rva0009D55BPair
{
	int a, b;
	Rva0009D55BPair() : a(0), b(0) {}
};

class Rva0009AB6B { public: void rva0009AB85(); };
class TextureBaseClass { public: void Release_Ref(); };

#define D55B_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define D55B_SLOTS16(p) D55B_SLOTS4(p##0) D55B_SLOTS4(p##1) D55B_SLOTS4(p##2) D55B_SLOTS4(p##3)

// The ref-counted words: slot 0 deletes, the count is at +4.
class Rva0009D6FARef
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_numRefs == 0) Delete_This(); }
	int m_numRefs;
};
class Rva0009D6FARenderObj : public Rva0009D6FARef
{
public:
	D55B_SLOTS16(r0) D55B_SLOTS16(r1) D55B_SLOTS16(r2) D55B_SLOTS16(r3)
	D55B_SLOTS16(r4) D55B_SLOTS16(r5) D55B_SLOTS16(r6)
	D55B_SLOTS4(r70) D55B_SLOTS4(r71) virtual void r720(); virtual void r721();
	virtual bool isInScene();	// slot 123
};
class Rva0009D6FAScene : public Rva0009D6FARef
{
public:
	virtual void s1(); virtual void s2();
	virtual void removeRenderObject(Rva0009D6FARenderObj *obj);	// slot 3
	virtual void s4(); virtual void s5();
	virtual void slot6(const Rva0009D55BVec3 &color);	// slot 6
};
struct Rva0009D6FATexture
{
	Rva0009D6FATexture() : m_ptr(0) {}
	~Rva0009D6FATexture() { if (m_ptr) m_ptr->Release_Ref(); }
	TextureBaseClass *m_ptr;
};
#define D55B_REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

class LivingWorld
{
public:
	LivingWorld();
	virtual ~LivingWorld();
	virtual void rva002BF391(bool active);	// the state handler 0x002BF391

private:
	char m_body[0xC0 - 4];
};

class Rva0009D55BProduct : public LivingWorld
{
public:
	Rva0009D55BProduct();
	virtual ~Rva0009D55BProduct();
	virtual void rva0009C784(unsigned int phase, unsigned int previous);
	virtual void rva0009D862();
	virtual void rva0009DB5A(bool active);
	virtual void rva0009BC17();
	virtual void rva0009C144();
	virtual void rva0009C4FC(int x, int y, int width, int height);
	void rva0009BAA4();
	virtual void rva0009C422(bool active);
	virtual void rva0009BD98(const Vector2 *, float);

private:
	Rva0009D6FARef *m_C0;
	Rva0009D6FAScene *m_C4;
	Rva0009D6FARenderObj *m_C8;
	Rva0009D6FARenderObj *m_CC;
	Rva0009D6FARenderObj *m_D0;
	int m_D4;
	float m_D8;
	float m_DC;
	Rva0009D55BVec3 m_E0;
	Rva0009D55BVec3 m_EC;
	Rva0009D55BVec3 m_F8;
	Rva0009D55BVec3 m_104;
	Rva0009D55BVec3 m_110;
	float m_11C;
	float m_120;
	char m_pad124[0x134 - 0x124];
	float m_134;
	float m_138;
	float m_13C;
	ICoord3D m_140[4];
	char m_pad170[0x188 - 0x170];
	int m_188;
	int m_18C;
	int m_190;
	int m_194;
	float m_198;
	int m_19C;
	float m_1A0;
	float m_1A4;
	float m_1A8;
	float m_1AC;
	Rva0009D55BPair m_1B0;
	Rva0009D55BPair m_1B8;
	std::vector<int> m_1C0;
	int m_1CC;
	Rva0009D6FATexture m_1D0;
};



// ?rva0009C784@Rva0009D55BProduct@@UAEXII@Z retail 0x0009C784 (144 bytes,
// ret 8; slot 19 of the product table 0x00BC89C8): after the rowed
// LivingWorld handler 0x002BE7FA, phase 2 clears the +0x198 fade, starts
// the "FadeInGameMovie" transition group (rowed setGroup / enable) and hides
// the engine mouse; phase 3 sets the fade to 1, clears +0x134/+0x138 and
// calls the table's slot 10 with true.
class Rva002BE7FA { public: void rva002BE7FA(unsigned int a, unsigned int b); };
class GameWindowTransitionsHandler { public: void setGroup(AsciiString name, bool immediate); };
extern GameWindowTransitionsHandler *TheTransitionHandler;
class Rva001DBB82OneSetter { public: void enable(); };
class Mouse { public: void _bfme_setEngineVisibility(bool visible); };
extern Mouse *TheMouse;
class Rva0009C784Slots
{
public:
	D55B_SLOTS4(v0) D55B_SLOTS4(v1) virtual void v20(); virtual void v21();
	virtual void slot10(bool flag);
};

void Rva0009D55BProduct::rva0009C784(unsigned int phase, unsigned int previous)
{
	((Rva002BE7FA *)this)->rva002BE7FA(phase, previous);
	if (phase == 2)
	{
		m_198 = 0.0f;
		TheTransitionHandler->setGroup(AsciiString("FadeInGameMovie"), false);
		((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
		TheMouse->_bfme_setEngineVisibility(false);
	}
	else if (phase == 3)
	{
		m_198 = 1.0f;
		m_134 = 0.0f;
		m_138 = 0.0f;
		((Rva0009C784Slots *)this)->slot10(true);
	}
}

// ?rva0009D862@Rva0009D55BProduct@@UAEXXZ retail 0x0009D862 (319 bytes, EH;
// slot 4 of the product table): after the rowed shutdown 0x0009AB85 it
// creates the camera (+0xC0, CameraClass), the scene built on this (+0xC4,
// rowed 0x0009AA0F) and three lights (+0xC8/+0xCC/+0xD0, LightClass type 1),
// sets +0x134 to 1, copies the +0x104 vector to +0xF8 and runs the pinned
// refreshes 0x0009BAA4 and 0x0009CD9B.
class CameraClass { public: CameraClass(); void Set_Clip_Planes(float znear, float zfar); void Set_View_Plane(float hfov, float vfov); void Set_Viewport(const Vector2 &min, const Vector2 &max); void Set_Aspect_Ratio(float ratio); float Get_Aspect_Ratio() const; char m_data[0x3FC]; };
class Rva0009AA0F { public: Rva0009AA0F(int owner); char m_data[0x10C]; };
class LightClass { public: enum LightType { POINT = 0, DIRECTIONAL = 1 }; LightClass(LightType type); char m_data[0x120]; };
class Matrix3D;
class Rva0009C134Host { public: void rva0009BAA4(); void rva0009CD9B(); void rva0009AACF(int obj, float opacity); void buildCameraTransform(Matrix3D &tm, float distance, float pitch); };


// ?rva0009DB5A@Rva0009D55BProduct@@UAEX_N@Z retail 0x0009DB5A (154 bytes,
// ret 4): deactivation first resets the view (rowed 0x0009DA28); the
// LivingWorld handler 0x002BF391 (unrowed, pinned) always runs, but only a
// change of the +0x18 state continues: activation runs the manager's
// rowed cleanup and, with the global data's +0x60 shadow flag, copies the
// manager's +0x1E4 word into the shadow manager, places its light at
// +0x1A0..+0x1A8 and adds the shadows (rowed 0x0009DB47); deactivation runs
// the manager's 0x002141D1 and resets the view again.
class Rva0009D9BD { public: void rva0009DA28(); void rva0009DB47(); };
class LivingWorldManager { public: void rva002142EA(); };
extern LivingWorldManager *TheLivingWorldManager;
class Rva002141D1 { public: void rva002141D1(); };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;
class W3DGameClientShadowShim { public: void setLightPosition(int index, float x, float y, float z); };
struct Rva0009DB5AShadowView { void *m_vtbl; int m_04; };
struct Rva0009DB5AGlobalView { unsigned char m_pad[0x60]; bool m_shadows; };
struct Rva0009DB5AManagerView { unsigned char m_pad[0x1E4]; int m_1E4; };
struct Rva0009DB5ALivingWorldView { unsigned char m_pad[0x18]; bool m_active; bool m_viewMode; };

void Rva0009D55BProduct::rva0009DB5A(bool active)
{
	if (!active)
		((Rva0009D9BD *)this)->rva0009DA28();
	if (((Rva0009DB5ALivingWorldView *)this)->m_active == active)
	{
		LivingWorld::rva002BF391(active);
		return;
	}
	LivingWorld::rva002BF391(active);
	if (active)
	{
		TheLivingWorldManager->rva002142EA();
		if (((Rva0009DB5AGlobalView *)TheWritableGlobalData)->m_shadows)
		{
			((Rva0009DB5AShadowView *)TheW3DShadowManager)->m_04 = ((Rva0009DB5AManagerView *)TheLivingWorldManager)->m_1E4;
			((W3DGameClientShadowShim *)TheW3DShadowManager)->setLightPosition(0, m_1A0, m_1A4, m_1A8);
			((Rva0009D9BD *)this)->rva0009DB47();
		}
	}
	else
	{
		((Rva002141D1 *)TheLivingWorldManager)->rva002141D1();
		((Rva0009D9BD *)this)->rva0009DA28();
	}
}

// ?rva0009BC17@Rva0009D55BProduct@@UAEXXZ retail 0x0009BC17 (385 bytes;
// slot 8 of the product table): with the camera (+0xC0), the scene (+0xC4)
// and the +0x18 active state it raises the byte at 0x00DB5F84, clears colour,
// depth and stencil to black (DX8Wrapper::Clear 0x0011D330), blends +0x13C
// and +0xD8 from the float triples at 0x00DE5E38 and 0x00DE5E2C by the +0x198
// fade (row 1 when the global data's +0xD2E byte is set), sets the opacity of
// the three render words +0x18C/+0x190/+0x194 from +0x134 through 0x0009AACF
// (a member that ignores this, ret 8), passes +0xE0 to scene slot 6, runs the
// pinned refresh 0x0009BAA4 and renders the scene through 0x00118660.
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};
class DX8Wrapper
{
public:
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};
bool Rva00118660Call(void *scene, void *camera);
extern bool ShaderOverbrightEnabled;
extern float g_Va00DE5E2C[3];
extern float g_Va00DE5E38[3];
float g_Va00DB4AB4 = 0.6000000238418579f;	// retail RVA 0x009B4AB4 (.data), defined here
static inline float Rva0009BC17Lerp(float a, float b, float t) { return (b - a) * t + a; }
struct Rva0009BC17GlobalView { unsigned char m_pad[0xD2E]; bool m_D2E; };


// ?rva0009BAA4@Rva0009D55BProduct@@QAEXXZ retail 0x0009BAA4 (371 bytes; the
// refresh slots 8 and 9 and the setup 0x0009D862 run, pinned there as
// Rva0009C134Host::rva0009BAA4): eases the +0x134 zoom through the rowed
// 0x0009AAA8 into a distance between +0xD8 and +0xDC and a pitch from +0x13C
// towards 0 (TheLivingWorldManager's +0x38 float under +0x19); with a
// camera it sets the clip planes (10, 1.5 * distance + 2000) and a 50-degree
// view plane, builds the camera transform from an identity matrix through
// 0x0009B510, hands it to camera slot 21 and pokes TheAudio's slot 22.
class Matrix3D
{
public:
	__declspec(dllimport) __forceinline explicit Matrix3D(bool identity) { if (identity) Make_Identity(); }
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
private:
	struct RowType
	{
		float X, Y, Z, W;
		__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	};
	RowType Row[3];
};
class Rva0009BAA4CameraSlots
{
public:
	D55B_SLOTS16(c0) D55B_SLOTS4(c1) virtual void c20();
	virtual void Set_Transform(const Matrix3D &m);	// slot 21
};
class AudioManager;
extern AudioManager *TheAudio;
class Rva0009BAA4AudioSlots
{
public:
	D55B_SLOTS16(a0) D55B_SLOTS4(a1) virtual void a20(); virtual void a21();
	virtual void slot22();
};
float __cdecl Rva0009AAA8Get(float x);
struct Rva0009BAA4HostView { unsigned char m_pad[0x38]; float m_38; };
struct Rva0009BAA4LivingWorldView { unsigned char m_pad[0x19]; bool m_19; };



// ?rva0009C4FC@Rva0009D55BProduct@@UAEXHHHH@Z retail 0x0009C4FC (648 bytes,
// ret 0x10; slot 9 of the product table): the viewport sibling of slot 8.
// With the camera, the scene and both the +0x19 and +0x18 states it records
// the rectangle at +0x1B0/+0x1B8, maps it through the display size (slots
// getHeight 0x44 then getWidth 0x40) into a camera viewport clamped to 0..1
// (rowed CameraClass::Set_Viewport, Set_Aspect_Ratio of width over height),
// clears depth and stencil only and runs slot 8's blend, taking +0x13C from
// TheLivingWorldManager's +0x38 float under +0x19; the three render words
// get fixed opacities 0, 0 and 0.8 before the same scene render tail.
class Display
{
public:
	D55B_SLOTS16(d0)
	virtual unsigned int getWidth();	// slot 16
	virtual unsigned int getHeight();	// slot 17
};
extern Display *TheDisplay;
struct Rva0009C4FCLivingWorldView { unsigned char m_pad[0x18]; bool m_active; bool m_19; };


// ?rva0009C422@Rva0009D55BProduct@@UAEX_N@Z retail 0x0009C422 (218 bytes,
// ret 4; slot 20 of the product table): remembers the camera's aspect ratio
// once (+0x1AC) unless the +0x19 view mode is already on, stores the mode,
// and either copies the living-world manager's +0x34 and +0x2C/+0x30 words
// into +0x134/+0xF8/+0xFC and refreshes (0x0009BAA4), or restores the full
// viewport and saved aspect ratio and calls the table's slot 7.
class Rva0009C422Slots
{
public:
	D55B_SLOTS4(v0) virtual void v4(); virtual void v5(); virtual void v6();
	virtual void slot7();
};


// Native 0009BD98..0009BF33, RET8: camera pan and angle update at slot11
// of BC89C8, installed by the owned397B constructor0009D55B. Native factory
// 0004C8DD and the LivingWorld base establish the class relationship; the
// original derived class and method names remain unknown. This extends the
// bank's native/WB reconstruction using canonical Vector2 and ICoord3D.
class Rva0009BD98Slots
{
public:
	D55B_SLOTS16(s0) D55B_SLOTS4(s1) virtual void s20(); virtual void s21();
	virtual void rva0009B023(const Vector3 *pos);	// slot 22
};
class Rva00213A85 { public: void rva00213B88(void *point); };
// Native mutable tuning values DB4AB0/DB4AAC; original identifiers unknown.
float BfmeCameraPanRotationRate = 1.0f;
float BfmeCameraPanRotationLimit = 1.0f;


// MSVC 7.1 evaluates Y before X in the returned Vector2 constructor;
// retain that form and the X-then-Y position updates for native SSE ordering.
struct PanRotation
{
    static __forceinline float sine(float a) { return sinf(a); }
    static __forceinline float cosine(float a) { return cosf(a); }

    static __forceinline Vector2 core(const Vector2 &p, float s, float c)
    {
        return Vector2(c * p.X - s * p.Y, c * p.Y + s * p.X);
    }
    static __forceinline Vector2 rotate(const Vector2 &p, float a)
    {
        return core(p, sine(a), cosine(a));
    }
};
void Rva0009D55BProduct::rva0009BD98(const Vector2 *pan, float rotation)
{
	if (pan == 0)
		return;
	Vector2 step(pan->X * 0.5f, pan->Y * 0.5f);
	if (step.X != 0.0f || step.Y != 0.0f)
	{
		Vector3 pos;
		pos.X = m_F8.x;
		pos.Y = m_F8.y;
		pos.Z = m_F8.z;
		step = PanRotation::rotate(step, -m_11C);
		float scale = (m_134 * 4.0f + 1.0f) * 0.25f;
		pos.X = step.X * scale + pos.X;
		pos.Y = pos.Y - step.Y * scale;
		((Rva0009BD98Slots *)this)->rva0009B023(&pos);
		if (TheLivingWorldManager)
		{
			Vector2 point(pos.X, pos.Y);
			((Rva00213A85 *)TheLivingWorldManager)->rva00213B88(&point);
		}
	}
	m_11C = BfmeCameraPanRotationRate * rotation + m_11C;
	if (-BfmeCameraPanRotationLimit > m_11C)
		m_11C = -BfmeCameraPanRotationLimit;
	if (m_11C > BfmeCameraPanRotationLimit)
		m_11C = BfmeCameraPanRotationLimit;
}
