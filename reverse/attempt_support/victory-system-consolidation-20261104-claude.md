# VictorySystem.cpp consolidation, second pass (2026-11-04, claude-opus-5-5)

TU: `Code/GameEngine/Source/Common/VictorySystem.cpp`. Served by
`tools/next_work.py --claim` (TU consolidation, 2 donors). Follows
`victory-system-consolidation-20261028-claude.md`.

## Landed in this pass

- `Rva00404D70Init.cpp` (VictorySystem::init): dropped its private
  `_STL::allocator`/`vector` and VictorySystem layout. It now takes the TU's
  flags and VictorySystem layout and reads `parameters120` as the record vector.
  `push_back` stays a declaration bound to the kept `0x004055BB` provider. 5/5.
- Seed: `Object` view gains `m_experienceTracker` at +0x264 (object.h's
  offset), and `Rva004051BC` takes the donor's full layout. 31/31.
- `Rva004051BC.cpp`: TU flags and the TU's Object view, then the placeholder
  `Rva004051BCFilter` became `Rva00260E2AFilter` over the canonical
  `PartitionFilter.h` (as `SpecialAbilityUpdate.cpp` spells it). The two
  `/alternatename` hatches that bound its slots to that class's rows are gone
  (alternatename 2807 -> 2805). Its `??1Rva004051BCFilter` row at the
  `0x0049C38A` ICF fold is tombstoned. The emitted `??1Rva00260E2AFilter` is
  already rowed there. 4/4; `link_check`: LINKS (163 -> 156 bytes, the 7-byte
  shared fold now credited to its existing owner).
- Merge of `Rva00404D70Init.cpp` into the TU: 36/36. The TU's own `$L1248`
  (`0x00784EC4`, parent `0x00405684`) collided by name with the donor's
  `$L1248` (`0x00784EB2`). The TU row was renamed to the merged object's label
  `$L6748` and tombstoned. The header-queue key `VictorySystem` for the donor is
  retired by `Debt-Retired:` because the TU already holds that key.

## Remaining

- `Rva004051BC.cpp` composes and verifies beside the TU, but the merge's link
  guard rejects it: "no longer defines `??1Rva004051BCFilter@@UAE@XZ`, which the
  census still references". In census `2f0cb97f52`, that symbol's only
  referencer is `??_GRva004051BCFilter@@UAEPAXI@Z` in the same donor object,
  which also goes. The rejection is recorded as a false reject in
  `re_attempts.log`. Rerun `tu_skeleton.py --merge ... --dry-run` after the
  next scheduled census.
- The mixed files listed in the 2026-10-28 handoff still need splits.

## Audits

- Registers: no `code_identity_baseline.tsv`, `data_check_baseline.txt` or
  `flag_overrides.csv` key names either donor. The tool moved the hatch keys
  and header-queue rows.
- Tooling path audit over the outgoing range: the deleted
  `Rva00404D70Init.cpp` path is still named by the TU's `// ---- from`
  provenance comment, the header queue's stored compile message (history), the
  census-owned `link_status.csv`, and historical handoffs. Nothing under
  `tools/`, `.githooks/` or `.github/` names it.
