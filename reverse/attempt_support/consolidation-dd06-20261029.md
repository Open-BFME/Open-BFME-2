# dd-06 consolidation / header handoff, 2026-10-29

Worker `dd-06`, sandbox `fleet-dd-06` (bx_k5wtr73b) from
`bfme2-toolchain-20261029`, master `ab249dd2c4`. Nothing was pushed; the
commits in this bundle are the re_log verdicts and this note.

Every attempt below was run on the sandbox with the tool's own dry run; no
source or ledger change survived, and the tree was reverted clean before the
next item.

## 1. Class header `Xfer` — `PersistentStorageThread.cpp` (class:Xfer)

Queue row 651, claimed and released.

- Its blocker line (`Data rows: FAIL 3 of 3`) is **stale**: on `ab249dd2c4`,
  `python3 tools/data_rows.py --verify Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp`
  reports `Data rows: OK (3 row(s) byte-verified)`.
- The real blocker is the unit's private `XferStub`: its declared slot order
  disagrees with `Code/GameEngine/Include/Common/BfmeXfer.h` (stub index 10 is
  `_slot28(StatsXferVersion &)`, index 27 is `_slot6c(AsciiString &)`, index 30
  is `_slot78(int &)`), and the unit also declares `class Xfer : public XferStub`
  plus `XferSave`/`XferLoad` deriving from the stub. Adopting the canonical
  header needs those two classes to declare the header's pure-virtual overrides
  (`BeginBlock`/`EndBlock`/`SkipBlock`/`operator==(const char *const &)`/
  `XferData`) first, which is a reconstruction, not a header adoption.
- Remedy order: reconcile `XferSave`/`XferLoad` against `BfmeXfer.h` in their own
  verified commits, then retry the adoption.

## 2. Split `GameWindowManagerSendMsg.cpp` -> `GameWindowManager.cpp`

Carve of `0x002C0E7D`/`0x002C0EA9` verifies (`alone: 2/2 carved rows match
beside the TU under its flags`), residual keeps 2 rows. The merge verifier then
refuses the donor:

    error C2365: 'GWM_DESTROY' : redefinition; previous definition was an 'enumerator'
    error C2365: 'WIN_STATUS_DESTROYED' : redefinition; ...

The seed is a ZH-derived TU that includes `GameClient/GameWindowGlobal.h`, which
already defines both enumerators; the donor's anonymous enums duplicate them.
`tu_skeleton`'s duplicate-declaration repair covers declarations, not anonymous
enums.

Remedy (shared, unlocks the C2011/C2365 family in the merge map, ~275 donors):
teach the carve to drop a donor-local anonymous enum whose enumerators the
seed's included headers already define, or guard it in the donor on the header's
include guard where the values agree.

## 3. Split `W3DGameClient_setTimeOfDay.cpp` -> `W3DGameClient.cpp`

Carve of `0x0004C884` is refused before writing:

    blocked: an escape-hatch count would grow (hatch_counters rule 3): a copied
    helper or datum carries one

`data_moved: ['W3DGCData00DE2000']` — the carved body uses an address-named
datum whose row would have to travel. Remedy: give the datum a real name
(`tools/name_globals.py`) before carving, or split the other direction.

## 4. Split `GameSlotIsPlayer.cpp` -> `GameInfo.cpp`

Carve of `0x003FFF62` verifies (`alone: 1/1`). The merge verifier refuses:

    error C2365: 'SLOT_OPEN' : redefinition; previous definition was an 'enumerator'
    error C2365: 'SLOT_CLOSED' : ...

This one is **semantic**, not cosmetic: the donor's enum numbers `SLOT_PLAYER`
6 (BFME 2, `SLOT_AI_5` inserted), while the seed's
`reference/shims/nat/GameNetwork/GameInfo.h` `enum SlotState` numbers it 5. The
body compares `[ecx+4]` against 6, so taking the seed's header would change the
emitted constant. Remedy: correct the shim's `SlotState` to BFME 2's numbering
(shared fix, touches `reference/shims/` and needs the full gate), then split.

## 5. Merge `AnimationAsset.cpp` (merge-map "ready" TU, 2 accepted donors)

Claimed the TU and its 3 donors, ran `tu_skeleton.py --merge` with `--no-claim`.
The merge wrote its candidate, then the gate's `ms_header_audit` index build
spent **21+ minutes at 100% CPU in a single `cl.exe -E -MD -EHsc` probe**
(`build/ms_header_audit/tmp*.cpp`) with no progress past the `kitchen sink (c)
drops <...>` lines. Abandoned; `git reset`/`checkout`/`clean` restored the tree.

This is the README's "first merge in a fresh sandbox" cost, but the probe did not
finish in the window: consider a snapshot with the index prebuilt
(`bfme2-toolchain-20261029b`) or a per-probe timeout in the audit.

## 6. ms-header item `AnimalAIUpdate.cpp` — not attempted

Left for the next seat with the trap named: the file's
`extern "C" void __cdecl free(void *)` / `extern "C" int __cdecl fprintf(void *,
const char *, ...)` exist because the bodies call the **in-image** CRT rows
(`free` is rowed at `0x00030830`) and pass `void *theLogicRandomLogFile` as the
stream. Replacing them with `<stdlib.h>`/`<stdio.h>` makes both declarations
dllimport (indirect calls) and needs a `FILE *` cast at ~15 call sites; check the
callee bytes before taking the row.

## 7. Three more split candidates, all refused by the tool itself

Picked from `build/fleet/merge_map/` as files that are mixed in exactly two TUs
with at most two rows each; claimed, dry-run with `--no-claim`, nothing written.

- `ToggleSpecialAbilityUpdateSlot17.cpp` -> `ToggleHiddenSpecialAbilityUpdate.cpp`:
  the carve itself is fine (`carved: ['0x004AE22D']`, `alone: 1/1`), but the
  merged candidate fails to compile at line 227 with a `compile:` rejection
  (the diagnostic was truncated by my log capture; re-run
  `--split ... --dry-run` without the `cut` to read it). Same shape as the
  anonymous-enum family: a donor declaration the seed's headers already carry.
- `CrateCreationEntryListInsert.cpp` -> `CrateSystem.cpp`: `no row could be
  carved` — both rows (`0x0035CB8D`, `0x0035CBFE`) are `no definition spells its
  name`, i.e. emitted by a macro/loop the carve cannot attribute. Not splittable
  by this tool until those rows are spelled explicitly.
- `VslotSmallBodiesAF.cpp` -> `AptOnline.cpp`: `a namespace/extern "C" block
  defines something: carve not supported` (the row `0x005174E4` carves, the
  guard refuses). Remedy: move the defining block out of the anonymous
  namespace/extern "C" scope in its own verified change, then split.

Net for the split lane: the dominant refusals in one worker's sample are the
anonymous-enum redefinition at the merge verifier (items 2 and 4) and
tool-level carve limits (item 7). Both are shared fixes, not per-file work.

