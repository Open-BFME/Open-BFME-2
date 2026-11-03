# ObjectCreationUpgradeModuleData canonical-base probe

Scratch-only private experiment,2026-11-03. Candidate changes only ObjectCreationUpgradeModuleData's base from Snapshot to canonical ModuleData, inserts Common/ModuleData.h immediately before that class, and shrinks the opaque prefix from0x120-sizeof(Snapshot) to0x120-sizeof(ModuleData). Existing first-Snapshot context and the three real AsciiString members stay unchanged. No name, pin or table is added.

Control passes20/20 current source rows. Candidate passes19/20; the actual destructor at0x004B45E8 changes from84B to89B. Its three AsciiString release calls retain their offsets and bytes. After those calls, the current Snapshot teardown is an inline vptr reset. Canonical ModuleData.h declares its destructor out of line, so the candidate instead emits EH state -1, restores this and calls ??1ModuleData@@UAE@XZ, changing the epilogue schedule. This is a real compile-shape blocker, not a false rejection. No nonmatching source was left in Code.

The external definition comparison is31->28. Only ??1ObjectCreationUpgradeModuleData@@UAE@XZ changes; Snapshot's inline destructor, Snapshot deleting helper and16-byte Snapshot vtable cease to be emitted. Nothing is added. All other ordinary external definitions/relocations remain unchanged. The candidate is not ready to land.

Important table boundary: ObjectCreationUpgradeModuleData is declared __declspec(novtable), so NEITHER control nor candidate emits its child vtable. The observed16-byte table is ??_7Snapshot@@6B@ (base teardown), NOT an incomplete four-slot leaf table. Accordingly this probe does NOT observe a16->124-byte child-table expansion and does NOT prove the31 retail slot identities at0x008577C8. The existing constructor source still owns the separate rowed g_00C577C8[31], whose actual native slots and binding aliases remain their own verification scope. Do not retire or repoint it based on this destructor experiment.

A possible future separate hypothesis is a justified TU-local inline ModuleData destructor definition that reproduces the native Snapshot reset, as other canonical module families sometimes require; it has NOT been tested here and could affect emitted provider selection. Any such experiment needs its own full byte/EH/provider proof and must not alter the shared header merely to force this candidate. The current report banks the actual result only.

Artifacts: control.cpp/candidate.cpp, their private objects, probe.py and proof.json. No tracked source, ledger, claim, network or shared build-cache mutation was performed. No census or sourcefile credit is claimed.

Resolved follow-up: canonical inheritance now passes all23 rows and four EH
graphs with an ordinary TU-local EMPTY inline ModuleData destructor, allowing
automatic Snapshot teardown. See ../objectcreation-moduledata-inline-base-20261103/README.md.
The earlier out-of-line-declaration trial remains negative evidence, but is
no longer an open base-call-shape prerequisite for the current typed leaf.
Constructor lifetime and31-slot data ownership remain separate.
