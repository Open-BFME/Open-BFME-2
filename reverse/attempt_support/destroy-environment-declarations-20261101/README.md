# DestroyEnvironment uses its native destructor providers

The constructor has the same inherited-virtual-destructor omission as AIGate.
Its existing private UpdateModule and DestroyEnvironmentUpdate views now declare
their virtual destructors out of line. The real providers already live in
Rva0024A797DeletingDtor.cpp and DestroyEnvironmentUpdate.cpp. No layout, body,
shared header, source path, ledger, pin or alias changes.

The original private control has 62 external code definitions; the corrected
object has 58. Every retained definition preserves its complete bytes and
symbolic relocations. Four implicit destructor definitions disappear and none
is added. The constructor and real derived-destructor unit pass all nine strict
rows, including their current compiler-local cleanup mappings.

The current five-source cohort predicts the constructor 0 -> 70 linking bytes
and its destructor unit 0 -> 207. AIGate's earlier 62 bytes are retained, giving
339 in this cohort. This repair contributes 277 of those predicted bytes; it
does not claim a census gain. UpdateModuleCtor still emits the remaining wrong
base destructor copy, so its own unit and Rva0024A797DeletingDtor remain blocked.

The prior AIGate publication's broader audit remains INCONCLUSIVE: index86db074988
predates base c07165aac2 and affected AICowerState_onEnter.cpp lacks a current
strict receipt. Carry that scope into the next scheduled census. Scoped
predictions and strict row checks do not clear this historical audit.
