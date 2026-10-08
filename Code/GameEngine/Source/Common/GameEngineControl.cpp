// cl: /O1 /MD /EHsc
// Target: registration 0x003FE7E6..0x003FE881 (155B), and append
// 0x003FE60F..0x003FE624 (21B). The append entry is a short jump into
// its own loop; the Ghidra inventory's 2B thunk extent omits that loop.
// WorldBuilder identifies GameEngineEventSequencer::AddControl and its
// GameEngineEvent::Append callee. BFME1 ba7ddda7e8 postTimedOp.cpp supplies
// the allocation/serial/list semantics. BFME2 calls its existing 56B node
// constructor rather than inlining it, and releases through 0x0007DEEF.
// Existing address names are retained for compatibility with verified callers.
// Target bytes prove next+4, owning handle+8, 24B allocation and the shared
// one-pointer reference representation; they do not establish donor type names.
// Serial VA 0x00DC1984 contains 1234 in retail; the list head at 0x00E02EC0
// is defined by TimedOperations_updateTimedOps.cpp.
// The callback/reference view cast reconciles those already used one-pointer
// wrappers. Copy and destruction retain the native AddRef/Release operations.
// Release can unwind through its virtual destruction call, so its declaration
// must preserve the two retail registration EH states.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
	TargetRef00217D4C *m_ptr;
	// ?TreeHintRef00217D4C::TreeHintRef00217D4C present-unmatched
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
		if (m_ptr) ++m_ptr->references;
	}
	// ?TreeHintRef00217D4C::~TreeHintRef00217D4C present-unmatched
	__forceinline ~TreeHintRef00217D4C() {
		if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
class Rva003FE792 {
	const void *m_vtable;
	Rva003FE792 *m_next;
	TreeHintRef00217D4C m_hint08;
	bool m_b0C;
	int m_i10;
	int m_i14;
public:
	Rva003FE792(TreeHintRef00217D4C hint, int value);
	~Rva003FE792();
 __declspec(noinline) void append(Rva003FE792 *node);
};

void Rva003FE792::append(Rva003FE792 *node) {
 while (m_next) { m_next->append(node); return; }
 m_next = node;
}
class Rva00211E75 {
public:
 // ?Rva00211E75::Rva00211E75 present-unmatched
 Rva00211E75(const Rva00211E75 &other) : impl(other.impl) { if (impl) ++impl->references; }
 // ?Rva00211E75::~Rva00211E75 present-unmatched
 ~Rva00211E75() { if (impl) ReleaseTreeHintRef00217D4C(impl); }
 TargetRef00217D4C *impl;
};
class Rva00211E75Callback : public Rva00211E75 {};
class TimedOp;
extern TimedOp *g_timedOperationHead;
int g_timedOperationSerial = 1234;
bool Rva003FE7E6(Rva00211E75Callback callback, int *id) {
 *id = g_timedOperationSerial;
 ++g_timedOperationSerial;
 Rva003FE792 *node = new Rva003FE792(*reinterpret_cast<const TreeHintRef00217D4C *>(&callback), *id);
 if (node) {
  if (g_timedOperationHead) reinterpret_cast<Rva003FE792 *>(g_timedOperationHead)->append(node);
  else g_timedOperationHead = reinterpret_cast<TimedOp *>(node);
 }
 return node != 0;
}
