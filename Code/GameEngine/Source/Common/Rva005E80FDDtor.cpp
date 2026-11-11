// ??1Rva005E80FD@@UAE@XZ
// cl: /MD /EHsc
//
// ??1Rva005E80FD@@UAE@XZ, retail 0x005E80FD 134B: MI virtual dtor with three
// vptrs (+0 +8 +0xC), two CreateAHeroData erases via 0x002B7250, vector dtor
// at +0x24 via 0x005E8005, clear at +0x20 via 0x005E7FC8, base 0x005F7750.
// Evidence: pin name; caller deleting dtor 0x005E8240; callees 0x002B7250
// twice 0x005E8005 0x005E7FC8 base 0x005F7750; three-vptr MI precedent
// Rva0056B126Dtor; secondary-base args (this+8 this+0xC) precedent Rva005D2111;
// member layout (+0x20 holder +0x24 vector) from retail lea targets.
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
struct Holder1C
{
	char m_pad[4];
	Rva002B7250 m_erase;
};
struct Holder18
{
	char m_pad[8];
	Rva002B7250 m_erase;
};
class Rva005E8005
{
public:
	~Rva005E8005();
private:
	void *m_start;
	void *m_finish;
	void *m_end;
};
class Rva005E7FC8
{
public:
	~Rva005E7FC8() { clear(); }
	void clear();
private:
	void *m_ptr;
};
class Rva005F830A
{
public:
	virtual ~Rva005F830A();
private:
	char m_pad04[4];
};
#include "../../Include/Common/Rva0057605DSecond.h"
#include "../../Include/Common/Base0C_80FD.h"
// ??0Base0C_80FD@@QAE@XZ @0x0007E126 9B: the default constructor, storing the
// class's own vtable (VA 0x00BC6F34) and returning this.
Base0C_80FD::Base0C_80FD()
{
}
namespace StrategicInGameUI { class BuildQueueDetailsPanel { public: class Impl; }; }
class StrategicInGameUI::BuildQueueDetailsPanel::Impl : public Rva005F830A, public Rva0057605DSecond, public Base0C_80FD
{
public:
	virtual ~Impl();
 virtual void rva005E716D();
 virtual void onLivingWorldBuildingNuggetSpawnArmyUnitDequeued(Rva005E72B4Queue &,int);
 virtual void onLivingWorldBuildingNuggetSpawnArmyUnitQueued(Rva005E72B4Queue &,int);
private:
	char m_pad10[0x18 - 0x10];
	Holder18 *m_holder18;
	Holder1C *m_holder1C;
	Rva005E7FC8 m_clear20;
	Rva005E8005 m_vec24;
};
StrategicInGameUI::BuildQueueDetailsPanel::Impl::~Impl()
{
	m_holder1C->m_erase.rva002B7250((CreateAHeroData *)(Base0C_80FD *)this);
	m_holder18->m_erase.rva002B7250((CreateAHeroData *)(Rva0057605DSecond *)this);
}
