# Sphere emission position and canonical Coord3D dependency

This is banked evidence, not recovered coverage. No constructor/header trial or
Sphere ledger row is landed by this package. The current POD-header candidate is
138 bytes against the complete 129-byte target; its first 85 bytes are exact.
The bank conservatively scores that proven prefix as 0.66.

## Donor facts

The clean donor is Open-BFME-1 revision
`34f59164f6d1efd413c5fd37f4894ec834c3c0fe`,
`game/GameEngine/Source/GameClient/System/FXParticleSystem/SphereEmissionVolumeModuleGetPosition.cpp`.
The reader sweep compiled it with BFME2 /O1 /arch:SSE /G7 and placed its whole
129-byte callback at `0x0055D48C`. The original donor body instead lives at
BFME1 `0x005FAA40`. The donor supplies the named module, inheritance model,
field names and modeled size 0x28; these are not inferred from bytes alone.

## Independent target facts

`reverse/ghidra_functions.csv` bounds `0x0055D48C` to 129 bytes. Retail compares
the receiver byte at +0x20, reads the float at +0x24, and ends RET 0x14 with a
hidden twelve-byte output and four scalar arguments. Its complete string is
`C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameClient\System\FXParticleSystem\fxpsemitterspherevolumemodule.cpp`,
line 86. The resolved calls are the existing 72-byte random provider at
`0x00234111` and 198-byte unit-vector provider at `0x003AFA64`.

The callback is slot 7 (zero based) of primary table VA `0x00C1C7B8`.
Constructor `0x003AC087` installs that table on the complete receiver at its
instruction `0x003AC0B7`, and installs secondary tables at receiver +0x14,
+0x18 and +0x1C. Two additional tables also contain this shared callback.
The target source literal and observed behavior corroborate the donor identity;
the target does not independently recover every donor base-class name.

## Measured canonical-header trial

A flat twelve-byte canonical struct with an empty default constructor and a
visible memberwise user copy constructor produces both the exact Sphere129
and exact native copy25 at `0x004216D3`. No inheritance change or destructor
is required. The ordinary POD header produces Sphere138 because MSVC7.1
stores the scaled local then block-copies it to hidden return storage.
`docs/matching.md` documents this named-return-value copy-constructor rule.

The normal dependent gate checked 241 sources / 1283 rows after the constructor
compile repairs. Four rows failed; their names are in `header-gate-failures.txt`.
The two owned sites were subsequently repaired and passed both full row checks:

- Rva00474B51: default-construct position, then assign from the object position.
- HordeContainXfer: default-construct its coordinate member, then assign it in
  the surrounding record copy constructor.

The remaining two are Pathfinder::CheckForTarget and BuildActualPath; both
copy-initialize a Coord3D temporary. Their source was actively reserved by
external owner `codex-ec82-root`, so it was not edited. All trial edits were
restored and their claims released. `dependent-repairs.patch` preserves only
the measured, owned repairs; `canonical-contract.patch` preserves the proposed
header/contract. Apply neither without current claims and complete gates.

Three GameMessage union views need genuine trivial XYZ wire storage, rather
than a class with a user copy constructor. Four files with aggregate-initialized locals
need equivalent explicit field initialization. Static/serialized lighting
triplets need their genuine trivial storage. These bounded compatibility
repairs passed eleven rows across seven sources, and NetPacket independently
passed all 96 rows; their logs are retained here. They are currently reverted.

The existing copy25 owner in coord3d.cpp still uses the legacy class/V key.
Do not add a second real-name pin for the struct/U key. Any out-of-line copy
binding must reconcile the actual provider and its callers honestly.

## Rejected alternatives and next step

Genuine memcpy copy constructors, a force-inline variant, /Oi, and an explicit
integer-field copy were tested. They produced Sphere138/142/146/147 or a
copy18/24 rather than the required pair Sphere129 + copy25. Aggregate returns,
return helpers and derived temporaries did not close the original POD138.
No aliases, emission anchors, private canonical type, class exception, or
verification override was introduced.

Resume when the Pathfinder reservation permits the two real default-and-assign
consumer repairs, or new evidence supplies an exact canonical alternative.
Re-run every dependent body, the native providers, placement mining and current
linkage checks before counting or publishing the 129 bytes.

## Completed independent provider adoption

The unit-vector provider and its sole existing direct consumer in
FXParticleSystemModuleParsers now include the unchanged canonical Coord3D
header. The provider's actual ledger owner is renamed from class/V to struct/U
at the same 0x003AFA64/198 extent; the consumer uses that real owner. There is
no new alias or pin and no extra body at the address. All 23 rows in both units
are exact, including strings and float references. A normal link_check --refresh
recompiled 348 stale objects: both units LINKS, 710 -> 710 linked bytes. This
is canonical type repair, with zero newly recovered C++ bytes.
