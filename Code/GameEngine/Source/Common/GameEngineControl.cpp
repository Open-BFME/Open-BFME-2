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
#include "TimedOperationNodeBFME2.h"

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
