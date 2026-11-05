# Particle factory export signatures, 2026-11-05

Inspected source revision: `d1c843526e`. Ordinary preview index:
`f44cbcf5b0`, 2026-11-05 15:19 UTC.

`reverse/exit_link_blockers.tsv` lists 27 missing names for
`ModuleTemplateFactorySlots.cpp` and one for `Rva003AD6DFCreate.cpp`.
Retail `reverse/exports.csv` supplies all 27 exact factory signatures at
0x003AD6DF through 0x003ADC0F. The former unit emitted placeholder member
names; the latter put `TrackingPtr` inside `FXParticleSystem`, whereas the
export has global `TrackingPtr<FXParticleSystem::ParticleSystem>`.

The repair emits the exact exported virtual `createModule` specializations,
retaining each allocation size, constructor name, constructor parameter ABI
and exception specification. It does not identify the constructors or recover
the full module layouts. The address-based constructor views remain explicit.
The first factory already has an owner in `Rva003AD6DFCreate.cpp`; its duplicate
placeholder row and body in the other unit are removed. No source file moves,
pin additions, weak aliases, data definitions or debt retirements occur.

Verification:

- `./build.sh` on both units: **27/27 exact**, string/float/import checks pass.
- `find_declared_unmatched.py` on each: all defined functions matched.
- `check_csv.py`: passes, 99,480 rows (one duplicate removed).
- Ordinary `link_check.py` on both: **2/2 LINKS**. The displayed sum changes
  from 1,423 to 1,363 bytes because it previously counted 0x003AD6DF twice;
  the 27 unique factory bodies still cover 1,363 bytes.
- All **31,981** local `build/**/*.obj` files were searched for the removed
  external symbol names, parsing any hits as COFF symbols. None references
  or defines those names. See `removed-symbol-audit.json`.
- All 27 exact export names have compiled providers. See
  `export-providers.json`; no current local object references these names.
  This proves provider availability, not a new real-link result.
- `changes.json` records the old rows and exact replacement export names.

The next scheduled real link must confirm these names disappear from its
errors. No census gain or whole-game link result is claimed.
