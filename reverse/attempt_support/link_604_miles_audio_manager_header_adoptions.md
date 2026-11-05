# LINK-604: three MilesAudioManager consumer adoptions

Inspected revision: `d7dd0eadbeb1bf772eef88bfaa25ab8a45fba741`.
Preview index: `f44cbcf5b0`, 2026-11-05 15:19 UTC.

The queued consumers used private manager declarations with incompatible typed
views of fields that the canonical header deliberately leaves opaque. Adopted
`Code/GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h` without
changing that header, function identities, compiler flags or ledger extents:

| Consumer under `Code/GameEngineDevice/Source/MilesAudioDevice/` | Existing target facts and retained access |
| --- | --- |
| `MilesAudioManagerScaledValue.cpp` | Settings pointer +0x10, scale +0x8C, three volume records at +0x12C with stride 0x1C4, selector +0x678. The local settings view casts the canonical pointer; the existing nested GlobalVolumeData declaration now follows the header's forward declaration. |
| `MilesAudioManager_getGlobalReverbMultiplier.cpp` | Settings pointer +0x10, flag +0x6A7, provider table +0x6CC and count/selection +0x9CC/+0x9D0. The reverb view casts the canonical settings pointer; ProviderInfo comes from the header. |
| `MilesAudioManager_isPlayingLowerPriority.cpp` | List storage at +0xA40/+0xA44. Cast the canonical opaque spans to the existing local list-head view. |

These offsets and operations were already documented in each source and the
canonical header; no donor layout or new semantic name is inferred here.

Provider preservation: saved each original verified object before editing and
compared COFF graphs with `class_cleanup.runtime_graph` / `same_runtime`.
All three preserve every external definition, relocation target, weak binding,
COMDAT policy, code and data section. ScaledValue's complete non-debug graph is
identical. The other two differ only in `.drectve`: including the canonical
header inherits its seven existing AsciiString-to-StringBase aliases, alongside
the unchanged MSVCRT/OLDNAMES directives. No alias or provider was removed, and
no source pragma was added. Original private manager declarations supplied no
inline bodies. Local detailed comparisons are in `build/miles_adopt/`.

Checks:

- Original and final `./build.sh` runs: all three functions byte-match; literal,
  float and import checks pass.
- `find_declared_unmatched.py`: all defined functions already matched.
- One `header_adopt_lane.py accept --class MilesAudioManager` over all three
  consumers: three passes and three queue rows retired by the owning tool.
- Combined `link_check.py` preview: all three link cleanly; 751 own executable
  bytes retained (83 reverb, 135 priority, 533 scaled value).
- `check_csv.py` and `git diff --check`: pass.

This retires three header debts and removes three private manager declarations.
It does not claim a new census, a successful real link or any game run.
