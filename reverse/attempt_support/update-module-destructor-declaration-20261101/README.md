# Remove the final implicit UpdateModule destructor copy

UpdateModuleCtor.cpp now declares the existing virtual destructor out of line.
Its native constructor row remains exact. The original-source private control
has 60 external code definitions; the corrected object has 59. The sole removed
definition is the implicit UpdateModule destructor. Every retained definition
preserves its complete bytes and symbolic relocations; nothing is added.
No layout, body, shared header, row, pin, alias or source path changes.

The constructor and real base-destructor unit pass all three strict rows.
With the current AIGate and DestroyEnvironment constructors overlaid together,
Rva0024A797DeletingDtor.cpp now predicts LINKS 0 -> 52 bytes. The six-source
cohort retains the two earlier family repairs and predicts 545 linking bytes
over five units: AIGate62+154, DestroyEnvironment70+207 and the common base52.
The newly unpublished DestroyEnvironment/base batch contributes 329 predicted
bytes. Census figures remain unchanged until the scheduled measurement.

UpdateModuleCtor itself remains blocked by the two incidental BehaviorModule
vtable COMDATs from its canonical header's inline destructor. The 59-definition
control proves this repair does not change those bodies. A TU-private copy of
the registered class is not an allowed remedy. Reconcile the canonical
BehaviorModule destructor contract and its native providers as a separate
shared-header task before claiming that constructor's unit links.
