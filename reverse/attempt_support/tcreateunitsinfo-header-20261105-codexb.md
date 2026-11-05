# TCreateUnitsInfo: three canonical-header adoptions

Inspected revision: `828dcea71e`, 2026-11-05; worker `yasinschroeder-codexb`.
Scope was claimed through `class:TCreateUnitsInfo` and its adoption footprint.

## Applied scope and evidence

Replaced the private `struct TCreateUnitsInfo` definitions in:

- `Code/GameEngine/Source/GameLogic/AI/AIPlayerTeamBuild.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AISkirmishPlayer.cpp`
- `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsReinforcements.cpp`

Each now includes the existing registered
`Code/GameEngine/Include/GameLogic/TCreateUnitsInfo.h`. The header and class-key
are unchanged. Its target-evidence comment establishes the 0x18 stride and the
fields at +0, +4, +8, +0xC, +0x10 and +0x14; its size assertion remains active.
AIPlayerTeamBuild's `unitInfo[i].m_bfmeString0C` accesses become `m_0C`.
ScriptActionsReinforcements's explicitly qualified unit-info accesses become
`m_08` (+8, formerly `experienceLevel`) and `m_0C` (+0xC, formerly `upgradeList`).
The unrelated `params.m_08` and the loader's local `upgradeList` are untouched.
These are reconciliations to existing canonical fields, with no new semantic
name, layout claim, symbol identity, pin or alias.

The automatic adoption codemod declined ambiguous member uses, a spelling
collision, an unresolved include during inventory, and a layout-probe compile.
Manual adoption follows `docs/linking.md`'s supported `accept` path; none of
those automatic transformations was forced. The complete sources pass the
normal compiler, byte verifier and acceptance checks below.

## Verification

- Before edits, `./build.sh` on all four queued sources: 140/140 function rows
  exact, string/float/import references pass.
- Applied three sources: 109/109 function rows exact; 57 literals, six empty
  strings and 26 compiler float literals verify.
- `header_adopt_lane.py accept --class TCreateUnitsInfo` on those three sources:
  PASS for each, and the tool retired exactly three rows from
  `reverse/header_queue.tsv`.
- Final build including the restored loader: 140/140 function rows exact;
  58 literals, seven empty strings and 26 float literals verify.
- `find_declared_unmatched.py` before and after: all defined functions matched.
- Current-input `link_check.py` preview: all three sources LINKS. Against the
  index's 2026-11-05 15:52 census at `112a456a2c`, AIPlayerTeamBuild preserves
  9,162 bytes, AISkirmishPlayer previews 3,658 -> 3,663 bytes, and
  ScriptActionsReinforcements preserves 1,834 bytes. This is a scoped prediction,
  not a new census or real-link result; no headline link gain is claimed.

Local logs: `build/tcreate-final-build.log`, `build/tcreate-final-link.log`.

## Remaining loader adoption

`Code/GameEngine/Source/Common/RTS/TeamTemplateInfoLoadFromDict.cpp` is restored
byte-for-byte to HEAD, rebuilt successfully, and retains its header-queue row.
Replacing its private record and qualifying only its unit-info member accesses
keeps `loadFromDict` at 3,606 bytes but reverses two independent register
restores after the home-location copy:

```
retail +2235: 8b 75 08 8b 7d e0   mov esi,[ebp+8]; mov edi,[ebp-20h]
trial  +2235: 8b 7d e0 8b 75 08   mov edi,[ebp-20h]; mov esi,[ebp+8]
```

Those four operand-byte differences are the only parent-body differences for
both the existing inline `copyHome` helper and direct Coord3D assignment. The
dependent scoped funclet verification consequently refuses the nonexact parent.
An explicit `memcpy` trial changes register allocation more widely, despite
retaining the same length. All trials were reverted; no nonmatching source
remains in Code. The next useful hypothesis must explain this VC7.1 scheduling
change while retaining the canonical record, rather than repeating those three
copy spellings. Local trial logs are `build/tcreate-loader-trial.log`,
`build/tcreate-loader-direct.log` and `build/tcreate-loader-memcpy.log`.
