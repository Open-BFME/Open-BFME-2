# AIGate constructor references the existing destructors

The constructor's existing private UpdateModule view inherited the canonical
virtual BehaviorModule destructor without declaring its own. AIGateUpdate
likewise had no destructor declaration. The constructor TU therefore emitted
implicit inline UpdateModule/AIGateUpdate destructors instead of referring to
their rowed native definitions. Those copies were duplicate, non-retail
providers and also pulled in BehaviorModule's incidental destructor tables.

Both existing classes now declare their virtual destructors out of line.
No class layout, body, shared header, row, pin, alias or source path changes.
The constructor's native row remains exact. An original-source private control
has 60 external code definitions; the corrected object has 56. Every retained
definition preserves its complete bytes and symbolic relocations. No definition
is added; the four removed definitions are the implicit AIGateUpdate,
UpdateModule and BehaviorModule destructors and BehaviorModule deleting wrapper.

The constructor and its real destructor provider pass all five strict rows.
The index86db074988 preview improves the constructor from 0 to 62 linking bytes
and its destructor unit from 0 to 154. These are scoped predictions, not census
figures. Rva0024A797DeletingDtor.cpp remains blocked by another UpdateModule
destructor copy, from the separate DestroyEnvironmentUpdate constructor family.
The earlier shared-header and broader-layout obstacles remain distinct.
