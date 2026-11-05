# MemoryReadFile canonical File prerequisite

2026-11-05; inspected base `c1a5a2b848fc382bcfb6d7088dfe1886bd24bd1f`;
claim owner `yasinschroeder-codexb5`.

## Retained repair

`Code/GameEngine/Source/Common/System/MemoryReadFile.cpp` now includes the
registered `Common/File.h` instead of declaring File privately. Constructor
accesses use the canonical `m_open`, `m_access` and `m_nameStorage` fields.
The latter remains storage for the existing StringBase operation at +4;
this change does not claim a new string layout.

`File_createMemoryReadFile.cpp` includes only that File header and its existing
MemoryReadFile declaration. Unused File-family declarations and the BFME1
PreRTS/AsciiString header environment are removed. Its scalar typedefs become
their identical underlying types. The donor-path comment remains BFME1
provenance, not evidence of BFME2's original translation-unit path; the current
TU map approves the provisional MemoryReadFile.cpp grouping.

## Verification

- Before and after: `./build.sh` on both sources passes all three rows
  (38-byte `bfmeTakeEC`, 89-byte constructor and 71-byte factory), one string
  reference, and all float/import checks.
- `find_declared_unmatched.py` on both sources: all defined functions matched.
- `header_adopt_lane.py accept --class File .../MemoryReadFile.cpp`: PASS,
  retires exactly one header queue row through its owning tool.
- Ordinary `link_check.py` on both current objects: LINKS, 127 -> 127 and
  71 -> 71 authored bytes, against census 2026-11-04 22:40 at `3a95b274a2`.
  These are preview preservation results, not new census coverage.
- COFF comparison with saved pre-edit objects: all retained external code/data
  symbols have identical bytes and relocation tuples (seed: four code/two data;
  factory: one code). Neither object adds an undefined symbol. The factory drops
  only an unrowed compiler vector-construction helper
  `??_H@YGXPAXIHP6EPAX0@Z@Z` and three unused TU-local timing constants.
  The existing Locomotor.cpp object also defines that helper. No alias, pin,
  class header, compiler flag or path is changed.
- `check_csv.py` passes; no data/code-identity/hatch/flag-override or remaining
  header/ms-header register keys name either source. No debt is retired by a
  hand deletion or by removing a source.

Local raw logs: `build/memoryreadfile-before-build-codexb5.log`,
`build/memoryreadfile-prerequisite-build-codexb5.log`,
`build/memoryreadfile-header-accept-codexb5.log`,
`build/memoryreadfile-prerequisite-link-codexb5.log` and
`build/memoryreadfile-prerequisite-symbols-codexb5.txt`.

## Supported composition remains blocked

The initial `tu_skeleton.py --merge .../MemoryReadFile.cpp --dry-run` stopped
on duplicate StringBase definitions from the two header environments. After
the retained prerequisite it compiles and reaches the link guard. Neither
dry run writes source or ledger moves.

The seed declares an abstract MemoryReadFile view with three overrides; the
factory needs the larger concrete view. Composition selects that concrete
view, changing the constructor-emitted vtable's references. The guard refuses
the merge because the previously linking factory would acquire unresolved
`?convertToRAMFile@MemoryReadFile@@UAEPAVFile@@XZ`,
`?nextLine@MemoryReadFile@@UAEXPADH@Z`, and
`?open@MemoryReadFile@@UAE_NPBDH@Z` (the guard reports the first three).
No nonmatching composed source is retained. Current separate objects still
link in the ordinary preview.

Next: reconcile the target vtable slots with their existing rowed providers
and identities before making the constructor use the concrete view. Do not
add aliases or stubs to satisfy the missing method spellings. File.cpp and
VslotSmallBodiesAR.cpp remain mixed satellites, not approved whole-file
donors. Repeat the supported merge only after that prerequisite changes.
Local diagnostic: `build/memoryreadfile-aligned-dryrun-codexb5.log`.
