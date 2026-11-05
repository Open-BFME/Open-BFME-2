# Experience-level find composition: claim handoff

Base: `0178c1723f`. The supported trial now accepts
`GameLogic/System/ExperienceLevelSystem.cpp` with
`Common/Rva00288940Find.cpp` and `WWLib/Rva002897A8Find.cpp` (all under
`Code/GameEngine/Source/` except the WWLib donor under
`Code/Libraries/Source/WWVegas/`). The preceding declaration repair preserves
the seed's emitted code; this trial is evidence for a future merge, not a
source-file reduction.

The actual `tu_skeleton.py --merge` invocation wrote no source or ledger
changes. Its whole-cohort claim refused `0x0007FAB3`, held by
`yasinschroeder-codexb2` for `GameLogic/SkirmishAI/AIDozerManager.cpp`.
The experience-level cohort includes this ICF address through
`ExperienceLevelDtor.cpp`'s `Rva002894A2PointerVector` destructor, even though
that donor is not part of the successful trial. A read-only claim check
confirmed the peer's ownership. Do not force or bypass that claim.

Before applying, ordinary byte verification passed 53/53 code rows and four
data rows across the three proposed input files. String, float and import
reference checks passed. Ordinary link prediction against census index
`c95fcfcfcd` retained LINKS for all three files: 2,990 + 56 + 106 = 3,152
authored bytes. This is prediction only; no census gain is claimed.
`link_check.py --prepare-current` twice rejected reusable witnesses because
preparation inputs or verified objects moved; these attempts do not establish
strict receipts. The merge trial's own census-linked cohort guard passed.

Retry the supported merge after the peer releases the shared ICF address;
refresh the consolidation planner first if its inputs changed. Then perform
the combined byte, binding, debt-transfer and path-consumer audit. The other
donors still have the recorded base/layout and STL specialization blockers.
Local scratch logs: `build/codexb4-experience-dry-after.log`,
`build/codexb4-experience-merge.log`,
`build/codexb4-experience-move-prepare-before.log` and
`build/codexb4-experience-move-preview-before.log`.
