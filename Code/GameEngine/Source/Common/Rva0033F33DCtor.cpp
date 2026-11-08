// cl: /MD
//
// ??0Rva0033F33D@@QAE@PAVStateMachine@@@Z, retail 0x0033F33D, 33 bytes.
// State-derived ctor forwarding (machine, 0x6D9C1CB9) to the unsigned-hash
// twin ??0State@@QAE@PAVStateMachine@@I@Z at 0x004D73FC then zeroing dword
// at +0x20 then installing vtable 0x00810EE0. Caller is 0x0035245D.
// The compiler installs the State-derived table; the destructor uses the same
// 17-slot view. Getter and lifecycle identities still need reconciliation.

class StateMachine;

#include "../../Include/Common/StateMachine.h"

class Rva0033F33DMember;

class Rva0033F33D : public State
{
public:
	Rva0033F33D(StateMachine *machine);
	virtual ~Rva0033F33D();
protected:
	virtual void xfer(Xfer *xfer);

private:
	Rva0033F33DMember *m_20;
};

Rva0033F33D::Rva0033F33D(StateMachine *machine) : State(machine, 0x6D9C1CB9u)
{
	m_20 = 0;
}
