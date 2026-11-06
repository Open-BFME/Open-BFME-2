# Coord3D class-key resolver prerequisite, 2026-11-07

Inspected `33208d26a2`. This is a tooling correction and blocked linking
handoff. No canonical header, contract, game source, function identity, pin,
data identity or debt row is changed. No real-link or runtime gain is claimed.

## Target evidence

Retail exports use the class key for Coord3D (15 V-form exports, no U-form
votes). Snapshot's Matrix4D axis-angle names need V-form Coord3D, while the
canonical POD header still defines a struct. Private copies of that header
under ignored `build/` prove both variants retain all 22 Snapshot rows. Their
external bytes, relocations, storage/COMDAT properties, providers, undefined
names, weak/alternate bindings and include routes agree after the explicit
literal-key normalization used by these Snapshot rows. This is local compiler
evidence, not proof that all Coord3D consumers can migrate.

The same compiler independently emits these authentic changes:

* `??8Coord3D@@QAE_NABU0@@Z` to `??8Coord3D@@QAE_NABV0@@Z`.
* `?CoordKeyProbe@@YAPAUCoord3D@@PAU1@@Z` to
  `?CoordKeyProbe@@YAPAVCoord3D@@PAV1@@Z`.

`compiler-proof.json` records the original proof and source hash;
`compiler_probe.py` reproduces it through `tu_skeleton.Verifier` in a private
cache. Run from the repository root with the normal compiler environment.
It never invokes `build.compile_source` or changes tracked source/ledgers.
Its final refusal inventory naturally changes after the resolver fix.

## Resolver and independent review

The old header lane refused any potentially relevant `U<digit>@`, and its
literal substitution could not produce complete class-key names. The new
resolver combines the existing full supported grammar guard with WB's exact
name-table mechanics. It retains template identities with their source spans,
resolves qualified names, validates argument references against their separate
table, edits only proven key positions, then reparses and compares all resolved
type identities and table shapes. It refuses unsupported grammar and mixed
keys. No external demangler is a production dependency.

`prototype-results.json` lists all 84 previously refused old/new spellings.
Independent Windows DbgHelp full-signature decoding agrees on all 84: exactly
global `struct Coord3D` becomes `class Coord3D`; every other type is preserved.
`dbghelp-results.json` and `dbghelp_oracle.py` preserve this separate oracle.
`argument-scope-dbghelp.json` records sixteen further argument-table probes,
including invalid references and nested callbacks within return types. A
bounded native reviewer found the initial argument-reference and mixed-union
false accepts; both are now permanent refusal fixtures.

The production resolver reproduces all 84 mappings. A streaming inventory of
only names containing `Coord3D@` finds 1,111 function-name rewrites, 85 pin-name
rewrites, three data-name rewrites and zero converged data-name rewrites.
There are no resulting names already in the function ledger and no generated
source owners among these proposals. These are naming proposals, not approved
migrations. The six refused forms are four local-static destructors in
`Rva009F66F0.cpp`/`GameLogicDispatchDoSetRallyPoint.cpp` and two adjustors in
`DozerAIUpdateCtor.cpp`/`WorkerAIUpdateCtor.cpp`. `production_probe.py` reproduces
the comparison and narrow inventory into ignored `build/` reports.

## Remaining migration boundary

The lane's current writer owns function name columns, not a complete key
migration transaction. The new preflight refuses old names embedded in notes
(including out-of-cohort funclet parents), unplanned row families, pins, data,
body owners and active debt registers; existing target names and target
tombstones also refuse. It runs before candidate source writes. The writer
adds a defensive check and preserves every record's exact terminator and
untouched fields. No metadata is silently respelled or retired.

Before the actual header flip, resolve canonical-header dependents and seed
headers, preserve existing private-view lifetime semantics, select already-
adopted users, and migrate complete provider/caller and metadata families.
The existing header-dependency scan reports 3,341 dependent ledger sources;
this is a broad recompilation scope, not the count of rows requiring renaming.
The existing adoption lane selects private views and cannot itself apply this
whole canonical-header migration. Keep LINK-018 and the Region3D obstacle open.

## Validation

322 tests pass, with one existing open-audit-escape fixture skipped by the
suite, across `test_header_key_backref.py`, `test_header_adopt_lane.py`,
`test_header_run_all.py` and `test_gate_exploits.py`. Cases include exact
rewrites/inverses, unrelated types, qualified scopes, template/argument tables,
malformed names, mixed keys, metadata-only parents outside the cohort, pins,
data, body owners, registers, collisions, tombstones, coordinated caller
failure, interrupted gates and byte-preserving ledger writes. All enforced
exploit tests remain passing. Fixture Git processes use `core.autocrlf=true`
on Windows and their own hooks, rather than inheriting this live checkout's
absolute native-hook launcher.

Command: `python3 -m pytest -q tools/tests/test_header_key_backref.py
tools/tests/test_header_adopt_lane.py tools/tests/test_gate_exploits.py
tools/tests/test_header_run_all.py`.
