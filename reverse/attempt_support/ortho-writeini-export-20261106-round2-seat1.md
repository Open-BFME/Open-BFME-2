# Ortho emission-velocity writer export reconciliation

2026-11-06; base `85d0ac929f8`; worker `codex-20261106-round2-seat1`.
Source: `Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva0055E969Write.cpp`.

## Evidence and scope

The coordinated supported ranked picker shard `0/3` served this exit-link
candidate. After documenting the preceding blocked Default physics writer,
its RVA and file were claimed before editing. `reverse/exports.csv` ordinal
1950 names `0x0055E969`
`?writeINI@OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z`.
The ledger already owned that exact 275-byte body under the placeholder
`?rva0055E969@OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z`.
This reconciles an existing owner; it adds no recovered body or source file.

The existing declaration is already virtual. Only the identifier, constness
and `File *` to `File &` signature change; helper calls take `&file` as needed.
Field offsets, source path, extent and the single body remain. There is no
canonical header for this class. No shared header, vtable, initializer, alias,
pin, stub or emit anchor changes.

The ordinary `rename.py function --rva 0x0055E969 --new <exact-export>
--basis canonical:export --evidence <ordinal> --dry-run` refuses the signature
change beyond the identifier. `docs/naming.md`'s explicit hand-signature
exception applies; this does not perform a virtual respell. The old spelling
is tombstoned and the successful result recorded through `re_log.py`.

## Provider safety and measured checks

Source, symbol-pin and data-register searches find the old spelling only in
its owner's comment, declaration and definition. The published index
`47fd56b879` (2026-11-06 05:39 UTC) reports only this source in
`link_batch_audit.affected_sources(index, {old_name})` and no alternatename
edge naming it. That is bounded historical evidence, not a current full audit.

- Normal `./build.sh <source>`: **1/1 matched** before and after; **3 string
  literals** verified each time, zero unverified/skipped.
- COFF comparison: all **275 body bytes** identical; **21 relocations**
  preserved after the expected compiler-generated EH-label rename. All **556
  non-debug sections** have identical contents and normalized relocation
  targets. **552 external definitions** remain; the old writer is the only
  removed definition and the exact retail export the only added one.
- `link_check.py --prepare-current <source>`: **1 explicit provider** byte
  verified with a strict reusable receipt; index/census/status unchanged.
- Final `link_check.py <source>`: **1/1 link cleanly**, bounded **LINKS 275 ->
  275 B** against that dated index, matching the baseline preview. The repair
  supplies an exported name; it claims no extra census-linked bytes.
- `find_declared_unmatched.py <source>`: all definitions already matched.
- `check_csv.py`: **99,515 function rows**, **9,320 symbols**, **2,272 data
  rows**, OK. `git diff --check` passes.

The normal build uses the existing local x86 QEMU/Wine compiler wrappers;
no compiler flags or verifier code changed. Original source/object and
comparison JSON remain in ignored `build/round2-seat1-ortho/`.

## Remaining verification

The outgoing batch audit belongs to root's publication tree. A strict source
receipt and bounded preview do not prove full provider/consumer closure.
The last inspected automated real link `42174078539` at `da59156dc4f2` still
lists this writer among **308 unresolved**, **0 duplicates**, with no image.
No new real link, startup/menu, skirmish, save/load or CRC test ran here.
Export clearance awaits the next automated real link; other Ortho module
data/vtable obligations remain separate.
