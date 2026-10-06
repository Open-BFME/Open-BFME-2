// cl: /MD /EHsc /DNDEBUG
// ??1W3DTruckDraw@@UAE@XZ, retail 0x000CDE73, 151 bytes.
// W3DTruckDraw dtor: vptr stores at +0/+0xC/+0x10, tossEmitters, two 0x88 Audio
// members at +0x374/+0x3FC via rowed 0x2D9A43, three 12B handles at
// +0x2EC/+0x2F8/+0x304 via rowed 0x4CBC0 with null guards, base
// W3DScriptedModelDraw dtor at 0xC79C9. Layout from ctor 0xCB3FB (size 0x488,
// handles zeroed, Audios constructed, int at +0x484) and BFME1 donor
// W3DTruckDraw.h (tossEmitters-only body). Caller is deleting dtor 0xCDF34
// with vtable 0xBCC650 and pool key 0xCB578 using string W3DTruckDraw.
class Thing;
class ModuleData;

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

class BfmeStringTailRecord144
{
public:
	virtual ~BfmeStringTailRecord144();
private:
	char m_pad[0x88 - 4];
};

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle() throw();
	void *m_system;
	void *m_prev;
	void *m_next;
};

struct RvaSmartPtr12
{
	~RvaSmartPtr12() throw()
	{
		BfmeParticleSystemHandle *p = (BfmeParticleSystemHandle *)this;
		if (p->m_system != 0)
			p->~BfmeParticleSystemHandle();
	}
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class W3DTankTruckDraw
{
	friend class W3DTruckDraw;
protected:
	void tossEmitters();
};

class W3DTruckDraw : public W3DScriptedModelDraw
{
public:
	virtual ~W3DTruckDraw();
private:
	bool m_effectsInitialized;
	bool m_wasAirborne;
	bool m_isPowersliding;
	char m_pad2EB;
	RvaSmartPtr12 m_dust;
	RvaSmartPtr12 m_dirt;
	RvaSmartPtr12 m_power;
	char m_zeroSlots[0x374 - 0x310];
	BfmeStringTailRecord144 m_sound374;
	BfmeStringTailRecord144 m_sound3FC;
	int m_unk484;
};

W3DTruckDraw::~W3DTruckDraw()
{
	((W3DTankTruckDraw *)this)->tossEmitters();
}
