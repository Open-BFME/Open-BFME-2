# GlobalLanguage consumer header adoption (2026-11-05)

Inspected revision: `2e8ed35197`. This is header debt cleanup; no census,
real-link or runtime improvement is claimed.

Ten consumers now include the existing canonical
`Code/GameEngine/Include/Common/GlobalLanguageClass.h` instead of defining
private GlobalLanguage/font records. The header and its contract are unchanged.

The display/debug font fields previously flattened at +0xC8/+0xCC/+0xD0
now use `m_nativeDebugDisplay.name/size/bold`, retaining their measured offsets.
The four help-box override records at +0x104/+0x110/+0x11C/+0x128 now use the
canonical FontDesc members. The returned 16-byte getter records retain their
existing identities and fourth dword; only their 12-byte language overrides
change declaration. Credits, message, time-separator, default display-string
font and hard-wrap accesses retain the same offsets through the shared class.

Verification:

- `./build.sh` over all ten sources: 184/184 matched rows; 11 data rows,
  129 nonempty literals, 39 empty-string references, 69 float literals and
  13 named imports verified. Funclet renumbering is resolved by the verified
  parent EH graphs.
- `find_declared_unmatched.py` over all ten sources: all defined functions
  are already matched.
- `header_adopt_lane.py accept --class GlobalLanguage` accepts all ten;
  the tool retired exactly ten rows from `reverse/header_queue.tsv`.
- `link_check.py` over the final cohort: 10/10 LINKS, 24,365 -> 24,365 bytes,
  using the published census index dated 2026-11-05 05:17 at `c95fcfcfcd`.
  This is a current-object preview, not a new census.
- Before/after `link_census.object_symbols` equality: all 517 external
  definitions, references, weak bindings, alternatenames and forced includes
  preserved. No provider or linker alias is removed.
- `check_csv.py` and `git diff --check` pass.

Remaining queued units are unchanged: GameEngineInit.cpp includes
`spline_service.h`'s separate SubsystemInterface definition; the owner
GlobalLanguage.cpp still has a typed local-font list at +0x138 where the
canonical header retains an opaque pointer, plus separate subsystem/font
views. Those require separate contract reconciliation, not a consumer-only
header substitution. Their queue rows remain.

Accepted sources:

- `Code/GameEngine/Source/GameClient/Credits.cpp`
- `Code/GameEngine/Source/GameClient/InGameUIMessages.cpp`
- `Code/GameEngine/Source/GameClient/InGameUIPostDraw.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayGatherAnimationDebuggingInfo.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayGatherDebugStats.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayGatherNetworkStats.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayInit.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayStringManager.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayStringWordWrap.cpp`
- `Code/GameEngine/Source/Common/Rva0029F8B8.cpp`
