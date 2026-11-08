// cl: /MD /EHsc
// ??1Rva0033F33D@@UAE@XZ @0x003401E4 75B: Rva0033F33D public virtual dtor.
// Native ctor 0x0033F33D uses State, hash 0x6D9C1CB9 and table 0x00810EE0.
// The member at +0x20 is released through slot 0 then global delete.
// The base teardown at 0x0049B47C is the rowed State destructor.
// Both lifecycle units declare native xfer slot 3 at 0x0034027D.
// Unblocks deleting dtor at 0x003428F1.
class StateMachine;
#include "../../Include/Common/StateMachine.h"

class Rva0033F33DMember {
public:
	virtual void *v0(int);
};
class Rva0033F33D : public State {
public:
	virtual ~Rva0033F33D();
protected:
	virtual void xfer(Xfer *xfer);
private:
	Rva0033F33DMember *m_20;
};
#include <new>
Rva0033F33D::~Rva0033F33D()
{
	if (m_20) {
		void *p = m_20->v0(0);
		::operator delete(p);
		m_20 = 0;
	}
}
