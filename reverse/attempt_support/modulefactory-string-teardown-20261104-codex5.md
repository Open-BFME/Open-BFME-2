# ModuleFactory string teardown identity repair

Inspected base: `ba78dd08de0ab3c2b9ffaa760e3c225a18c35660`. Seat: `yasinschroeder-codex5`.

The picker assigned the single identity key for
`CreateCrateDieModuleData::buildFieldParse` (0x00253991), which previously bound
`DieMuxData::getFieldParse` at 0x004CE52E to a wrong kept body. The provider's
retail table had already been recovered in `07ce664309`; this was registered
debt, not uncovered retail code. LINK-068 retains that provider's history.

The initial fresh-object retirement refused both stale providers and a newly
visible finding: `GrantScienceUpgradeModuleData::~GrantScienceUpgradeModuleData`
(0x0025637D) reached `??1AsciiString@@QAE@XZ` at 0x00036410, classified divergent.
The TU's `/DBFME_ASCII_DTOR_DECL` came from `8c19079209`, which suppressed its
wrong range-destruction copy. Retail's 53-byte destructor calls the narrow
`StringBase<char>::releaseBuffer` worker at 0x00036410 directly (call instruction
at 0x00256395); the actual rowed `AsciiString` destructor is a five-byte tail
jump at 0x0048BA39. These are target facts; the local-object emission scaffold
and donor GrantScienceUpgrade class are not evidence of recovered BFME2 source.

Remove the TU-wide declaration-only destructor switch and declare only the
existing `_STL::_Destroy<AsciiString *>` range specialization out of line.
This retains the existing range provider at 0x0002CB64 in INI.cpp and permits
the direct member to inline releaseBuffer. No shared header, pin, alias, row
identity, path or extent changes. The TU's emitted AsciiString destructor is
still the canonical five-byte jump to releaseBuffer.

## Verification

- Before and after: `./build.sh Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp`:
  54/54 functions plus its one data row pass; string, float and import checks pass.
- `find_declared_unmatched.py` before and after: all defined functions are already
  matched; unchanged inventory of ten existing unclaimed-definition markers.
- Fetched published index: 2026-11-04 16:16, `2f0cb97f52`; 17,123 objects imported
  into the object store. Enumerated stale providers through the retirement tool's
  own identity inputs, then refreshed all 35 distinct source files with `./build.sh`:
  1,127/1,127 functions and 16 data rows pass; 23 stale TUs, seven restored from
  the store, with twelve already current. Scratch logs:
  `build/codex5-modulefactory/provider_build.log`, `stale_providers.json`.
- `link_check.py ModuleFactory.cpp`: LINKS, 2,404 -> 2,404 bytes, against that
  index; no new linked-byte or census claim. The existing unreferenced AngleFXInfo
  allocator diagnostic remains nonblocking.
- `repair_queue.py retire identity Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp`:
  PASS, one key retired by the owning tool, zero remaining findings. No key was
  deleted by hand; the first refusal was resolved before the passing verdict.
- Full outgoing consumer regression audit belongs to the publication hook. This
  evidence establishes the stated source, provider refresh and ordinary-preview
  scope; carry any inconclusive consumer scope into the next scheduled census.

Current ModuleFactory object inspection (COFF relocation offsets are decimal):

```text
??1GrantScienceUpgradeModuleData@@UAE@XZ
  body size=53, bytes=b800000000e80000000051568bf18975f08365fc008d4e60e800000000834dfcff8bcee8000000008b4df45e64890d00000000c9c3
  relocation 1 type=6: __ehhandler$??1GrantScienceUpgradeModuleData@@UAE@XZ
  relocation 6 type=20: __EH_prolog
  relocation 25 type=20: ?releaseBuffer@?$StringBase@D@@AAEXXZ
  relocation 36 type=20: ??1UpgradeModuleData@@UAE@XZ
  relocation 47 type=6: __except_list
??1AsciiString@@QAE@XZ
  body size=5, bytes=e900000000
  relocation 1 type=20: ?releaseBuffer@?$StringBase@D@@AAEXXZ
??$_Destroy@PAVAsciiString@@@_STL@@YAXPAVAsciiString@@0@Z
  external reference; no definition in ModuleFactory object
```

The repaired functions are compiler-generated destructors and an unchanged
inherited parser; no unclear local or parameter binding was renamed.
