# Canonical device-guard unlock declaration, 20261104-0110

Correct the existing BFMEDX8DeviceLock header's void unlock declaration to bool,
matching the existing native90-byte provider at0x00120F50 in dx8wrapper.cpp.
Its source returns the saved last-unlock condition, and normal symbol-scoped
verification passes the complete90B with all3 named imports. The previous void
pin already points at the same RVA. No provider, pin, alias or contract register
is edited. Existing users ignore the return value; no locking algorithm changes.

The native header dependency graph finds exactly6 ledger-backed consumers.
Update their5 repeated declarations coherently. Claims now permit the shared
scope that was unavailable on03 November. Read prior index-buffer handoff and
the split obstacle entry; this addresses that recorded compiler prerequisite.

Normal verification retains 125 existing function/EH ledger rows;
string/float references and frozen gates pass. All346 external code instances
retain their instruction bytes. Seven change only the void->bool reference to
the SAME native0x00120F50 provider; the remaining339 keep raw external refs.
All427 non-debug sections, data, EH contents and relocations compare
equal after defined-local-label resolution and ONLY that proved callee-name
normalization. The private comparator does not edit or replace any repository
verifier. The ordinary header hook still verifies every reached consumer.

This is one shared declaration repair, not125 newly authored functions, a full
link, runtime/memory/crash/FPS or multicore improvement. Existing private guard
copies can now take the same header without the bool/void C2556 conflict.
