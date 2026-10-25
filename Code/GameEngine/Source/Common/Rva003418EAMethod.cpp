// cl: /MD
// ?onExit@Rva00341796@@UAEXH@Z @0x003418EA 70B: Rva00341796 slot 5.
// Member at +0x20 via virtual slot15 then slot0 with 0 plus delete plus clear plus ptr chase +0x18 +0x14 +0x258 null-checked plus byte at +0x3BA cleared.
// Precedent Rva00341796 dtor member shape plus State m_machine chase.
// Vtable 0x008113B8 slot 5.
class StateMachine;
namespace FXParticleSystem {
class WindModuleInfo {
public:
	virtual ~WindModuleInfo();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};
}
class Rva003418EAMember {
public:
	virtual void *v0(int);
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
};
struct ChaseC {
	char m_pad000[0x3BA];
	bool m_canPathThroughUnits;
};
struct ChaseB {
	char m_pad000[0x258];
	ChaseC *m_258;
};
struct StateMachine {
	char m_pad000[0x14];
	ChaseB *m_14;
};
class Rva00341796 : public FXParticleSystem::WindModuleInfo {
public:
	virtual void onExit(int status);
private:
	Rva003418EAMember *m_20;
};
void __cdecl operator delete(void *);
void Rva00341796::onExit(int status)
{
	(void)status;
	if (m_20) {
		m_20->v15();
		void *memory;
		if (m_20)
			memory = m_20->v0(0);
		else
			memory = 0;
		::operator delete(memory);
		m_20 = 0;
	}
	ChaseC *chaseC = m_machine->m_14->m_258;
	if (chaseC)
		chaseC->m_canPathThroughUnits = 0;
}
