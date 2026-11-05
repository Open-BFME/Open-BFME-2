# GameLODManager consumer adoption, 2026-11-05

Inspected source revision: `7ac44ac9c4`. Worker: `yasinschroeder-codexb5`.
Provider index: census 2026-11-05 05:17, `c95fcfcfcd`.

## Retained change and target evidence

Five consumers include the existing `Code/GameEngine/Include/Common/GameLODManager.h`
instead of their private GameLODManager bodies. The header's documented native
constructor/allocation and consumer accesses establish the offsets used here:

| Consumer | Preserved use | Link preview bytes before/after |
| --- | --- | --- |
| Common/GameEngineInit.cpp | allocate 0x17F8 and call constructor/init | 9,424 / 9,424 |
| Drawable/Draw/Rva000C433AAttachment.cpp | detail word +0x1774, now m_1774 | 291 / 291 |
| GameClient/W3DDisplay.cpp | detail word +0x1774, now m_1774 | 4,734 / 4,734 |
| GameClient/W3DDisplayInit.cpp | static level +0x1768, now m_1768 | 1,599 / 1,599 |
| GameClient/Water/W3DWaterDrawRiverWater.cpp | water word +0x1784, now word1784 | 1,984 / 1,984 |

Names remain the canonical header's existing names; no donor name is inferred.
No header, provider, ledger identity, pin, alias or compiler option changes.

The initializer's first trial used the header's GameLODManager::rva00202739
prototype directly. Bytes matched, but accept refused loss of linked bytes:
the actual provider at 0x00202739 is still Rva00202739::rva00202739 in GameLOD.cpp.
The retained call explicitly casts to that existing provider view, preserving the
original call identity and removing the old private GameLODManager forwarding
wrapper. This is a prerequisite for adoption, not a new provider or alias.

## Verification

- `find_declared_unmatched.py` passed before and after edits for all five sources.
- Scoped `./build.sh` runs: 165/165 code rows matched across five sources;
  three data rows verified; strings, float constants and imports passed.
- `header_adopt_lane.py accept --class GameLODManager` passed all five retained
  units together and retired their five queue rows through the owning tool
  (two earlier accept calls retired four, the final call retired the fifth).
- Final `link_check.py` on all five current sources: 5/5 LINKS,
  18,032 -> 18,032 bytes against the above index. No census gain is claimed;
  no real link or smoke run was started.
- `check_csv.py` passed after the initial pull. Commit hooks perform final gates.

## Remaining cohort

Automatic adoption was attempted for all seven selected consumers. Two were
left unchanged and remain in header_queue.tsv:

- Rva00201DC4LODDefaults.cpp: its two 32-bit word17D0/word17D4 fields must be
  reconciled with the header's 64-bit m_numRAM, plus the component declarations
  and old 0x17F4 size assertion. Verify constructor stores after reconciliation;
  do not change the canonical native allocation/alignment evidence.
- MilesAudioManager.cpp: its AudioLODSettings projection and opaque padding
  differ from the header. Preserve the native narrow ambient-cap read and
  Dolby byte-to-bool behavior while adopting AudioLODInfo; field-size agreement
  alone does not establish those access contracts.
