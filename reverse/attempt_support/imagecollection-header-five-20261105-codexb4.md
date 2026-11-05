# ImageCollection header adoption in five W3D consumers

Inspected revision: `690fe638d473`. Date: 2026-11-05.

## Changes

The selected five `ImageCollection` queue rows could not include `Image.h`
because their sources lacked STLport opt-in. Add `// stlport46` in each and
replace the private collection declarations with the registered header.

- `GUI/GUICallbacks/W3DControlBar.cpp` and `Rva0010461FCtor.cpp` switch from
  `ImageClass.h` to `Image.h` to avoid duplicate definitions of `Image`.
- `GUI/Gadget/W3DPushButton.cpp` replaces its padded size-only `Image` view
  with the canonical class.
- `GUI/W3DGameWindow_initBorders.cpp` needs only the opt-in and collection swap.
- `GUI/W3DAptComponentColorPicker.cpp` replaces its private image view with
  canonical fields/accessors: dimensions +0x24/+0x28, filename +8,
  UV lower corner +0x14/+0x18 and texture dimensions +0x0C/+0x10.
  Include `Image.h` before `wwmath.h` and select `always.h`'s existing
  `_OPERATOR_NEW_DEFINED_` guard: STLport's `<new>` already supplies the
  placement-array new/delete definitions. No shared header is changed.

All paths above are relative to
`Code/GameEngineDevice/Source/W3DDevice/GameClient/`.
The target layout facts are documented in the existing canonical `Image.h`.
No new donor identity or layout inference is claimed.

## Verification

- `find_declared_unmatched.py` passes for all five sources.
- Scoped `./build.sh`: 99/99 rows for the four other units; 17/17 for the
  color picker, including funclets, string, float and named-import checks.
- `header_adopt_lane.py accept --class ImageCollection` passes each source
  and retires all five rows from `reverse/header_queue.tsv` itself.
- Combined ordinary `link_check.py` against census 2026-11-04 22:40,
  revision `3a95b274a2`, previews all five units as LINKS:

| Source basename | Census-linked bytes before | Preview after |
| --- | ---: | ---: |
| W3DControlBar.cpp | 8,152 | 8,152 |
| W3DPushButton.cpp | 5,098 | 5,098 |
| W3DAptComponentColorPicker.cpp | 1,762 | 1,762 |
| W3DGameWindow_initBorders.cpp | 2,046 | 2,046 |
| Rva0010461FCtor.cpp | 978 | 978 |

Total preview: 18,036 -> 18,036 bytes. This preserves existing coverage;
it is not a new census or a real-link/smoke result.

## Remaining work

The separate `Image` queue row for `W3DPushButton.cpp` remains: its required
header is `ImageClass.h`, while this source now uses `Image.h`, which defines
`Image` independently. Resolve the two canonical header definitions before
retiring that row. Image TU merge prerequisites in LINK-212 are unchanged.
The pre-existing dirty AttackObjectGroupOrder sources were not part of this work.
