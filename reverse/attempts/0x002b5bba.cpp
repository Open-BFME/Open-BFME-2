// ?rva002B5BBA@Rva002B5BBA@@QAEXXZ
// partial score=0.9 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /EHsc /MD
//
// ?rva002B5BBA@Rva002B5BBA@@QAEXXZ, retail 0x002B5BBA (99 bytes, thiscall,
// RET0).  Takes the first queued message reference of the +0x154 queue
// (by value from 0x002B3638), and when it is set shows it (0x004FBD3A),
// makes it the current message at +0x160 (rowed TreeHintRef00217D4C
// operator= 0x002174A4) and pops it from the queue (rowed vector erase
// 0x004F70D1 at begin); the local reference is released through rowed
// 0x0007DEEF.  Evidence: retail EH frame with one 4-byte by-value result
// slot, the +0x154/+0x160 offsets shared with the rowed gate 0x002B4C09
// and its tail dispatcher 0x002B6875 (which already calls this body under
// this name), and the WorldBuilder twin 0xD81E30 (same calls, same order).
// Owner and message class identities are not established: address-derived.

struct TreeHintRef00217D4C
{
	void *m_target;

	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C();
};

void __fastcall ReleaseTreeHintRef00217D4C(struct TargetRef00217D4C *target);

inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	TargetRef00217D4C *target = (TargetRef00217D4C *)m_target;
	if (target != 0)
		ReleaseTreeHintRef00217D4C(target);
}

class Rva004FBC02
{
public:
	void rva004FBD3A();
};

class Rva004F70D1
{
public:
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

	char m_pad00[0x154];
	Rva004F70D1 m_queue;	// +0x154
	TreeHintRef00217D4C m_current;	// +0x160
};

void Rva002B5BBA::rva002B5BBA()
{
	TreeHintRef00217D4C ref = rva002B3638();
	if (ref.m_target != 0) {
		((Rva004FBC02 *)ref.m_target)->rva004FBD3A();
		m_current = ref;
		m_queue.rva004F70D1(m_queue.m_begin);
	}
}
