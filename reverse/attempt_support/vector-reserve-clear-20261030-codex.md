# Vector reserve cleanup identity

Source base: `9e8a503c96c1`. Scope:
`Code/Libraries/Source/WWVegas/WWLib/StlVectorRva00500EFA.cpp` and its existing
cleanup provider, `Code/GameEngine/Source/Common/VectorPod88MClear.cpp`.

Retail's 116-byte reserve at `0x00500EFA` calls the existing 30-byte outer-vector
cleanup at `0x00500EDC`. The latter calls the rowed range destructor at
`0x00500AF8` and free. These target calls establish helper ownership; they do
not identify the opaque record's application type. The STLport 4.5.3 template
is structural reference evidence. The earlier overflow repair in
`vector-helper-owners-link-20261018/readme.md` supplies the same supported
cleanup binding for the separate caller at `0x0050129F`.

Declare the native cleanup specialization and forward the opaque specialization
through an inline ABI view. Reserve's COFF relocation at offset `0x45` now
names the existing outer-vector cleanup owner. The competing opaque cleanup
definition is absent from the object. No row, pin, alias, path or application
name changes. The three existing folded helper rows remain at `0x00500B11`
(45 bytes), `0x00500B5B` (38 bytes) and `0x00500BC8` (45 bytes).

Verification:

- Ordinary source build: all four rows match. Frozen-file check passes before
  and after the edit.
- `link_check.py --prepare-current` for caller and cleanup provider: all five
  rows match with strict reusable receipts; no extra sources are prepared.
- Before and after ordinary preview: both sources LINKS, 244 caller bytes and
  30 provider bytes against index `85f6b7f40c` (2026-10-29 15:08). The caller's
  census figure of 116 predates its three existing folds; this repair adds no
  unique coverage and claims no census gain.
- The first identity retirement refused ten missing ledger objects. A normal
  build of those ten current units passes 174/174 function rows, four data rows,
  79 string literals, eleven float literals and 41 renumbered funclet placements.
  No prerequisite source is edited.
- Re-running `repair_queue.py retire identity` passes and removes the source's
  sole identity key, with zero remaining findings. The register is changed only
  by that owning tool.
- Staged-tree `link_batch_audit.py`: INCONCLUSIVE, because the index predates
  the source base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Carry this consumer and the caller/provider scope into the next
  scheduled census; broader consumer closure remains unverified.

Reproduction commands:

```sh
./build.sh Code/Libraries/Source/WWVegas/WWLib/StlVectorRva00500EFA.cpp
python3 tools/find_declared_unmatched.py Code/Libraries/Source/WWVegas/WWLib/StlVectorRva00500EFA.cpp
python3 tools/link_check.py --prepare-current Code/Libraries/Source/WWVegas/WWLib/StlVectorRva00500EFA.cpp Code/GameEngine/Source/Common/VectorPod88MClear.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WWLib/StlVectorRva00500EFA.cpp Code/GameEngine/Source/Common/VectorPod88MClear.cpp
```
