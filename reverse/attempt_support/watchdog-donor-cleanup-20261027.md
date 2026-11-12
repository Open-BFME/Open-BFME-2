# Watchdog donor cleanup and current-queue checks, 2026-10-27

Inspected source revision: `48ba8143a5`. Ordinary-preview index:
`bf3dd31211`, 2026-10-27 00:39, retail-truth-4; fetched again before this pass.
This is source/debt cleanup and preview evidence, not a census measurement.

## Watchdog scope (LINK-112)

Claim: `file:Code/GameEngine/Source/Common/Watchdog.cpp`.
The constructor's native thread-wrapper binding was already repaired by
`ff79e49d51`; this pass does not claim that link repair again.

Before editing, `find_declared_unmatched.py` reported six matched rows and
three donor definitions allowed by `present-unmatched`. The three names were
`?suppressTimeouts@Watchdog@@QAEXXZ`, `?update@Watchdog@@QAEXXZ` and
`?resumeTimeouts@Watchdog@@QAEXXZ`. Searching C++/headers under `Code/` found
only their declarations/definitions in Watchdog.cpp. For each exact decorated
name, `link_check.is_referenced(link_check.load_index(), name)` returned false;
the index reference graph had no incoming edges.

Current matched retail owners already cover the counter/timestamp operations:

| RVA | Size | Existing source under `Code/GameEngine/Source/Main/` |
| --- | ---: | --- |
| 0x00225476 | 28 | `BfmeDfe6e4_M_rva00625476.cpp` |
| 0x00225492 | 56 | `BfmeDfe6e4_rva00225492.cpp` |
| 0x00225699 | 39 | `BfmeDfe6e4_M_rva00625699.cpp` |

The middle unit also owns the two 11-byte critical-section helpers at
0x00225460 and 0x0022546B. These are current ledger/retail facts. The donor
Watchdog spellings and the shared field/call structure are an identity lead;
this pass neither proves nor applies a class rename. In particular, the donor
resume body was an expanded reconstruction, whereas the existing decrement
owner calls the timestamp sibling. No native body is newly recovered here.

Removed the three donor definitions, their declarations, their now-unused
lock helper class and enter/leave methods, and unused import declarations.
Kept the critical-section storage and all other layout/flags. Removed exactly
the corresponding three `present_unmatched` baseline keys. No pins, rows,
data identities, source paths or shared headers change.

Verification:

- `./build.sh Code/GameEngine/Source/Common/Watchdog.cpp`: 6/6 matched;
  two renumbered funclets verified through parent EH data; named import passes.
- `find_declared_unmatched.py` after: all defined functions already matched.
- `eh_verify.py`: EXACT 2, zero missing objects or baseline findings.
- `data_check.py`: zero shadow findings; `--converged`: ten addresses,
  zero second names or unjudged rows.
- Compared `link_census._comdat_sections` on the saved before-object and the
  ordinary build's after-object: no added external COMDATs and no digest change
  among retained external COMDATs. Digests include bytes and named relocations.
  Only the three donor methods, ScopedWatchdogLock constructor/destructor and
  WatchdogCriticalSection enter/leave disappear (seven names).

The same explicit current-object cohort previews LINKS for all seven units
before and after; each unit's authored-byte count is unchanged:

| Source | Authored bytes |
| --- | ---: |
| `Code/GameEngine/Source/Common/Watchdog.cpp` | 203 |
| `Code/GameEngine/Source/Common/WatchdogDtor.cpp` | 127 |
| `Code/GameEngine/Source/Common/WatchdogThreadFunction.cpp` | 440 |
| `Code/Libraries/Source/WWVegas/WWLib/thread.cpp` | 294 |
| `Code/GameEngine/Source/Main/BfmeDfe6e4_M_rva00625476.cpp` | 28 |
| `Code/GameEngine/Source/Main/BfmeDfe6e4_rva00225492.cpp` | 78 |
| `Code/GameEngine/Source/Main/BfmeDfe6e4_M_rva00625699.cpp` | 39 |

Scratch before-object and preview logs are under
`build/watchdog-cleanup-20261027/`. The preview's 889 census bytes versus
1,209 current bytes includes earlier repairs and is identical before/after
this cleanup. No linking or image-ownership headline gain is claimed.

Remaining: reconcile the existing BfmeDfe6e4/Watchdog identities with their
callers in the naming lane. Confirm earlier link repairs in the normal census.

## Default-queue triage

`WW3D2/Rva00131965TextureLoaders.cpp` was served for its historical selected
BFME_DX8_Thread_Lock blocker. With the already-repaired current
`WW3D2/BfmeDX8ThreadLock.cpp` provider, both preview LINKS (2,458 and 247
authored bytes). The texture-loader build verifies 18/18 rows, seven funclets
through their parent EH data, two string references and three imports.
No source change was needed. This extends LINK-106's caller evidence only.

`WWLib/StlSweepW4Rva00584405.cpp` reproduces LINK-064's U1/C1/S1 on the
current object: the copy-constructor name is pinned to the assignment at
0x00583A1E, and the selected overflow at 0x0058431D is wrong. The family is
still split among Rva002337F0, BfmeStringRecord00111ACF and Rva00584405Element.
No trial repeats the already-documented `/Ob0` forwarder failure. Source is
unchanged; the tool-recorded blocked attempt in `reverse/re_attempts.log`
hands off family identity reconciliation as the prerequisite.

The data picker also served ToggleDeploySpecialAbilityUpdateCtor.cpp's
secondary table at 0x00855348. Its proposed owner remains ModuleUpdateDtors.cpp's
private dummy storage, already recorded as blocked in the attempt log. No
declaration trial or identity substitution was attempted. All these triage
scope claims were released before the Watchdog cleanup.

### Synchronization members and TU composition, 2026-11-12

At a7b64a57f7 the three Watchdog sources disagreed on the critical section
and the mutex guard. The constructor and destructor pass this+0x70 to
InitializeCriticalSection and DeleteCriticalSection; the working thread
locks the same member. All three now use CRITICAL_SECTION directly.
The seed and destructor use WWLib/mutex.h. The seed passes its mutex
member at +0x88 directly to the guard.

Including mutex.h in the constructor as well introduces a nontrivial mutex
destructor and an extra EH state in the 0x00225616 body. The accepted
constructor retains its existing mutex declaration. All 22 rows and 14
named imports pass together; the three units preview LINKS at 915 bytes
both before and after the change.

The remaining tu_views conflict is Watchdog's base clause. The dry merge
rejects the constructor because ThreadClass is absent from the seed's base
list, and rejects the destructor on bytes. At RVA 0x007E6FD8 the bridge
queue records a 20-byte emitted table for a 16-byte retail table. Slot 1
selects ThreadClass::Execute instead of RVA 0x002256C0; slot 3 selects
Watchdog::start instead of RVA 0x002255AD. Reconcile the base override
and verify both installers before merging. No source paths moved.
