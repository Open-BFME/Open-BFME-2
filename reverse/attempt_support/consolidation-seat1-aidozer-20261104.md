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

## Follow-up merge (2026-11-05)

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/SkirmishAI/AIDozerManager.cpp`
accepted the unchanged `Code/Libraries/Source/WWVegas/WWLib/Rva005996FFListErase.cpp`
donor in its dry run and moved row `0x005996FF` (`unRegisterDozer`) in a local
trial. The destination build passed (`Functions: OK 11/11 matched`; STLport
fold, strings, floats and imports passed), and `find_declared_unmatched.py`
passed on the destination. Merge LinkGuard accepted this census-linked
composition. The pre-commit hook then refused the composition:
`AIDozerManager.cpp: declares its own StringBase; include
reference/shims/bfme2_ascii/string_base.h instead`. The trial was restored;
no merge is pending publication. This donor needs a manual shared-view repair
by its prerequisite owner before retrying.
`code_identity_gate.py --staged` retained the shadow finding for
`preEmptivelyBuildDozers` -> `vector<Rva00599435Keyframe>::push_back` at
`0x00539A2E`; `data_check.py --staged` found none. No identity or data debt was
retired.

Current dry-run rejected the other AIDozer donors for duplicate `StringBase`,
duplicate STL iterator templates, and missing methods/members; leave them to
their prerequisite owners. The path-consumer audit found no active reference to
the donor under `tools/`, `.githooks/` or `.github/`. The remaining
`reverse/link_status.csv` donor-path row is a prior census snapshot.
