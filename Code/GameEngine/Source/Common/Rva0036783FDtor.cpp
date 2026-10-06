// cl: /MD /EHsc /Ireference/shims/moduledata
// ??1Rva0036783F@@UAE@XZ @0x0036783F 79B
// ?v1@Rva0036783F@@UAEHXZ @0x0036960E 63B: slot 4 (v1) override: two guarded virtual dispatches plus slot-143 fetch then tail pinned rva00369064. Evidence: vtable 0x00817548 slot 4 plus donor TU layout plus rowed callees plus pin 0x00369064.
// Dtor: vtable 0x00817548 plus delete of heap member at +0x28 via virtual
// slot 0 plus operator delete 0x0002FD60 plus base WindModuleInfo dtor
// 0x0049B47C. Evidence: caller 0x003689AB; rowed base dtor plus delete.
// Slot 4 is WindModuleInfo::v1, retyped int (no args) from retail tail-jmp
// to int callee; names address-derived otherwise.
void __cdecl operator delete(void *p);
class Rva0036783FMember
{
public:
	virtual void *slot00(int flag);
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08(int zero);
};
#include "Common/Snapshot.h"
namespace FXParticleSystem
{
class WindModuleInfo : public Snapshot
{
public:
	virtual ~WindModuleInfo();
	virtual int v1() = 0;
};
}
struct Rva0036960EA
{
	char m_pad[0x14];
	void *m_14;
};
struct Rva0036960EB
{
	char m_pad[0x258];
	void *m_258;
};
class Rva0036960EEdi
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual void v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual void v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
	virtual void v129();
	virtual void v130();
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual void v137();
	virtual void v138();
	virtual void v139();
	virtual void v140();
	virtual void v141();
	virtual void v142();
	virtual int v143();
};
class Rva0036A88AOwner
{
public:
	int rva00369064();
};
class Rva0036783F : public FXParticleSystem::WindModuleInfo
{
public:
	virtual ~Rva0036783F();
	virtual int v1();
private:
	char m_pad04[0x18 - 4];
	Rva0036960EA *m_18;
	char m_pad1C[0x24 - 0x1C];
	int m_24;
	Rva0036783FMember *m_28;
	int m_2C;
};
int Rva0036783F::v1()
{
	Rva0036960EB *b = (Rva0036960EB *)m_18->m_14;
	Rva0036960EEdi *edi = (Rva0036960EEdi *)b->m_258;
	m_28->v05();
	m_28->v08(0);
	m_24 = edi->v143();
	m_2C = 5;
	return ((Rva0036A88AOwner *)this)->rva00369064();
}
Rva0036783F::~Rva0036783F()
{
	::operator delete(m_28 ? m_28->slot00(0) : 0);
	m_28 = 0;
}
