// cl: /O1 /G7 /arch:SSE /EHsc /MD
//
// ?rva002B3638@Rva002B5BBA@@QAE?AUTreeHintRef00217D4C@@XZ, retail
// 0x002B3638..0x002B3669 (49 bytes, RET 4) and
// ?rva002B5BBA@Rva002B5BBA@@QAEXXZ, retail 0x002B5BBA..0x002B5C1D (99 bytes,
// RET 0). The owner keeps a queue of message references at +0x154 (begin /
// end / capacity; erase is the rowed 0x004F70D1) and the current message at
// +0x160. 0x002B3638 returns the first queued reference by value (a counted
// copy, +4 is the referent's count) or a null one; 0x002B5BBA takes it and,
// when set, shows it (rowed 0x004FBD3A), makes it current (rowed
// TreeHintRef00217D4C::operator= 0x002174A4) and pops the queue front; the
// local reference is released through the rowed 0x0007DEEF.
// Evidence (target): retail bytes, the +0x154/+0x160 offsets shared with the
// rowed gate 0x002B4C09 and its dispatcher 0x002B6875 (which calls 0x002B5BBA
// under this name), and the WorldBuilder twin 0xD81E30 (same calls, same
// order). Owner and message class identities are not established: names stay
// address-derived.
// The getter and operator= (same bytes as 0x002174A4, as in
// PAUTreeHintRef00217D4CRva004F9565.cpp) are visible here: cl then knows
// neither keeps the local reference's address and holds its pointer in EDI
// across the calls, as retail does.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}
inline __declspec(noinline) TreeHintRef00217D4C &TreeHintRef00217D4C::operator=(const TreeHintRef00217D4C &other)
{
	if (this != &other) {
		if (other.m_ptr)
			++other.m_ptr->references;
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
		m_ptr = other.m_ptr;
	}
	return *this;
}


#include "../../Include/GameLogic/Rva004FBC02.h"

class Rva004F70D1
{
public:
	bool empty() const { return m_begin == m_finish; }
	TreeHintRef00217D4C &front() { return *m_begin; }
	TreeHintRef00217D4C *rva004F70D1(TreeHintRef00217D4C *pos);
	TreeHintRef00217D4C *m_begin;
	TreeHintRef00217D4C *m_finish;
	TreeHintRef00217D4C *m_eos;
};

class Rva002B5BBA
{
public:
	TreeHintRef00217D4C rva002B3638();
	void rva002B5BBA();
private:
	char m_pad00[0x154];
	Rva004F70D1 m_queue;			// +0x154
	TreeHintRef00217D4C m_current;	// +0x160
};

TreeHintRef00217D4C Rva002B5BBA::rva002B3638()
{
	if (!m_queue.empty())
		return m_queue.front();
	return TreeHintRef00217D4C();
}

void Rva002B5BBA::rva002B5BBA()
{
	TreeHintRef00217D4C ref = rva002B3638();
	if (ref.m_ptr != 0) {
		((Rva004FBC02 *)ref.m_ptr)->rva004FBD3A();
		m_current = ref;
		m_queue.rva004F70D1(m_queue.m_begin);
	}
}
