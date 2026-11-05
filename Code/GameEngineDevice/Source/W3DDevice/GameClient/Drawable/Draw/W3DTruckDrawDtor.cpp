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

#include "../../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"

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

#include "../../../../../../GameEngine/Include/GameClient/BfmeParticleSystemHandle.h"

struct RvaSmartPtr12
{
	void rva0004CBC0() throw(); // 0x0004CBC0, the unlink the inline dtor null test calls

	~RvaSmartPtr12() throw()
	{
		BfmeParticleSystemHandle *p = (BfmeParticleSystemHandle *)this;
		if (p->m_system != 0)
			reinterpret_cast<RvaSmartPtr12 *>(p)->rva0004CBC0();
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
public:
	// retail slot 4: the rowed ?getModuleNameKey@W3DTruckDraw@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual void doDrawModule(const Matrix3D *);
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline W3DTruckDraw::~W3DTruckDraw()
{
	((W3DTankTruckDraw *)this)->tossEmitters();
}

// ?bfmeAnchorW3DTruckDrawDtor absent-from-retail
void bfmeAnchorW3DTruckDrawDtor(W3DTruckDraw *w3DTruckDraw)
{
	w3DTruckDraw->W3DTruckDraw::~W3DTruckDraw();
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot8C@DrawInterface8C@@UAEXXZ=?rva000BFB76@Rva000BFB76Interface@@UAEXABVModelConditionFlags@@_NH@Z")
#pragma comment(linker, "/alternatename:?slotC@DrawInterfaceC@@UAEXXZ=?clientOnly_getRenderObjInfo@Rva000B34D8@@UAE_NPAVVector3@@PAMPAURva000B34D8Out30@@@Z")
