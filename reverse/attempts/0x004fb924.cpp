// ?rva004FB924@Rva004FB582Owner@@QAEXXZ
// partial score=0.88 date=2026-10-09
// stlport
// cl: /Ob1 /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <vector>
struct Rva004FB7B2Record { void *id; int unknown04; void *target; int key; int region; };
template<> bool StringBase<char>::isEmpty() const;
//
// 0x004FB582 (126B): channel-driven init. One-time init of the channel
// object at 0x00E04508 (its first byte is the done flag), three channel
// queries off the target's +0x14 field into +0x0C/+0x10/+0x14, then a
// by-value slot call on each of the +0x68/+0x74/+0x80 subobjects. All
// seven callees are pinned, not recovered; identities unproven.

class Rva0050366B
{
public:
	void rva0050366B();
};

class Rva00501DF1
{
public:
	int rva00501DF1(int v);
};

class Rva00501813
{
public:
	int rva00501813(int v);
};

class Rva00501844
{
public:
	int rva00501844(int v);
};

struct Rva004FB582Slot
{
	int m_a;	// +0x00
	int m_b;	// +0x04
};

struct Rva004FB924RegionRecord { unsigned char mode; unsigned char pad[3]; int region; int templateKey; void *key; };
struct Rva004FB924Pair { int key; class Rva004E3184 *value; };
class Rva003FA4DB
{
public:
	void rva003FA4DB(Rva004FB582Slot v);

public:
	std::vector<Rva004FB924Pair> records;
};

class Rva002BF70F
{
public:
	void rva002BF70F(Rva004FB582Slot v);

public:
	std::vector<Rva004FB924RegionRecord> records;
};

class Rva005B129F { public:
 void rva005B129F(Rva004FB582Slot);
 std::vector<Rva004FB7B2Record> records;
};

struct Rva00E04508Channel
{
	unsigned char m_initialized;	// +0x00 done flag
};

// The data ledger owns this address in Rva007B6880Thunks.cpp.
extern unsigned int g_Va00E04508;

struct Rva004FB582Target
{
	char m_pad[0x14];
	int val14;	// +0x14 queried field
};

class Rva004FB582Owner
{
public:
	void rva004FB582();
	void rva004FB7B2();
	void rva004FB924();

private:
	Rva004FB582Target *m_00;	// +0x00 (queried target)
	char m_pad04[8];		// +0x04..0x0B
	int m_0C;			// +0x0C
	int m_10;			// +0x10
	int m_14;			// +0x14
	char m_pad18[0x50];		// +0x18..0x67
	Rva003FA4DB m_68;		// +0x68
	char m_pad70[4];		// +0x70..0x73
	Rva002BF70F m_74;		// +0x74
	char m_pad7C[4];		// +0x7C..0x7F
	Rva005B129F m_80;		// +0x80
};

void Rva004FB582Owner::rva004FB582()
{
	Rva00E04508Channel *channel = (Rva00E04508Channel *)&g_Va00E04508;
	if (!channel->m_initialized)
	{
		((Rva0050366B *)channel)->rva0050366B();
		channel->m_initialized = 1;
	}
	if (m_00)
	{
		m_0C = ((Rva00501DF1 *)channel)->rva00501DF1(m_00->val14);
		m_10 = ((Rva00501813 *)channel)->rva00501813(m_00->val14);
		m_14 = ((Rva00501844 *)channel)->rva00501844(m_00->val14);
	}
	m_68.rva003FA4DB(*(Rva004FB582Slot *)&m_68);
	m_74.rva002BF70F(*(Rva004FB582Slot *)&m_74);
	m_80.rva005B129F(*(Rva004FB582Slot *)&m_80);
}

// Native 4FB7B2..4FB8A8: unsigned count of twenty-byte records at +80.
// WB131AA30 confirms order-vector traversal; field meanings below remain
// address-derived. Native calls establish member lookup and move dispatch.
struct Rva004FB7B2Range {
 Rva004FB7B2Record *first,*finish,*limit;
 unsigned size() const { return (unsigned)(finish-first); }
 Rva004FB7B2Record &operator[](unsigned index) { return first[index]; }
};
class Rva002E0A9FElem { public: int rva002E0A9F(void *); };
class Rva00318F42 { public: bool rva00318F42(); };
struct LivingWorldArmy;
class LivingWorldLogic { public: bool CanMoveArmyMember(struct LivingWorldArmy *,int,int); };
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002B4076 { public: void rva002B4076(LivingWorldArmy *,int,LivingWorldArmy *); };
class Rva0020E89C;
class Rva0020EAF6View { public: Rva0020E89C *rva0020EAF6(int); };
struct Rva004FB7B2LogicView { char pad[0xB0]; Rva0020EAF6View *regions; };
class Rva002B2702 { public: void rva002B2702(void *,void *,int); };
void Rva004FB582Owner::rva004FB7B2() {
 std::vector<Rva004FB7B2Record> &orders=m_80.records;
 unsigned count=orders.size();
 for(unsigned i=0;i<count;++i) {
  LivingWorldArmy *member=(LivingWorldArmy *)((Rva002E0A9FElem *)m_00)->rva002E0A9F(orders[i].id);
  if(member && (((Rva00318F42 *)member)->rva00318F42() || !((AsciiString *)((char *)member+0x18))->isEmpty()))continue;
  if(orders[i].target) {
   if(TheLivingWorldLogic->CanMoveArmyMember(member,orders[i].key,((Rva002E0A9FElem *)m_00)->rva002E0A9F(orders[i].target)))
    ((Rva002B4076 *)TheLivingWorldLogic)->rva002B4076(member,orders[i].key,(LivingWorldArmy *)((Rva002E0A9FElem *)m_00)->rva002E0A9F(orders[i].target));
  } else {
   ((Rva002B2702 *)TheLivingWorldLogic)->rva002B2702(member,((Rva004FB7B2LogicView *)TheLivingWorldLogic)->regions->rva0020EAF6(orders[i].region),1);
  }
 }
 m_80.rva005B129F(*(Rva004FB582Slot *)&m_80);
}

