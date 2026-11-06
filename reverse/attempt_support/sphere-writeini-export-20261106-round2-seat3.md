# Sphere emission-volume writer export reconciliation

Date: 2026-11-06. Base: `85d0ac929f8`. Claim owner: `codex-20261106-round2-seat3`.

## Selection and target facts

The default `next_work.py --claim` twice redrew the already-landed Box writer, and `--claim --shard 2/3` redrew the already-landed Line writer. Their current definitions, ledger identities and landed history were checked and each stale claim was released without source edits. The supported `next_work.py --ranked --tier link --limit 15` served Sphere at 0x0055D525 as an unrepaired 252-byte packet. After coordinator assignment, `claims.py claim 0x0055D525 file:Code/GameEngine/Source/GameClient/Rva0055D525Write.cpp` acquired both scopes before edits.

Retail export ordinal 1957 (`reverse/exports.csv:1958`) names `?writeINI@SphereEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z` at 0x0055D525. The ledger already rows its 223-byte body under the pointer-taking non-const placeholder `?rva0055D525@SphereEmissionVolumeModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z`, plus its 10-byte handler and two unwinds of 11/8 bytes. This is placeholder/signature cleanup, not a lost body. The latest inspected authoritative `errors.tsv`, run 42174078539 at `da59156dc4f2`, still lists the exact export as an exit.exp LNK2001. Its scoreboard is 308 unresolved, zero duplicates and no image; no newer run is claimed.

## Change and safety

Only the owning source's private declaration and existing definition are reconciled to `writeINI(File &, unsigned int) const`; unchanged pointer-taking helpers receive the reference's address. The parent and handler names, both unwind parent notes and two tombstones move together. No body, code row, pin, alias, table, global or shared header is added. No registered/shared header for this template class was found; its separate Info class is not a replacement for the template declaration.

`rename.py function --rva 0x0055D525 --new '<exact export>' --basis canonical:export --evidence 'reverse/exports.csv:1958 exact exported address and signature' --dry-run` refuses changes beyond the identifier. The documented manual-signature exception in `docs/naming.md` applies: exact retail export evidence, placeholder-only replacement, recorded verdict and tombstones; `name_basis.csv` remains untouched.

A complete Code text scan of `rva0055D525` finds only the defining source, and no symbols-ledger pin uses it. Before/after COFF inspection preserves all 551 external definitions after normalizing the two parent/handler names, with no unexpected additions or removals. Undefined-name sets and `.drectve` bytes are identical, retaining all other providers and linker alias directives. Scratch receipts are in `build/round2-seat3-sphere-export/`; `build.read_object_symbols` was used only to read compiler output, never to compile into the match cache.

## Commands and measurements

Commands use the established local x86 VM wine wrapper and repository `.venv` on PATH, `BFME_VM_WINEPREFIX=/home/bfme/.wine-pdb`, and the stated stable owner/namespace. The current published link index is copied byte-for-byte from the coordinator's hosted index file; no census or index update is run.

- `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameClient/Rva0055D525Write.cpp`: all definitions matched before and after.
- Baseline `./build.sh Code/GameEngine/Source/GameClient/Rva0055D525Write.cpp`: **4/4** matched rows, **2** literals, no skipped string references. Both renamed compiler labels are proved through parent EH data.
- Changed-source `python3 tools/link_check.py --prepare-current Code/GameEngine/Source/GameClient/Rva0055D525Write.cpp`: **1** explicit safe provider prepared with a strict reusable receipt; its ordinary scoped build reuses that object and passes **4/4** rows and **2** literals. Index, census and status stay unchanged; this command explicitly does not verify link closure.
- `python3 tools/eh_verify.py Code/GameEngine/Source/GameClient/Rva0055D525Write.cpp`: **1 EXACT**, **0** not exact/baselined/missing objects.
- COFF definition inspection: required export **0 -> 1**, old placeholder **1 -> 0**; external definitions **551 -> 551**, unexpected definition changes **0**, undefined-name changes **0**, `.drectve` unchanged.
- Before and after `python3 tools/link_check.py Code/GameEngine/Source/GameClient/Rva0055D525Write.cpp`: **1/1 LINKS**, **233 -> 233** authored bytes against index `47fd56b879` (2026-11-06 05:39). The unit preview alone never detected the absent export; this is not a real-link count or gain.
- `python3 tools/check_csv.py`: OK, **99,515** function rows, **9,320** symbol rows, **2,272** data rows; counts unchanged.
- `git diff --check`: clean.

## Remaining verification

The coordinator will integrate this substantive repair separately and run its bounded outgoing batch audit. Full current affected-consumer selection remains unverified here: the preceding same-family audit was inconclusive on its older census baseline and a missing current receipt for `Common/0CreateAHeroManager21FE49.cpp`. Strict preparation here resolves only this provider's receipt. Preserve that distinction if the new audit still cannot verify consumers.

The scheduled authoritative real link must confirm this one export disappears. No reduction from 308 unresolved, linked image, startup/menu/skirmish/save-load result or retail CRC agreement is claimed. No crash investigation or maintainer-only run was started.
