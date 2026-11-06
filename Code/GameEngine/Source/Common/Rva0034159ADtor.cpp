// cl: /MD /EHsc
// ??1Rva0033F540@@UAE@XZ @0x0034159A 91B: Rva0033F540 public virtual dtor.
// Vptr install plus member at +0x20 via virtual slot15 then slot0 with 0 plus
// delete 0x0002FD60, then the base State destructor (the rowed
// ??1State@@UAE@XZ, the 7-byte fold body at 0x0049B47C).
// The class derives from the canonical State (Include/Common/StateMachine.h):
// its retail table is the one the State-derived constructor 0x0033F540 installs.
// Precedent Code/GameEngine/Source/Common/Rva0034149BDtor.cpp (same 91B shape same base).
// Unblocks deleting dtor at 0x00342E74.
class StateMachine;

#include "../../Include/Common/StateMachine.h"

class Rva0034159AMember {
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
class Rva0033F540 : public State {
public:
	virtual ~Rva0033F540();
private:
	Rva0034159AMember *m_20;
};
#include <new>
Rva0033F540::~Rva0033F540()
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
