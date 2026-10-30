# Font glyph API header cleanup

Inspected base: `4a9c1bf77d24c26497db7951d272607bfd0697f1`, 2026-10-30.
All three source scopes were claimed before editing.

The font rasterizer, character-data loader and missing-glyph check now obtain
`GetGlyphIndicesW` from the toolchain's real Platform SDK `windows.h`.
`FontCharsClassLoadCharacterData.cpp` also removes its local handle types and
`SelectObject` declaration. These are header repairs to existing matched
bodies; no donor name, new layout or source-file placement is established.

The SDK's `WinGDI.h:3171` gates the glyph declarations on
`_WIN32_WINNT >= 0x0500`, so each unit sets that supported configuration
input. The rasterizer opts into `// platformsdk` and drops the sweep include
directory, which otherwise selects the copied `windows.h` ahead of the SDK.
It also uses the SDK's `NO_STRICT` configuration to preserve its existing
opaque-handle `FontGlyphDCSelection` constructor signature. The missing-glyph
check already used `NO_STRICT`; the character-data unit uses the SDK's default
typed handles. The two newly opted-in units use `WIN32_LEAN_AND_MEAN` and
`NOMINMAX`.

Initial rasterizer trials established the prerequisites: retaining the sweep
include directory still hid the real header; without `_WIN32_WINNT` the SDK
omitted the API declaration; without `NO_STRICT` the constructor's external
name changed. The final source resolves all three and retains the original
external graph. No failed reconstruction remains in `Code/`.

Verification:

- Ordinary before/after builds pass all six rows across the three units and
  all eleven named import checks. All three declared-unmatched checks pass.
- Supported strict preparation passes 6/6 rows with reusable receipts. The
  rasterizer's existing funclet label renumbers to `$L23212`; its parent EH
  data still binds it to native `0x00766FA0`. `eh_verify.py` reports EXACT 1
  with no baseline exception across the scope.
- Before/after `link_census._comdat_sections` fingerprints are identical:
  five external COMDATs in the rasterizer and one in each sibling. Complete
  `object_symbols` results are identical for every unit, including definitions,
  references, weak bindings, alternate bindings and forced includes. This was
  checked again after strict preparation.
- Ordinary combined preview retains 3/3 LINKS and 1,754 authored bytes
  (1,322 rasterizer, 260 character-data, 172 missing-glyph check) against the
  index at `12b9e7a7c0` (2026-10-30 10:11 UTC).
- The owning `ms_header_audit.scan_files` and `refresh_queue` retire only
  these three queue records, covering nine local definitions. Each scoped
  scan completes without an error and classifies the unit clean; the only
  indexed occurrences left are supported configuration inputs. This does
  not clear the repository's wider header or include-closure debt.
- The staged-tree source/consumer audit exits 2, INCONCLUSIVE: the index
  predates the inspected base and affected consumer
  `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Full consumer
  selection/loss checks remain unverified. Carry these font providers and
  affected consumers into the next scheduled census; no census gain is claimed.

Object snapshots, scoped scans and the audit output are scratch under
`build/font-glyph-sdk-codexb4/`. No source paths, rows, pins or hatch counts
change.
