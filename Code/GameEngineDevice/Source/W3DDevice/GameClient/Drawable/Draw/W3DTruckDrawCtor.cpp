// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG
// ??0W3DTruckDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0x000CB3FB 381B: LINK body, vtable slot ctor; evidence: base ??0W3DScriptedModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z pin 0x000C0DD8, three vptrs +0/+0xC/+0x10, bools +0x2E8, handles +0x2EC/+0x2F8/+0x304, zeros +0x310-+0x370, two BfmeAudioEventPrefix136 +0x374/+0x3FC via rowed 0x002D97D6, int +0x484; donor /workspace/reference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTruckDrawConstructor.cpp plus Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTruckDrawDtor.cpp layout
class Thing;
class ModuleData;
class OpaqueRefCounted
{
public:
	void Release_Ref();
};
struct OpaqueRefElement4
{
	OpaqueRefCounted *referent;
};
struct BfmePoolRef08
{
	OpaqueRefCounted *m_target;
	BfmePoolRef08() : m_target(0) {}
	~BfmePoolRef08() { if (m_target != 0) m_target->Release_Ref(); }
};
struct BfmeAudioEventPrefix136
{
	BfmeAudioEventPrefix136(const OpaqueRefElement4 &arg, int v);
	virtual ~BfmeAudioEventPrefix136();
	char m_pad[0x88 - 4];
};
class DrawModule
{
public:
	virtual ~DrawModule();
private:
	char m_pad[8];
};
class DrawInterfaceC
{
public:
	virtual void slotC();
};
class DrawInterface8C
{
public:
	virtual void slot8C();
};
class W3DScriptedModelDraw : public DrawModule, public DrawInterfaceC, public DrawInterface8C
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DScriptedModelDraw();
private:
	char m_pad[0x2E8 - 0x0C - 0x04 - 0x04];
};
struct BfmeParticleSystemHandle
{
	BfmeParticleSystemHandle(void *system) { m_system = system; m_next = 0; m_previous = 0; }
	~BfmeParticleSystemHandle();
	void *m_system;
	void *m_previous;
	void *m_next;
};
class W3DTruckDraw : public W3DScriptedModelDraw
{
public:
	W3DTruckDraw(Thing *thing, const ModuleData *moduleData);
private:
	bool m_effectsInitialized;
	bool m_wasAirborne;
	bool m_isPowersliding;
	char m_pad2EB;
	BfmeParticleSystemHandle m_dust;
	BfmeParticleSystemHandle m_dirt;
	BfmeParticleSystemHandle m_power;
	float m_f310;
	float m_f314;
	float m_f318;
	float m_f31C;
	int m_i320;
	int m_i324;
	int m_i328;
	int m_i32C;
	int m_i330;
	int m_i334;
	int m_i338;
	int m_i33C;
	int m_i340;
	int m_i344;
	int m_i348;
	int m_i34C;
	int m_i350;
	int m_i354;
	int m_i358;
	int m_i35C;
	int m_i360;
	float m_f364;
	int m_i368;
	float m_f36C;
	int m_i370;
	BfmeAudioEventPrefix136 m_sound374;
	BfmeAudioEventPrefix136 m_sound3FC;
	int m_unk484;
};
W3DTruckDraw::W3DTruckDraw(Thing *thing, const ModuleData *moduleData)
	: W3DScriptedModelDraw(thing, moduleData)
	, m_effectsInitialized(false)
	, m_wasAirborne(false)
	, m_isPowersliding(false)
	, m_dust(0)
	, m_dirt(0)
	, m_power(0)
	, m_f310(0)
	, m_f314(0)
	, m_f318(0)
	, m_f31C(0)
	, m_i320(0)
	, m_i324(0)
	, m_i328(0)
	, m_i32C(0)
	, m_i330(0)
	, m_i334(0)
	, m_i338(0)
	, m_i33C(0)
	, m_i340(0)
	, m_i344(0)
	, m_i348(0)
	, m_i34C(0)
	, m_i350(0)
	, m_i354(0)
	, m_i358(0)
	, m_i35C(0)
	, m_i360(0)
	, m_f364(0)
	, m_i368(0)
	, m_f36C(0)
	, m_i370(0)
	, m_sound374((const OpaqueRefElement4 &)BfmePoolRef08(), 0)
	, m_sound3FC((const OpaqueRefElement4 &)BfmePoolRef08(), 0)
	, m_unk484(0)
{
}
