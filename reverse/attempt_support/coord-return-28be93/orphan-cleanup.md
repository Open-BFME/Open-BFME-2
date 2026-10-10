# Obsolete explicit-output source removed

`bf2ecc545b668c08ce142e3dd9a06b7092de9d34` removed the 77-byte row
`?rva0028BE93@Object@@QBEPAUCoord3D@@PAU2@@Z` but retained its source,
`Code/GameEngine/Source/GameLogic/Object/Rva0028BE93Coord.cpp`. The file
therefore had no matched rows and refused the full source-claims gate.

The existing code pin and `WeaponGetPreAttackDelay.cpp` consumer instead use
`?rva0028BE93@Object@@QBE?AUCoord3D@@XZ`: a by-value result with a hidden
result pointer. The removed file defined the obsolete explicit-output form;
no other Code source references that form.

The complete correct-contract reconstruction remains in
`reverse/attempts/0x0028be93.cpp`, with its canonical-header investigation in
`proof.json` beside this note. Its private memberwise-copy proof is bank-only:
the canonical Coord3D aggregate-initializer migration remains unfinished.
Removing the orphan does not admit that bank or restore the withdrawn row.

The pre-cleanup full gate verified all 76,108 function rows, all 106 data
rows, string and float literals, imports, pins, and module registrations.
Its sole refusal was this row-less source. No verifier or whitelist changes
are required for the cleanup.

At publication rebase, upstream `3d069fec3f8679ecba11cfdaf88604b02e8105e3`
had independently moved the same obsolete source to
`refuted-pointer-prototype.cpp` beside this note. That archived draft is
preserved; only the redundant production-source deletion is superseded.
