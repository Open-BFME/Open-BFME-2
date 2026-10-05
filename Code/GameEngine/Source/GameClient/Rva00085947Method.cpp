// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
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
	virtual void vslot070();
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
private:
	unsigned char m_pad000[0x138 - 4];
	float m_138;
	unsigned char m_pad13C[0x2408 - 0x13C];
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
