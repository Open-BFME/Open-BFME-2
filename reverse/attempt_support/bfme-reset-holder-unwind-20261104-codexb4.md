# Counted-holder constructor cleanup 0x007682C7

Inspected base: `b69ebf4a5c0bc79ae7834fcd88fd9689556f855f` (2026-11-04).
Scope: `Code/Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.cpp`,
constructor `0x00180649` and unwind state zero `0x007682C7`.

Target facts: the complete native eight-byte cleanup is
`8B 4D F0 E9 BE 86 A0 FF`; its tail target is `0x0017098D`.
The constructor zeroes its one-pointer base and calls the existing assignment.
The current parent EH graph is EXACT and places compiler label `$L55509`
at `0x007682C7`. This placement comes from the whole parent graph, not
adjacency or similarity to another cleanup.

Existing provider facts: `dx8wrapper.cpp` owns the already-rowed
`BfmeResetAnyRef` destructor at `0x0017098D` (12 bytes). Its established
counted-holder view stores one pointer and conditionally releases it through
`0x0061ED10`. The constructor previously named the unresolved destructor
`Rva00180649Base::~Rva00180649Base`; the prior blocked attempt in
`reverse/re_attempts.log` records that exact missing-callee prerequisite.

Change: reuse the established `BfmeResetAnyRef` base view with inline zero
initialization and its existing out-of-line destructor. Repoint only the
generated cleanup row through `add_match.py --replace-existing`. No generated
source is edited; `uw_gen_011.cpp` retains its orphaned body. No pin, alternate
name, ICF alias or new physical code range is added. This is an ABI-view
reconciliation, not proof of an original retail class name or inheritance.

Verification:

- Before editing: all 17 destination rows pass; four EH graphs are EXACT.
- After source repair: all 17 existing destination rows still pass and all
  four EH graphs remain EXACT. Frozen-file check passes.
- Unmasked `add_match.py` verifies the new cleanup at its exact native target.
- Final `./build.sh` over destination and generated source passes 220/220
  rows (18 destination, 202 remaining generated). Four EH graphs remain EXACT.
- Ordinary paired link preview with the existing provider reports 2/2 LINKS:
  destination 462 authored bytes, dx8wrapper 28,658 authored bytes. Index:
  2026-11-04 12:23, census `40fe1783d7`. This is a preview, not a census gain.

The default TU-approval pick is not completed: the consolidation planner
finds no original-path evidence for these placeholder owners. No map or
approval is changed. The approved parent-group destination is used only for
the existing generated cleanup. Full generated-unit link closure and new
census coverage remain unverified. The publication hook supplies the scoped
consumer audit; an inconclusive audit requires current receipts/index in the
next maintainer census.
