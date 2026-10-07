// cl: /MD /EHsc /DNDEBUG
// ?rva00085947@Rva00085947@@QAEXXZ @0x00085947 174B thiscall method.
// Vtable slot 26 of the 187-slot vtable at VA 0x00BC7514 (same vtable as range-2
// neighbours 0x86245/0x8B1E5/0x8CE2E/0x8A2EF/0x89E2A/0x86BC5/0x865DB/0x8691F).
// Virtuals used: slot56(+0xE0,int) slot50(+0xC8,int,int,float,float)
// slot47(+0xBC,int) slot111(+0x1BC,FloatPair*). Direct callees all rowed:
// BfmeThingBFG::rva0025F3F3 0x25F3F3, Rva0030E8DF::rva0030E8DF 0x30E8DF
// (subobject +0x2458), Rva00BCF670CameraSettings::reset 0x101A20 + slot17
// (subobject +0x24C8). Float +0x2408 is 10.0f compiler literal (retail .rdata 0xBC2428).
// Owner identity unproven; honest address-derived names. Boundary verified:
// push ebp prologue at 0x85947, pop edi/esi/ebx + leave + ret at 0x859F0-0x859F4.

class BfmeThingBFG { public: void rva0025F3F3(); };
class Rva0030E8DF { public: void rva0030E8DF(); };
struct RvaFloatPair { float a; float b; };
struct RvaLoc12 { int a; int b; int c; };
class Vector3 { public: float x; float y; float z; };
class RenderObjClass {
public:
	Vector3 Get_Position() const;
};
class W3DView {
	void setCameraTransform();
	friend class Rva00085947;
};
class Rva0025EB36 {
public:
	void rva0025EB36();
};