class Rva004E3184 {
public:
 Rva004E3184(const Rva004E3184 &);
 virtual ~Rva004E3184();
private: unsigned char payload[84];
};
class Rva0020EEF4Outer { public: int rva0020EEF4(int); };
class Rva004E0625 { public: int rva004E0625() const; };
class Rva004FB924Spawner {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual void spawn(const Rva004E3184 *);
};
class Rva003F1093 { public: void rva003F1CFE(void *,int); };
class Rva003F1C56Plot;
struct Rva003F1BD3TemplateView;
class LivingWorldRegion {
public: void *rva003F0588(); void BuildBuilding(Rva003F1C56Plot *,const Rva003F1BD3TemplateView *);
};
enum NameKeyType { NAMEKEY_INVALID=0,NAMEKEY_MAX=1<<23,FORCE_NAMEKEYTYPE_LONG=0x7fffffff };
class ArmorTemplate;
class Rva002B6498 { public: ArmorTemplate *rva002B6498(NameKeyType); };
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
void Rva004FB582Owner::rva004FB924() {
 if(!m_00)return;
 unsigned count=m_68.records.size();
 for(unsigned i=0;i<count;++i) {
  int region=((Rva0020EEF4Outer *)((Rva004FB7B2LogicView *)TheLivingWorldLogic)->regions)->rva0020EEF4(m_68.records[i].key);
  if(region) {
   Rva004FB924Spawner *spawner=(Rva004FB924Spawner *)((Rva004E0625 *)region)->rva004E0625();
   Rva004E3184 request(*m_68.records[i].value);
   spawner->spawn(&request);
  }
 }
 m_68.rva003FA4DB(*(Rva004FB582Slot *)&m_68);
 count=m_74.records.size();
 for(unsigned j=0;j<count;++j) {
  Rva0020E89C *region=((Rva004FB7B2LogicView *)TheLivingWorldLogic)->regions->rva0020EAF6(m_74.records[j].region);
  if(region) {
   if(m_74.records[j].mode)((Rva003F1093 *)region)->rva003F1CFE(m_74.records[j].key,1);
   else {
    void *plot=((LivingWorldRegion *)region)->rva003F0588();
    ArmorTemplate *building=((Rva002B6498 *)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)m_74.records[j].templateKey);
    ((LivingWorldRegion *)region)->BuildBuilding((Rva003F1C56Plot *)plot,(const Rva003F1BD3TemplateView *)building);
   }
  }
 }
 m_74.rva002BF70F(*(Rva004FB582Slot *)&m_74);
 std::vector<Rva004FB7B2Record> &orders=m_80.records;
 count=orders.size();
 for(unsigned i=0;i<count;++i) {
  LivingWorldArmy *member=(LivingWorldArmy *)((Rva002E0A9FElem *)m_00)->rva002E0A9F(orders[i].id);
  if(member && (((Rva00318F42 *)member)->rva00318F42() || !((AsciiString *)((char *)member+0x18))->isEmpty()))continue;
  if(orders[i].target) {
   if(TheLivingWorldLogic->CanMoveArmyMember(member,orders[i].key,((Rva002E0A9FElem *)m_00)->rva002E0A9F(orders[i].target)))
    ((Rva002B4076 *)TheLivingWorldLogic)->rva002B4076(member,orders[i].key,(LivingWorldArmy *)((Rva002E0A9FElem *)m_00)->rva002E0A9F(orders[i].target));
  } else {
   ((Rva002B2702 *)TheLivingWorldLogic)->rva002B2702(member,((Rva004FB7B2LogicView *)TheLivingWorldLogic)->regions->rva0020EAF6(orders[i].region),1);
  }
 }
 m_80.rva005B129F(*(Rva004FB582Slot *)&m_80);
}
