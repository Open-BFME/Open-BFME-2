# TU evidence 0x00262045..0x0026228F: DisplayStringManager identity, no rename path

Served: `next_work.py` TU-evidence item, 11 rows in 11 sources between
`DisplayStringManager::link` (0x00262027, approved Z) and AIUpdate.cpp
(0x002622E9, proposed S). `tu_evidence.py --source` reaches none of them.

## Target facts (retail, ledger)

- 0x00262002 26B `??0Rva0026201C`: SubsystemInterface base ctor 0x001B4E63,
  +0x0C and +0x10 cleared, own vptr 0x00BF9010.
- 0x0026201C 11B `??1Rva0026201C`: re-seats the vptr, tail-jumps the
  SubsystemInterface dtor 0x001B4E74.
- 0x00262027 30B `DisplayStringManager::link` (head +0x0C, string next +0x0C).
- 0x00262045 50B `Rva00262045::unLink`: if string null or head (+0x0C) null
  return; next->prev = prev; prev ? prev->next = next : head = next.
  Called by `W3DDisplayStringManager::freeDisplayString` (0x00090381) on its
  own `this`.
- 0x00262077 28B `??_GRva0026201C`: scalar deleting dtor of the same class.
- `W3DDisplayStringManager` ctor 0x00090360 calls 0x00262002 as its base ctor;
  its source already views the base as `Rva0026201C` with `m_stringList` +0x0C
  and `m_currentCheckpoint` +0x10.

## Donor facts (Zero Hour, BFME 1)

- ZH `GameClient/DisplayStringManager.cpp` defines, in this order: ctor
  (`m_stringList = m_currentCheckpoint = NULL`), empty dtor, `link`, `unLink`
  (lines 43, 53, 67, 85). ZH's `unLink` is the same next/prev unlink with
  `assert`s where BFME 2 has null guards (as BFME 2's rowed `link` does).
- BFME 1 (`reference/open-bfme-1/game/GameEngine/Source/GameClient/DisplayStringManager.cpp`)
  rows the ctor at b1 0x00410240 and the dtor (vptr re-seat plus tail call) at
  b1 0x00410290: the same shapes.

## Structural inference

Retail order ctor, dtor, link, unLink, then the deleting dtor is ZH's file
order, and W3DDisplayStringManager derives from this class. `Rva0026201C`
and `Rva00262045` are DisplayStringManager. Respelled, 0x00262002..0x00262077
carry Z anchors for DisplayStringManager.cpp (ZH defines all four
out of line there), so tu_map would approve the served row 0x00262045 and its
neighbours. The rows after 0x00262093 (accessors, StateMachine inline copies,
FLT_MAX vslot leaves) sit before AIUpdate.obj and stay unplaced either way:
AIUpdate.cpp is only proposed (noncontiguous), so no bracket names them.

## Why nothing landed

- `rename.py class --name Rva00262045|Rva0026201C --new DisplayStringManager`:
  refused, the token already names the `link` row (the class mode never merges
  into an existing class).
- `rename.py class --fold Rva0026201C --into DisplayStringManager`: needs a
  `??_7DisplayStringManager@@6B@` name at 0x00BF9010; the ctor's object binds
  only `??_7Rva0026201C@@6B@`.
- `canonical:zh`: `name_evidence.py` has no zh-body candidate (ZH's sweep
  `unLink` is 44B with asserts, no placement; ZH ctor placed near elsewhere).
- `rename.py function` changes the identifier only, never the class.

Next step: a rename mode (or class-reconciliation commit) that folds a
placeholder class into an existing real-named class on ZH same-order and
base-ctor evidence; then the four rows take Z and the TU map approves them.
