// cl: /MD /EHsc
// ??1Rva00285BEC@@UAE@XZ retail 0x00285BEC 68B
// ??0Rva00285BEC@@QAE@ABV0@@Z retail 0x00285C30 88B: copy ctor copies +8/+0xC from src then m_10=-1 then rowed rva00285708. Evidence: same vptrs BFB700/BFB6F0 plus BBB554 base plus single caller 0x00286279.
// Two-base dtor: own vptrs BFB700 at +0 and BFB6F0 at +4, then under EH
// state 1 the rowed ?rva0028572A@Rva0028572AHost 0x0028572A on this (which
// unregisters from g_00DFE1A8 when m_10 is set); the inline base dtors then
// restore BBB554 (second base at +4, the Snapshot vtable) and BFB698 (+0).
// Names address-derived.

class Rva0028572AHost
{
public:
	void rva0028572A();
};

class Rva00285708Host
{
public:
	void rva00285708();
};

#include "Rva00285BEC.h"

Rva00285BEC::Rva00285BEC(int a, int b) : m_08(a, b), m_10(-1)
{
	((Rva00285708Host *)this)->rva00285708();
}

Rva00285BEC::Rva00285BEC(const Rva00285BEC &src)
{
	m_08.m_00 = src.m_08.m_00;
	m_08.m_04 = src.m_08.m_04;
	m_10 = -1;
	((Rva00285708Host *)this)->rva00285708();
}

Rva00285BEC::~Rva00285BEC()
{
	((Rva0028572AHost *)this)->rva0028572A();
}

extern unsigned char g_00DFEA50[76];
extern unsigned char g_00DFE794[16];
#include "../../Include/GameLogic/Rva002862C9.h"
Rva00SlotFloat2FromInts Rva00285BEC::vslot00(){return Rva00SlotFloat2FromInts(m_08.m_00,m_08.m_04);}
Rva00SlotFloat2FromInts Rva00285BEC::vslot01()const{return Rva00SlotFloat2FromInts(m_08.m_00,m_08.m_04);}
unsigned char *Rva00285BEC::vslot02(){return g_00DFEA50;}
unsigned char const *Rva00285BEC::vslot03()const{return g_00DFEA50;}
unsigned char *Rva00285BEC::vslot04(){return g_00DFE794;}
unsigned char const *Rva00285BEC::vslot05()const{return g_00DFE794;}
short Rva00285BEC::vslot06()const{return 1;}
LargeGroupAudioKeyMap *Rva00285BEC::vslot07()const{return ((Rva002862C9*)this)->rva002862C9();}
bool Rva00285BEC::vslot08()const{return false;}
bool Rva00285BEC::vslot09()const{return false;}
int Rva00285BEC::vslot10()const{return m_10;}
const char*Rva00285BECSnapshotBase::GetSnapshotName()const{return "FireLogicSystem::BurningCell";}

class Rva00285CEDInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void rva00285CEDSlot10(void *out) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void rva00285CEDSlot19(void *out) = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void rva00285CEDSlot31(void *out) = 0;
};


struct Rva00285CEDFlags
{
	unsigned char first;
	unsigned char second;
};


void Rva00285BECSnapshotBase::xfer(Xfer *interfaceObject)
{
	Rva00285CEDFlags flags = { 1, 1 };
	Rva00285CEDInterface *input = (Rva00285CEDInterface *)interfaceObject;
	input->rva00285CEDSlot10(&flags);
	input->rva00285CEDSlot19((char *)this + 4);
	input->rva00285CEDSlot31((char *)this + 0xC);
}