struct Rva00087CF7Vec3
{
	__forceinline Rva00087CF7Vec3(const Rva00087CF7Vec3 &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	float x, y, z;
};

struct Rva00087CF7Vec4 : Rva00087CF7Vec3
{
	__forceinline Rva00087CF7Vec4(const Rva00087CF7Vec3 &position, float value)
		: Rva00087CF7Vec3(position), w(value) {}
	float w;
};

static __forceinline Rva00087CF7Vec3 copyRva00087CF7Position(
	const Rva00087CF7Vec3 &position)
{
	return position;
}

class Rva00087CF7Probe
{
public:
	virtual void slot000() = 0;
	virtual void slot001() = 0;
	virtual void slot002() = 0;
	virtual void slot003() = 0;
	virtual void slot004() = 0;
	virtual void slot005() = 0;
	virtual void slot006() = 0;
	virtual void slot007() = 0;
	virtual void slot008() = 0;
	virtual void slot009() = 0;
	virtual void slot010() = 0;
	virtual void slot011() = 0;
	virtual void slot012() = 0;
	virtual void slot013() = 0;
	virtual void slot014() = 0;
	virtual void slot015() = 0;
	virtual void slot016() = 0;
	virtual void slot017() = 0;
	virtual void slot018() = 0;
	virtual void slot019() = 0;
	virtual void slot020() = 0;
	virtual void slot021() = 0;
	virtual void slot022() = 0;
	virtual void slot023() = 0;
	virtual void slot024() = 0;
	virtual void slot025() = 0;
	virtual void slot026() = 0;
	virtual void slot027() = 0;
	virtual void slot028() = 0;
	virtual void slot029() = 0;
	virtual void slot030() = 0;
	virtual void slot031() = 0;
	virtual void slot032() = 0;
	virtual void slot033() = 0;
	virtual void slot034() = 0;
	virtual void slot035() = 0;
	virtual void slot036() = 0;
	virtual void slot037() = 0;
	virtual void slot038() = 0;
	virtual void slot039() = 0;
	virtual void slot040() = 0;
	virtual void slot041() = 0;
	virtual void slot042() = 0;
	virtual void slot043() = 0;
	virtual void slot044() = 0;
	virtual void slot045() = 0;
	virtual void slot046() = 0;
	virtual void slot047() = 0;
	virtual void slot048() = 0;
	virtual void slot049() = 0;
	virtual void slot050() = 0;
	virtual void slot051() = 0;
	virtual void slot052() = 0;
	virtual void slot053() = 0;
	virtual void slot054() = 0;
	virtual void slot055() = 0;
	virtual void slot056() = 0;
	virtual void slot057() = 0;
	virtual void slot058() = 0;
	virtual void slot059() = 0;
	virtual void slot060() = 0;
	virtual void slot061() = 0;
	virtual void slot062() = 0;
	virtual void slot063() = 0;
	virtual void slot064() = 0;
	virtual void slot065() = 0;
	virtual void slot066() = 0;
	virtual void slot067() = 0;
	virtual void slot068() = 0;
	virtual void slot069() = 0;
	virtual void slot070() = 0;
	virtual void slot071() = 0;
	virtual void slot072() = 0;
	virtual void slot073() = 0;
	virtual void slot074() = 0;
	virtual void slot075() = 0;
	virtual void slot076() = 0;
	virtual void slot077() = 0;
	virtual void slot078() = 0;
	virtual void slot079() = 0;
	virtual void slot080() = 0;
	virtual void slot081() = 0;
	virtual void slot082() = 0;
	virtual void slot083() = 0;
	virtual void slot084() = 0;
	virtual void slot085() = 0;
	virtual void slot086() = 0;
	virtual void slot087() = 0;
	virtual void slot088() = 0;
	virtual void slot089() = 0;
	virtual void slot090() = 0;
	virtual void slot091() = 0;
	virtual void slot092() = 0;
	virtual void slot093() = 0;
	virtual void slot094() = 0;
	virtual void slot095() = 0;
	virtual void slot096() = 0;
	virtual void slot097() = 0;
	virtual void slot098() = 0;
	virtual void slot099() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual void slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115() = 0;
	virtual void slot116() = 0;
	virtual void slot117() = 0;
	virtual void slot118() = 0;
	virtual void slot119() = 0;
	virtual void slot120() = 0;
	virtual void slot121() = 0;
	virtual void slot122() = 0;
	virtual void slot123() = 0;
	virtual void slot124() = 0;
	virtual void slot125() = 0;
	virtual void slot126() = 0;
	virtual void slot127() = 0;
	virtual void slot128() = 0;
	virtual bool slot129(const Rva00087CF7Vec4 *value) = 0;
};
class Rva00BCF670CameraSettings {
public:
	virtual void camSlot00();
	virtual void camSlot01();
	virtual void camSlot02();
	virtual void camSlot03();
	virtual void camSlot04();
	virtual void camSlot05();
	virtual void camSlot06();
	virtual void camSlot07();
	virtual void camSlot08();
	virtual void camSlot09();
	virtual void camSlot10();
	virtual void camSlot11();
	virtual void camSlot12();
	virtual void camSlot13();
	virtual void camSlot14();
	virtual void camSlot15();
	virtual void camSlot16();
	virtual void camSlot17();
	virtual void camSlot18(int v, void *p);
	virtual bool camSlot19(int v, RvaLoc12 *loc);
	void reset();
};
class Rva00085947 {
public:
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void vslot032();
	virtual void vslot033();
	virtual void vslot034();
	virtual void vslot035();
	virtual void vslot036();
	virtual void vslot037();
	virtual void vslot038();
	virtual void vslot039();
	virtual void vslot040();
	virtual void vslot041();
	virtual void vslot042();
	virtual void vslot043();
	virtual void vslot044();
	virtual void vslot045();
	virtual void vslot046();
	virtual void vslot47(int v);
	virtual void vslot048();
	virtual void vslot049();
	virtual void vslot50(int a, int b, float c, float d);
	virtual void vslot051();
	virtual void vslot052();
	virtual void vslot053();
	virtual void vslot054();
	virtual void vslot055();
	virtual void vslot56(int v);
	virtual void vslot057();
	virtual void vslot058();
	virtual void vslot059();
	virtual void vslot060();
	virtual void vslot061();
	virtual void vslot062();
	virtual void vslot063();
	virtual void vslot064();
	virtual void vslot065();
	virtual void vslot066();
	virtual void vslot067();
	virtual void vslot068();
	virtual void vslot069();
	virtual void vslot070(RvaLoc12 *loc);
	virtual void vslot071();
	virtual void vslot072();
	virtual void vslot073();
	virtual void vslot074();
	virtual void vslot075();
	virtual void vslot076();
	virtual void vslot077();
	virtual void vslot078();
	virtual void vslot079();
	virtual void vslot080();
	virtual void vslot081();
	virtual void vslot082();
	virtual void vslot083();
	virtual void vslot084();
	virtual void vslot085();
	virtual void vslot086();
	virtual void vslot087();
	virtual void vslot088();
	virtual void vslot089();
	virtual void vslot090();
	virtual void vslot091();
	virtual void vslot092();
	virtual void vslot093();
	virtual void vslot094();
	virtual void vslot095();
	virtual void vslot096();
	virtual void vslot097();
	virtual void vslot098();
	virtual void vslot099();
	virtual void vslot100();
	virtual void vslot101();
	virtual void vslot102();
	virtual void vslot103();
	virtual void vslot104();
	virtual void vslot105();
	virtual void vslot106();
	virtual void vslot107();
	virtual void vslot108();
	virtual void vslot109();
	virtual void vslot110();
	virtual void vslot111(RvaFloatPair *p);
	void rva00085947();
	bool rva000879A9(int v);
	Vector3 *rva00087D42();
	void rva0008D253();
	bool rva00087CF7(const Rva00087CF7Vec3 *position, float value);
private:
	unsigned char m_pad004[0x8];
	RvaLoc12 m_00C;
	unsigned char m_pad018[0x28 - 0x18];
	int m_028;
	unsigned char m_pad02C[0x6C - 0x2C];
	float m_06C;
	float m_070;
	unsigned char m_pad074[0xA0 - 0x74];
	float m_0A0;
	unsigned char m_pad0A4[0x104 - 0xA4];
	RenderObjClass *m_p104;
	unsigned char m_pad108[0x138 - 0x108];
	float m_138;
	unsigned char m_pad13C[0x23E8 - 0x13C];
	float m_23E8;
	float m_23EC;
	unsigned char m_pad23F0[0x2408 - 0x23F0];
	float m_2408;
	unsigned char m_pad240C[0x241C - 0x240C];
	unsigned char m_241C;
	unsigned char m_pad241D[0x2458 - 0x241D];
	unsigned char m_pad2458[0x24BC - 0x2458];
	int m_24BC;
	int m_pad24C0;
	int m_24C4;
	Rva00BCF670CameraSettings m_24C8;
};

// ?rva000879A9@Rva00085947@@QAE_NH@Z @0x000879A9 61B: slot 158 of vtable 0xBC7514.
// Fills a 12-byte local through slot70, probes CameraSettings slot19 with it plus
// the int argument, copies to +0x0C when accepted, returns the probe result.
void Rva00085947::rva00085947()
{
	((BfmeThingBFG *)this)->rva0025F3F3();
	m_24BC = 0;
	vslot56(1);
	m_24C8.camSlot17();
	vslot50(0, 0, 0.0f, 0.0f);
	vslot47(9);
	RvaFloatPair p;
	p.a = 0.0f;
	p.b = 0.0f;
	vslot111(&p);
	m_138 = 0.0f;
	m_24C4 = 0;
	m_2408 = 10.0f;
	((Rva0030E8DF *)((unsigned char *)this + 0x2458))->rva0030E8DF();
	m_241C = 0;
	m_24C8.reset();
}

// ?rva000879A9@Rva00085947@@QAE_NH@Z @0x000879A9 61B: slot 158 of vtable 0xBC7514.
// Fills a 12-byte local through slot70, probes CameraSettings slot19 with it plus
// the int argument, copies to +0x0C when accepted, returns the probe result.
bool Rva00085947::rva000879A9(int v)
{
	RvaLoc12 loc;
	vslot070(&loc);
	bool ok = m_24C8.camSlot19(v, &loc);
	if (ok)
		m_00C = loc;
	return ok;
}

// ?rva00087D42@Rva00085947@@QAE?AVector3@@XZ @0x00087D42 94B: slot 94 of
// vtable 0xBC7514. Caches the +0x104 RenderObjClass position into .data
// floats on first call (atexit-guarded) and returns their address.
static Vector3 g_00DE2068;
static int g_00DE2074;
extern "C" void rva00BB6C15Cleanup();
extern "C" int __cdecl atexit(void (__cdecl *)());
#pragma comment(linker, "/alternatename:_atexit=__atexit")
Vector3 *Rva00085947::rva00087D42()
{
	Vector3 pos = m_p104->Get_Position();
	if (!(g_00DE2074 & 1)) {
		g_00DE2074 |= 1;
		atexit(rva00BB6C15Cleanup);
	}
	g_00DE2068.x = pos.x;
	g_00DE2068.y = pos.y;
	g_00DE2068.z = pos.z;
	return &g_00DE2068;
}
extern "C" void rva00BB6C15Cleanup() {}

// ?rva0008D253@Rva00085947@@QAEXXZ @0x0008D253 101B: slot 100 of vtable
// 0xBC7514. Frameless thiscall ending in a tail jump to W3DView::
// setCameraTransform. Runs the View helper, probes CameraSettings slot18,
// folds +0xA0 into +0x23E8/EC, plants the 1.0f and 0.87266463f defaults.
void Rva00085947::rva0008D253()
{
	((Rva0025EB36 *)this)->rva0025EB36();
	m_24C8.camSlot18(0, &m_028);
	m_23E8 *= m_0A0;
	m_23EC *= m_0A0;
	m_070 = 1.0f;
	m_06C = 0.87266463f;
	((W3DView *)this)->setCameraTransform();
}

// Native 87CF7..87D42, slot 93 of BC7514: extend the three input floats
// by one scalar, dispatch through this+104 at slot204, and invert AL.
// Original owner, vector types and probe method identity remain unknown.
bool Rva00085947::rva00087CF7(const Rva00087CF7Vec3 *position, float value)
{
	Rva00087CF7Vec4 vector(copyRva00087CF7Position(*position), value);
	return !reinterpret_cast<Rva00087CF7Probe *>(m_p104)->slot129(&vector);
}
