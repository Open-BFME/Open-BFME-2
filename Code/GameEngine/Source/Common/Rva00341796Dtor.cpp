// cl: /MD /EHsc
// ??1Rva00341796@@UAE@XZ @0x00341796 91B: Rva00341796 public virtual dtor.
// Vptr install plus member at +0x20 via virtual slot15 then slot0 with 0 plus delete 0x0002FD60 plus base WindModuleInfo 0x0049B47C via row.
// Precedent Code/GameEngine/Source/Common/Rva0034149BDtor.cpp (same 91B shape same base).
// Unblocks deleting dtor at 0x00342E90.
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
class Rva00341796Member {
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
class Rva00341796 : public FXParticleSystem::WindModuleInfo {
public:
	virtual ~Rva00341796();
private:
	Rva00341796Member *m_20;
};
void __cdecl operator delete(void *);
Rva00341796::~Rva00341796()
{
	if (m_20) {
		m_20->v15();
		void *p;
		if (m_20)
			p = m_20->v0(0);
		else
			p = 0;
		::operator delete(p);
		m_20 = 0;
	}
}
