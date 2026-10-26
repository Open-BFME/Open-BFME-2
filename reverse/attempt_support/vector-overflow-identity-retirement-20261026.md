# Vector overflow: retire a repaired clear binding

Inspected upstream `d75f6cf62f`; reference BFME 1 `f633d0e97a`.

The default queue served `VectorOverflowRva0048D48F.cpp` for its single
code-identity key: the 178-byte overflow at 0x0048D48F called an allegedly
wrong `_M_clear<Rva0048D48FRecord>` copy at 0x000C060A. The complete source
and its prior attempt history were read. The original application identity
remains unknown; the distinct CameraMarker overflow is rowed at 0x000D05C1.

Upstream `5300eb2972` had already forwarded this opaque record's construction
to `Rva0048C81FConstruct` and destruction to `_Destroy<CameraMarker*>`.
No new source, pin, ledger, class layout or name change was necessary here.

Current evidence:

- `find_declared_unmatched.py` passes before and after retirement.
- Normal `build.sh` verifies the existing 178-byte body. It also verifies
  all 75 rows in `stlport_vector_cameramarker_clear.cpp`,
  `StlportVectorDtorChains.cpp` and `stlport_construct_game_structs.cpp`.
- `allowed_symbols.py --source` finds six references: one owner, five folds,
  **zero wrong bindings**. The call at offset 151 to 0x000C060A is now a
  verified fold. This does not identify the opaque application record.
- The ordinary `link_check.py` preview is already clean: **178 -> 178 bytes**
  against census index `f995f30157` (2026-10-25 21:36 UTC).
- `repair_queue.py retire identity` passes and removes the source's single
  stale key from `reverse/code_identity_baseline.tsv`, with zero remaining.

The result is one retired identity debt. No new C++ conversion, linked-byte
gain, complete-image link or runtime result is claimed. The old helper pins
and application-name uncertainty are unchanged.

Original pre-consolidation commands (historical):

```text
./build.sh Code/Libraries/Source/WWVegas/WWLib/VectorOverflowRva0048D48F.cpp
python3 tools/allowed_symbols.py --source Code/Libraries/Source/WWVegas/WWLib/VectorOverflowRva0048D48F.cpp
python3 tools/link_check.py Code/Libraries/Source/WWVegas/WWLib/VectorOverflowRva0048D48F.cpp
```

## Rebase after upstream consolidation

Upstream `b85e569cee` moves this body and its baseline key into
`Code/GameEngine/Source/GameLogic/Object/Update/FlammableUpdate.cpp`. The
rebase initially preserves that transferred key, rather than deleting it by
hand. After claiming the new file, its frozen-file check and normal whole-unit
build pass all eight rows. The new upstream AutoFindHealingUpdate unit is
also built (3/3 rows), resolving the retirement tool's explicit missing-object
prerequisite. The owning `repair_queue.py retire identity` then removes this
same obsolete clear-binding key at the new source path. One separate identity
finding in FlammableUpdate remains registered.

Logs under `build/codex-cleanup-20261025/`:
`iteration22-flammable-build.log`, `iteration22-autofind-provider-build.log`,
`iteration22-flammable-retire.log` (initial refusal), and
`iteration22-flammable-retire-current.log` (one key retired, one retained).
This revalidates the existing retirement at its new owner, not a second debt
reduction or a new linked-byte gain.
