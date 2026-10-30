# Shroud holder argument cleanup

Base: `b9f4ccb4a1`, 2026-10-30. The default picker served
`uw_0075ed9d` in `Code/gen_small/uw_gen_006.cpp`. Ordinary preview confirms
that generated unit cannot link: its synthetic sink, external call and
destructor names have no providers. LINK-095 already explains this design;
this is placeholder cleanup, not a lost-row regression.

The current TU map rebuilt in memory approves `0x0075ED9D` for
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud.cpp`, by
`P=0x00072A51@FuncInfo0x0090143C p-group`. The existing setter at
`0x00072A51` already lives there. Its independently EXACT EH graph places
the current compiler label `$L59151` at that native eight-byte cleanup.
The cleanup takes the address of the by-value argument at frame `+8` and
jumps to the existing counted-pointer destructor at `0x0007B724`.

The TU already emits `??1Rva00072A94@@QAE@XZ`: all 16 bytes equal that
native destructor, with no relocations. `add_match.py --icf-owner` records
this existing body as an ICF twin of `??1Rva00087A93@@QAE@XZ`, then
`add_match.py --replace-rva` moves the generated cleanup row to its real
parent. The native argument lifetime and the emitted byte twin prove this
binding. They do not recover an original class name. The existing
address-derived holder spelling remains; no pin or unique code bytes are
added. There is one physical cleanup owner, and the original physical
destructor owner remains in W3DView.cpp.

No C++ source or compiler flags change. The generated file is untouched.
[Target and object facts](shroud-holder-unwind-20261030-codex3.json) record
the exact EH placement, native tail target, relocation-free destructor
comparison and object hash.

Verification:

- Normal byte gates pass all 12 destination rows and all 56 remaining
  generated rows. Frozen-source checks pass before and after. The destination
  retains all three EXACT parent EH graphs without exceptions.
- The paired destination/provider byte gate passes 31/31 functions and ten
  data rows, plus one string, twelve float constants and eight imports.
- Ordinary paired preview retains 2/2 LINKS and 2,533 authored bytes
  (1,113 + 1,420) against index `6fe1089c24` (2026-10-30 04:25).
  This does not establish a census gain.
- Pin admission, hatch counters, TU ownership and the staged code-identity
  gate pass; code identity reports zero new findings in shadow mode.

Path and register audit: only the cleanup's ledger source changes; both
source paths remain live. The generated source has no relevant data,
code-identity or header-register keys to transfer. The destination's existing
Microsoft-header queue entry remains, since its declarations did not change.
The active tooling, hooks, workflow and source-list search has no path
consumer requiring an update. Existing skeleton comments are historical
scaffolding; the ledger and parent EH graph determine current ownership.
The wider already-handed-over range's retired HighlanderBodyPoolKey and
AISpecialPowerRva004B327F paths occur only as source-history comments, not
active includes or tooling consumers. No source file is removed in this repair.

Strict receipt preparation failed twice: paired preparation and an isolated
W3DView retry both reused the byte-verified objects, then reported
`prepared receipt went stale during normal gates` for W3DView. A subsequent
read-only check finds the destination strict-current and W3DView
ordinary-current but not strict-current. This is recorded as a false reject
for the unchanged provider; no verifier was changed or bypassed.

The scoped staged-tree consumer audit exits 2, INCONCLUSIVE: index
`6fe1089c24` predates this outgoing base, and W3DView lacks a current strict
receipt. Consumer preservation is unverified. Carry this binding into the
next maintainer census and repeat the audit with current receipts and index.
The remaining 56 generated rows still require their own parent placement and
callee proofs; whole-unit closure remains open. No census, linked-byte,
source-file, ownership or debt gain is claimed.
