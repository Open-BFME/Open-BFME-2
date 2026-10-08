// cl: /MD /EHsc /Ireference/shims/moduledata
// ??1GiantBirdAttackMoveToState@@UAE@XZ @0x0036783F 79B
// Dtor: vtable 0x00817548 (slot 2 returns "GiantBirdAttackMoveToState")
// plus delete of the attack machine at +0x28 via virtual slot 0 plus
// operator delete 0x0002FD60 plus the State base dtor 0x0049B47C (ICF fold
// of the Snapshot dtor). Evidence: caller 0x003689AB; rowed base dtor plus
// delete. Slot 4 is onEnter (GiantBirdNormalFlightStates.cpp).
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
enum StateReturnType
{
	STATE_CONTINUE = 0
};
class State : public Snapshot
{
public:
	virtual ~State();
	virtual StateReturnType onEnter() = 0;
};
class GiantBirdAttackMoveToState : public State
{
public:
	virtual ~GiantBirdAttackMoveToState();
	virtual StateReturnType onEnter();
private:
	char m_pad04[0x18 - 4];
	void *m_18;
	char m_pad1C[0x24 - 0x1C];
	int m_24;
	Rva0036783FMember *m_28;
	int m_2C;
};
GiantBirdAttackMoveToState::~GiantBirdAttackMoveToState()
{
	::operator delete(m_28 ? m_28->slot00(0) : 0);
	m_28 = 0;
}
