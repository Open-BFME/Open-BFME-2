# MeshModelClass memory-accounting header adoption

Inspected base: `2b6ed5e90f1188301b63a6e5092476d365b50c64`.
Source: `Code/Libraries/Source/WWVegas/WW3D2/MeshModelClass_ComputeRamSize.cpp`.

Replace the private MeshModelClass definition with its existing canonical header.
MatInfo now has the canonical MaterialInfoClass pointer type. The call at target
RVA 0x00188117 still names the existing opaque BfmeThingVNQ::bfmeTotalVNQ owner
at 0x0016EEE0 through a call-only cast; this does not establish that owner's
original method name. The function remains the existing 67-byte row at
0x001880E0. Correct the source comment to distinguish that BFME2 address from
the BFME1 donor address 0x0096C9B0.

Verification:

- Normal `./build.sh` before and after: 1/1 exact, with string, float and import
  checks passing. `find_declared_unmatched.py`: all defined functions matched.
- [Object comparison](object-comparison.json): both non-debug sections have
  identical contents, flags and symbolic relocations. The one external provider,
  its COMDAT fingerprint, and all four root references are identical.
- Independent before/after `link_check.py` previews both report LINKS,
  67 -> 67 bytes against census 2026-11-03 20:03 at 8661f15284.
- `header_adopt_lane.py accept --class MeshModelClass` passes and retires exactly
  this source's queue row. No other header debt is retired.
- `check_csv.py` passes: 99,433 function rows, 9,341 symbols, 2,269 data rows.

The automatic 24-unit cohort trial applied no changes: remaining units need
local declaration/include, field-view or code-generation reconciliation. This
commit changes only the memory-accounting unit. No source paths, hatches,
pins, global names or census measurements change. No new linking credit,
full real-link or runtime verification is claimed.
