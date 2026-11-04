# W3DMouse mutex storage and remaining flag identity

Inspected revision: `4ee23edebd`, 2026-11-04, seat codex4.

## Landed repair

`W3DMouse.cpp` formerly defined file-static `CriticalSectionClass mutex` and
`MutexClass threadMutex`, while `Rva007B6880Thunks.cpp` supplied separate
four-byte unsigned globals with the C names used by the split mouse units.
The mouse startup initializers therefore constructed the private objects,
not the objects the asset unit locked and the cleanup unit destroyed.

The real class objects now provide the C names. The cleanup unit only declares
them and calls their destructors. Both explicit data rows follow the definitions
to `W3DMouse.cpp`; the data-row sizeof probes require eight bytes for each real
class, and all eight zero-initialized bytes verify against retail. No initializer,
cleanup row, alias, pin or source path was removed.

## Verification

- `./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp Code/GameEngine/Source/Common/Rva007B6880Thunks.cpp`:
  **923/923 functions matched**, **18/18 data rows verified**, source claims OK.
  The mutex startup initializers remain matched, unlike the earlier logged
  attempts that replaced the static definitions with declarations alone.
- Both sources pass `find_declared_unmatched.py`; `check_csv.py` passes with
  99,451 function rows and 2,268 data rows. `git diff --check` passes.
- `data_check.py` on both sources finds only the pre-existing `duplicate-def
  _isThread 0x009E4B30`. The two mutex wrong-name findings are gone, but
  `repair_queue.py retire data .../W3DMouse.cpp` refuses this unregistered flag
  finding. **No debt-register line was removed.**
- Current-object `link_check.py` preview against the published index dated
  2026-11-04 13:15 at `f6d845ecd4`: W3DMouse **LINKS**, own scope 776 bytes.
  The cleanup unit remains blocked by `?g_Va00DDEEE4@@3PAIA` and
  `?g_Va00DDEF14@@3PAIA`, neither changed by this repair. These are preview
  results, not a census gain or whole-image clearance.

## Reverted flag experiment / next step

The split asset unit defines external C `isThread`, while W3DMouse defines a
second file-static flag. The asset unit was held by `class:CameraClass`
(`yasinschroeder-claude`), so this pass did not edit it.

Declaring the external flag in W3DMouse makes every checked body except
`W3DMouse::init` match. At RVA `0x000990CF`, size 58, retail orders the redraw-mode
comparison, flag clear and thread-address load in that order. The external flag
with the original C++ orders the flag clear before the comparison. Duplicating
the clear into the two branches instead orders comparison, thread address,
flag clear. Boolean temporaries add setcc/test instructions; integer temporaries
load the mode into a register and increase the body to 60 bytes. Ordinary
conditional, comma, goto, typed-view and qualified-call forms did not recover
the target order in isolated scratch compilations.

The flag experiment was fully reverted; no nonmatching body remains in Code.
Next, recover an exact external-flag source form, or reconcile the flag during
an approved TU merge after the separate AsciiString obstacle in LINK-213 is
cleared. Then rerun the full source match and the data retirement command.
