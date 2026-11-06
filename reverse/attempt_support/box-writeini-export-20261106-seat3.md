# Box emission-volume writer export reconciliation

Date: 2026-11-06. Inspected base: `d707d2f53bf`. Claim owner: `codex-20261106-seat3`.

## Target facts

`python3 tools/next_work.py --claim` served `Code/GameEngine/Source/GameClient/Rva0055D2E8Write.cpp`, 252 row bytes, for the missing export `?writeINI@BoxEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z`.
`reverse/exports.csv` ordinal 1941 places this exact const File-reference signature at 0x0055D2E8. The existing 223-byte parent already owns that address under `?rva0055D2E8@BoxEmissionVolumeModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z`; its three EH rows own another 29 bytes. This is existing-placeholder identity cleanup, not a lost body or a new recovery.
The official real-link artifact for run 42174078539, measured commit `da59156dc4f2`, still contains this export in `errors.tsv` (an exit.exp LNK2001). The aggregate scoreboard there is 308 unresolved, zero duplicates and no image. No new real-link run was launched.

## Change and provider safety

The private declaration and existing definition now spell `writeINI(File &, unsigned int) const`. The calls pass the reference's address to the unchanged pointer-taking helpers. The parent and handler ledger names, unwind parent notes and two rename tombstones move together; no second code row, body, pin, alias, table or stub is added. No shared header changes.

The documented manual-signature path is used after `rename.py function --rva 0x0055D2E8 --new '<export>' --basis canonical:export --evidence 'reverse/exports.csv:1942 exact exported address and signature' --dry-run` refused changes beyond the identifier. A full Code text scan found the old identifier only in its own source; the symbols ledger contained no pin for it. The compiled before/after COFF symbol check found 551 external definitions both times, no unexpected lost or added definition after normalizing the two renamed parent/handler names, and identical undefined-name sets. Thus no other provider or `/alternatename` target is removed.

## Measurements

Normal commands ran with the existing local x86 verification VM's wine wrapper and root `.venv` on PATH, `BFME_VM_WINEPREFIX=/home/bfme/.wine-pdb`, and the same seat claim owner/namespace. Initial host-only attempts stopped before compilation because Wine was absent; the established VM resolved that environment blocker without changing gates.

- `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameClient/Rva0055D2E8Write.cpp`: all defined functions already matched, before and after.
- `./build.sh Code/GameEngine/Source/GameClient/Rva0055D2E8Write.cpp`: 4/4 functions match before and after; 252 ledger bytes retained. Two string literals pass, zero skipped. Both unwind labels are verified through the parent EH data despite compiler-label renumbering.
- `python3 tools/eh_verify.py Code/GameEngine/Source/GameClient/Rva0055D2E8Write.cpp`: EXACT 1, not exact 0, baseline 0, missing objects 0.
- COFF symbol inspection using `build.read_object_symbols`, without compiling through that API: required exported definition 0 -> 1; old placeholder definition 1 -> 0; external definitions 551 -> 551; unexpected definition changes 0; undefined-name changes 0. Scratch comparison receipts remain under `build/seat3-box-export-20261106/`.
- `python3 tools/link_check.py Code/GameEngine/Source/GameClient/Rva0055D2E8Write.cpp`: before and after LINKS, LINKED 233 -> 233 authored bytes, one of one unit link-clean, against published census index `47fd56b879` (2026-11-06 05:39). This preview did not detect the missing retail export and is not a real-link result.
- `python3 tools/check_csv.py`: OK, 99,515 function rows, 9,320 symbol rows and 2,272 data rows. Row counts unchanged.
- `git diff --check`: clean.

## Remaining checks

The next scheduled real link must confirm that this one export disappears from its errors. No decrease from the authoritative 308 unresolved is claimed here. Current whole-image linking, startup, menu, skirmish, save/load and retail CRC agreement were not tested. The parent will publish this repair with the other independent writer repairs and retain each substantive change as a separate commit.
