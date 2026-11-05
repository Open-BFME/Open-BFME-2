### LINK-439: matpass donors fail baseline and compile prerequisites
Status: Blocked. Updated: 2026-11-05; inspected revision: 463674729a.
Evidence / affected units: `Code/Libraries/Source/WWVegas/WW3D2/matpass.cpp` and six approved pull donors; [allocated consolidation dry run](../../reverse/attempt_support/matpass-consolidation-20261105-codex.md).
Completed: allocation, scoped planner and TU plan passed; dry run accepted no donors due baseline row losses and a duplicate `RefCountClass` declaration/definition.
Remaining / next check: reconcile affected donors' compiler/header and row-byte prerequisites, then rerun the supported merge and consumer checks.
Clearance: pending; no composed object or consumer-binding verification was possible.
Census confirmation: not claimed.

2026-11-05: MaterialPassClassDestructor.cpp adopts canonical RefCountClass; 6/6 rows match, the owning lane retires one header-queue row, and the preview retains 167 linked bytes. MaterialPassClass layout and merge flag prerequisites remain; [evidence](../../reverse/attempt_support/materialpass-refcount-adoption-20261105-codex.md).
