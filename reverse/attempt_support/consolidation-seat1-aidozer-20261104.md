# AIDozerManager consolidation handoff (2026-11-04)

`AIDozerManager.cpp` remains allocated and its narrow planner snapshot passed
`--check`. `tu_skeleton.py --merge` accepted the unchanged
`Rva005997CDDtor.cpp` donor (destructor plus four EH rows); the other donors
remain untouched. `./build.sh Code/GameEngine/Source/GameLogic/SkirmishAI/AIDozerManager.cpp`,
`find_declared_unmatched.py` and `check_csv.py` pass. The merge LinkGuard saw the
pre-merge destination and donor units census-linked and accepted the composition.

Staged `code_identity_gate.py --staged` completed in shadow with one new
`wrong` binding at `AIDozerManager.cpp`: `preEmptivelyBuildDozers` to the
`vector<Rva00599435Keyframe>::push_back` COMDAT at `0x00539A2E`. Preserve this
finding for the identity lane; no identity key was retired. `data_check.py
--staged` reported no findings.

Dry-run blockers left for prerequisite owners: `Rva005996FFListErase.cpp`
(undefined AsciiString in donor views), `Rva00599825ListAdd.cpp` (duplicate
_STL list iterator definitions), `Rva005997CDCtor.cpp` (missing constructor
declaration), and `Rva005997CDNearestPick.cpp` (missing member and `m_list`).
Do not retry until those declarations/views change. The path-consumer search
found no active references to the deleted donor under `tools/`, `.githooks/` or
`.github/`; ledger/history references are intentional.
