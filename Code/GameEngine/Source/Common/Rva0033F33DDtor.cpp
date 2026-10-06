// cl: /MD /EHsc
// ??1Rva0033F33D@@UAE@XZ @0x003401E4 75B: Rva0033F33D public virtual dtor.
// Donor Code/GameEngine/Source/Common/Rva0033F33DCtor.cpp ctor (State machine hash 0x6D9C1CB9 plus vtable 0x00810EE0 plus m_20 zero tail).
// Vptr install plus member at +0x20 via virtual slot0 with 0 plus delete 0x0002FD60 plus base WindModuleInfo 0x0049B47C via row.
// Unblocks deleting dtor at 0x003428F1.
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
class Rva0033F33DMember {
public:
	virtual void *v0(int);
};
extern "C" char Rva0033F33D_vftable;
class Rva0033F33D : public FXParticleSystem::WindModuleInfo {
public:
	virtual ~Rva0033F33D();
private:
	Rva0033F33DMember *m_20;
};
void __cdecl operator delete(void *);
Rva0033F33D::~Rva0033F33D()
{
	if (m_20) {
		void *p = m_20->v0(0);
		::operator delete(p);
		m_20 = 0;
	}
}
